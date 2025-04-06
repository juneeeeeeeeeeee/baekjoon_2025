#include <stdio.h>
#define MOD 1000000007
int N;
int arr[1000001];
long long int segtree[4000001];
long long int makesegtree(int node, int left, int right)
{
    if(left == right)
    {
        segtree[node] = arr[left];
        return segtree[node];
    }
    int mid = (left+right) >> 1;
    segtree[node] = makesegtree(node<<1, left, mid) * makesegtree((node<<1)+1, mid+1, right) % MOD;
    return segtree[node];
}
long long int mult(int node, int left, int right, int start, int end)
{
    if(left > end || right < start) return 1;
    if(left >= start && right <= end) return segtree[node];
    int mid = (left+right) >> 1;
    return mult(node<<1, left, mid, start, end) * mult((node<<1)+1, mid+1, right, start, end) % MOD;
}
long long int update(int node, int index, int after, int left, int right)
{
    if(right < index || left > index) return segtree[node];
    if(left == right)
    {
        segtree[node] = after;
        return segtree[node];
    } 
    int mid = (left+right) >> 1;
    segtree[node] = update(node<<1, index, after, left, mid) * update((node<<1)+1, index, after, mid+1, right) % MOD;
    return segtree[node];
}
int main(void)
{
    int M, K;
    scanf("%d %d %d", &N, &M, &K);
    int cases = M+K;
    for(int i=1;i<=N;i++)
    {
        scanf("%d", &arr[i]);
    }
    makesegtree(1, 1, N);
    while(cases--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) // update
        {
            update(1, b, c, 1, N);
            arr[b] = c;
        }
        else // mul print
        {
            printf("%d\n", (int)mult(1, 1, N, b, c));
        }
    }
}