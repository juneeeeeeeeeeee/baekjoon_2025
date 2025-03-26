#include <stdio.h>
#include <stdlib.h>
typedef struct _minheap{
    int arr[100001];
    int size;
} minheap;
inline int abs(int x)
{
    return (x>0)?x:-x;
}
void push(minheap* hp, int n)
{
    int findingpos = ++hp->size;
    while(findingpos != 1 && (abs(hp->arr[findingpos >> 1]) > abs(n) || (abs(hp->arr[findingpos >> 1]) == abs(n) && n < 0)))
    {
        hp->arr[findingpos] = hp->arr[findingpos >> 1];
        findingpos = findingpos >> 1;
    }
    hp->arr[findingpos] = n;
}
int pop(minheap* hp)
{
    if(!hp->size)
        return 0;
    int r = hp->arr[1];
    int last = hp->arr[hp->size--];
    int parent = 1;
    int child = 2;
    while(child <= hp->size)
    {
        if(child + 1 <= hp->size && (abs(hp->arr[child]) > abs(hp->arr[child+1]) || (abs(hp->arr[child]) == abs(hp->arr[child+1]) && hp->arr[child+1] < 0)))
            child++;
        if(abs(hp->arr[child]) > abs(last) || abs(hp->arr[child]) == abs(last) && last < 0)
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
    minheap* hp = malloc(sizeof(minheap));
    hp->size = 0;
    while(N--)
    {
        int a;
        scanf("%d", &a);
        if(!a)
            printf("%d\n", pop(hp));
        else
            push(hp, a);
    }
    free(hp);
    return 0;
}