#include<string>
#include<vector>
#include<jsoncpp/json/json.h> 
#include<sstream>
#include"json.hpp"
using namespace std;

typedef struct PriceTable_Message{
    string carrier;
    string departcity;
    string arivalcity; 
    vector<string> agency;
    string nextcarrier;
    string seqnum;
    int surcharge;

}PriceTable_Message;

vector<PriceTable_Message> All_Table;
void combine_airandseat();
void dealtable();