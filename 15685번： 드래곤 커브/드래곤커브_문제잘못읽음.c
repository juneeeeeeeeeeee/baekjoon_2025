#include <stdio.h>
#include <stdlib.h>
typedef struct _pos{
    int ypos;
    int xpos;
} pos;
typedef struct _ll{
    struct _pos pos1;
    struct _pos pos2;
    int dir;
    struct _ll* next;
} ll;
typedef struct _square{
    int side[4];
    int squared;
} square;
int ydir[4] = {0, -1, 0, 1};
int xdir[4] = {1, 0, -1, 0};
int N;
square square_list[100][100];
int square_count;
void square_check_core(int xpos, int ypos)
{
    for(int i=0;i<=3;i++)
        if(!square_list[xpos][ypos].side[i])
            return;
    square_list[xpos][ypos].squared = 1;
    square_count++;
}
void square_check(ll* temp)
{
    // 사각형 확인
    if(temp->dir == 0)
    {
        if(temp->pos1.ypos > 0 && !square_list[temp->pos1.xpos][temp->pos1.ypos - 1].squared)
        {
            square_list[temp->pos1.xpos][temp->pos1.ypos - 1].side[3] = 1;
            square_check_core(temp->pos1.xpos, temp->pos1.ypos-1);
        }
        if(temp->pos1.ypos < 100 && !square_list[temp->pos1.xpos][temp->pos1.ypos].squared)
        {
            square_list[temp->pos1.xpos][temp->pos1.ypos].side[1] = 1;
            square_check_core(temp->pos1.xpos, temp->pos1.ypos);
        }
    }
    else if(temp->dir == 1)
    {
        if(temp->pos1.xpos > 0 && !square_list[temp->pos1.xpos - 1][temp->pos1.ypos - 1].squared)
        {
            square_list[temp->pos1.xpos - 1][temp->pos1.ypos - 1].side[0] = 1;square_check_core(temp->pos1.xpos-1, temp->pos1.ypos-1);
        }
        if(temp->pos1.xpos < 100 && !square_list[temp->pos1.xpos][temp->pos1.ypos-1].squared)
        {
            square_list[temp->pos1.xpos][temp->pos1.ypos - 1].side[2] = 1;
            square_check_core(temp->pos1.xpos, temp->pos1.ypos-1);
        }
    }
    else if(temp->dir == 2)
    {
        if(temp->pos1.ypos > 0 && !square_list[temp->pos1.xpos - 1][temp->pos1.ypos - 1].squared)
        {
            square_list[temp->pos1.xpos - 1][temp->pos1.ypos - 1].side[3] = 1;square_check_core(temp->pos1.xpos-1, temp->pos1.ypos-1);
        }
        if(temp->pos1.ypos < 100 && !square_list[temp->pos1.xpos - 1][temp->pos1.ypos].squared)
        {
            square_list[temp->pos1.xpos - 1][temp->pos1.ypos].side[1] = 1;
            square_check_core(temp->pos1.xpos-1, temp->pos1.ypos);
        }
    }
    else if(temp->dir == 3)
    {
        if(temp->pos1.xpos > 0 && !square_list[temp->pos1.xpos - 1][temp->pos1.ypos].squared)
        {
            square_list[temp->pos1.xpos - 1][temp->pos1.ypos].side[0] = 1;
            square_check_core(temp->pos1.xpos-1, temp->pos1.ypos);
        }
        if(temp->pos1.xpos < 100 && !square_list[temp->pos1.xpos][temp->pos1.ypos].squared)
        {
            square_list[temp->pos1.xpos][temp->pos1.ypos].side[2] = 1;
            square_check_core(temp->pos1.xpos, temp->pos1.ypos);
        }
    }
}
ll* new_gen(ll* dragon_node)
{
    ll* new;
    if(dragon_node->next) new = new_gen(dragon_node->next);
    else new = dragon_node;
    ll* temp = malloc(sizeof(ll));
    temp->pos1 = new->pos2;
    temp->dir = (dragon_node->dir + 1) % 4;
    temp->pos2.ypos = temp->pos1.ypos + ydir[temp->dir];
    temp->pos2.xpos = temp->pos1.xpos + xdir[temp->dir];
    temp->next = NULL;
    new->next = temp;
    square_check(temp);
    return temp;
}
int main(void)
{
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
    {
        int x, y, d, g;
        scanf("%d %d %d %d", &x, &y, &d, &g);
        ll* dragon_start = (ll*)malloc(sizeof(ll));
        dragon_start->pos1.ypos = y;
        dragon_start->pos1.xpos = x;
        dragon_start->dir = d;
        dragon_start->pos2.ypos = dragon_start->pos1.ypos + ydir[d];
        dragon_start->pos2.xpos = dragon_start->pos1.xpos + xdir[d];
        dragon_start->next = NULL;
        square_check(dragon_start);
        while(g--)
        {
            new_gen(dragon_start);
        }
        ll* temp = dragon_start;
    }
    printf("%d", square_count);
    return 0;
}