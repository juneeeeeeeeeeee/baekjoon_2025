#include <stdio.h>
typedef struct _heap{
    int size;
    int arr[5002];
} heap;
int ans[5001];
void heap_push(heap* hp, int n, int is_minheap)
{
    int findingpos = ++hp->size;
    if(is_minheap) // minheap
    {
        while(findingpos != 1 && hp->arr[findingpos >> 1] > n)
        {
            hp->arr[findingpos] = hp->arr[findingpos >> 1];
            findingpos >>= 1;
        }
    }
    else
    {
        while(findingpos != 1 && hp->arr[findingpos >> 1] < n)
        {
            hp->arr[findingpos] = hp->arr[findingpos >> 1];
            findingpos >>= 1;
        }
    }
    hp->arr[findingpos] = n;
}
int heap_pop(heap* hp, int is_minheap)
{
    int r = hp->arr[1];
    int last = hp->arr[hp->size--];
    int child = 2;
    if(is_minheap) // minheap
    {
        while(child <= hp->size)
        {
            if(child < hp->size && hp->arr[child] > hp->arr[child+1]) child++;
            if(hp->arr[child] > last) break;
            hp->arr[child >> 1] = hp->arr[child];
            child <<= 1;
        }
    }
    else
    {
        while(child <= hp->size)
        {
            if(child < hp->size && hp->arr[child] < hp->arr[child+1]) child++;
            if(hp->arr[child] < last) break;
            hp->arr[child >> 1] = hp->arr[child];
            child <<= 1;
        }
    }
    hp->arr[child >> 1] = last;
    return r;
}
int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int M, start, mid, count;
        scanf("%d\n%d", &M, &start);
        M--;
        heap hp[2]; // hp[0]: maxheap, hp[1]: minheap
        hp[0].size = 0;
        hp[1].size = 0;
        mid = start;
        ans[0] = mid;
        count = 1;
        printf("%d\n", (M>>1) + 1);
        while(M)
        {
            int a, b;
            scanf("%d", &a);
            scanf("%d", &b);
            int where_a = (a>mid)?1:0;
            heap_push(&hp[where_a], a, where_a);
            int where_b = (b>mid)?1:0;
            heap_push(&hp[where_b], b, where_b);
            if(hp[0].size == hp[1].size + 2) // maxheap이 size 큼
            {
                int m1 = heap_pop(&hp[0], 0);
                heap_push(&hp[1], mid, 1);
                mid = m1;
            }
            else if(hp[0].size == hp[1].size - 2)
            {
                int m1 = heap_pop(&hp[1], 1);
                heap_push(&hp[0], mid, 0);
                mid = m1;
            }
            ans[count++] = mid;
            M -= 2;
        }
        for(int i=0;i<count;i++)
        {
            if(i % 10 == 0 && i) printf("\n");
            printf("%d ", ans[i]);
        }
    }
}