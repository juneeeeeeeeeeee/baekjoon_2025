#include <stdio.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    for(int i=1;i<=1000000;i++)
    {
        if(n<=1+((i*(i-1))*3))
        {
            printf("%d", i);
            return 0;
        }
    }
}