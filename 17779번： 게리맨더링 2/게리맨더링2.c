#include <stdio.h>
#define MAX 2147483647
int N;
int A[21][21];
int summation[6];
int main(void)
{
    int sum = 0;
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            scanf("%d", &A[i][j]);
            sum += A[i][j];
        }
    int mindiff = MAX;
    for(int y=1;y<=N-2;y++)
    {
        for(int x=2;x<=N-1;x++)
        {
            for(int d1=1;d1<=N-2;d1++)
            {
                for(int d2=1;d2<=N-2;d2++)
                {
                    if(y+d1+d2>N || x-d1<1 || x+d2>N)
                        continue;
                    for(int i=1;i<=5;i++)
                        summation[i] = 0;
                    
                    for(int i=1;i<=y-1;i++)
                        for(int j=1;j<=x;j++)
                            summation[1] += A[i][j];
                    for(int i=y;i<=y+d1-1;i++)
                        for(int j=1;j<=y+x-i-1;j++)
                            summation[1] += A[i][j];
                    int min = summation[1];
                    int max = summation[1];

                    for(int i=1;i<=y;i++)
                        for(int j=x+1;j<=N;j++)
                            summation[2] += A[i][j];
                    for(int i=y+1;i<=y+d2;i++)
                        for(int j=i-y+x+1;j<=N;j++)
                            summation[2] += A[i][j];
                    if(min > summation[2]) min = summation[2];
                    else if(max < summation[2]) max = summation[2];
                    
                    for(int i=y+d1;i<=y+d1+d2-1;i++)
                        for(int j=1;j<=i-y+x-2*d1-1;j++)
                            summation[3] += A[i][j];
                    for(int i=y+d1+d2;i<=N;i++)
                        for(int j=1;j<=x+d2-d1-1;j++)
                            summation[3] += A[i][j];
                    if(min > summation[3]) min = summation[3];
                    else if(max < summation[3]) max = summation[3];
                    
                    for(int i=y+d2+1;i<=y+d1+d2;i++)
                        for(int j=y+x+2*d2-i+1;j<=N;j++)
                            summation[4] += A[i][j];
                    for(int i=y+d1+d2+1;i<=N;i++)
                        for(int j=x+d2-d1;j<=N;j++)
                            summation[4] += A[i][j];
                    if(min > summation[4]) min = summation[4];
                    else if(max < summation[4]) max = summation[4];

                    summation[5] = sum - summation[1] - summation[2] - summation[3] - summation[4];
                    if(min > summation[5]) min = summation[5];
                    else if(max < summation[5]) max = summation[5];

                    if(mindiff > max-min) mindiff = max-min;
                }
            }
        }
    }

    printf("%d", mindiff);
    return 0;
}