#include"skheader.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
int admlog(char pass[])
{
    scr();
    char s[20]="sreeabhi",c2;
    employee e;
    doctor d;
    infra t;
    FILE *f;
    int c,c1;
    
    if(strcmp(s,pass))
    {
	printf("Check the password and login again...");
	return 0;
    }
    printf("Logged in successfully..\t");
sec:
    printf("PAGE 2");
    scr();
    printf("1.NEW EMPLOYEE\n2.NEW DOCTOR\n3.INFRASTRUCTURE\n4.LOG OUT\n");
    scanf("%d",&c);
    switch(c)
    {
	case 1:
	    Emp_rec();
	    break;
	case 2:
	    Doc_rec();
	    break;
	case 3:
inf:	    scr();
	    printf("1.ADD NEW INFRASTRUCTURE..\n");
	    printf("2.SEE THE AVAILABLE INFRASTRUCTURE\n");
	    printf("3.GO BACK\n");

	    scanf("%d",&c1);
	    switch(c1)
	    {
		case 1:
		    f=fopen("infra.dat","ab+");
		    if(f==NULL)
		    {
			printf("Overload");
			exit(-1);
		    }
		    getchar();
		    do
		    {
			printf("Department:");gets(t.dep);
			printf("Room no:");scanf(" %d",&t.room_no);
			getchar();
			printf("Equipments:");gets(t.equipments);
			fwrite(&t,sizeof(t),1,f);
			printf("Do you want to enter any new records???...(y/n)");
			scanf("%c",&c2);
		    }
		    while(c2=='y'||c2=='Y');
		    fclose(f);
		    break;
		case 2:
		    f=fopen("infra.dat","rb+");
		    if(f==NULL)
		    {
			printf("Problem in opening the file\n");
			goto sec;
		    }
		    fread(&t,sizeof(t),1,f);
		    while(!feof(f))
		    {
			printf("Department:");
			puts(t.dep);
			printf("Room no:%d\t",t.room_no);
			printf("Equipments:");
			puts(t.equipments);
			printf("\n");
			fread(&t,sizeof(t),1,f);
		    }
		    getchar();
		    printf("Enter any character to go back....");
		    getchar();
		    if(ftell(f)==0)
			printf("Records not found");
		    fclose(f);
		    goto inf;
		case 3:
		    goto sec;
		default:
		    printf("Invalid input.Please check and enter once again");
		    goto sec;
		    break;
	    }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
int emplog(long int UID)
{

    int c2;
    long int pid;
    employee p;
    FILE *emp;
    char s[30]="./employees_file/";
    
    strcat(s,itoa(UID));
    emp=fopen(s,"rb+");
    if(emp==NULL)
    {
	printf("\nData file not found.Check the UID and enter again!");
	getchar();
	return 0;
    }
    fseek(emp,0,0);
    fread(&p,sizeof(p),1,emp);
    printf("\n\t\t\t\t");
    empdisplay(p);
second: 
    if(!strcmp(p.department,"Reception"))
    {
    printf("\n0.NEW PATIENT\n1.INFRASTRUCTURE\n2.EDIT YOUR PROFILE\n3.LOG OUT\n");
    }
    else
    printf("\n\n1.INFRASTRUCTURE\n2.EDIT YOUR PROFILE\n3.LOG OUT\n");
    scanf("%d",&c2);
    switch(c2)
	{
	    case 1:
		scr();
		edisplay(p);
		printf("\n\n");
		infrastructure(p.department);
		goto second;
		
	    case 2:
		p=echange(p);
		fseek(emp,0,0);
		fwrite(&p,sizeof(p),1,emp);
		scr();
		edisplay(p);
		printf("\n\n");
		printf("Changed successfully");
		goto second;
	    case 3:
		fclose(emp);
		return 0;
		break;
	    case 0:
		if(!strcmp(p.department,"Reception"))
		{
		    Pat_rec();
		    getchar();
		    fclose(emp);
		    return 0;
		    break;
		}
	    default:
		printf("Wrong entry!!!Enter the given options only!!!\n");
		getchar();
		goto second;
		break;
	    }
    fclose(emp);
}
////////////////////////////////////////////////////////////////////////////////////////////////
int patlog(long int UID)
{
    int c,d;
    patient p;
    int day,month,year;
    char date[30];
    date[0]='\0';
    FILE * f;
    char s[30]="./patients_file/";
       strcat(s,itoa(UID));
       f=fopen(s,"rb+");
       puts(s);
       puts(itoa(UID));
       getchar();
       if(f==NULL)
         {

	    printf("Data file not found.Check your UID and enter again.");
	    getchar();
	    return 0;
          }
       fseek(f,0,0);
       fread(&p,sizeof(p),1,f);
       printf("\n\t\t\t\t");
       patdisplay(p);
first: printf("\n\n1.BOOK AN APPOINTMENT\n2.VIEW YOUR PROFILE\n3.EDIT YOUR PROFILE\n4.LOG OUT\n");
       scanf("%d",&c);
       switch(c)
       {
	   case 1:
	       scr();
	       patdisplay(p);
	       get_time(p.visit);
	       printf("\n\nToday's date:%s",p.visit);
	       printf("\nEnter the date for appointment(dd/mm/yyyy)(pl.give space after each entry):-");
	       scanf(" %d %d %d",&day,&month,&year);
	       time_t T=time(NULL);
	       struct tm *t=localtime(&T);
	       if((t->tm_year+1900)>year)
		   printf("wrong entry..");
	       else if((t->tm_year+1900==year)&&t->tm_mon+1>month)
		   printf("wrong entry..");
	       else if((t->tm_year+1900==year)&&(t->tm_mon+1==month)&&(t->tm_mday>day))
		   printf("wrong entry..");
	       getchar();
	       getchar();
	       return 0;
	       strcat(date,itoa(day));
	       strcat(date,"/");
	       strcat(date,itoa(month));
	       strcat(date,"/");
	       strcat(date,itoa(year));
	       strcat(date,"\0");
	       printf("\nYour date of appointment is:%s",date);
	       getchar();
    	       getchar();
	       goto first;
	       break;
	   case 2:
	       scr();
	       pdisplay(p);
	       getchar();
	       break;
	   case 3:
	       getchar();
	       p=pchange(p);
	       fseek(f,0,0);
	       fwrite(&p,sizeof(p),1,f);
	       scr();
	       pdisplay(p);
	       printf("\n\nChanged successfully\n");
	       goto first;
	       break;
	   case 4:
 	       fclose(f);
	       return 0;
	   default:
	       printf("Invalid input.Please enter once again.");
	       goto first;
       }
}
////////////////////////////////////////////////////////////////////////////////////////////////
int doclog(long int UID)
{
    int c;
    long int p;
    doctor d;
    FILE * f1;
    char s[30]="./doctors_file/";
    strcat(s,itoa(UID));
    f1=fopen(s,"rb+");
    if(f1==NULL)
       {
	    printf("Data file not found.check your UID and enter again.");
	     getchar();
	    return 0;
       }
    fseek(f1,0,0);
    fread(&d,sizeof(d),1,f1);
    printf("\n\t\t\t");
first:    
    scr();
    docdisplay(d);
    printf("\n\n1.PATIENT'S RECORDS\n2.VIEW YOUR PROFILE\n3.EDIT YOUR PROFILE\n4.LOG OUT\n");
       scanf("%d",&c);
       switch(c)
        {
	  case 1:
	      scr();
	      printf("\n");
	      view_and_add_to_the_patient_records();
	      getchar();
	      goto first;
	       break;
	  case 2:
	       scr();
	       ddisplay(d);
	       getchar();
	       getchar();
	       goto first;
	       break;
	  case 3:
		   getchar();
		   d=dchange(d);
		   fseek(f1,0,0);
		   fwrite(&d,sizeof(d),1,f1);
		   scr();
		   ddisplay(d);
		   printf("\n\nChanged successfully\n");
		   goto first;
		   break;
	  case 4:
	       fclose(f1);
	       return 0;
	  default:
	       printf("Invalid input.Please check and enter once again");
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
void scr()
{
    system("clear");
    printf("\n\t\t\tSAI KRIPA HOSPITALS,WHITEFIELD,BANGALORE.");
    printf("\n\t\t\t--- ----- --------- ---------- ----------\n\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////
void get_time(char * date)
{
    date[0]='\0';
    time_t T=time(NULL);
    struct tm *t=localtime(&T);
    strcat(date,itoa(t->tm_mday));
    strcat(date,"/");
    strcat(date,itoa(t->tm_mon+1));
    strcat(date,"/");
    strcat(date,itoa(t->tm_year+1900));
    strcat(date,"\0");
}
////////////////////////////////////////////////////////////////////////////////////////////////
char * itoa(long int a)
{
    char *s;
    int i=-1;
    long int t=a;
    while(t!=0)
    {
	t=t/10;
	i++;
    }
    if(i==-1)
    {
	s=(char *)malloc(2);
	s[0]='0';
	s[1]='\0';
	return s;
    }
    s=(char*)malloc(i+1);
    s[i+1]='\0';
    while(a!=0)
    {
	t=a%10;
	a=a/10;
	s[i]=t+48;
        i--;
    }
    return s;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void infrastructure(char * dep )
{
    FILE *p;
    infra t;
    int a;
    p=fopen("infra.dat","rb+");
    if(p==NULL)
    {
	printf("File cannot be opened\n");
	return;
    }
    while(!feof(p))
    {
	fread(&t,sizeof(t),1,p);
	if(!strcmp(t.dep,dep))
	{
	    printf("Room no:%d\n",t.room_no);
	    printf("Department:");puts(t.dep);
	    printf("Equipments:");puts(t.equipments);
  break;
	}
    }
    if(feof(p))
	printf("Records not found");
    fclose(p);
}
////////////////////////////////////////////////////////////////////////////////////////////////
employee echange(employee p)
{
    int c;
    printf("\n1.ADDRESS\n2.EMAIL\n3.PHONE NUMBER\n");
    scanf("%d",&c);
    switch(c)
    {
	case 1:
	    getchar();
	    printf("Enter your new address:");gets(p.address);
	    printf("City:");gets(p.city);
	    printf("State:");gets(p.state);
	    return p;
	    break;
	case 2:
	    printf("Enter your new email:");scanf("%s",p.email);
	    return p;
	    break;
	case 3:
	    printf("Enter your new phone number:");scanf("%s",p.phoneno);
	    return p;
	    break;
	default:
	    printf("Wrong entry!!!");
	    return p;
	    break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
patient pchange(patient q)
{
    int d;
third:    printf("\n1.PHONE NUMBER\n2.EMAIL\n3.ADDRESS\n4.CITY\n5.STATE\n6.GO BACK\n");
    scanf("%d",&d);
    switch(d)
      {
	case 1:
		getchar();
		printf("Enter your new phone number:");gets(q.phoneno);
		return q;
		break;
	case 2:
		getchar();
		printf("Enter your new email:");gets(q.email);
		return q;
                break;
	case 3:
		getchar();
		printf("Enter your new address:");gets(q.address);
		return q;
		break;
	case 4:
		getchar();
		printf("Enter your new city:");gets(q.city);
		return q;
		break;
	case 5:
		getchar();
		printf("Enter your new state:");gets(q.state);
		return q;
		break;
	case 6:
		return q;
		break;
	default:
		printf("Invalid input.Please enter once again.\n");
		goto third;
		return q;
      }
}
////////////////////////////////////////////////////////////////////////////////////////////////
doctor dchange(doctor d)
{
    int c;
    scr();
fourth:	   printf("1.PHONE NUMBER\n2.EMAIL\n3.ADDRESS\n4.CITY\n5.STATE\n6.SALARY\n7.GO BACK\n");
    scanf("%d",&c);
    switch(c)
      {
	case 1:
		getchar();
		printf("Enter your new phone number:");gets(d.phoneno);
		return d;
		break;
	case 2:
		getchar();
		printf("Enter your new email:");gets(d.email);
		return d;
                break;
	case 3:
		getchar();
		printf("Enter your new address:");gets(d.address);
		return d;
		break;
	case 4:
		getchar();
		printf("Enter your new city:");gets(d.city);
		return d;
		break;
	case 5:
		getchar();
		printf("Enter your new state:");gets(d.state);
		return d;
		break;
	case 6:
		getchar();
		printf("Enter your new salary:");gets(d.salary);
		return d;
		break;
	case 7:
		return d;
		break;
	default:
		printf("Invalid input.Please enter once again.");
		goto fourth;
		return d;
      }
}
/////////////////////////////////////////////////////////////////////////////////////////////
int Emp_rec()
{
    FILE * f;
    employee e;
    getchar();
    printf("UID:");scanf("%ld",&e.UID);
    getchar();
    printf("Name:");gets(e.name);
    printf("Age:");scanf("%d",&e.age);
    getchar();
    printf("Gender:");scanf("%c",&e.gender);
    getchar();    
    printf("Aadhar number:");gets(e.aadhar_no);
    printf("Phone number:");scanf("%s",e.phoneno);
    getchar();
    printf("Address:");gets(e.address);
    printf("City:");gets(e.city);
    printf("State:");gets(e.state);
    printf("Email:");scanf("%s",e.email);
    getchar();
    printf("Salary:");gets(e.salary);
    printf("Department:");scanf("%s",e.department);
    printf("\n\n\n");
    ////////////////////////////////////////////////
    char l[30]="employees_file/\0";
    strcat(l,itoa(e.UID));
    f=fopen(l,"wb+");
    if(f==NULL)
    {
	printf("File cannot be opened");
	return 1;
    }
    fwrite(&e,sizeof(e),1,f);
    fclose(f);
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////
int Pat_rec()
{
    FILE *f;
    patient p;
    getchar();
    printf("UID:");scanf("%ld",&p.UID);
    getchar();
    printf("Name:");gets(p.name);
    printf("Age:");scanf("%d",&p.age);
    getchar();
    printf("Gender:");scanf("%c",&p.gender);
    getchar();
    printf("Aadhar number:");gets(p.aadhar_no);
    printf("Phone number:");scanf("%s",p.phoneno);
    getchar();
    printf("Address:");gets(p.address);
    printf("City:");gets(p.city);
    printf("State:");gets(p.state);
    printf("Email:");scanf("%s",p.email);
    p.observations[0]='\0';
    p.diagnosis[0]='\0';
    p.medication[0]='\0';
    p.visit[0]='\0';
    time_t T=time(NULL);
    struct tm *t=localtime(&T);
    strcat(p.visit,itoa(t->tm_mday));
    strcat(p.visit,"/");
    strcat(p.visit,itoa(t->tm_mon+1));
    strcat(p.visit,"/");
    strcat(p.visit,itoa(t->tm_year+1900));
    strcat(p.visit,"\0");
    p.suggestions[0]='\0';
    p.doctor[0]='\0';
    p.department[0]='\0';
    char s[30]="patients_file/\0";
    strcat(s,itoa(p.UID));
    f=fopen(s,"wb+");
    if(f==NULL)
    {
	printf("File cannot be opened");
	return 1;
    }
    fwrite(&p,sizeof(p),1,f);
    fclose(f);
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////
int Doc_rec()
{
    FILE *f;
    doctor d;
    printf("UID:");scanf("%ld",&d.UID);
    getchar();
    printf("Name:");gets(d.name);
    printf("Age:");scanf("%d",&d.age);
    getchar();
    printf("Gender:");scanf("%c",&d.gender);
    getchar();
    printf("Aadhar number:");gets(d.aadhar_no);
    printf("Phone number:");gets(d.phoneno);
    printf("Address:");gets(d.address);
    printf("City:");gets(d.city);
    printf("State:");gets(d.state);
    printf("Email:");gets(d.email);
    printf("Department:");gets(d.department);
    printf("Salary:");gets(d.salary);
    printf("Available on:");gets(d.avail);
    ////////////////////////////////////////
    char s[30]="doctors_file/\0";
    strcat(s,itoa(d.UID));
    f=fopen(s,"wb+");
    if(f==NULL)
    {
	printf("File cannot be opened");
	return 1;
    }
    fwrite(&d,sizeof(d),1,f);
    fseek(f,0,0);
    fread(&d,sizeof(d),1,f);
    fclose(f);
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void edisplay(employee  e)
{
printf("UID:%ld\n",e.UID);
printf("\t\t\tName:");puts(e.name);
printf("Age:%d\t",e.age);
printf("Gender:%c\t",e.gender);
printf("Aadhar number:%s\t",e.aadhar_no);
printf("Phone number:%s\t",e.phoneno);
printf("Salary:");puts(e.salary);
printf("Email:%s\t",e.email);
printf("Department:%s\n",e.department);
printf("Address:");puts(e.address);
printf("City:");puts(e.city);
printf("State:");puts(e.state);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void pdisplay(patient q)
{
    printf("UID:%ld\n",q.UID);
    printf("\t\t\tName:"); puts(q.name);
    printf("Age:%d",q.age);
    printf("Gender:%c",q.gender);
    printf("Aadhar number:%s",q.aadhar_no);
    printf("Phone number:%s",q.phoneno);
    printf("Email:%s",q.email);
    printf("Address:");puts(q.address);
    printf("City:");puts(q.city);
    printf("State:");puts(q.state);
    printf("Observations:");puts(q.observations);
    printf("Diagnosis:");puts(q.diagnosis);
    printf("Medication:");puts(q.medication);
    printf("Visited on:");puts(q.visit);
    printf("Suggestions:");puts(q.suggestions);
    printf("Suggested by:");puts(q.doctor);
    printf("Department:");puts(q.department);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void ddisplay(doctor d)
{
    printf("UID:%ld",d.UID);
    printf("\t\t\tName:"); puts(d.name);
    printf("Age:%d\t",d.age);
    printf("Gender:%c\t",d.gender);
    printf("Aadhar number:%s",d.aadhar_no);
    printf("Phone number:%s",d.phoneno);
    printf("Email:%s",d.email);
    printf("Address:");puts(d.address);
    printf("City:");puts(d.city);
    printf("State:");puts(d.state);
    printf("Department:");puts(d.department);
    printf("Salary:");puts(d.salary);
    printf("Available on:");puts(d.avail);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void docdisplay(doctor d)
{
    printf("UID:%ld\n",d.UID);
    printf("Name:"); puts(d.name);
    printf("Age:%d",d.age);
    printf("\tGender:%c",d.gender);
    printf("\tDepartment:");puts(d.department);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void empdisplay(employee e)
{
    printf("UID:%ld\n",e.UID);
    printf("Name:"); puts(e.name);
    printf("Age:%d",e.age);
    printf("\tGender:%c",e.gender);
    printf("\tDepartment:%s\n",e.department);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void patdisplay(patient p)
{
    printf("UID:%ld\n",p.UID);
    printf("Name:"); puts(p.name);
    printf("Age:%d",p.age);
    printf("\tGender:%c",p.gender);
}
////////////////////////////////////////////////////////////////////////////////////////////////
void view_and_add_to_the_patient_records(){}
////////////////////////////////////////////////////////////////////////////////////////////////
int isleapyear(int y)
{
    return (y%400==0)||((y%4==0)&&(y%100!=0));
}
//////////////////////////////////////////////////////////////////////////////////////////////
int checkdate(int d,int m,int y)
{
    int daysinmonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (d<1||m<1||y<1)
        return 0;
    if (isleapyear(y))
        daysinmonth[2]=29;
    if (1<=m||m<=12)
    {
        if (d<=daysinmonth[m])
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

