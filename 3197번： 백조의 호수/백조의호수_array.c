#include <stdio.h>
typedef struct _pos{
    int y;
    int x;
} pos;
typedef struct _queue{
    pos arr[2250001];
    int start;
    int len;
} queue;
queue ice_start;
queue icetopond_start;
queue baekjo_pond;
int R, C;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
pos baekjo1, baekjo2;
char map[1501][1501];
char check[1501][1501];
int border(pos p, int dir)
{
    if(p.y+dy[dir] == 0 || p.y+dy[dir] == R+1 || p.x+dx[dir] == 0 || p.x+dx[dir] == C+1)
        return 1;
    else return 0;
}
void push(queue* q, pos p)
{
    q->arr[q->start + q->len++] = p;
}
pos pop(queue* q)
{
    q->len--;
    return q->arr[q->start++];
}
void BFS_firsttime(pos p)
{
    check[p.y][p.x] = 1;
    push(&ice_start, p);
    while(ice_start.len)
    {
        pos pop_p = pop(&ice_start);
        int checker = 0;
        for(int dir=0;dir<=3;dir++)
        {
            if(!border(pop_p, dir) && map[pop_p.y+dy[dir]][pop_p.x+dx[dir]] && !check[pop_p.y+dy[dir]][pop_p.x+dx[dir]])
            {
                pos new_p;
                new_p.y = pop_p.y+dy[dir];
                new_p.x = pop_p.x+dx[dir];
                push(&ice_start, new_p);
                check[new_p.y][new_p.x] = 1;
            }
            else if(!border(pop_p, dir) && !map[pop_p.y+dy[dir]][pop_p.x+dx[dir]] && checker == 0)
            {
                push(&icetopond_start, pop_p);
                checker = 1;
            }
        }
    }
}
void BFS_baekjopond(void)
{
    while(baekjo_pond.len)
    {
        pos pop_p = pop(&baekjo_pond);
        for(int dir=0;dir<=3;dir++)
        {
            if(!border(pop_p, dir) && !map[pop_p.y+dy[dir]][pop_p.x+dx[dir]] && !check[pop_p.y+dy[dir]][pop_p.x+dx[dir]])
            {
                pos new_p;
                new_p.y = pop_p.y + dy[dir];
                new_p.x = pop_p.x + dx[dir];
                push(&baekjo_pond, new_p);
                check[new_p.y][new_p.x] = -1;
            }
        }
    }
}
int main(void)
{
    scanf("%d %d", &R, &C);
    for(int i=1;i<=R;i++)
    {
        while(getchar() != '\n');
        for(int j=1;j<=C;j++)
        {
            char c;
            scanf("%c", &c);
            if(c == '.')
                map[i][j] = 0; // 물
            else if(c == 'X')
                map[i][j] = 1; // 얼음
            else if(!baekjo1.y)
            {
                baekjo1.y = i;
                baekjo1.x = j;
                map[i][j] = 0;
            }
            else
            {
                baekjo2.y = i;
                baekjo2.x = j;
                map[i][j] = 0;
            }
        }
    }
    // BFS
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            if(map[i][j] && !check[i][j])
            {
                pos p = {i, j};
                BFS_firsttime(p);
            }
        }
    }
    
    // BFS, 백조가 있는 pond에 대해
    push(&baekjo_pond, baekjo1);
    check[baekjo1.y][baekjo1.x] = -1;
    BFS_baekjopond();
    // 시간이 흐름에 따라
    int t = 0;
    while(check[baekjo2.y][baekjo2.x] != -1)
    {
        t++;
        // ice 축소
        int len = icetopond_start.len;

        while(len--)
        {
            pos p = pop(&icetopond_start);
            map[p.y][p.x] = 0;
            check[p.y][p.x] = 0;
            for(int dir=0;dir<=3;dir++)
            {
                if(!border(p, dir) && check[p.y+dy[dir]][p.x+dx[dir]] == -1 && check[p.y][p.x] != -1)
                {
                    push(&baekjo_pond, p);
                    check[p.y][p.x] = -1;
                }
                if(!border(p, dir) && map[p.y+dy[dir]][p.x+dx[dir]] && check[p.y+dy[dir]][p.x+dx[dir]] == 1)
                {
                    pos melt_p;
                    melt_p.y = p.y+dy[dir];
                    melt_p.x = p.x+dx[dir];
                    check[melt_p.y][melt_p.x] = 2;
                    push(&icetopond_start, melt_p);
                }
            }
        }
        // 1번 pond 확장
        BFS_baekjopond();
    }
    printf("%d", t);
    return 0;
}