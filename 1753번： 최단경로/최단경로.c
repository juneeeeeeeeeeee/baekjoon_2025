#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct _heap_node{
    int node;
    int fake_dist;
} heap_node;
typedef struct _minheap{
    int size;
    struct _heap_node arr[40001];
} minheap;
typedef struct _ll_node{
    int n;
    int dist;
    struct _ll_node* next;
} ll_node;
ll_node** map;
int V, E;
int dist[20001];
void push_hp(minheap* hp, int n, int fake_dist)
{
    int findingpos = ++hp->size;
    while(findingpos != 1 && hp->arr[findingpos >> 1].fake_dist > fake_dist)
    {
        hp->arr[findingpos] = hp->arr[findingpos >> 1];
        findingpos = findingpos >> 1;
    }
    hp->arr[findingpos].node = n;
    hp->arr[findingpos].fake_dist = fake_dist;
}
heap_node pop_hp(minheap* hp)
{
    heap_node r = hp->arr[1];
    heap_node last = hp->arr[hp->size--];
    int parent = 1;
    int child = 2;
    while(child <= hp->size)
    {
        if(child+1 <= hp->size && hp->arr[child].fake_dist > hp->arr[child+1].fake_dist) child++;
        if(hp->arr[child].fake_dist > last.fake_dist) break;
        hp->arr[parent] = hp->arr[child];
        parent = child;
        child = child << 1;
    }
    hp->arr[parent] = last;
    return r;
}
void dijkstra(int source)
{
    minheap hp;
    hp.size = 0;
    for(int i=1;i<=V;i++)
        dist[i] = INT_MAX;
    dist[source] = 0;
    push_hp(&hp, source, 0);
    while(hp.size)
    {
        heap_node pop = pop_hp(&hp);
        if(pop.fake_dist > dist[pop.node]) continue; // update 안됨
        ll_node* temp = map[pop.node]->next;
        while(temp)
        {
            if(dist[temp->n] > dist[pop.node] + temp->dist)
            {
                dist[temp->n] = dist[pop.node] + temp->dist;
                push_hp(&hp, temp->n, dist[temp->n]);
            }
            temp = temp->next;
        }
    }
}
int main(void)
{
    scanf("%d %d", &V, &E);
    map = (ll_node**)malloc(sizeof(ll_node*) * (V+1));
    for(int i=1;i<=V;i++)
    {
        map[i] = (ll_node*)malloc(sizeof(ll_node));
        map[i]->next = NULL;
    }
    int source;
    scanf("%d", &source);

    while(E--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        // map update, 어짜피 dijkstra에서 짧은 간선을 고름;이때 모든 입력에 대해서 각각의 edge를 update 하는 것보다 dijkstra에서 처리하는 게 시간이 더 빠름
        ll_node* temp = map[a];
        ll_node* new = (ll_node*)malloc(sizeof(ll_node));
        new->n = b;
        new->dist = c;
        new->next = temp->next;
        temp->next = new;
    }
    dijkstra(source);
    for(int i=1;i<=V;i++)
    {
        if(dist[i] == INT_MAX)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
    for(int i=1;i<=V;i++)
    {
        while(map[i]->next)
        {
            ll_node* temp = map[i]->next;
            ll_node* temptemp = temp->next;
            free(temp);
            map[i]->next = temptemp;
        }
        free(map[i]);
    }
    free(map);
    return 0;
}