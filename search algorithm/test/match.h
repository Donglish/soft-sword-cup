#include"preprocessing.h"
#include"form_answer.h"
#include"customer.h"

PriceTable_Message Match_PriceTable(Air_Message partmessage);
void Match_AirMessage(string date,string fromcity,string tocity,string passagenum);
void Match_Price(string from,string to,string carrier,tableflight& tmp);