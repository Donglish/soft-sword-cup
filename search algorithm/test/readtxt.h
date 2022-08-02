#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <iostream>
using namespace std;
typedef struct airmessage
{
	char company[3];
	char flightNo[5];
	char departureDatime[13];
	char arrivalDatetime[13];
	char departure[4];
	char arrival[4];
}airmessage;

airmessage planeair[100000];
int airmessage_amount;
//flightNo	departureDatime	arrivalDatetime	departure	arrival
//3879	202206201830	202206202015	XNN	CTU

typedef struct price
{
	char carrier[3];
	char departure[4];
	char arrival[4];
	char carbin[2];
	char amount[10];
}price;

price planeprice[100000];
int price_amount=0;

typedef struct seat
{
	char company[3];
	char flightNo[5];
	char departureDatime[13];
	//char arrivalDatetime[13];
	char departure[4];
	char arrival[4];
	char f_num[2];
	char c_num[2];
	char y_num[2]; 
}seat;

seat planeseat[120000];
int seat_amount; 

typedef struct pricetable
{
	char linetable[100];
}pricetable;

pricetable planetable[100000];
int table_amount;
void tablefunc();
void seatfunc();
void pricefunc();
void airfunc();