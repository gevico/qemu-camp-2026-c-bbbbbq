#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) {
    if (b == 0) {
        printf("错误：除数不能为零\n");
        return 0;
    }
    return a / b;
}

int main() {
    int a, b;
    char op;

    int (*operations[])(int, int) = {add, subtract, multiply, divide};

    char operators[] = "+-*/";

    printf("输入两个整数和一个运算符 (+, -, *, /): ");
    if (scanf("%d %d %c", &a, &b, &op) != 3) {
        printf("输入格式错误\n");
        return 1;
    }

    // 查找对应的运算符索引
    int index = -1;
    for (int i = 0; i < 4; i++) {
        if (op == operators[i]) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("无效的运算符\n");
        return 1;
    }

    int result = operations[index](a, b);
    printf("%d %c %d = %d\n", a, op, b, result);

    return 0;
}
