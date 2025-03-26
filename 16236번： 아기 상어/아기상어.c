#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 400
typedef struct _pos{
    int y;
    int x;
} pos;
typedef struct _sharkelement{
    int size;
    int xp;
    pos p;
} sharkelement;
typedef struct _mapelement{
    int fishsize; // 0이면 물고기 X, 9이면 상어
    int dist;
} mapelement;
typedef struct _queue{
    pos arr[1000];
    int start;
    int len;
} queue;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int N;
mapelement map[21][21];
sharkelement shark;
int check[21][21];
void queue_push(queue* q, pos p)
{
    q->arr[q->start + q->len++] = p;
}
pos queue_pop(queue* q)
{
    q->len--;
    return q->arr[q->start++];
}
int bound(pos p, int dir)
{
    if(p.y+dy[dir] == 0 || p.y+dy[dir] == N+1 || p.x+dx[dir] == 0 || p.x+dx[dir] == N+1)
        return 1;
    else return 0;
}
int cango(pos p, int dir)
{
    if(map[p.y+dy[dir]][p.x+dx[dir]].fishsize <= shark.size)
        return 1;
    else return 0;
}
void BFS(void)
{
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            check[i][j] = 0;
    queue* q = calloc(1, sizeof(queue));
    q->len = 0;
    q->start = 0;
    queue_push(q, shark.p);
    check[shark.p.y][shark.p.x] = 1;
    map[shark.p.y][shark.p.x].dist = 0;
    while(q->len)
    {
        pos pop_p = queue_pop(q);
        for(int dir=0;dir<=3;dir++)
        {
            if(!bound(pop_p, dir) && cango(pop_p, dir) && !check[pop_p.y+dy[dir]][pop_p.x+dx[dir]])
            {
                pos new_p = {pop_p.y+dy[dir], pop_p.x+dx[dir]};
                map[new_p.y][new_p.x].dist = map[pop_p.y][pop_p.x].dist + 1;
                queue_push(q, new_p);
                check[new_p.y][new_p.x] = 1;
            }
        }
    }
    free(q);
}
int fishing(void)
{
    int time = 0;
    while(1)
    {
        BFS();
        int mindist = INF;
        pos minp = {-1, -1};
        for(int i=N;i>=1;i--)
        {
            for(int j=N;j>=1;j--)
            {
                if(map[i][j].fishsize && map[i][j].fishsize != 9 && check[i][j] && map[i][j].fishsize < shark.size && map[i][j].dist <= mindist)
                {
                    mindist = map[i][j].dist;
                    minp.y = i;
                    minp.x = j;
                }
            }
        }
        if(minp.y == -1) break;
        time += mindist;
        if(++shark.xp == shark.size)
        {
            shark.size++;
            shark.xp = 0;
        }
        map[minp.y][minp.x].fishsize = 9;
        map[shark.p.y][shark.p.x].fishsize = 0;
        shark.p = minp;
    }
    return time;
}
int main(void)
{
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            scanf("%d", &map[i][j].fishsize);
            if(map[i][j].fishsize == 9)
            {
                shark.size = 2;
                shark.p.y = i;
                shark.p.x = j;
                shark.xp = 0;
            }
        }
    }
    printf("%d", fishing());
    return 0;
}