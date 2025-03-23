#include <stdio.h>
#include <stdlib.h>
typedef struct _house_pos{
    int ypos;
    int xpos;
} house_pos;
typedef struct _chicken_pos{
    int ypos;
    int xpos;
    int invalid;
} chicken_pos;
int** map;
int N, M;
house_pos house_list[100];
int house_num;
chicken_pos chicken_list[13];
int chicken_num;
int min_chicken_dist = 1000000;
inline int abs(x){
    return (x>0)?x:-x;
}
int dist(house_pos pos1, chicken_pos pos2){
    return abs(pos1.xpos - pos2.xpos) + abs(pos1.ypos - pos2.ypos);
}
int finding_chicken_dist()
{
    int dist_sum = 0;
    for(int i=0;i<=house_num-1;i++)
    {
        int house_chicken_dist = 10000;
        for(int j=0;j<=chicken_num-1;j++)
        {
            if(chicken_list[j].invalid)
                continue;
            int distance = dist(house_list[i], chicken_list[j]);
            if(distance < house_chicken_dist)
                house_chicken_dist = distance;
        }
        dist_sum += house_chicken_dist;
    }
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
        chicken_list[i].invalid = 1;
        finding_worst_chicken(i+1, order+1);
        chicken_list[i].invalid = 0;
    }
}
int main(void)
{
    scanf("%d %d", &N, &M);
    map = (int**)calloc(N+1, sizeof(int*));
    for(int i=1;i<=N;i++)
    {
        map[i] = (int*)calloc(N+1, sizeof(int));
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
    for(int i=1;i<=N;i++)
    {
        free(map[i]);
    }
    free(map);
    return 0;
}