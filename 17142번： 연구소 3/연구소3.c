#include <stdio.h>
typedef struct _pos{
    int y;
    int x;
} pos;
typedef struct _queue{
    pos arr[2501];
    int start;
    int len;
} queue;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int map[51][51];
int check[51][51];
int N, M, V;
int zeros;
queue virus_q;
pos viruses[2501];
int viruses_comb[11];
int mintime = 2501;
int border(pos p, int dir)
{
    if(p.y+dy[dir] == 0 || p.y+dy[dir] == N+1 || p.x+dx[dir] == 0 || p.x+dx[dir] == N+1 || map[p.y+dy[dir]][p.x+dx[dir]] == 1)
        return 1;
    else return 0;
}
void queue_push(queue* q, pos p)
{
    q->arr[q->start + q->len++] = p;
}
pos queue_pop(queue* q)
{
    q->len--;
    return q->arr[q->start++];
}
int BFS(void)
{
    int time = 0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            check[i][j] = 0;
    virus_q.start = 0;
    virus_q.len = 0;
    for(int i=1;i<=M;i++)
    {
        pos first_virus = viruses[viruses_comb[i]];
        queue_push(&virus_q, first_virus);
        check[first_virus.y][first_virus.x] = 1;
    }
    int bfs_zeros = zeros;
    while(virus_q.len)
    {
        if(!bfs_zeros) return time;
        time++;
        int before_len = virus_q.len;
        while(before_len--)
        {
            pos pop_pos = queue_pop(&virus_q);
            for(int dir = 0;dir<=3;dir++)
            {
                if(!border(pop_pos, dir) && !check[pop_pos.y+dy[dir]][pop_pos.x+dx[dir]])
                {
                    pos new_pos = {pop_pos.y+dy[dir], pop_pos.x+dx[dir]};
                    queue_push(&virus_q, new_pos);
                    check[new_pos.y][new_pos.x] = 1;
                    if(!map[new_pos.y][new_pos.x]) bfs_zeros--;
                }
            }
        }
    }
    return 2501;
}
void combi(int index, int i)
{
    if(index == M+1)
    {
        int t = BFS();
        if(t < mintime)
            mintime = t;
        return;
    }
    if(i >= V+1) return;
    viruses_comb[index] = i;
    combi(index+1, i+1);
    combi(index, i+1);
}
int main(void)
{
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            scanf("%d", &map[i][j]);
            if(map[i][j] == 2)
            {
                V++;
                viruses[V].y = i;
                viruses[V].x = j;
            }
            else if(!map[i][j])
                zeros++;
        }
    }
    combi(1, 1);
    if(mintime == 2501) printf("-1");
    else printf("%d", mintime);
    return 0;
}