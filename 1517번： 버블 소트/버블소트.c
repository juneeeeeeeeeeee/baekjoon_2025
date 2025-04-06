#include <stdio.h>
typedef struct _minheap{
    int size;
    int arr[500001];
} minheap;
int a[500001];
int segtree[2000000];
int N;
void hp_push(minheap* hp, int n)
{
    int findingpos = ++hp->size;
    while(findingpos != 1 && (a[hp->arr[findingpos >> 1]] > a[n] || (a[hp->arr[findingpos >> 1] == a[n] && hp->arr[findingpos >> 1] > n])))
    {
        hp->arr[findingpos] = hp->arr[findingpos >> 1];
        findingpos >>= 1;
    }
    hp->arr[findingpos] = n;
}
int hp_pop(minheap* hp)
{
    int r = hp->arr[1];
    int last = hp->arr[hp->size--];
    int child = 2;
    while(child <= hp->size)
    {
        if(child < hp->size && (a[hp->arr[child]] > a[hp->arr[child+1]] || (a[hp->arr[child]] == a[hp->arr[child+1]] && hp->arr[child] > hp->arr[child+1])))
            child++;
        if(a[hp->arr[child]] > a[last] || (a[hp->arr[child]] == a[last] && hp->arr[child] > last))
            break;
        hp->arr[child >> 1] = hp->arr[child];
        child <<= 1;
    }
    hp->arr[child >> 1] = last;
    return r;
}
int sum(int node, int left, int right, int start, int end)
{
    if(left > end || right < start) return 0;
    if(left >= start && right <= end) return segtree[node];
    int mid = (left+right) >> 1;
    return sum(node<<1, left, mid, start, end) + sum((node<<1)+1, mid+1, right, start, end);
}
void update(int node, int idx, int left, int right)
{
    if(left > idx || right < idx) return;
    segtree[node] += 1;
    if(left == right) return;
    int mid = (left+right) >> 1;
    update(node<<1, idx, left, mid);
    update((node<<1)+1, idx, mid+1, right);
}
int main(void)
{
    long long int total = 0;
    scanf("%d", &N);
    minheap hp;
    hp.size = 0;
    for(int i=1;i<=N;i++)
    {
        scanf("%d", &a[i]);
        hp_push(&hp, i);
    }
    while(hp.size)
    {
        int r = hp_pop(&hp);
        total += sum(1, 1, N, r+1, N);
        update(1, r, 1, N);
    }
    printf("%lld", total);
    return 0;
}