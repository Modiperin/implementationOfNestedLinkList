#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
struct node
{
    struct node *data;
    int innerData;
    struct node *next;
    struct node *innerNext;
    char name[50],row;
    unsigned long long int pnumber;
    int total,tstart,id,innerSeat,price;
    char innerRow[1];
}*head=NULL,*innerHead=NULL;
void red() {
  printf("\033[0;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset() {
  printf("\033[0m");
}
void reservation();
int choice1(void)
{
	int choice;
	printf("                 Simple Movie Ticket Booking System\n");
	printf(" ==================================================================\n");
	printf("||             1- To puchase ticket:                              ||\n");
	printf("||             2- To view reserved tickets (only admin):          ||\n");
	printf("||             3- To cancel the seat:                             ||\n");
	printf("||             4- Exit system:                                    ||\n");
	printf("||================================================================||\n");
	printf("  Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}
void screenChart()
{
    char alpha='A';
    struct node *t;
    int flag=0;
    while(alpha!='Z')
    {
        for(int j=1;j<=10;j++)
        {
            t=head;
            if(t==NULL)
            {
                printf("%c ",alpha);
                printf("%d\t",j);
            }
            else
            {
                while(t!=NULL)
                {
                    if((j>=(t->tstart)&& j<=(t->tstart + t->total)-1) && alpha==(t->row))
                    {
                        flag=1;
                    }
                    t=t->next;
                }
                if(flag==1)
                {
                    red();
                    printf("%c ",alpha);
                    printf("%d\t",j);
                    reset();
                }
                else
                {
                    printf("%c ",alpha);
                    printf("%d\t",j);
                }
                flag=0;
            }
            if(j==10)
            {
                printf("\n");
                alpha++;
            }
        }
    }
    reservation();
}
struct node *create(int totalInnNum,int r,int start)
{
    struct node *temp,*p,*innerTemp;
    int i,num;
    temp=(struct node*)malloc(sizeof(struct node));
    innerHead=(struct node*)malloc(sizeof(struct node));
    printf("Enter your name:");
    fflush(stdin);
    gets(temp->name);
    fflush(stdin);
    printf("Enter Your Phone Number");
    scanf("%llu",&temp->pnumber);
    temp->total=totalInnNum;
    temp->tstart=start;
    temp->row=r;
    num=rand() % 100+1;
    temp->id=num;
    temp->price=250;
    temp->data=innerHead;
    temp->next=NULL;
    for(i=start;i<start+totalInnNum;i++)
    {
        if(i==start)
        {
            innerHead=temp->data;
            innerHead->innerNext=NULL;
            innerHead->innerRow[0]=r;
            innerHead->innerSeat=i;
        }
        else
        {
            innerTemp=(struct node*)malloc(sizeof(struct node));
            innerTemp->innerNext=NULL;
            innerTemp->innerRow[0]=r;
            innerTemp->innerSeat=i;
            p=temp->data;
            while(p->innerNext!=NULL)
            {
                p=p->innerNext;
            }
            p->innerNext=innerTemp;
            printf("temp=%u\n",innerTemp);
            printf("p->innerNext=%u\n",p->innerNext);
        }
    }
    return temp;
}
void reservation()
{
    struct node *temp,*p,*z,*t;
    int totalInnNum,i,num,start,end,j,movie;
    char fname[50],r,y;
    printf("\n");
    printf("Enter the Total number of tickets you want\n");
    scanf("%d",&totalInnNum);
    fflush(stdin);
    printf("Enter the Row:");
    scanf("%c",&r);
    fflush(stdin);
    printf("Enter the Starting Seat Number\n");
    scanf("%d",&start);
    z=head;
    if(z==NULL)
    {
        if(start+totalInnNum-1 >10)
        {
            printf("Sorry We have only 10 seat per row to book more than 10 tickets Book it again\n");
            screenChart();
        }
    }
    while(z!=NULL)
    {
        if((start>=(z->tstart)&& start<=(z->tstart + z->total)-1) && r==(z->row))
        {
            printf("Sorry Tickets are already sold out\nPlease select again\n");
            screenChart();
        }
        if(start+totalInnNum-1 >10)
        {
            printf("Sorry We have only 10 seat per row to book more than 10 tickets Book it again\n");
            screenChart();
        }
        z=z->next;
    }
    if(head==NULL)
    {
        head=create(totalInnNum,r,start);
    }
    else
    {
        temp=create(totalInnNum,r,start);   
        p=head;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=temp;
    }
}
void display()
{
    struct node *inP,*p;
    int i=1;
    if(head==NULL)
    {
        printf("No element\n");
    }
    else
    {
        p=head;
        while(p!=NULL)
        {
            inP=p->data;
            fflush(stdin);
            system("cls");
            printf("\n\n");
            printf("\t-----------------THEATER BOOKING TICKET----------------\n");
            printf("\t============================================================\n");
            printf("\t Booking ID : %d \t\t\tShow Name : Avengers: EndGame\n",p->id);
            printf("\t Customer  : %s\n",p->name);
            printf("\t\t\t                              Date      : 29-04-2019\n");
            printf("\t                                              Time      : 08:00pm\n");
            printf("\t                                              Hall      : 02\n");
            printf("\t                                              price . : %d  \n\n",p->price);
            printf("\t============================================================\n");
            while(inP!=NULL)
            {
                printf("Seat No.%d=%c%d\n",i,inP->innerRow[0],inP->innerSeat);
                inP=inP->innerNext;
                i++;
            }
            printf("\n");
            p=p->next;
        }
    }
}
void adminDetails()
{
    int i,count=0;
    struct node *p;
	char pass[10],pak[10]="pass";
	printf("Enter the password to see details: ");
	scanf("%s",&pass);
	if (strcmp(pass,pak)==0)
	{
		p=head;
        if(p==NULL)
        {
            printf("No tickets are booked\n");
        }
        else
        {
            while(p!=NULL)
            {
                printf("%d",count);
                printf("Id=%d\n",p->id);
                printf("Name=%s\n",p->name);
                printf("Phone Number=%d\n",p->pnumber);
                printf("Row=%c\n",p->row);
                printf("Ticket from %d to %d\n",p->tstart,p->tstart+p->total);
                printf("\n\n");
                p=p->next;
                count++;
            }
        }
	}
	else                                                 
		printf("Entered password is wrong \n");
		system("PAUSE");
		system("CLS");
}
void cancel()
{
    struct node *p,*temp,*back;
    int ask;
    char yn;
    printf("Enter Your Ticket Id");
    scanf("%d",&ask);
    p=head;
    while(p!=NULL)
    {
        if(p->id==ask)
        {
            
            printf("Please confirm your identity");
            printf("Id=%d\n",p->id);
            printf("Name=%s\n",p->name);
            printf("Phone Number=%d\n",p->pnumber);
            printf("Row=%c\n",p->row);
            printf("Ticket from %d to %d\n",p->tstart,p->tstart+p->total);
            printf("Enter y/n to confirm");
            fflush(stdin);
            yn=getch();
            if(yn=='y' || yn=='Y')
            {
                if(p==head)
                {
                    temp=p->next;
                    free(p);
                    head=temp;
                }
                else if(p!=head)
                {
                    if(p->next==NULL)
                    {
                        free(p);
                        back->next=NULL;
                    }
                    else
                    {
                        back->next=p->next;
                        free(p);
                    }
                }
                printf("Ticket Cancellled Sucessfully\n");
                break;
            }
        }
        back=p;
        p=p->next;
    }
}
void main()
{
    int x,choice,selection;
	while(x!=4)
	{
		choice=choice1();
		switch(choice)
		{
			case 1:
                screenChart();
                display();
				break;
			case 2:
				adminDetails();
				break;	
			case 3:	
				cancel();
				break;
			case 4:
				x=4;
				break;
			default: 
				printf("Choice not available\n");
				break;	
		}
	}
}