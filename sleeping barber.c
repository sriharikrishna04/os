#include<stdio.h>
#include<unistd.h>
int customer=0;
int barber=0;
int seat=1;
int freeseat=5;
int waits(int v)
{v--;
return v;}
int signals(int v)
{v++;
return v;}
void barbers()
{while(customer)

{printf("\nno of customer %d",customer);
customer=waits(customer);
if(customer>=0)
{
seat=waits(seat);
freeseat++;
printf("\ncut the hair");
barber=signals(barber);
seat=signals(seat);
}
}}
void customers()
{seat=waits(seat);
if(freeseat>0)
{freeseat--;
customer=signals(customer);
seat=signals(seat);
barber=waits(barber);
printf("\ncustomer added");
printf("\nno of customer %d",customer);
}
else
{
printf("\ncustomer declined");
seat=signals(seat);
}
}
int main()
{int choice=1;

while(choice)
{printf("\ndo u wanna cut the hair ");
scanf("%d",&choice);
if(choice==1)
{customers();
}}
barbers();}
