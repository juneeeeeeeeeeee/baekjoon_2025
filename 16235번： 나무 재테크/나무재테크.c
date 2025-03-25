#include <stdio.h>
typedef struct _mapelement{
    unsigned char treeage[1000];
    int yb;
    int trees;
} mapelement;
mapelement map[11][11];
int N;
unsigned char A[11][11];
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int border(int y, int x, int dir)
{
    if(y+dy[dir] == 0 || y + dy[dir] == N+1 || x + dx[dir] == 0 || x + dx[dir] == N+1)
        return 1;
    else return 0;
}
void oneyear(void)
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(map[i][j].trees)
            {   
                int treecount = 0;
                // 나무 밥주기
                for(int k=map[i][j].trees-1;k>=0;k--)
                {
                    if(map[i][j].treeage[k] > map[i][j].yb)
                        break;
                    map[i][j].yb -= map[i][j].treeage[k];
                    map[i][j].treeage[k]++;
                    treecount++;
                }
                // 죽은 나무 양분으로 변함
                for(int k=map[i][j].trees-treecount-1;k>=0;k--)
                    map[i][j].yb += map[i][j].treeage[k] >> 1;
                // 산 나무 땡기기
                for(int k=0;k<=treecount-1;k++)
                {
                    map[i][j].treeage[k] = map[i][j].treeage[k+map[i][j].trees-treecount];
                }
                map[i][j].trees = treecount;
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            // 나무 번식
            for(int k=0;k<map[i][j].trees;k++)
                for(int dir=0;dir<=7;dir++)
                    if(!(map[i][j].treeage[k]%5) && !border(i, j, dir))
                        map[i+dy[dir]][j+dx[dir]].treeage[map[i+dy[dir]][j+dx[dir]].trees++] = 1;
            // 양분주기
            map[i][j].yb += A[i][j];
        }
    }
}
int main(void)
{
    int M, K;
    int totaltrees = 0;
    scanf("%d %d %d", &N, &M, &K);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            scanf("%d", &A[i][j]);
            map[i][j].yb = 5;
        }
    }
    while(M--)
    {
        int y, x, age;
        scanf("%d %d %d", &y, &x, &age);
        map[y][x].treeage[0] = age;
        map[y][x].trees = 1;
    }
    while(K--) oneyear();
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            totaltrees += map[i][j].trees;
    printf("%d", totaltrees);
    return 0;
}   