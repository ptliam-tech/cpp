#include<stdio.h>

#pragma pack(1)
typedef struct {
    int a;
    float b;
    char c;
} test_t;
#pragma pack()

int main() {
    test_t test1;
    printf("Memory: %d", sizeof(test1));

    return 0;
}