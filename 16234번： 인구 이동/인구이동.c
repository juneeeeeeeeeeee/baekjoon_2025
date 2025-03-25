#include <stdio.h>
#include <string.h>
typedef struct _pos{
    int y;
    int x;
} pos;
typedef struct _queue{
    pos arr[2500];
    int start;
    int len;
} queue;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int map[51][51];
int newmap[51][51];
int check[51][51];
queue q;
int N, L, R;
inline int abs(int x)
{
    return (x>0)?x:(-x);
}
int bound(pos p, int i)
{
    if(p.y + dy[i] == 0 || p.y + dy[i] == N+1 || p.x + dx[i] == 0 || p.x + dx[i] == N+1)
        return 1;
    else return 0;
}
int population_condition(pos p, pos q)
{
    if(abs(map[p.y][p.x] - map[q.y][q.x]) >= L && abs(map[p.y][p.x] - map[q.y][q.x]) <= R)
        return 1;
    else return 0;
}
void queue_push(pos p)
{
    q.arr[q.start + q.len++] = p;
}
pos queue_pop(void)
{
    /*if(!q.len)
        exit(1);*/
    q.len--;
    return q.arr[q.start++];
}
int bfs(pos p)
{
    // check 배열 초기화
    memset(check, 0, 51*51*sizeof(int));
    
    q.len = 0;
    q.start = 0;
    // 확인
    check[p.y][p.x] = 1;
    int total = 1;
    int sum = map[p.y][p.x];
    queue_push(p);
    while(q.len)
    {
        pos e = queue_pop();
        for(int i=0;i<=3;i++)
        {
            pos con = {e.y+dy[i], e.x+dx[i]};
            if(!bound(e, i) && !check[con.y][con.x] && population_condition(e, con))
            {
                queue_push(con);
                check[con.y][con.x] = 1;
                total++;
                sum += map[con.y][con.x];
            }
        }
    }
    
    if(total >= 2)
    {
        // 평탄화
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if(check[i][j])
                    newmap[i][j] = sum / total;
        return 1;
    }
    else
    {
        newmap[p.y][p.x] = map[p.y][p.x];
        return 0;
    }
}
int population_move(void)
{
    int population_moved = 0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(!check[i][j])
            {
                pos p = {i, j};
                if(bfs(p))
                    population_moved = 1;
            }
    if(population_moved)
    {
        memcpy(map, newmap, 51*51*sizeof(int));
        return 1;
    }
    else return 0;
}
int main(void)
{
    scanf("%d %d %d", &N, &L, &R);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            scanf("%d", &map[i][j]);
    int days = 0;
    while(1)
    {
        int move = population_move();
        if(!move) break;
        days += move;
    }
    printf("%d", days);
    return 0;
}