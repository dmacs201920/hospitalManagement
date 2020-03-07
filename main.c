#include"skheader.h"
#include<stdio.h>
#include<stdlib.h>
void main()
{
    int c;
    long int log;
    char adlog[20];
    printf("page 1");
   while(1)
   { 

        scr();
	printf("\t1.ADMIN LOGIN\n\t2.EMPLOYEE LOGIN\n\t3.PATIENT LOGIN\n\t4.DOCTOR LOGIN\n\t5.EXIT\n");
	scanf("%d",&c);
	
	switch(c)
	{
	    case 1:
                scr();
                printf("Enter the password:");
		getchar();
                gets(adlog);
		if(!admlog(adlog))
		    continue;
                break;
	    case 2:
                scr();
                printf("Enter your UID:");
                scanf("%ld",&log);
		if(!emplog(log))
		    continue;
                break;
	    case 3:
                scr();
		getchar();
                printf("Enter your UID:");
                scanf("%ld",&log);
		if(!patlog(log))
		    continue;
		break;
	    case 4:
		scr();
		printf("Enter your UID:");
		scanf("%ld",&log);
		if(!doclog(log))
		    continue;
		break;
            case 5:
		system("clear");
		exit(-1);
		break;
	    default:
		printf("Invalid input\n");
		continue;
	}
   }
}
