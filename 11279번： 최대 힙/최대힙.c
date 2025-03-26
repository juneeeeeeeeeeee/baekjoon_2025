#include <stdio.h>
#include <stdlib.h>
typedef struct _maxheap{
    unsigned int arr[100001];
    int size;
} maxheap;
void push(maxheap* hp, unsigned int n)
{
    hp->size++;
    int findingpos = hp->size;
    while(findingpos > 1 && hp->arr[findingpos >> 1] < n)
    {
        hp->arr[findingpos] = hp->arr[findingpos >> 1];
        findingpos = findingpos >> 1;
    }
    hp->arr[findingpos] = n;
}
unsigned int pop(maxheap* hp)
{
    if(!hp->size)
        return 0;
    unsigned int r = hp->arr[1];
    unsigned int last = hp->arr[hp->size];
    hp->size--;
    int parent = 1;
    int child = 2;
    while(child <= hp->size)
    {
        if(child + 1 <= hp->size && hp->arr[child] < hp->arr[child+1])
            child++;
        if(hp->arr[child] < last)
            break;
        hp->arr[parent] = hp->arr[child];
        parent = child;
        child = child << 1;
    }
    hp->arr[parent] = last;
    return r;
}
int main(void)
{
    int N;
    scanf("%d", &N);
    maxheap* hp = malloc(sizeof(maxheap));
    hp->size = 0;
    while(N--)
    {
        unsigned int a;
        scanf("%u", &a);
        if(!a)
            printf("%u\n", pop(hp));
        else
            push(hp, a);
    }
    free(hp);
    return 0;
}