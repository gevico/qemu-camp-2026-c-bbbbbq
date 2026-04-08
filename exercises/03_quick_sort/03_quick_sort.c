#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];

void quick_sort(int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int pivot = students[left + (right - left) / 2].score;

    while (i <= j) {
        while (students[i].score > pivot) {
            i++;
        }

        while (students[j].score < pivot) {
            j--;
        }

        if (i <= j) {
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quick_sort(left, j);
    }
    if (i < right) {
        quick_sort(i, right);
    }
}

int main(void) {
    FILE *file = fopen("03_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 03_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    quick_sort(0, n - 1);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}
