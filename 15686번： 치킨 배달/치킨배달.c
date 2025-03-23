#include <stdio.h>
#include <stdlib.h>
typedef struct _pos{
    int ypos;
    int xpos;
} pos;
typedef struct _node{
    int ypos;
    int xpos;
    int dist;
} node;
typedef struct _queue{
    node nodearray[2501];
    int start;
    int len;
} queue;
int** map;
int** check;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int N, M;
pos house_list[100];
int house_num;
pos chicken_list[13];
int chicken_num;
int min_chicken_dist = 1000000;
node queue_pop(queue* q)
{
    if(!q->len)
        exit(1);
    q->len--;
    return q->nodearray[q->start++];
}
void queue_push(queue* q, node newnode)
{
    q->nodearray[q->start+q->len] = newnode;
    q->len++;
}
int bfs(int ypos, int xpos)
{
    queue* q = malloc(sizeof(queue));
    q->start = 0;
    q->len = 0;
    node ognode = {ypos, xpos, 0};
    queue_push(q, ognode);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            check[i][j] = 0;
    check[ypos][xpos] = 1;
    while(q->len)
    {
        node popnode = queue_pop(q);
        if(map[popnode.ypos][popnode.xpos] == 2)
        {
            free(q);
            return popnode.dist;
        }
        
        for(int i=0;i<=3;i++)
        {
            int new_ypos = popnode.ypos + dy[i];
            int new_xpos = popnode.xpos + dx[i];
            if(new_ypos >= 1 && new_ypos <= N && new_xpos >= 1 && new_xpos <= N && !check[new_ypos][new_xpos])
            {
                node newnode = {new_ypos, new_xpos, popnode.dist+1};
                queue_push(q, newnode);
                check[new_ypos][new_xpos] = 1;
            }
        }
    }
}
int finding_chicken_dist()
{
    int dist_sum = 0;
    for(int i=0;i<=house_num-1;i++)
        dist_sum += bfs(house_list[i].ypos, house_list[i].xpos);
    return dist_sum;
}
void finding_worst_chicken(int num, int order)
{
    if(order == chicken_num - M)
    {
        int chicken_dist = finding_chicken_dist();
        if(chicken_dist < min_chicken_dist){
            min_chicken_dist = chicken_dist;
            return;
        }
    }
    for(int i=num;i<=chicken_num-1;i++)
    {
        map[chicken_list[i].ypos][chicken_list[i].xpos] = -1;
        finding_worst_chicken(i+1, order+1);
        map[chicken_list[i].ypos][chicken_list[i].xpos] = 2;
    }
}
int main(void)
{
    scanf("%d %d", &N, &M);
    map = (int**)calloc(N+1, sizeof(int*));
    check = (int**)calloc(N+1, sizeof(int*));
    for(int i=1;i<=N;i++)
    {
        map[i] = (int*)calloc(N+1, sizeof(int));
        check[i] = (int*)calloc(N+1, sizeof(int));
        for(int j=1;j<=N;j++)
        {
            scanf("%d", &map[i][j]);
            if(map[i][j] == 1)
            {
                house_list[house_num].ypos = i;
                house_list[house_num].xpos = j;
                house_num++;
            }
            else if(map[i][j] == 2)
            {
                chicken_list[chicken_num].ypos = i;
                chicken_list[chicken_num].xpos = j;
                chicken_num++;
            }
        }
    }
    finding_worst_chicken(0, 0);
    printf("%d", min_chicken_dist);
    return 0;
}