#include"skheader.h"
void main()
{
    int c;
    long int log;
    char adlog[20],pw[MAXPW] = {0},*p = pw;
    FILE *fp = stdin;
    ssize_t nchr = 0;

    while(1)
    {
       	printf("Home/");
  	scr();
  	printf("\t1.ADMIN LOGIN\n\t2.EMPLOYEE LOGIN\n\t3.PATIENT LOGIN\n\t4.DOCTOR LOGIN\n\t5.EXIT\n");
  	c=getch()-48; 
	scr();
  	switch(c)
  	{
	    case 1:
		printf ( "\n Enter password: ");
		nchr = getpasswd (&p, MAXPW, '*', fp);
  		if(!admlog(p))
  		    continue;
  		break;
  	    case 2:
  		printf("Enter your UID:");
  		scanf("%ld",&log);
		getchar();
  		if(!emplog(log))
  		    continue;
  		break;
  	    case 3:
  		printf("Enter your UID:");
  		scanf("%ld",&log);
		getchar();
  		if(!patlog(log))
  		    continue;
  		break;
  	    case 4:
  		printf("Enter your UID:");
  		scanf("%ld",&log);
		getchar();
  		if(!doclog(log))
  		    continue;
  		break;
	    case 5:
  		system("clear");
  		break;
  	    default:
  		printf("Invalid input\n");
  		continue;
  	}
	break;
    }
}
