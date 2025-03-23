#include <stdio.h>
#include <stdlib.h>
int N, M, H;
int min_line_num = 4;
int** map;
int test()
{
    for(int startpos = 1;startpos <= N-1; startpos++) // N-1개 맞으면 N번째는 자동으로 맞음
    {
        int pos = startpos;
        for(int vert = 1;vert<=H;vert++)
        {
            if(map[vert][pos]) pos++;
            else if(map[vert][pos-1]) pos--;
        }
        if(pos!=startpos) return 0;
    }
    return 1;
}
void dfs(int line_num)
{
    if(line_num == min_line_num) return;
    if(test())
    {
        min_line_num = line_num;
        return;
    }
    for(int j=1;j<=N-1;j++)
    {
        for(int i=1;i<=H;i++)
        {
            if(map[i][j] || map[i][j-1] || map[i][j+1]) continue;
            map[i][j] = 1;
            dfs(line_num+1);
            map[i][j] = 0;
            while(i<=H && !map[i][j-1] && !map[i][j+1]) i++;
        }
    }
}
int main(void)
{
    scanf("%d %d %d", &N, &M, &H);
    map = (int**)calloc(H+1, sizeof(int*));
    for(int i=1;i<=H;i++)
        map[i] = (int*)calloc(N+1, sizeof(int));
    for(int i=1;i<=M;i++)
    {
        int temp_a, temp_b;
        scanf("%d %d", &temp_a, &temp_b);
        map[temp_a][temp_b] = 1;
    }
    dfs(0);
    if(min_line_num == 4)
        printf("-1");
    else
        printf("%d", min_line_num);
    for(int i=0;i<=H;i++)
        free(map[i]);
    free(map);
    return 0;
}