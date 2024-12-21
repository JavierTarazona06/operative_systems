/* NAME: Javier Andres Tarazona Jimenez, Thomas Brown, Tianze Kuang
   NSID: elr490, vwg123, wde364
   Student Number: 11411898, 11332966, 11352826

   CMPT 332 Term 1 2024

   Lab 3
*/

#include <stdio.h>
#include <standards.h>
#include <os.h>

int Mutex, Customer, Barber, CustomerDone, BarberDone;
int CustomersWaiting, MaxQueue, customer_thr_finished;

void cutHair()
{
	printf("Customers waiting: %d\n", CustomersWaiting-1);
	printf("Cut hair\n");
	Sleep(1*100);
}

void getHairCut()
{
	printf("get hair cut\n");
	Sleep(1*100);
}
	

void CustomerThread()
{
	P(Mutex);
	if(CustomersWaiting == MaxQueue)
	{
		printf("Customer left because queue is filled\n");
		customer_thr_finished++;
		V(Mutex);
		Pexit(); /*balk()*/
	}
	
	CustomersWaiting += 1;
	printf("Customer is waiting. Total count waiting: %d\n", CustomersWaiting-1);
	V(Mutex);
	
	V(Customer);
	P(Barber);
	
	getHairCut();
	
	/* customer done */
	V(CustomerDone);
	P(BarberDone);
	
	P(Mutex);
	CustomersWaiting -= 1;
	customer_thr_finished++;
	V(Mutex);
	
	Pexit();
}
	
void BarberThread()
{
	while(1){
		P(Customer);
		V(Barber);
	
		cutHair();
	
		P(CustomerDone);
		V(BarberDone);
	}
	
	printf("Exit Parent thread!!!\n");
	Pexit();
}
	
void MainThread(int* CustomerCount)
{
	int i;
	PID barberPID;
	
	barberPID = Create(BarberThread, 3*1024*1024, "", NULL, HIGH, USR);
	
	customer_thr_finished = 0;
	
	for(i = 0; i < *CustomerCount; i++)
	{
		Sleep(0.3*100);
		Create(CustomerThread, 3*1024*1024, "", NULL, NORM, USR);
	}
	
	while (customer_thr_finished < *CustomerCount){
		Sleep(1*100);
	}
	
	Kill(barberPID);
	
	FreeSem(Mutex);
	FreeSem(Customer);
	FreeSem(Barber);
	FreeSem(CustomerDone);
	FreeSem(BarberDone);
	
	Pexit();
}

void mainp(int args, char* argv[])
{
	int  CustomerCount;
	
	
	if (args != 3){
		printf("Error> Usage is program queue+barber_chair total_customers_approach\n");
		return;
	}
	
	MaxQueue = atoi(argv[1]);
	CustomerCount = atoi(argv[2]);

	if(MaxQueue <= 0){printf("invalid number maxqueue\n"); return ;}
	
	Mutex = NewSem(1);
	Customer = NewSem(0); /*No customers*/
	Barber = NewSem(0); /*Barber is waiting*/
	CustomerDone = NewSem(0); /*No customers done*/
	BarberDone = NewSem(0); /*No cuts made by the barber*/
	
	Create(MainThread, 6*1024*1024, "", &CustomerCount, HIGH, USR);

}
	
