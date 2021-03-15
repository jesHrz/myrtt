#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *c;
    int n;

    scanf("%d", &n);
    c = (char *)malloc(n + 1);
    scanf("%s", c);
    printf("you input: %s\n", c);
    printf("Hello, world!\n");
    return 0;
}