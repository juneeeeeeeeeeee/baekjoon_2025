#include <stdio.h>
int inorder[100001];
int postorder[100001];
int index[100001];
int N;
void getpreorder(int instart, int inend, int poststart, int postend)
{
    if(instart > inend || poststart > postend) return;
    printf("%d ", postorder[postend]);
    int rootindex = index[postorder[postend]];
    int leftlen = rootindex - instart;
    getpreorder(instart, rootindex-1, poststart, poststart+leftlen-1); // left
    getpreorder(rootindex+1, inend, poststart+leftlen, postend-1); // right
}
int main(void)
{
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d", &inorder[i]);
        index[inorder[i]] = i;
    }
    for(int i=1;i<=N;i++)
    {
        scanf("%d", &postorder[i]);
    }
    getpreorder(1, N, 1, N);
    return 0;
}