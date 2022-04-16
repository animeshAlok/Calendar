#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

//For changing color of the fonts
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[33m"

//For finding first day of the month.
int startingday(int year,int month){
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    year -= month < 3; 
    return ( year + year/4 - year/100 + year/400 + t[month-1] + 1) % 7;
}

//Will return total number of days in a month
int mounth(int month){
    switch(month){
        case 1:
            return(31);
        case 2:
            return(28);
        case 3:
            return(31);
        case 4:
            return(30);
        case 5:
            return(31);
        case 6:
            return(30);
        case 7:
            return(31);
        case 8:
            return(31);
        case 9:
            return(30);
        case 10:
            return(31);
        case 11:
            return(30);
        case 12:
            return(31);
    }
    return 0;
}




//For adding event/to do in the calendar
void addevent(int val1,int val2){
    int i,val3;
    char f1[6];
    char arr[20];
    FILE *fp;
    system("cls");
    printf("Enter the date in which event is to be added: ");
    scanf("%d",&val3);
    i=val3;
    sprintf(f1,"%d.txt",val1);
    printf("Enter the event name : ");
    fgets(arr, sizeof(arr), stdin);
    fgets(arr, sizeof(arr), stdin);
    fp=fopen(("%s",f1),"a+");
    fprintf(fp,"%d/%d/%d   ",i,val2,val1);
    for(i=0;i<strlen(arr);i++){
        fputc(arr[i],fp);
    }
    fclose(fp);
    printf("Event is Successfully Saved\n");
}

//To delete a saved event in a date
void delete_event(){
    int i,val1,val2,val3;
    char c;
    char f1[10],f2[40],temp[20],arr[20];
    FILE *fp,*fptr;
    printf("Enter the year : ");
    scanf("%d",&val1);
    printf("Enter the month number : ");
    scanf("%d",&val2);
    printf("Enter the date : ");
    scanf("%d",&val3);
    i=val3;
    printf("Enter The Event Name : ");
    fgets(arr,19,stdin);
    fgets(arr,19,stdin);
    sprintf(f1,"%d.txt",val1);
    fp=fopen(("%s",f1),"r");
    fptr=fopen("temp.txt","w");
    sprintf(f2,"%d/%d/%d",i,val2,val1);
    while(fgets(temp,19,fp)!=NULL){
        if(strcmp(temp,strcat(f2,arr))!=0)
        {
            fputs(temp,fptr);
        }
    }
    fclose(fp);
    fclose(fptr);
    remove(f1);
    rename("temp.txt",f1);
} 

void view_event(){
    //To see the saved events
    int val5;
    char ch;
    char f10[10];
    FILE *fps;
    printf("Enter the year to see the events of that year : ");
    scanf("%d",&val5);
    sprintf(f10,"%d.txt",val5);
    fps=fopen(("%s",f10),"r");
    if(fps==NULL){
        printf("No event has been added in this year!!!\n");
        printf("Press any key to continue..");
        return;
    }
    //printf("*\n");
    rewind(fps);

    while(1){
        ch=fgetc(fps);
        if(ch==EOF){
            break;
        }
        printf("%c",ch);
    }
}

void c_month(char *month_name[], int month, int day1, int year){
    //Main UI
    int loop1=0, choice, temp, date;
    char ch;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    temp=startingday(year,month);
    date=mounth(month);

    printf("----------------------------------------------------------------------\n");
    printf("|                  A To-Do Calendar app by Animesh Alok              |\n");
    printf("----------------------------------------------------------------------\n");
    printf("\nCurrent year :  %d\n\n",stime.wYear);
    printf("Today is : %s",month_name[stime.wMonth-1]);
    printf(" %d %d\n\n",day1,stime.wYear);
    printf("---------------------------------------------------\n");
    printf("                    %s %d\n",month_name[month-1],year);
    printf("---------------------------------------------------\n");
    printf("Sun\tMon\tTue\tWed\tThur\tFri\tSat \n\n");
    
    for(int i=0;i<temp;i++){
        printf("\t");
        loop1++;
    }
   


   
    int sun = (8-temp+7)%7;
    for(int loop=1;loop<=date;loop++)
    {
        if((loop-sun+7)%7 == 0){
            printf(ANSI_COLOR_RED "%d\t" ANSI_COLOR_RESET,loop);
        }
        else printf("%d\t",loop);
        if(++loop1>6)
        {
            printf("\n\n");
            loop1=0;
        }
        temp=(temp+date)%7;
    }
    while(1){
    printf("\n\n1. Change month\n");
    printf("2. Change year \n");
    printf("3. Add Event in %s %d\n", month_name[month-1],year);
    printf("4. Delete Event\n");
    printf("5. View Event \n");
    printf("6. About me\n");
    printf("7. Quit\n\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);
        switch(choice){
            case 1: {
                    printf("Enter P for previous month or Enter N for next: ");
                    ch=getch();
                    if(ch=='p' || ch=='P'){
                        system("cls");
                        c_month(month_name,month-1,day1,year);
                    }
                    else if(ch=='n' || ch=='N'){
                        system("cls");
                        c_month(month_name,month+1,day1,year);
                    }
                    break;
            }

            case 2: {
                    printf("Enter P for previous year or Enter N for next: ");
                    ch=getch();
                    if(ch=='p' || ch=='P'){
                        system("cls");
                        c_month(month_name,month,day1,year-1);
                    }
                    else if(ch=='n' || ch=='N'){
                        system("cls");
                        c_month(month_name,month,day1,year+1);
                    }
                    break;
            }

            case 3: {
                    addevent(year,month);
                    printf("Press any key to continue...");
                    getch();
                    system("cls");
                    c_month(month_name,month,day1,year);
                    break;
            }

            case 4: {
                    delete_event();
                    c_month(month_name,month,day1,year);
                    break;
            }

            case 5: {
                    system("cls");
                    view_event();
                    printf("Press any key to continue...");
                    getch();
                    system("cls");
                    c_month(month_name,month,day1,year);
                    break;
            }

            case 6: {
                    printf("Myself " ANSI_COLOR_YELLOW "Animesh Alok" ANSI_COLOR_RESET " an IT underGrad of MAKAUT, WB.\n\n");
                    printf("\nPress any key to continue...");
                    getch();
                    // system("cls");
                    // c_month(month_name,month,day1,year);
                    break;
            }
            case 7: {
                    system("cls");
                    
                    exit(1);
            }

            default: {
                    printf("Wrong Choice!!!");
                    exit(0);
            }
        }
    }

}

int main(){
    
    //To set the title of console
    SetConsoleTitleA("To-Do Calendar App by Animesh Alok");
    
    char *month_name[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    int day1,month,year;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    day1=stime.wDay;
    year=stime.wYear;
    month=stime.wMonth;
    system("cls");

    c_month(month_name,month,day1,year);

    
    return 0;
}
