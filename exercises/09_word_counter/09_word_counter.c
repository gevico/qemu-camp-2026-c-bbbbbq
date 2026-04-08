#include <stdio.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\n' && !in_word) {
            in_word = 1;
            wordCount++;
        } else if (str[i] == ' ' || str[i] == '\n') {
            in_word = 0;
        }
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}
