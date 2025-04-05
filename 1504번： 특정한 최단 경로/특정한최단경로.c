#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct _heap_node{
    int node;
    int fake_dist;
} heap_node;
typedef struct _heap{
    int size;
    heap_node arr[4000];
} heap;
int map[801][801];
int dist[801];
int N;
void heap_push(heap* hp, int n, int fake_dist)
{
    int findingpos = ++hp->size;
    while(findingpos != 1 && hp->arr[findingpos >> 1].fake_dist > fake_dist)
    {
        hp->arr[findingpos] = hp->arr[findingpos >> 1];
        findingpos >>= 1;
    }
    hp->arr[findingpos].node = n;
    hp->arr[findingpos].fake_dist = fake_dist;
}
heap_node heap_pop(heap* hp)
{
    heap_node r = hp->arr[1];
    heap_node last = hp->arr[hp->size--];
    if(!hp->size) return last;
    int child = 2;
    while(child <= hp->size)
    {
        if(child < hp->size && hp->arr[child].fake_dist > hp->arr[child+1].fake_dist)
            child++;
        if(hp->arr[child].fake_dist > last.fake_dist)
            break;
        hp->arr[child >> 1] = hp->arr[child];
        child <<= 1;
    }
    hp->arr[child >> 1] = last;
    return r;
}
int* dijkstra(int source, int dest)
{
    heap hp;
    hp.size = 0;
    for(int i=1;i<=N;i++)
        dist[i] = INT_MAX;
    dist[source] = 0;
    heap_push(&hp, source, 0);
    while(hp.size)
    {
        heap_node popped = heap_pop(&hp);
        if(popped.fake_dist > dist[popped.node]) continue;
        for(int i=1;i<=N;i++)
        {
            if(map[popped.node][i] != INT_MAX && dist[i] > map[popped.node][i] + dist[popped.node])
            {
                dist[i] = map[popped.node][i] + dist[popped.node];
                heap_push(&hp, i, dist[i]);
            }
        }
    }
    int* arr = (int*)malloc(sizeof(int) * 3);
    arr[0] = dist[1];
    arr[1] = dist[dest];
    arr[2] = dist[N];
    return arr;
}
int main(void)
{
    int E;
    scanf("%d %d", &N, &E);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            map[i][j] = INT_MAX;
    while(E--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a == b) continue;
        map[a][b] = c;
        map[b][a] = c;
    }
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    int* v1_arr = dijkstra(v1, v2);
    int* v2_arr = dijkstra(v2, v1);
    // 1->v1->v2->N
    int v1_v2, v2_v1;
    if(v1_arr[0] == INT_MAX || v1_arr[1] == INT_MAX || v2_arr[2] == INT_MAX)
        v1_v2 = INT_MAX;
    else v1_v2 = v1_arr[0] + v1_arr[1] + v2_arr[2];
    if(v2_arr[0] == INT_MAX || v2_arr[1] == INT_MAX || v1_arr[2] == INT_MAX)
        v2_v1 = INT_MAX;
    else v2_v1 = v2_arr[0] + v2_arr[1] + v1_arr[2];
    if(v1_v2 == INT_MAX && v2_v1 == INT_MAX)
        printf("-1");
    else
        printf("%d", (v1_v2 > v2_v1) ? v2_v1 : v1_v2);
    free(v1_arr);
    free(v2_arr);
    return 0;
}