#include <stdio.h>
#include <stdlib.h>
typedef struct _pos{
    int y;
    int x;
} pos;
typedef struct _queuenode{
    pos p;
    struct _queuenode* next;
} queuenode;
queuenode* ice_start;
queuenode* icetopond_start;
queuenode* baekjo_pond;
int R, C;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
pos baekjo1, baekjo2;
char map[1501][1501];
int check[1501][1501];
/*
void printmap(void)
{
    printf("map:\n");
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}
void printcheck(void)
{
    printf("check:\n");
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            printf("%d ", check[i][j]);
        }
        printf("\n");
    }
}
*/
int border(pos p, int dir)
{
    if(p.y+dy[dir] == 0 || p.y+dy[dir] == R+1 || p.x+dx[dir] == 0 || p.x+dx[dir] == C+1)
        return 1;
    else return 0;
}
void push(queuenode* startnode, pos p)
{
    queuenode* temp = startnode;
    while(temp->next)
    {
        temp = temp->next;
        if(temp->p.y == p.y && temp->p.x == p.x) // 이미 queue에 있음
            return;
    }
        
    queuenode* newnode = (queuenode*)malloc(sizeof(queuenode));
    newnode->p = p;
    newnode->next = NULL;
    temp->next = newnode;
}
pos pop(queuenode* startnode)
{
    queuenode* temp = startnode->next;
    startnode->next = temp->next;
    pos p = temp->p;
    free(temp);
    return p;
}
int queue_len(queuenode* startnode)
{
    queuenode* temp = startnode;
    int len = 0;
    while(temp->next)
    {
        temp = temp->next;
        len++;
    }
    return len;
}
void BFS_firsttime(pos p)
{
    check[p.y][p.x] = 1;
    push(ice_start, p);
    while(ice_start->next)
    {
        pos pop_p = pop(ice_start);
        for(int dir=0;dir<=3;dir++)
        {
            if(!border(pop_p, dir) && (map[pop_p.y+dy[dir]][pop_p.x+dx[dir]] == 1) && !check[pop_p.y+dy[dir]][pop_p.x+dx[dir]])
            {
                pos new_p;
                new_p.y = pop_p.y+dy[dir];
                new_p.x = pop_p.x+dx[dir];
                push(ice_start, new_p);
                check[new_p.y][new_p.x] = 1;
            }
            if(!border(pop_p, dir) && !map[pop_p.y+dy[dir]][pop_p.x+dx[dir]])
            {
                push(icetopond_start, pop_p);
            }
        }
    }
}
void BFS_baekjopond(void)
{
    while(baekjo_pond->next)
    {
        pos pop_p = pop(baekjo_pond);
        for(int dir=0;dir<=3;dir++)
        {
            if(!border(pop_p, dir) && !map[pop_p.y+dy[dir]][pop_p.x+dx[dir]] && !check[pop_p.y+dy[dir]][pop_p.x+dx[dir]])
            {
                pos new_p;
                new_p.y = pop_p.y + dy[dir];
                new_p.x = pop_p.x + dx[dir];
                push(baekjo_pond, new_p);
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
    ice_start = (queuenode*)malloc(sizeof(queuenode));
    ice_start->next = NULL;
    icetopond_start = (queuenode*)malloc(sizeof(queuenode));
    icetopond_start->next = NULL;
    // BFS
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            if(map[i][j] == 1 && !check[i][j])
            {
                pos p = {i, j};
                BFS_firsttime(p);
            }
        }
    }
    
    // BFS, 백조가 있는 pond에 대해
    baekjo_pond = (queuenode*)malloc(sizeof(queuenode));
    baekjo_pond->next = NULL;
    push(baekjo_pond, baekjo1);
    check[baekjo1.y][baekjo1.x] = -1;
    BFS_baekjopond();
    // printmap();
    // printcheck();
    // 시간이 흐름에 따라
    int t = 0;
    while(check[baekjo2.y][baekjo2.x] != -1)
    {
        t++;
        // ice 축소
        int len = queue_len(icetopond_start);

        while(len--)
        {
            pos p = pop(icetopond_start);
            map[p.y][p.x] = 0;
            check[p.y][p.x] = 0;
            for(int dir=0;dir<=3;dir++)
            {
                if(!border(p, dir) && check[p.y+dy[dir]][p.x+dx[dir]] == -1)
                {
                    push(baekjo_pond, p);
                    check[p.y][p.x] = -1;
                }
                if(!border(p, dir) && map[p.y+dy[dir]][p.x+dx[dir]] == 1)
                {
                    pos melt_p;
                    melt_p.y = p.y+dy[dir];
                    melt_p.x = p.x+dx[dir];
                    push(icetopond_start, melt_p);
                }
            }
        }
        // printf("time %d, ice 축소\n", t);
        // printmap();
        // printcheck();
        // 1번 pond 확장
        BFS_baekjopond();
        // printf("time %d, pond 확장\n", t);
        // printmap();
        // printcheck();
    }
    printf("%d", t);
    // free
    free(ice_start);
    free(icetopond_start);
    return 0;
}