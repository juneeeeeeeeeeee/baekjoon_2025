#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _linked_list{
    int n;
    int value;
    struct _linked_list* next;
} linked_list;
linked_list** map;
int* check;
int* dist;
int max_dist, max_node;
int N;
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
    scanf("%d", &N);
    if(N == 1)
    {
        printf("0");
        return 0;
    }
    map = (linked_list**)malloc(sizeof(linked_list*) * (N+1));
    for(int i=1;i<=N;i++)
    {
        map[i] = (linked_list*)malloc(sizeof(linked_list));
        map[i]->next = NULL;
    }
    for(int i=1;i<=N-1;i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        ll_push(map[a], b, c);
        ll_push(map[b], a, c);
    }
    check = (int*)calloc(N+1, sizeof(int));
    dist = (int*)calloc(N+1, sizeof(int));
    DFS(1);
    memset(check, 0, sizeof(int) * (N+1));
    memset(dist, 0, sizeof(int) * (N+1));
    max_dist = 0;
    DFS(max_node);
    printf("%d", max_dist);
    free(check);
    free(dist);
    for(int i=1;i<=N;i++)
        ll_free(map[i]);
    free(map);
    return 0;
}