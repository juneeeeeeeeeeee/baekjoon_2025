#include <stdio.h>
#include <stdlib.h>
typedef struct _ll_node{
    int n;
    struct _ll* next;
} ll_node;
ll_node** ll;
int N;
int* check;
int* parent;
void ll_push(ll_node* ll, int n)
{
    ll_node* temp = ll;
    while(temp->next)
        temp = temp->next;
    ll_node* new = (ll_node*)malloc(sizeof(ll_node));
    new->n = n;
    new->next = NULL;
    temp->next = new;
}
void DFS(int cur)
{
    check[cur] = 1;
    ll_node* temp = ll[cur]->next;
    while(temp)
    {
        if(!check[temp->n])
        {
            parent[temp->n] = cur;
            DFS(temp->n);
        }
        temp = temp->next;
    }
}
int main(void)
{
    scanf("%d", &N);
    ll = (ll_node**)malloc(sizeof(ll_node*) * (N+1));
    for(int i=1;i<=N;i++)
    {
        ll[i] = (ll_node*)malloc(sizeof(ll_node));
        ll[i]->next = NULL;
    }
    check = (int*)calloc(N+1, sizeof(int));
    parent = (int*)calloc(N+1, sizeof(int));
    for(int i=1;i<=N-1;i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        ll_push(ll[a], b);
        ll_push(ll[b], a);
    }
    DFS(1);
    for(int i=1;i<=N;i++)
    {
        while(ll[i]->next)
        {
            ll_node* temp = ll[i]->next;
            ll_node* temptemp = temp->next;
            free(temp);
            ll[i]->next = temptemp;
        }
    }
    for(int i=2;i<=N;i++)
        printf("%d\n", parent[i]);
    free(check);
    free(parent);
    free(ll);
    return 0;
}