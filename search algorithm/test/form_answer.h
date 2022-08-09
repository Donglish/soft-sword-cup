#include<string>
#include<vector>
#include<queue>
#include<stack>
#include"search.h"
#include"customer.h"
using namespace std;
typedef struct cabininfo
{
    string cabintype;
    string num;
    string singleprice;
}cabininfo;

typedef struct partinfo
{
    string carrier;
    string planetype;
    string startTime;
    string startCity;
    string startDate;
    string endDate;
    string endTime;
    string endCity;
    vector<cabininfo> cabin;
    int partprice;
    /* data */
}partinfo;

typedef struct partans
{
    vector<partinfo> part;
    string anency;
    int allprice;
}partans;
int cul(char a_type,int a,int a_num,char b_type,int b,int b_num,char c_type,int c,int c_num,partinfo& info);
void culprice(partinfo& info,tableflight part);
bool CheakOne(string predate,string pretime,string backdate,string backtime);
void deal(PATHTYPE anspath);
void Search6();