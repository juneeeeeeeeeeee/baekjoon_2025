#include <stdio.h>
long long int segtree[4000001];
long long int arr[1000001];
long long int make_segment_tree(int node, int start, int end)
{
    if(start == end)
    {
        segtree[node] = arr[start];
        return segtree[node];
    }
    int mid = (start+end)>>1;
    segtree[node] = make_segment_tree(node<<1, start, mid) + make_segment_tree((node<<1) + 1, mid+1, end);
    return segtree[node];
}
long long int sum(int node, int start, int end, int left, int right)
{
    if(start > right || end < left) return 0;
    if(start >= left && end <= right) return segtree[node];
    int mid = (start+end)>>1;
    return sum(node<<1, start, mid, left, right) + sum((node<<1) + 1, mid+1, end, left, right);
}
void update(int node, int start, int end, int index, long long int diff)
{
    if(start > index || end < index) return;
    segtree[node] += diff;
    if(start == end) return;
    int mid = (start+end)>>1;
    update(node<<1, start, mid, index, diff);
    update((node<<1)+1, mid+1, end, index, diff);
}
int main(void)
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    for(int i=1;i<=N;i++)
    {
        long long int n;
        scanf("%lld", &n);
        arr[i] = n;
    }
    make_segment_tree(1, 1, N);
    for(int i=1;i<=M+K;i++)
    {
        int a;
        scanf("%d", &a);
        if(a == 1) // update
        {
            int b;
            long long int c;
            scanf("%d %lld", &b, &c);
            update(1, 1, N, b, c-arr[b]);
            arr[b] = c;
        }
        else // sum
        {
            int b, c;
            scanf("%d %d", &b, &c);
            printf("%lld\n", sum(1, 1, N, b, c));
        }
    }
}