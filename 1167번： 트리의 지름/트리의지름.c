#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _linked_list{
    int n;
    int value;
    struct _linked_list* next;
} linked_list;
int V;
int max_node, max_dist;
int* check;
int* dist;
linked_list** map;
void ll_push(linked_list* ll, int n, int value)
{
    // 순서 중요 X
    linked_list* new = (linked_list*)malloc(sizeof(linked_list));
    new->n = n;
    new->value = value;
    new->next = ll->next;
    ll->next = new;
}
void ll_free(linked_list* ll)
{
    while(ll->next)
    {
        linked_list* temp = ll->next;
        linked_list* temptemp = temp->next;
        free(temp);
        ll->next = temptemp;
    }
    free(ll);
}
void DFS(int node)
{
    check[node] = 1;
    linked_list* temp = map[node]->next;
    while(temp)
    {
        if(!check[temp->n])
        {
            dist[temp->n] = dist[node] + temp->value;
            if(dist[temp->n] > max_dist)
            {
                max_dist = dist[temp->n];
                max_node = temp->n;
            }
            DFS(temp->n);
        }
        temp = temp->next;
    }
}
int main(void)
{
    scanf("%d", &V);
    dist = (int*)calloc(V+1, sizeof(int));
    check = (int*)calloc(V+1, sizeof(int));
    map = (linked_list**)malloc(sizeof(linked_list*) * (V+1));
    for(int i=1;i<=V;i++)
    {
        map[i] = (linked_list*)malloc(sizeof(linked_list));
        map[i]->next = NULL;
    }
    for(int i=1;i<=V;i++)
    {
        int n;
        scanf("%d", &n);
        while(1)
        {
            int a, b;
            scanf("%d", &a);
            if(a == -1) break;
            scanf("%d", &b);
            ll_push(map[n], a, b);
        }
    }
    DFS(1);
    max_dist = 0;
    memset(dist, 0, sizeof(int) * (V+1));
    memset(check, 0, sizeof(int) * (V+1));
    DFS(max_node);
    printf("%d", max_dist);
    free(check);
    free(dist);
    for(int i=1;i<=V;i++)
        ll_free(map[i]);
    free(map);
    return 0;
}