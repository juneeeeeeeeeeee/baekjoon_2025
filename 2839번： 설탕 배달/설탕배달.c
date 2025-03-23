#include <stdio.h>
int main(void)
{
    int N;
    scanf("%d", &N);
    int ans = 0;
    while(N>0)
    {
        if(N%5 == 0)
        {
            ans += N/5;
            break;
        }
        ans += 1;
        N -= 3;
    }
    if(N == -1 || N == -2)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}