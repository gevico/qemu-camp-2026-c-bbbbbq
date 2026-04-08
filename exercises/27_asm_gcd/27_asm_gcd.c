#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(int argc, char* argv[]) {
    printf("%d\n", gcd_asm(12, 8));
    printf("%d\n", gcd_asm(7, 5));
    return 0;
}
