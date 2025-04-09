#include <stdio.h>
typedef struct _mapelement{
    int col; // 0: 흰색, 1: 빨간색, 2: 파란색
    int mals[4]; // 최대 3개까지 쌓일 수 있음
    int malno;
} mapelement;
typedef struct _mal{
    int dir;
    int y;
    int x;
} mal;
mal malarray[11]; // 1~K
mapelement map[13][13];
int dy[5] = {0, 0, 0, -1, 1};
int dx[5] = {0, 1, -1, 0, 0};
int N, K;
int border(int y, int x)
{
    if(y == 0 || y == N+1 || x == 0 || x == N+1) return 1;
    else return 0;
}
int main(void)
{
    int t = 0;
    scanf("%d %d", &N, &K);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            scanf("%d", &map[i][j].col);
    for(int i=1;i<=K;i++)
    {
        int a, b;
        scanf("%d %d %d", &a, &b, &malarray[i].dir);
        malarray[i].y = a;
        malarray[i].x = b;
        map[a][b].mals[++map[a][b].malno] = i;
    }
    while(1)
    {
        if(t == 1000)
        {
            printf("-1");
            return 0;
        }
        t++;
        for(int i=1;i<=K;i++)
        {
            int y = malarray[i].y;
            int x = malarray[i].x;
            int dir = malarray[i].dir;
            int pos;
            for(int j=1;j<=map[y][x].malno;j++)
            {
                if(map[y][x].mals[j] == i)
                {
                    pos = j;
                    break;
                }
            }
            int new_y = y+dy[dir];
            int new_x = x+dx[dir];
            if(border(new_y, new_x) || map[new_y][new_x].col == 2) // 파란색
            {
                int reflected_y = y-dy[dir];
                int reflected_x = x-dx[dir];
                malarray[i].dir = (dir <= 2) ? (3-dir) : (7-dir);
                if(!border(reflected_y, reflected_x) && map[reflected_y][reflected_x].col != 2)
                {
                    if(map[reflected_y][reflected_x].col == 0) // 흰색
                    {
                        if(map[reflected_y][reflected_x].malno + map[y][x].malno - pos + 1>=4) goto um;
                        for(int j=pos;j<=map[y][x].malno;j++)
                        {
                            malarray[map[y][x].mals[j]].y = reflected_y;
                            malarray[map[y][x].mals[j]].x = reflected_x;
                            map[reflected_y][reflected_x].mals[j+1-pos+map[reflected_y][reflected_x].malno] = map[y][x].mals[j];
                        }
                        map[reflected_y][reflected_x].malno += map[y][x].malno-pos+1;
                        map[y][x].malno = pos-1;
                    }
                    if(map[reflected_y][reflected_x].col == 1) // 빨간색
                    {
                        if(map[reflected_y][reflected_x].malno + map[y][x].malno - pos + 1>=4) goto um;
                        for(int j=map[y][x].malno;j>=pos;j--)
                        {
                            malarray[map[y][x].mals[j]].y = reflected_y;
                            malarray[map[y][x].mals[j]].x = reflected_x;
                            map[reflected_y][reflected_x].mals[1+map[y][x].malno-j+map[reflected_y][reflected_x].malno] = map[y][x].mals[j];
                        }
                        map[reflected_y][reflected_x].malno += map[y][x].malno-pos+1;
                        map[y][x].malno = pos-1;
                    }

                }
            }
            else if(map[new_y][new_x].col == 0) // 흰색
            {
                if(map[new_y][new_x].malno + map[y][x].malno - pos + 1>=4) goto um;
                for(int j=pos;j<=map[y][x].malno;j++)
                {
                    malarray[map[y][x].mals[j]].y = new_y;
                    malarray[map[y][x].mals[j]].x = new_x;
                    map[new_y][new_x].mals[j+1-pos+map[new_y][new_x].malno] = map[y][x].mals[j];
                }
                map[new_y][new_x].malno += map[y][x].malno-pos+1;
                map[y][x].malno = pos-1;
            }
            else // 빨간색
            {
                if(map[new_y][new_x].malno + map[y][x].malno - pos + 1>=4) goto um;
                for(int j=map[y][x].malno;j>=pos;j--)
                {
                    malarray[map[y][x].mals[j]].y = new_y;
                    malarray[map[y][x].mals[j]].x = new_x;
                    map[new_y][new_x].mals[1+map[y][x].malno-j+map[new_y][new_x].malno] = map[y][x].mals[j];
                }
                map[new_y][new_x].malno += map[y][x].malno-pos+1;
                map[y][x].malno = pos-1;
            }
        }
        
    }
    um:
    printf("%d", t);
    return 0;
}