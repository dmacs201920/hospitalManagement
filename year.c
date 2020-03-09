#include<stdio.h>
int isleapyear(int y)
{
    return (y%400==0)||((y%4==0)&&(y%100!=0));
}

int checkdate(int d,int m,int y)
{
    int daysinmonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (d<1||m<1||y<1)
        return 0;
    if (isleapyear(y))
        daysinmonth[2]=29;
    if (1<=m&&m<=12)
    {
        if (d<=daysinmonth[m])
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
void main()

{
    int d,m,y;
    printf("Enter the date,month,year:-");
    scanf(" %d %d %d",&d,&m,&y);
    printf("\t%d\n",checkdate(d,m,y));
    printf("\t%d\n",isleapyear(y));
}
