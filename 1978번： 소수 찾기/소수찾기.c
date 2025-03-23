#include <stdio.h>
int main(void)
{
    int N;
    int sum = 0;
    scanf("%d", &N);
    for(int i=0;i<=N-1;i++)
    {
        int num;
        int check = 1;
        scanf("%d", &num);
        if(num == 1)
            continue;
        for(int j=2;j<num;j++)
        {
            if(num % j == 0)
            {
                check = 0;
                break;
            }
        }
        sum += check;
    }
    printf("%d", sum);
    return 0;
}