                       SAI KRIPA HOSPITAL,WHITEFIELD,BANGLORE
		       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
HEADER FILES THAT I HAVE INCLUDED ARE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stdio.h,string.h,stdlib.h,termios.h,unistd.h,time.h,skheader.

defined MAXPW as 32.

THERE ARE SOME STRUCTURES THAT I HAVE DEFINED
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct employee
{
    long int UID;
    char name[100];
    char gender;
    int age;
    char aadhar_no[15];
    char phoneno[15];
    char address[150];
    char city[20];
    char state[20];
    char email[50];
    char salary[15];//per month
    char department[30];
    
}employee;
typedef struct patient
{
    long int UID;
    char name[100];
    int age;
    char gender;
    char aadhar_no[16];
    char phoneno[15];
    
    char address[150];
    char city[20];
    char state[20];
    char email[50];
    
    char observations[300];
    char diagnosis[150];
    char medication[150];
    char visit[15];
    char suggestions[300];
    char doctor[50];
    char department[30];
}patient;
typedef struct doctor
{
    long int UID;
    char name[100];
    int age;
    char gender;
    char aadhar_no[15];
    char phoneno[15];
    
    char address[150];
    char city[20];
    char state[20];
    char email[50];

    char department[30];
    char salary[15];
    char avail[100];
}doctor;
typedef struct infra
{
    int room_no;
    char dep[30];
    char equipments[200];
}infra;
typedef struct dept
{

}dept;


FUNCTIONS THAT I HAVE DEFINED ARE............
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

01.void scr(void);
02.char * itoa(long int);
03.void infrastructure(char *);
04.void get_time(char *);
05.int admlog(char[]);
06.int emplog(long int);
07.int doclog(long int);
08.int patlog(long int);
09.void empdisplay(employee);
10.void docdisplay(doctor);
11.void patdisplay(patient);
12.void edisplay(employee);
13.void pdisplay(patient);
14.void ddisplay(doctor);
15.void edisplay(employee);
16.void pdisplay(patient);
17.void ddisplay(doctor);
18.employee echange(employee);
19.patient pchange(patient);
20.doctor dchange(doctor);
21.int Emp_rec(void);
22.int Pat_rec(void);
23.int Doc_rec(void);
24.void view_and_add_to_the_patient_records(void);
26.int checkdate(int,int,int);
27.int getch();
28.ssize_t getpasswd (char **, size_t, int, FILE *);
29.int add_inf();
30.void infdisplay();
31.void staff();

