#include<string>
#include<vector>
#include<stack>
//#include"form_answer.h"
using namespace std;

typedef struct Air_Message{
    string departcity;
    string arivalcity;
    string date;
    string carrier;  
    string acctime;
    string flightNo;
    vector<pair<char,char> > cabin;
    string arrivaltime;
    //map<char,pair<char,int>> cabin;
    char seatnum;
}Air_Message;
vector<Air_Message> All_Message;

typedef struct OnePart
{
    vector<Air_Message>  flight;
    //Price_Message price;//???三个位置
    //PriceTable_Message table;
}OnePart;
vector<OnePart> All_Part;

typedef struct tableflight//???
{
    string departcity;
    string arivalcity;
    string carrier;
    int surcharge;
    string f_num,c_num,y_num;
    string f_price,c_price,y_price;
    string nextcarrier;
    string flightNo;
    string acctime;
    string arrivaltime;
    //string singleprice;
    
    /* data */
}tableflight;

stack<tableflight> tmp_stack1;
vector<stack<tableflight> > path1;
typedef vector<stack<tableflight> > PATHTYPE;
PATHTYPE ALL_PATH[8];

stack<tableflight> tmp_stack2;
vector<stack<tableflight> > path2;

string only_agency;
void Search5(int task_num);
void Search2(int startpart,int lastpart);
void Search3(string only_carrier,int floor,int lastfloor);
int Find_Agency(vector<string> agencys);
int Search1(int task_num);