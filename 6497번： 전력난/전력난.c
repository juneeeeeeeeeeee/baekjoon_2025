#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct _vector{
    int dest;
    int dist;
} vector;
typedef struct _ll_node{
    vector v;
    struct _ll_node* next;
} ll_node;
typedef struct _minheap{
    vector arr[200001];
    int size;
} minheap;
int M, N;
ll_node** map;
void hp_push(minheap* hp, vector v)
{
    int findingpos = ++hp->size;
    while(findingpos != 1 && hp->arr[findingpos >> 1].dist > v.dist)
    {
        hp->arr[findingpos] = hp->arr[findingpos >> 1];
        findingpos >>= 1;
    }
    hp->arr[findingpos] = v;
}
vector hp_pop(minheap* hp)
{
    vector r = hp->arr[1];
    vector last = hp->arr[hp->size--];
    int child = 2;
    while(child <= hp->size)
    {
        if(child < hp->size && hp->arr[child].dist > hp->arr[child+1].dist)
            child++;
        if(last.dist < hp->arr[child].dist)
            break;
        hp->arr[child >> 1] = hp->arr[child];
        child <<= 1;
    }
    hp->arr[child >> 1] = last;
    return r;
}
int prim(int source)
{
    int mindist = 0;
    minheap hp;
    bool* check = (bool*)calloc(M, sizeof(bool));
    hp.size = 0;
    ll_node* temp = map[source]->next;
    while(temp)
    {
        hp_push(&hp, temp->v);
        temp = temp->next;
    }
    check[source] = true;

    // M-1번 반복
    for(int i=1;i<=M-1;i++)
    {
        vector pop_v;
        do
        {
            pop_v = hp_pop(&hp);
        } while (check[pop_v.dest]);
        mindist += pop_v.dist;
        temp = map[pop_v.dest]->next;
        while(temp)
        {
            if(!check[temp->v.dest])
                hp_push(&hp, temp->v);
            temp = temp->next;
        }
        check[pop_v.dest] = true;
    }
    return mindist;
}
int main(void)
{
    while(1)
    {
        scanf("%d %d", &M, &N);
        if(!M && !N) return 0;
        map = (ll_node**)malloc(sizeof(ll_node*) * M);
        for(int i=0;i<M;i++)
        {
            map[i] = (ll_node*)malloc(sizeof(ll_node));
            map[i]->next = NULL;
        }
        int og_sum = 0;
        while(N--)
        {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            ll_node* new = (ll_node*)malloc(sizeof(ll_node));
            new->v.dest = y;
            new->v.dist = z;
            new->next = map[x]->next;
            map[x]->next = new;
            ll_node* new2 = (ll_node*)malloc(sizeof(ll_node));
            new2->v.dest = x;
            new2->v.dist = z;
            new2->next = map[y]->next;
            map[y]->next = new2;
            og_sum += z;
        }
        printf("%d\n", og_sum - prim(0));
        for(int i=0;i<M;i++)
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
    }
}
