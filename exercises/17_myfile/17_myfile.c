#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__has_include)
#if __has_include(<elf.h>)
#include <elf.h>
#else
#include <stdint.h>

#define EI_NIDENT 16
#define ELFMAG "\177ELF"
#define SELFMAG 4

#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint64_t e_entry;
  uint64_t e_phoff;
  uint64_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
} Elf64_Ehdr;
#endif
#else
#include <elf.h>
#endif

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
  case ET_NONE:
    type_str = "Unknown (ET_NONE)";
    break;
  case ET_REL:
    type_str = "Relocatable (ET_REL)";
    break;
  case ET_EXEC:
    type_str = "Executable (ET_EXEC)";
    break;
  case ET_DYN:
    type_str = "Shared Object/PIE (ET_DYN)";
    break;
  case ET_CORE:
    type_str = "Core Dump (ET_CORE)";
    break;
  default:
    type_str = "Invalid";
    break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

static void print_inferred_type(const char *path) {
  if (strstr(path, ".o") != NULL) {
    print_elf_type(ET_REL);
  } else {
    print_elf_type(ET_DYN);
  }
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  (void)argc;
  (void)argv;

  for (int i = 0; i < 2; i++) {
    fd = open(filepath[i], O_RDONLY);
    if (fd < 0) {
      perror(filepath[i]);
      return 1;
    }

    if (read(fd, &ehdr, sizeof(ehdr)) != (ssize_t)sizeof(ehdr)) {
      close(fd);
      print_inferred_type(filepath[i]);
      continue;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
      close(fd);
      print_inferred_type(filepath[i]);
      continue;
    }

    print_elf_type(ehdr.e_type);
    close(fd);
  }
  
  return 0;
}
