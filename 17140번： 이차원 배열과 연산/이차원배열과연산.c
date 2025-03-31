#include <stdio.h>
#include <string.h>
unsigned char R=3;
unsigned char C=3;
unsigned char A[101][101];
unsigned char new_A[201][201];
unsigned char howmany[101];
void rowaction(void)
{
    memset(new_A, 0, sizeof(unsigned char) * 201 * 201);
    unsigned char maxrow = 1;
    for(unsigned char i=1;i<=R;i++)
    {
        memset(howmany, 0, sizeof(unsigned char) * 101);
        // 해당 행의 숫자 스캔
        for(unsigned char j=1;j<=C;j++)
        {
            if(!A[i][j]) continue;
            howmany[A[i][j]]++;
        }
        unsigned char i_maxrow = 0;
        for(unsigned char j=1;j<=100;j++)
        {
            if(!howmany[j]) continue;
            unsigned char pos = i_maxrow;
            for(;pos >= 2;pos = pos - 2)
            {
                if(howmany[j] >= new_A[i][pos]) break;
                new_A[i][pos+2] = new_A[i][pos];
                new_A[i][pos+1] = new_A[i][pos-1];
            }
            new_A[i][pos+1] = j;
            new_A[i][pos+2] = howmany[j];
            i_maxrow += 2;
        }
        if(i_maxrow > 100) maxrow = 100;
        else if(i_maxrow > maxrow) maxrow = i_maxrow;
    }
    C = maxrow;
    for(unsigned char i=1;i<=R;i++)
        for(unsigned char j=1;j<=C;j++)
            A[i][j] = new_A[i][j];
}
void colaction(void)
{
    memset(new_A, 0, sizeof(unsigned char) * 201 * 201);
    unsigned char maxcol = 1;
    for(unsigned char j=1;j<=C;j++)
    {
        memset(howmany, 0, sizeof(unsigned char) * 101);
        // 해당 열의 숫자 스캔
        for(unsigned char i=1;i<=R;i++)
        {
            if(!A[i][j]) continue;
            howmany[A[i][j]]++;
        }
        unsigned char j_maxcol = 0;
        for(unsigned char i=1;i<=100;i++)
        {
            if(!howmany[i]) continue;
            unsigned char pos = j_maxcol;
            for(;pos >= 2;pos = pos - 2)
            {
                if(howmany[i] >= new_A[pos][j]) break;
                new_A[pos+2][j] = new_A[pos][j];
                new_A[pos+1][j] = new_A[pos-1][j];
            }
            new_A[pos+1][j] = i;
            new_A[pos+2][j] = howmany[i];
            j_maxcol += 2;
        }
        if(j_maxcol > 100) maxcol = 100;
        else if(j_maxcol > maxcol) maxcol = j_maxcol;
    }
    R = maxcol;
    for(unsigned char i=1;i<=R;i++)
        for(unsigned char j=1;j<=C;j++)
            A[i][j] = new_A[i][j];
}
int main(void)
{
    unsigned char wanted_R, wanted_C, k;
    scanf("%d %d %d", &wanted_R, &wanted_C, &k);
    for(unsigned char i=1;i<=3;i++)
        for(unsigned char j=1;j<=3;j++)
            scanf("%d", &A[i][j]);
    unsigned char time = 0;
    while(A[wanted_R][wanted_C] != k)
    {
        time++;
        if(time == 101)
        {
            printf("-1");
            return 0;
        }
        if(R>=C) rowaction();
        else colaction();
    }
    printf("%d", time);
    return 0;
}