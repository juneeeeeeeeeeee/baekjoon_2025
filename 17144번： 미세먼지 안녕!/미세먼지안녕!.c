#include <stdio.h>
int map[51][51];
int gongcheong_higher;
int gongcheong_lower;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int R, C;
int border(int y, int x, int dir)
{
    if(y+dy[dir] == 0 || y+dy[dir] == R+1 || x+dx[dir] == 0 || x+dx[dir] == C+1 || (x+dx[dir] == 1 && (y+dy[dir] == gongcheong_higher || y+dy[dir] == gongcheong_lower)))
        return 1;
    else return 0;
}
void diffusion()
{
    int newmap[51][51];
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            newmap[i][j] = map[i][j];
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            if(map[i][j] && map[i][j] != -1)
            {
                int cnt = 0;
                for(int dir=0;dir<=3;dir++)
                {
                    if(!border(i, j, dir))
                    {
                        newmap[i+dy[dir]][j+dx[dir]] += map[i][j]/5;
                        cnt++;
                    }
                }
                newmap[i][j] -= (map[i][j]/5) * cnt;
            }
        }
    }
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            map[i][j] = newmap[i][j];
}
void gongcheong()
{
    // 위쪽 공기청정기
    for(int i = gongcheong_higher - 2;i>=1;i--)
        map[i+1][1] = map[i][1];
    for(int i=1;i<=C-1;i++)
        map[1][i] = map[1][i+1];
    for(int i=1;i<=gongcheong_higher-1;i++)
        map[i][C] = map[i+1][C];
    
    // 아래쪽 공기청정기
    for(int i = gongcheong_lower + 2; i<=R;i++)
        map[i-1][1] = map[i][1];
    for(int i=1;i<=C-1;i++)
        map[R][i] = map[R][i+1];
    for(int i=R;i>=gongcheong_lower + 1;i--)
        map[i][C] = map[i-1][C];
    
    // 공통
    for(int i=C;i>=3;i--)
    {
        map[gongcheong_higher][i] = map[gongcheong_higher][i-1];
        map[gongcheong_lower][i] = map[gongcheong_lower][i-1];
    }
    map[gongcheong_higher][2] = 0;
    map[gongcheong_lower][2] = 0;
}
int main(void)
{
    int T;
    scanf("%d %d %d", &R, &C, &T);
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            scanf("%d", &map[i][j]);
            if(map[i][j] == -1 && !gongcheong_higher)
            {
                gongcheong_higher = i;
                gongcheong_lower = i+1;
            }
        }
    }
            
    while(T--)
    {
        diffusion();
        gongcheong();
    }
    int sum = 0;
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            sum += map[i][j];
    printf("%d", sum+2);
    return 0;
}