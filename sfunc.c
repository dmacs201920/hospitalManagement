#include"skheader.h"
int admlog(char pass[])
{
    scr();
    char p[20]="sreeabhi",c2;
    int c,c1,c3;
    char es[30]="./employees_file/";
    employee e,ep;
    doctor d,dp;
    FILE *f,*ef;
    long int ek;
    
    if(strcmp(p,pass))
    { 
	printf("Check the password and login again...");
	return 0;
    }
    printf("Logged in successfully..\t");
    while(1)
    {
    	printf("Home/Admin/");
    	scr();
    	printf("1.NEW EMPLOYEE\n2.NEW DOCTOR\n3.INFRASTRUCTURE\n4.STAFF\n5.DEPARTMENT\n6.LOG OUT\n");
    	c=getch()-48;
	switch(c)
    	{
    	    case 1:
    		printf("Home/Admin/New Employee");
    		scr();	    
    		printf("Enter the data of new employee:\n");
    		Emp_rec();
    		printf("Added Successfully...");
    		continue;
    	    case 2:
    		printf("Home/Admin/New Doctor");
    		scr();
    		printf("Enter the data of new doctor:\n");
    		Doc_rec();
    		printf("Added Successfully...");
    		continue;
	
    	    case 3:
    		while(1)
    		{
    		    printf("Home/Admin/Infrastructure");
    		    scr();
    		    printf("1.ADD NEW INFRASTRUCTURE..\n");
    		    printf("2.SEE THE AVAILABLE INFRASTRUCTURE\n");
    		    printf("3.GO BACK\n");
    		    c1=getch()-48;
    		    switch(c1)
    		    {
    			case 1:
    			    if(add_inf())
    				printf("Successfully added");
    			    else
    				printf("not added");
    			    continue;
    			case 2:
    			    infdisplay();
    			    continue;
    			case 3:
    			    break;		
    			default:
    			    printf("Invalid input.Please check and enter once again");
    			    continue;
    		    }
    		    break;
		}
		continue;
	    case 4:
		staff();
		continue;
	    case 5:
		printf("Home/Admin/New Department");
		scr();
		printf("Enter the data of new department:\n");
		Dep_rec();
		continue;
	    case 6:
		return 0;
	    default:
		printf("wrong entry...check and enter the input correctly..");
		break;    
	}
	break;    
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
	return 0;
    }
    fseek(emp,0,0);
    fread(&p,sizeof(p),1,emp);
    printf("Home/Employee/");
    scr();   
    empdisplay(p);
    while(1)
    {
	if(!strcmp(p.department,"Reception"))
	    printf("\n0.NEW PATIENT\n1.VIEW YOUR PROFILE\n2.EDIT YOUR PROFILE\n3.INFRASTRUCTURE\n4.LOG OUT\n");
        else if(!strcmp(p.department,"Pharmacy"))
        {
         	printf("\n0.MEDICINE\n1.VIEW YOUR PROFILE\n2.EDIT YOUR PROFILE\n4.LOG OUT\n");
        }

    	else
	    printf("\n1.VIEW YOUR PROFILE\n2.EDIT YOUR PROFILE\n3.INFRASTRUCTURE\n4.LOG OUT\n");
	c2=getch()-48;
	switch(c2)
	{
	    case 1:
		scr();
		edisplay(p);
		continue;
	    case 2:
		p=echange(p);
		fseek(emp,0,0);
		fwrite(&p,sizeof(p),1,emp);
		scr();
		edisplay(p);
		printf("\n\n");
		printf("Changed successfully");
		continue;
	    case 3:
		scr();
		empdisplay(p);
		printf("\n");
		infrastructure(p.department);
		continue;
	    case 4:
		fclose(emp);
		return 0;
	    case 0:
		if(!strcmp(p.department,"Reception"))
		{
		    Pat_rec();
		    getch();
		    fclose(emp);
		    return 0;
                }
		else if(!strcmp(p.department,"Pharmacy"))
		{
		    Med_rec();
		    getchar();
		    fclose(emp);
		    break;
		}

	
	    default:
		scr();   
		printf("Wrong entry!!!Enter the given options only!!!\n");
		empdisplay(p);
		continue;
	    }
   }
    fclose(emp);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int patlog(long int UID)
{
    int choice,day,month,year,d;
    char date[15];
    date[0]='\0';
    patient p;
    FILE * f;
    char app[30];
    char s[30]="./patients_file/";
    strcat(s,itoa(UID));
    f=fopen(s,"rb+");
    puts(s);
    puts(itoa(UID));
    getchar();
    if(f==NULL)
    {
	printf("\nFile cannot be opened\n");
	getchar();
	return 0;
    }
    fseek(f,0,0);
    fread(&p,sizeof(p),1,f);
    patdisplay(p);
    while(1){
	printf("\n\n\n1.BOOK AN APPOINTMENT\n2.VIEW YOUR APPOINTMENTS\n3.VIEW YOUR PROFILE\n4.EDIT YOUR PROFILE\n5.LOG OUT\n");
	choice=getch()-48;
	switch(choice)
	{
	    case 1:
		while(1){
		    scr();
		    get_time(p.visit);
		    printf("Today's date:%s\n",p.visit);
		    printf("Please give space after each entry\n");
		    printf("Enter the (dd/mm/yyyy) on which you want to book an appointment:");
		    scanf(" %d %d %d",&day,&month,&year);
		    if(!checkdate(day,month,year))
		    {
			printf("You have entered wrong date...please check and enter again...\n");
			getch();
			continue;
		    }
		    time_t T=time(NULL);
		    struct tm*t=localtime(&T);
		    if(year<t->tm_year+1900||month<t->tm_mon+1||day<t->tm_mday)
		    {
			printf("You have entered wrong date....please check and enter again..\n");
			getch();
			continue;
		    }
		    strcat(date,itoa(day));
		    strcat(date,"-");
		    strcat(date,itoa(month));
		    strcat(date,"-");
		    strcat(date,itoa(year));
		    strcat(date,"\0");
		    fseek(f,0,2);
		    fputs(date,f);
		    fputc('\t',f);
		    fputs(p.department,f);
		    fputc('\n',f);
		    printf("\nYou have booked an appointment on:");puts(date);
		    continue;
		}
		break;
	    case 2:
		fseek(f,sizeof(p),0);
		printf("Your booked appointments on:-");
		app[0]=fgetc(f);
		while(!feof(f))
		{
		    printf("%c",app[0]);
		    app[0]=fgetc(f);
		}
		continue;
	    case 3:
		scr();
		pdisplay(p);
		getchar();
		continue;
	    case 4:
		getchar();
		p=pchange(p);
		getchar();
		fseek(f,0,0);
		fwrite(&p,sizeof(p),1,f);
		scr();
		pdisplay(p);
		printf("\n\nChanged successfully\n");
		continue;
	    case 5:
		fclose(f);
		return 0;
	    default:
		printf("\nInvalid input.Please enter once again.\n");
		continue;
	}
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int doclog(long int UID)
{
    int c;
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
    scr();
    docdisplay(d);
    while(1){
    	printf("\n\n1.PATIENT'S RECORDS\n2.VIEW YOUR PROFILE\n3.EDIT YOUR PROFILE\n4.LOG OUT\n");
 	c=getch()-48;
 	switch(c)
	{
  	    case 1:
  		scr();
  		printf("\n");
  		view_and_add_to_the_patient_records();
  		getch();
  		continue;
  	    case 2:
		scr();
 		ddisplay(d);
 		continue;
  	    case 3:
		getchar();
		d=dchange(d);
		fseek(f1,0,0);
		fwrite(&d,sizeof(d),1,f1);
		scr();
		ddisplay(d);
		printf("\n\nChanged successfully\n");
		continue;
  	    case 4:
 		fclose(f1);
 		return 0;
  	    default:
 		printf("Invalid input.Please check and enter once again");
	}
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void scr()
{
    system("clear");
    printf("\n\t\t\tSAI KRIPA HOSPITALS,WHITEFIELD,BANGALORE.");
    printf("\n\t\t\t--- ----- --------- ---------- ----------\n\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
employee echange(employee e)
{
    int c;
    printf("\n1.ADDRESS\n2.EMAIL\n3.PHONE NUMBER\n");
    c=getch()-48;
    switch(c)
    {
	case 1:
	    printf("Enter your new address:");gets(e.address);
	    printf("City:");gets(e.city);
	    printf("State:");gets(e.state);
	    return e;
	case 2:
	    printf("Enter your new email:");scanf("%s",e.email);
	    return e;
	case 3:
	    printf("Enter your new phone number:");scanf("%s",e.phoneno);
	    return e;
	default:
	    printf("Wrong entry!!!");
	    scr();
	    empdisplay(e);
	    e=echange(e);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
patient pchange(patient p)
{
    int d;
    printf("\n1.PHONE NUMBER\n2.EMAIL\n3.ADDRESS\n4.GO BACK\n");
    d=getch()-48;
    switch(d)
      {
	case 1:
		printf("Enter your new phone number:");gets(p.phoneno);
		return p;
	case 2:
		printf("Enter your new email:");gets(p.email);
		return p;
	case 3:
		printf("Enter your new address:");gets(p.address);
		printf("Enter your new city:");gets(p.city);
		printf("Enter your new state:");gets(p.state);
		return p;
	case 4:
		return p;
	default:
		printf("Invalid input.Please enter once again.\n");
		scr();
		patdisplay(p);
		p=pchange(p);
		return p;
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
doctor dchange(doctor d)
{
    int c;
    scr();
    printf("1.PHONE NUMBER\n2.EMAIL\n3.ADDRESS\n4.GO BACK\n");
    c=getch()-48;
    switch(c)
      {
	case 1:
		printf("Enter your new phone number:");gets(d.phoneno);
		return d;
	case 2:
		printf("Enter your new email:");gets(d.email);
		return d;
	case 3:
		printf("Enter your new address:");gets(d.address);
		printf("Enter your new city:");gets(d.city);
		printf("Enter your new state:");gets(d.state);
		return d;
	case 4:
		return d;
	default:
		printf("Invalid input.Please enter once again.");
		scr();
		docdisplay(d);
		d=dchange(d);
		return d;
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int Emp_rec()
{
    FILE * f;
    employee e;
    getch();
    printf("UID:");scanf("%ld",&e.UID);
    getch();
    printf("Name:");gets(e.name);
    printf("Age:");scanf("%d",&e.age);
    getch();
    printf("Gender:");scanf("%c",&e.gender);
    getch();    
    printf("Aadhar number:");gets(e.aadhar_no);
    printf("Phone number:");scanf("%s",e.phoneno);
    getch();
    printf("Address:");gets(e.address);
    printf("City:");gets(e.city);
    printf("State:");gets(e.state);
    printf("Email:");scanf("%s",e.email);
    getch();
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
int Doc_rec()
{
    FILE *f;
    doctor d;
    printf("UID:");scanf("%ld",&d.UID);
    getch();
    printf("Name:");gets(d.name);
    printf("Age:");scanf("%d",&d.age);
    getch();
    printf("Gender:");scanf("%c",&d.gender);
    getch();
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
void edisplay(employee  e)
{
    printf("UID:%ld\t",e.UID);
    printf("Name:");puts(e.name);
    printf("\nAge:%d\t",e.age);
    printf("Gender:%c  ",e.gender);
    printf("Aadhar number:%s\t",e.aadhar_no);
    printf("Phone number:%s\n",e.phoneno);
    printf("Salary:%s\t",e.salary);
    printf("Email:%s\t",e.email);
    printf("Department:%s\n",e.department);
    printf("Address:");puts(e.address);
    printf("City:");puts(e.city);
    printf("State:");puts(e.state);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void pdisplay(patient q)
{
    printf("UID:%ld\n",q.UID);
    printf("Name:"); puts(q.name);
    printf("Age:%d  ",q.age);
    printf("Gender:%c  ",q.gender);
    printf("Aadhar number:%s\t  ",q.aadhar_no);
    printf("Phone number:%s  ",q.phoneno);
    printf("Email:%s\n",q.email);
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
void ddisplay(doctor d)
{
    printf("UID:%ld\t",d.UID);
    printf("Name:"); puts(d.name);
    printf("Age:%d\t",d.age);
    printf("Gender:%c  ",d.gender);
    printf("Aadhar number:%s  ",d.aadhar_no);
    printf("Phone number:%s  ",d.phoneno);
    printf("Email:%s\n",d.email);
    printf("Address:");puts(d.address);
    printf("City:");puts(d.city);
    printf("State:");puts(d.state);
    printf("Department:");puts(d.department);
    printf("Salary:");puts(d.salary);
    printf("Available on:");puts(d.avail);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void docdisplay(doctor d)
{
    printf("UID:%ld\t",d.UID);
    printf("Name:"); puts(d.name);
    printf("Age:%d",d.age);
    printf("\tGender:%c",d.gender);
    printf("\tDepartment:");puts(d.department);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void empdisplay(employee e)
{
    printf("UID:%ld\t",e.UID);
    printf("Name:"); puts(e.name);
    printf("\nAge:%d\t",e.age);
    printf("\tGender:%c",e.gender);
    printf("\tDepartment:%s\n",e.department);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void patdisplay(patient p)
{
    printf("UID:%ld\t",p.UID);
    printf("Name:"); puts(p.name);
    printf("Age:%d  ",p.age);
    printf("Gender:%c  ",p.gender);
    printf("Department:");
    puts(p.department);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void view_and_add_to_the_patient_records()
{
    /**/
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int isleapyear(int y)
{
    return (y%400==0)||((y%4==0)&&(y%100!=0));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////
int getch()
{
    struct termios oldtc, newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
   ch=getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
   return ch;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
ssize_t getpasswd (char **pw, size_t sz, int mask, FILE *fp)
{
    if (!pw || !sz || !fp) return -1;       /* validate input   */
#ifdef MAXPW
    if (sz > MAXPW) sz = MAXPW;
#endif

    if (*pw == NULL) {              /* reallocate if no address */
        void *tmp = realloc (*pw, sz * sizeof **pw);
        if (!tmp)
            return -1;
        memset (tmp, 0, sz);    /* initialize memory to 0   */
        *pw =  (char*) tmp;
    }

    size_t idx = 0;         /* index, number of chars in read   */
    int c = 0;

    struct termios old_kbd_mode;    /* orig keyboard settings   */
    struct termios new_kbd_mode;

    if (tcgetattr (0, &old_kbd_mode)) { /* save orig settings   */
        fprintf (stderr, "%s() error: tcgetattr failed.\n", __func__);
        return -1;
    }   /* copy old to new */
    memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

    new_kbd_mode.c_lflag &= ~(ICANON | ECHO);  /* new kbd flags */
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    if (tcsetattr (0, TCSANOW, &new_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    /* read chars from fp, mask if valid char specified */
    while (((c = fgetc (fp)) != '\n' && c != EOF && idx < sz - 1) ||
            (idx == sz - 1 && c == 127))
    {
        if (c != 127) {
            if (31 < mask && mask < 127)    /* valid ascii char */
                fputc (mask, stdout);
            (*pw)[idx++] = c;
        }
        else if (idx > 0) {         /* handle backspace (del)   */
            if (31 < mask && mask < 127) {
                fputc (0x8, stdout);
                fputc (' ', stdout);
                fputc (0x8, stdout);
            }
            (*pw)[--idx] = 0;
        }
    }
    (*pw)[idx] = 0; /* null-terminate   */

    /* reset original keyboard  */
    if (tcsetattr (0, TCSANOW, &old_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    if (idx == sz - 1 && c != '\n') /* warn if pw truncated */
        fprintf (stderr, " (%s() warning: truncated at %zu chars.)\n",
                __func__, sz - 1);

    return idx; /* number of chars in passwd    */
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int add_inf()
{
    infra s,t;
    FILE *f;
    f=fopen("infra.dat","rb+");
    if(f==NULL)
    {
	printf("Overload");
	return 0;
    }
    printf("Department:");gets(t.dep);
    printf("Room no:");scanf("%d",&t.room_no);
    getch();
    printf("Equipments:");gets(t.equipments);
    while(!feof(f))
    {
	fread(&s,sizeof(s),1,f);
	if(!strcmp(s.dep,t.dep)||s.room_no==t.room_no)
	{
	    strcpy(s.dep,t.dep);
	    s.room_no=t.room_no;
	    strcat(s.equipments,",");
	    strcat(s.equipments,t.equipments);
	    break;
	}
    }
    if(!feof(f))
    {
	fseek(f,-sizeof(s),1);
    	fwrite(&s,sizeof(s),1,f);
    	fclose(f);
	return 1;
    }
    else
    {
	fseek(f,0,2);
	fwrite(&t,sizeof(t),1,f);
    	fclose(f);
	return 1;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void infdisplay()
{
    FILE *f;
    infra t;
    f=fopen("infra.dat","rb+");
    if(f==NULL)
    {
	printf("Problem in opening the file\n");
	return;
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
    printf("Enter any character to go back....");
    getch();
    fclose(f);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void staff()
{
    int c,k;
    char s[30];
    FILE *f;
    employee e;
    doctor d;

    scr();
    printf("\n1.EMPLOYEES\n2.DOCTORS\n3.GO BACK\n");
    c=getch()-48;
    switch(c)
    {
	case 1:
	    for(k=0;k<200000;k++)
	    {
		strcpy(s,"./employees_file/");
		strcat(s,itoa(k));
		f=fopen(s,"rb+");
		if(f==NULL)
		    continue;
		fseek(f,0,0);
		fread(&e,sizeof(e),1,f);
		empdisplay(e);
		printf("\n\n");
		fclose(f);
	    }
	    printf("press any key to go back!!!\n");

	    getch();
	    break;
	case 2:
	    for(k=0;k<200000;k++)
	    {
		strcpy(s,"./doctors_file/");
		strcat(s,itoa(k));
		f=fopen(s,"rb+");
		if(f==NULL)
		    continue;
		fseek(f,0,0);
		fread(&d,sizeof(d),1,f);
		docdisplay(d);
		printf("\n\n");
		fclose(f);
	    }
	    printf("press any key to go back!!!\n");
	    getch();
		    return;
		case 3:
		    return;
		default:
		    printf("wrong entry...");
		    staff();

	    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
int Med_rec()
{
    FILE * f;
    medicine m,p,q;
    int choice;
    scr();
    while(1)
    {
	scr();
	printf("\n\n1.NEW MEDICINE\n2.AVAILABLE MEDICINES\n3.EXISTING MEDICINE\n4.EXIT\n");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		scr();
		printf("Enter the new medicine:");
		scanf("%s",m.name);
		printf("Enter the medicine code:");
		scanf("%s",m.code);
		printf("Enter the quantity:");
		scanf("%d",&m.quantity);
		printf("Enter the cost:Rs ");
		scanf("%f",&m.cost);
		f=fopen("medicines.dat","ab+");
		if(med_search(m.code,f)==0)
		{
		    fseek(f,0,2);
		    fwrite(&m,sizeof(m),1,f);
		    printf("\nSuccessfully added\n");
		}
		else
		    printf("\nThis medicine already exists\n");
		fclose(f);
		break;
	    case 2:
		f=fopen("medicines.dat","rb");
		fseek(f,0,0);
		scr();
		printf("\t\tMEDICINE\tCODE\tQUANTITY\tCOST\t\n");
		printf("\t\t--------\t----\t--------\t----\t\n");
		fread(&p,sizeof(p),1,f);
		while(!feof(f))
		{

		    printf("\t\t%s\t%s\t%d\t%f\n",p.name,p.code,p.quantity,p.cost);
		    fread(&p,sizeof(p),1,f);
		}
		getchar();
		printf("\nPress any character to go back\n");
		getchar();
		fclose(f);
		break;
	    case 3:
		scr();
		printf("Enter the medicine code:");
		scanf("%s",m.code);
		printf("Enter the quantity you want to add:");
		scanf("%d",&q.quantity);
		f=fopen("medicines.dat","ab+");
		fseek(f,0,0);
		while(!feof(f))
		{
		    fread(&m,sizeof(m),1,f);
		    if(strcmp(q.code,m.code)==0)
		    {
			printf("Came inside\n");
			getchar();
			m.quantity+=q.quantity;
			fseek(f,-sizeof(m),1);
			fwrite(&m,sizeof(m),1,f);
		    }
		    printf("\nSuccesfully added\n");
		}
		fclose(f);
		break;
	    case 4:
		exit(0);
		break;
	    default:
		printf("Invalid input.Please check and enter once again\n");
		break;
	}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
int Dep_rec()
{
    dept d;
    int choice;
    FILE * f;
    char c,p[1000];
    char s[45]="departments_file/file\0";
first:scr(); 
    printf("\n1.ADD NEW DEPARTMENT\n2.SEE THE AVAILABLE DEPARTMENTS\n3.GO BACK\n");
    scanf("%d",&choice);
    switch(choice)
    {
	case 1:
	    printf("\nEnter the department:");
	    scanf("%s",d.dep);
	    printf("Enter the room no:");
	    scanf("%d",&d.room);
	    f=fopen(s,"ab+");
	    if(search(d.dep,d.room,f)==0)
	    {
		fprintf(f,"%s\n",d.dep);
		printf("\nSuccessfully added\n");
	    }
	    else
		printf("\nThis department already exists or this room no is already allotted to                         some other department.So please check....\n");
	    fclose(f);
	    goto first;
	    break;
	case 2:
	    f=fopen(s,"rb");
	    fseek(f,0,0);
	    scr();
	    printf("\t\tDEPARTMENTS\tROOM NO\n");
	    printf("\t\t-----------\t-------\n");
	    fgets(p,sizeof(d),f);
	    while(!feof(f))
	    {
		fprintf(stdout,"\t\t%s",p);
		fgets(p,sizeof(d),f);
	    }
	    getchar();
	    printf("\nEnter any charcter to go back\n");
	    getchar();
	    fclose(f);
	    goto first;
	    break;
	case 3:
	    return 0; 
	    break;
	default:
	    printf("\nInvalid input.Please check and enter once again\n");
	    break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int search(char s[],int r,FILE *f)
{
    char p[45];
    strcat(s,"\t  ");
    strcat(s,itoa(r));
    while(!feof(f))
    {
	fscanf(f,"%s",p);
	if(strcmp(s,p)==0)
	    return 1;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
int med_search(char s[],FILE *f)
{
    medicine q;
    while(!feof(f))
    {
	fread(&q,sizeof(q),1,f);
	if(strcmp(s,q.code)==0)
	    return 1;
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
