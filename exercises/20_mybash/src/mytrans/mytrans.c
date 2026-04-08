// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void to_lowercase(char *str);

void trim(char *str) {
  if (str == NULL) {
    return;
  }

  char *start = str;
  while (*start != '\0' && isspace((unsigned char)*start)) {
    start++;
  }

  if (start != str) {
    memmove(str, start, strlen(start) + 1);
  }

  size_t len = strlen(str);
  while (len > 0 && isspace((unsigned char)str[len - 1])) {
    str[--len] = '\0';
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    trim(line);
    if (line[0] == '\0') {
      continue;
    }

    if (line[0] == '#') {
      if (in_entry && current_word[0] != '\0' && current_translation[0] != '\0') {
        if (hash_table_insert(table, current_word, current_translation)) {
          (*dict_count)++;
        }
      }

      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      trim(current_word);
      to_lowercase(current_word);
      current_translation[0] = '\0';
      in_entry = 1;
      continue;
    }

    if (strncmp(line, "Trans:", 6) == 0 && in_entry) {
      strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
      current_translation[sizeof(current_translation) - 1] = '\0';
      trim(current_translation);
    }
  }

  if (in_entry && current_word[0] != '\0' && current_translation[0] != '\0') {
    if (hash_table_insert(table, current_word, current_translation)) {
      (*dict_count)++;
    }
  }

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

static const char *resolve_dictionary_path(void) {
  static const char *candidates[] = {
    "../exercises/20_mybash/src/mytrans/dict.txt",
    "src/mytrans/dict.txt",
    "./src/mytrans/dict.txt",
    "exercises/20_mybash/src/mytrans/dict.txt",
  };

  size_t count = sizeof(candidates) / sizeof(candidates[0]);
  for (size_t i = 0; i < count; i++) {
    if (access(candidates[i], R_OK) == 0) {
      return candidates[i];
    }
  }

  return NULL;
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  const char *dict_path = resolve_dictionary_path();
  if (dict_path == NULL || load_dictionary(dict_path, table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%" PRIu64 "词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件: %s\n", filename);
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " \t\r");
    while (word != NULL) {
      to_lowercase(word);
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " \t\r");
    }
  }

  fclose(file);
  free_hash_table(table);
  return 0;
}
