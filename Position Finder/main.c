#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start, end;
    start = clock();
    int i, n, x, y, rem, temp;
    printf("Enter no of steps : ");
    scanf("%d", &n);
    rem = n % 4;
    temp = (n + 4 - rem) / 2;
    if (rem == 0) {temp = n / 2;}
    x = (rem == 1) ? temp - 2 : temp;
    y = (rem == 1 || rem == 2) ? (temp - 1) : temp;
    if (rem == 0 || rem == 1) {x *= -1;}
    if (rem == 0 || rem == 3) {y *= -1;}
    printf("Your position is (%d,%d)\n", x, y);
    end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("The program took %f seconds to execute\n", time_taken);
    return 0;
}