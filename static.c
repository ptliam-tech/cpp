#include<stdio.h>

int c;

void test() {
    static int c = 0;
    c++;
    printf("c in func = %d\n", c);

}

int main() {
    c = 10;
    test();
    test();
    printf("c global = %d", c);

    return 0;
}