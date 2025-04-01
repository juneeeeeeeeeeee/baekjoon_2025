#include <stdio.h>
typedef struct _node{
    int n;
    int left;
    int right;
} node;
int N;
node map[27];
void pre(int n)
{
    printf("%c", n+64);
    if(map[n].left) pre(map[n].left);
    if(map[n].right) pre(map[n].right);
}
void in(int n)
{
    if(map[n].left) in(map[n].left);
    printf("%c", n+64);
    if(map[n].right) in(map[n].right);
}
void post(int n)
{
    if(map[n].left) post(map[n].left);
    if(map[n].right) post(map[n].right);
    printf("%c", n+64);
}
int main(void)
{
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
    {
        char a, b, c;
        while(getchar()!='\n');
        scanf("%c %c %c", &a, &b, &c);
        if(b == '.') map[(int)a-64].left = 0;
        else map[(int)a-64].left = (int)b-64;
        if(c == '.') map[(int)a-64].right = 0;
        else map[(int)a-64].right = (int)c-64;
    }
    pre(1);
    printf("\n");
    in(1);
    printf("\n");
    post(1);
    return 0;
}