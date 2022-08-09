#include<vector>
#include<queue>
#include<string>
using namespace std;
#define MAXFLIGHTONEDAY 1000
#define MAXBUF 10000
int ERROR2=-1;
typedef struct Customer_Request{

    vector<pair<string,string> > fromto_city;
    vector<string> daytime;
    int travelnum;
    string custnum;
    int ansnum;
    queue <string>agency;
}Customer_Request;
Customer_Request crequest;
vector<string> request_agency;
int task;
int traveller;
int request_ans;