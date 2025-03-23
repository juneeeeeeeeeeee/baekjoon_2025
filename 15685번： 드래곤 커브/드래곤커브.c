#include <stdio.h>
#include <stdlib.h>
typedef struct _pos{
    int ypos;
    int xpos;
} pos;
typedef struct _ll{
    struct _pos pos;
    int dir;
    struct _ll* next;
} ll;
typedef struct _square{
    int side[4];
    int squared;
} square;
int ydir[4] = {0, -1, 0, 1};
int xdir[4] = {1, 0, -1, 0};
int square_ydir[4] = {-1, -1, 0, 0};
int square_xdir[4] = {-1, 0, 0, -1};
int N;
square square_list[100][100];
int square_count;
void square_check_core(int xpos, int ypos, int dir)
{
    if(xpos >= 0 && xpos <= 99 && ypos >= 0 && ypos <= 99 && !square_list[xpos][ypos].squared)
    {
        square_list[xpos][ypos].side[dir]=1;
        for(int i=0;i<=3;i++)
            if(!square_list[xpos][ypos].side[i])
                return;
        square_list[xpos][ypos].squared = 1;
        square_count++;
    }
}
void square_check(ll* temp)
{
    // 사각형 확인
    for(int i=0;i<=3;i++)
    {
        pos squarepos;
        squarepos.xpos = temp->pos.xpos + xdir[temp->dir] + square_xdir[i];
        squarepos.ypos = temp->pos.ypos + ydir[temp->dir] + square_ydir[i];
        square_check_core(squarepos.xpos, squarepos.ypos, i);
    }
}
ll* new_gen(ll* dragon_node)
{
    ll* new;
    if(dragon_node->next) new = new_gen(dragon_node->next);
    else new = dragon_node;
    ll* temp = malloc(sizeof(ll));
    temp->dir = (dragon_node->dir + 1) % 4;
    temp->pos.xpos = new->pos.xpos + xdir[new->dir];
    temp->pos.ypos = new->pos.ypos + ydir[new->dir];
    temp->next = NULL;
    new->next = temp;
    square_check(temp);
    return temp;
}
void free_ll(ll* node)
{
    if(node->next)
        free_ll(node->next);
    free(node);
}
int main(void)
{
    scanf("%d", &N);
    for(int testcase=1;testcase<=N;testcase++)
    {
        int x, y, d, g;
        scanf("%d %d %d %d", &x, &y, &d, &g);
        ll* dragon_start = (ll*)malloc(sizeof(ll));
        dragon_start->pos.xpos = x;
        dragon_start->pos.ypos = y;
        dragon_start->dir = d;
        dragon_start->next = NULL;
        
        for(int i=0;i<=3;i++)
        {   
            pos squarepos;
            // pos1 update
            squarepos.xpos = x + square_xdir[i];
            squarepos.ypos = y + square_ydir[i];
            square_check_core(squarepos.xpos, squarepos.ypos, i);
            // pos2 update
            squarepos.xpos = x + xdir[d] + square_xdir[i];
            squarepos.ypos = y + ydir[d] + square_ydir[i];
            square_check_core(squarepos.xpos, squarepos.ypos, i);
        }
        while(g--)
        {
            new_gen(dragon_start);
        }
        free_ll(dragon_start);
    }
    printf("%d", square_count);
    return 0;
}