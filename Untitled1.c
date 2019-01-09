
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void input_sud(int a[100][100], int n);
void print_sud(int a[100][100], int n);
void unit_cells(int sudoku[100][100], int uu_cells[100][10][10], int n);
void solver_sud(int sudoku[100][100], int uu_cells[100][10][10], int n);
void cutter(int sudoku[100][100], int uu_cells[100][10][10], int n);
int search(int sudoku[100][100], int uu_cells[100][10][10], int n, int x, int p, const int c);     /* c = 0 denotes search in unit cells.
                                                                                                      c = -1 denotes search in row.
                                                                                                      c = 1 denotes search in columns. */

int main()
{
    int n, sudoku[100][100], uu_cells[100][10][10];
    printf("Enter the dimension of your sudoku : ");
    scanf("%d", &n);
    printf("Enter your sudoku : (If there are no elements then enter 0) :\n");
    input_sud(sudoku, n);
    printf("Thanks for entering! Your sudoku is : \n");
    unit_cells(sudoku, uu_cells, n);
    lb:
    for(int i=0;i<n;i++)
    {
        if(search(sudoku, uu_cells, n, 0, i, 1)==1)
        {
            cutter(sudoku, uu_cells, n);
            goto lb;
        }
    }
    printf("\nThe sudoku after solving is :\n");
    print_sud(sudoku, n);
    return 0;
}



void input_sud(int a[100][100], int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            scanf("%d", &a[i][j]);
    }
}



void print_sud(int a[100][100], int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}



void unit_cells(int sudoku[100][100], int uu_cells[100][10][10], int n)
{
    int r, c, p=(int)sqrt(n);
    for(int i=0;i<n;i++)
    {
        r=i/p;
        c=i%p;
        for(int j=0;j<p;j++)
        {
            for(int k=0;k<p;k++)
            {
                uu_cells[i][j][k]=sudoku[p*r+j][p*c+k];
            }
        }
    }
    solver_sud(sudoku, uu_cells, n);
}


void solver_sud(int sudoku[100][100], int uu_cells[100][10][10], int n)
{
    int viable[10], counts=0, p, q, x;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(sudoku[i][j]==0)
            {
                p=i/(int)sqrt(n);
                q=j/(int)sqrt(n);
                x=(int)sqrt(n)*p+q;
                counts=0;
                for(int k=1;k<=n;k++)
                {
                    if(search(sudoku, uu_cells, n, k, i, -1)==0)
                        if(search(sudoku, uu_cells, n, k, j, 1)==0)
                            if(search(sudoku, uu_cells, n, k, x, 0)==0)
                            {
                                viable[counts]=k;
                                counts++;
                            }
                }
                if(counts==1)
                {
                    sudoku[i][j]=viable[0];
                    unit_cells(sudoku, uu_cells, n);
                    break;
                }
            }
        }
    }
}


void cutter(int sudoku[100][100], int uu_cells[100][10][10], int n)
{
    srand(time(NULL));
    int viable[10], counts=0, p, q, x;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(sudoku[i][j]==0)
            {
                p=i/(int)sqrt(n);
                q=j/(int)sqrt(n);
                x=(int)sqrt(n)*p+q;
                counts=0;
                for(int k=1;k<=n;k++)
                {
                    if(search(sudoku, uu_cells, n, k, i, -1)==0)
                        if(search(sudoku, uu_cells, n, k, j, 1)==0)
                            if(search(sudoku, uu_cells, n, k, x, 0)==0)
                            {
                                viable[counts]=k;
                                counts++;
                            }
                }
                int rand_num = rand() % counts+0;
                sudoku[i][j]=viable[rand_num];
                unit_cells(sudoku, uu_cells, n);
                break;
            }
        }
    }
}

int search(int sudoku[100][100], int uu_cells[100][10][10], int n, int x, int p, const int c)
{
    if(c!=0)
    {
        for(int i=0;i<n;i++)
        {
            if(c==1)
                if(sudoku[i][p]==x)
                    return 1;
            if(c==-1)
                if(sudoku[p][i]==x)
                    return 1;
        }
        return 0;
    }
    else
    {
        for(int i=0;i<sqrt(n);i++)
            for(int j=0;j<sqrt(n);j++)
                if(uu_cells[p][i][j]==x)
                    return 1;
        return 0;
    }
}
