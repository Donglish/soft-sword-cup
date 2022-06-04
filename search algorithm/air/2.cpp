#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<queue>
#include<vector>
#define MAXFLIGHTONEDAY 1000
#define ERROR2 -2
using namespace std;

typedef struct Air_Message{
    string carrier;  
    int acctime;
    int flightNo;
    vector<pair<char,char>> cabin;
    //map<char,pair<char,int>> cabin;
    char seatnum;
}Air_Message;

typedef struct Price_Message{
    pair<char,int> basic_price;

}Price_Message;

typedef struct PriceTable_Message{
    vector<string> agency;
    string nextcarrier;
    int seqnum;
    int surcharge;

}PriceTable_Message;

typedef struct OnePart
{
    vector<Air_Message>  flight;
    Price_Message price;
    PriceTable_Message table;
}OnePart;
vector<OnePart> All_Part;
int task;
int traveller;

void read_from_database()
{
    /**/
    for(int i=0;i<task;i++){
        ;
        /*判断余座是否满足要求*/
        //All_Part[i]
    }
}

void Search1(int task_num)
{
    int minnum_flight=MAXFLIGHTONEDAY;
    int min_part;
    for(int i=0;i<task_num;i++){  
        int sizenum=All_Part[i].flight.size();
        if(sizenum<minnum_flight){
            min_part=i;
            minnum_flight=sizenum;
        }
    }

}

typedef struct Ans_Flight
{
    string carrier;  
    int acctime;
    int flightNo;
    int F_cabin,C_cabin,Y_cabin;
    int F_price,C_price,Y_price;
    int prices;
    /* data */
};



typedef struct Answer
{
    string agency;
    int sumprice;
    vector<Ans_Flight> ansflight;
}Answer;

vector<Answer> All_Answer;
/*agency请求是否合法*/
vector<string> request_agency;



void Search2(int startpart)
{
    vector<Air_Message> tmp_flight=All_Part[startpart].flight;
    PriceTable_Message tmp_table;
    for(int i=0;i<tmp_flight.size();i++){
        /*查找运价规则*/
        for(int j=0;j<request_agency.size();j++){
            for(int k=0;k<tmp_table.agency.size();k++){
                if(request_agency[j]==tmp_table.agency[k]){  //匹配成功
                    only_agency=request_agency[j];
                    Search3(tmp_table.nextcarrier,startpart+1);
                    Search4(tmp_flight[i].carrier,startpart-1);
                }
            }
        }
    }
}

string only_agency;

int Find_Agency(vector<string> agencys)
{
    for(int i=0;i<agencys.size();i++){
        if(agencys[i]==only_agency){
            return 1;
        }
    }
    return ERROR2;
}

typedef struct tableflight
{
    string carrier;
    int surcharge;
    int f_num,c_num,y_num;
    string nextcarrier;
    int flightNo;
    int acctime;
    /* data */
}tableflight;


void Search3(string only_carrier,int floor)
{
    //递归结束条件
    vector<tableflight> tmp_ans;
    vector<Air_Message> tmp_air;
    PriceTable_Message tmp_table;
    int tmp_price;

    //tmp_price=All_Part[floor].price.basic_price;
    tmp_air=All_Part[floor].flight;
    if(only_carrier.size()!=0){  //若指定nextcarrier
        for(int i=0;i<tmp_air.size();i++){
            if(tmp_air[i].carrier==only_carrier){
                /*查找运价规则*/
                /*没有运价规则该如何*/
                if(Find_Agency(tmp_table.agency)!=ERROR2){  //航班是否有该代理人
                    tableflight tmp_taf;
                    tmp_taf.carrier=tmp_air[i].carrier;
                    tmp_taf.surcharge=tmp_table.surcharge;
                    tmp_taf.nextcarrier=tmp_table.nextcarrier;
                    tmp_taf.flightNo=tmp_air[i].flightNo;
                    tmp_taf.acctime=tmp_air[i].acctime;
                    /*选择每个舱位的数量*/
                    tmp_ans.push_back(tmp_taf);
                }
                
            }
            else return ERROR2;
        }
        for(int i=0;i<tmp_ans.size();i++){
            if(Search3(tmp_ans[i].nextcarrier,floor+1)!=ERROR2){
                /*加入答案队列*/
            }

        }
    }



    else{
        for(int i=0;i<tmp_air.size();i++){           
            /*查找运价规则*/
            if(Find_Agency(tmp_table.agency)!=ERROR2){  //航班是否有该代理人
                tableflight tmp_taf;
                tmp_taf.carrier=tmp_air[i].carrier;
                tmp_taf.surcharge=tmp_table.surcharge;
                tmp_taf.nextcarrier=tmp_table.nextcarrier;
                tmp_taf.flightNo=tmp_air[i].flightNo;
                tmp_taf.acctime=tmp_air[i].acctime;
                /*选择每个舱位的数量*/
                tmp_ans.push_back(tmp_taf);
            }
                
            
            else return ERROR2;
        }
        for(int i=0;i<tmp_ans.size();i++){
            if(Search3(tmp_ans[i].nextcarrier,floor+1)!=ERROR2){
                /*加入答案队列*/
            }

        }
    }
}

void Search4(string only_carrier,int floor)
{
    if(floor<0)return;//递归结束
    vector<tableflight> tmp_ans;
    vector<Air_Message> tmp_air;
    PriceTable_Message tmp_table;
    int tmp_price;

    //tmp_price=All_Part[floor].price.basic_price;
    tmp_air=All_Part[floor].flight;
    
    for(int i=0;i<tmp_air.size();i++){
        
            /*查找运价规则*/
            /*没有运价规则该如何*/
            if(Find_Agency(tmp_table.agency)!=ERROR2&&(tmp_table.nextcarrier==only_carrier||tmp_table.nextcarrier==NULL)){  //航班是否有该代理人
                tableflight tmp_taf;
                tmp_taf.carrier=tmp_air[i].carrier;
                tmp_taf.surcharge=tmp_table.surcharge;
                tmp_taf.nextcarrier=tmp_table.nextcarrier;
                tmp_taf.flightNo=tmp_air[i].flightNo;
                tmp_taf.acctime=tmp_air[i].acctime;
                /*选择每个舱位的数量*/
                tmp_ans.push_back(tmp_taf);
            }
            
        
        
    }
    if(tmp_ans.size()==0) return ERROR2;
    for(int i=0;i<tmp_ans.size();i++){
        if(Search4(tmp_ans[i].carrier,floor-1)!=ERROR2){
            /*加入答案队列*/
        }

    }
    
}

void Search5(int task_num)
{
    Search1(task_num);
    int startpart;
    Search5(startpart-1);
    Search2(startpart);

}