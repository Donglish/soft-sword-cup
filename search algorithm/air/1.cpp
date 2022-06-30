#include<algorithm>
#include<iostream>
#include<queue>
#include<string>

#define ERROR1 -1// 用户输入非法
#define ERROR2 -2// 没有匹配合适项

using namespace std;

const int Air_Number_Length=4;
const int Time_Length=12;
const int City_Length=3;
const int Air_Company_Length=2;
const int Price_Length=8;
const int Extent_Price_Length=3;
const int Cabin_Lenth=1;


typedef string Font_City;
typedef int Font_Date;

typedef struct Customer_Request{

    vector<pair<string,string>> fromto_city;
    int daytime;
    int custnum,travelnum;
    int ansnum;
    queue <string>agency;
}Customer_Request;
Customer_Request crequest;
/*舱位能否请求*/

queue <string>Apply_Agency;
typedef struct  Finans_Air
{
    int takeon_time,takeoff_time;
    string agen;
    int FinPrice;   //Price是否会是整数未知，待定，四舍五入or向上取整待定

}Finans_Air;

class comfin_price
{
    public:
        bool operator()(Finans_Air& a,Finans_Air& b){
            return a.FinPrice>b.FinPrice;
        }
};


priority_queue<Finans_Air,vector<Finans_Air>,comfin_price> Re_Mulage_Queue;





void Read_From_Front()
{
    /*从前端填crequest*/

}

typedef pair<string,string>  city_abbrev;//城市名->城市简写
vector<city_abbrev> City_Name; //存放城市名



int Search_CityName()
{
    string city;
    string city_abberviationp;
    int flag=0;
    for(int i=0;i<City_Name.size();i++){
        if(City_Name[i].first==city){
            flag=1;
            city_abberviationp=City_Name[i].second;
            //在有序的情况下可加快查找
            break;//查找到该城市
            /**/
        }
    }
    if(!flag)return ERROR2;
}

void Search_City()
{
    string city;
    /*连接数据库*/
}
int current_year=2020;

int Search_Date()
{
    //前四位表示年，后四位表示月日
    int daytime;
    int year = daytime/10000;
    if(year!=current_year)return ERROR1;
    int month = (daytime/100)%100;
    int day = daytime%100;

    /*判断出发当天是一年中的哪一天*/
    int sumday = 0;
    int monthday[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                monthday[1] = 29;
            }
        } else {
            monthday[1] = 29;
        }
    }

    for (int i = 0; i < month - 1; i++) {
        sumday += monthday[i];
    }
    sumday += day;
    /*判断出发当天是一年中的哪一天*/

    /*连接数据库*/
    

}

string Current_Carrier;
string NextCarrier;

void Select_Carrier()
{

    if(NextCarrier.size()!=0){
        /*指定下一航空公司*/
        /*判断余座是否满足要求*/
    }

    else{
        /*没有指定下一航空公司*/
        /*开始遍历*/
        /*判断余座是否满足要求*/
        Select_PriceTable();
    }


}


string current_agency;
void Select_Agency()
{
    if(current_agency.size()!=0){
        /*航班代理人已确定*/
    }
    else{
        /*航班代理人未确定*/
        /*开始遍历*/
    }
}

void Select_PriceTable()
{
    /*连接数据库*/
    //Current_Carrier
    //从四种分类中选出符合的city-city
    int min_seqnum;
    Select_Agency();

}

int task=crequest.travelnum;
int finish_task=0;

void Schedule()
{
    
    while(task<finish_task){

    }
}

void Back_Ans()
{
    Search_City();
    Search_City();
    Search_Date();
    Select_Carrier();
}

int main()
{

}