#include "workflow/WFFacilities.h"
#include <csignal>
#include "wfrest/HttpServer.h"
#include "wfrest/json.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <iostream>
#include<algorithm>
#include<string>
#include<map>
#include<queue>
#include<vector>
#include<stack>
#define MAXFLIGHTONEDAY 1000
int ERROR2=-1;
using namespace wfrest;
using Json = nlohmann::json;
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


string air_e[40]={"BK","2Z","OQ","CN","JI","HU","GS","NS","KY","QW","HO","SC","FM","3U","ZH","GS","MF","JR","TV","PN","CZ","KN","CA","MU"};
string air_c[40]={"奥凯","长安航空","重庆航空","大新华","翡翠","海南航空","华夏","河北航空","昆明航空","青岛航空","上海吉祥","山航","上航","川航","深航","天航","厦航","幸福","藏航","西航","南航","联航","国航","东航"};


map<string,string> carrier_e;
map<string,string> carrier_c;

string city_e[50]={"HKG","MFM","TSA","BJS","TSN","SHA","CAN","SZX","NKG","CTU","CKG","KMG","HGH","XIY","WUH","CGO","CGQ","CSX","TYN","DLC","FOC","XMN","HAK","SYX","HET","HFE","HRB","LHW","URC","SJW","SHE","TNA","INC","KWE","NNG","KHN","XNN","LXA","TAO","NGB"};
string city_c[50]={"香港","澳门","台北","北京","天津","上海","广州","深圳","南京","成都","重庆","昆明","杭州","西安","武汉","郑州","长春","长沙","太原","大连","福州","厦门","海口","三亚","呼和浩特","合肥","哈尔滨","兰州","乌鲁木齐","石家庄","沈阳","济南","银川","贵阳","南宁","南昌","西宁","拉萨","青岛","宁波"};

map<string,string> cityname_e;
map<string,string> cityname_c;


map<string,string> cabinname;


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
typedef struct OnePart
{
    vector<Air_Message>  flight;

}OnePart;
vector<OnePart> All_Part;
int task;
int traveller;
int request_ans;



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

int pathnum;

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

//vector<partans> ans;

struct cmp1{
	bool operator()(const partans& a,const partans& b){
    return a.allprice<b.allprice;
	}
};

priority_queue<partans,vector<partans>,cmp1> ans;
string previousdate="0000";
string previoustime;

void tablefunc();
void seatfunc();
void pricefunc();
void airfunc();
void BuildCarrier();
void BuildCity();
void BuildCabin();
void combine_airandseat();
void dealtable();
PriceTable_Message Match_PriceTable(Air_Message partmessage);
void Match_AirMessage(string date,string fromcity,string tocity,string passagenum);
void Match_Price(string from,string to,string carrier,tableflight& tmp);
int Search1(int task_num);
int Find_Agency(vector<string> agencys);
void Form_Part();
void Search3(string only_carrier,int floor,int lastfloor);
int cul(char a_type,int a,int a_num,char b_type,int b,int b_num,char c_type,int c,int c_num,partinfo& info);
void culprice(partinfo& info,tableflight part);
bool CheakOne(string predate,string pretime,string backdate,string backtime);
void Printcc(partans& oneans);
void Printdd(tableflight a);
void deal(PATHTYPE anspath);
void Search6();
void Search2(int startpart,int lastpart);
void Search4(string only_carrier,int floor,int firstfloor);
void Search5(int task_num);
void dealempty();
void recover();
static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
    wait_group.done();
}

int main()
{
    pricefunc();      
	airfunc();
    seatfunc();
    tablefunc();  
    combine_airandseat(); 
    dealtable();
    BuildCarrier();
    BuildCity();
    BuildCabin();
    

    signal(SIGINT, sig_handler);

    HttpServer svr;

	svr.POST("/test", [](const HttpReq *req, HttpResp *resp)
    {

		if (req->content_type() != APPLICATION_JSON)
        {
            resp->String("NOT APPLICATION_JSON");
            return;
		}
		 //解析json数据
		 std::cout << "recv body 1:" << req->body() << std::endl;
		 Json inJson = Json::parse(req->body());
		
		// std::cout << "passengerNum:" << inJson["passengerNum"]<<std::endl;
		// std::cout << "date:" << inJson["planeList"][0]["date"]<<std::endl;

		// //TODO::在此处添加业务处理逻辑

		// //返回json数据
		// Json json = {
		// 	{
		// 		"returnList",{
		// 			{
		// 				{
		// 					"part",{
		// 						{
		// 							{"planeInfo",{{"companyName","国航"},{"planeType","0100"}}},
		// 							{"timeInfo",{
		// 								{"start",{{"startDate","2022年7月11日"},{"startTime","12:00"},{"startCity","长沙"}}},
		// 								{"end",{{"endDate","2022年7月11日"},{"endTime","15:00"},{"endCity","南京"}}}}
		// 							},
		// 							{"cabin",{{{"cabinType","F"},{"num","1"},{"singlePrice","1000"}}}},
		// 							{"partPrice","1000"}
		// 						}
		// 					}


		// 				}
		// 			}
		// 		}
		//     }
		// };
         
         crequest.custnum = inJson["passengerNum"];
      
         // cin>>crequest.custnum;
         crequest.ansnum = atoi(((std::string)(inJson["planeNum"])).c_str());
       
         // cin>>crequest.travelnum;
         crequest.travelnum = inJson["planeList"].size();
         // cin>>crequest.ansnum;
     
         request_ans = crequest.ansnum;
         traveller = atoi(crequest.custnum.c_str());
     
         for (int i = 0; i < crequest.travelnum; i++)
         {
             string datetime;
             datetime = inJson["planeList"][i]["date"];
             // cin>>datetime;
             datetime = datetime.erase(4, 1);
             datetime = datetime.erase(6, 1);
             datetime = datetime.substr(0, 8);
             crequest.daytime.push_back(datetime);
             pair<string, string> tmpcity;

             string fromcity, tocity;
             fromcity = inJson["planeList"][i]["fromCityAndToCity"]["fromCity"];
            std::cout << "recv body 1:"<<std::endl;
             tocity = inJson["planeList"][i]["fromCityAndToCity"]["toCity"];
             std::cout << "recv body 2:"<<std::endl;
             // cin>>fromcity;
             // cin>>tocity;
             map<string, string>::iterator iter = cityname_e.find(fromcity);
             tmpcity.first = iter->second;
             iter = cityname_e.find(tocity);
             tmpcity.second = iter->second;
             crequest.fromto_city.push_back(tmpcity);
	}
  
    int agencynum=1;
    string tmpstr;
    tmpstr=inJson["agentList"][0];
    //cin>>tmpstr;
    request_agency.push_back(tmpstr);
   
    Form_Part();
    
	
    Search5(crequest.travelnum);
    if(ans.size()==0)dealempty(); 
    int anssize=ans.size();
    cout<<"anssize"<<anssize<<endl;
	//返回json的构造 
	 
	Json json;
	for(int i=0;i<anssize;i++){
        cout<<"for start"<<endl;
		partans tmpans=ans.top();
    	Printcc(tmpans);
		ans.pop();
		for(int j=0;j<tmpans.part.size();j++){
            cout<<"for 2 start"<<endl;
			partinfo tmpinfo=tmpans.part[tmpans.part.size()-j-1];
			json["returnList"][i]["part"][j]["planeInfo"]["companyName"]=tmpinfo.carrier;
			cout<<tmpinfo.carrier<<"4"<<endl;
			json["returnList"][i]["part"][j]["planeInfo"]["planeType"]=tmpinfo.planetype;
			cout<<tmpinfo.planetype<<endl;
			json["returnList"][i]["part"][j]["start"]["startDate"]=tmpinfo.startDate;
			cout<<tmpinfo.startDate<<endl;
			json["returnList"][i]["part"][j]["start"]["startTime"]=tmpinfo.startTime;
			cout<<tmpinfo.startTime<<endl;
			json["returnList"][i]["part"][j]["start"]["startCity"]=tmpinfo.startCity;
			cout<<tmpinfo.startCity<<endl;
			json["returnList"][i]["part"][j]["end"]["endDate"]=tmpinfo.endDate;
			cout<<tmpinfo.endDate<<endl;
			json["returnList"][i]["part"][j]["end"]["endTime"]=tmpinfo.endTime;
			cout<<tmpinfo.endTime<<endl;
			json["returnList"][i]["part"][j]["end"]["endCity"]=tmpinfo.endCity;
			cout<<tmpinfo.endCity<<"2"<<endl;
			for(int k=0;k<tmpinfo.cabin.size();k++){
				json["returnList"][i]["part"][j]["cabin"][k]["cabinType"]=tmpinfo.cabin[k].cabintype;
				cout<<tmpinfo.cabin[k].cabintype<<endl;
				json["returnList"][i]["part"][j]["cabin"][k]["num"]=tmpinfo.cabin[k].num;
				cout<<tmpinfo.cabin[k].num<<endl;
				json["returnList"][i]["part"][j]["cabin"][k]["singlePrice"]=tmpinfo.cabin[k].singleprice;
				cout<<tmpinfo.cabin[k].singleprice<<endl;
			}
			json["returnList"][i]["part"][j]["partPrice"]=tmpinfo.partprice;
			cout<<tmpinfo.partprice<<" 1"<<endl;
		}
		
	}
	recover(); 
        std::cout << "-----recv body:"<<json.dump()<<std::endl;
		resp->Json(json);
        std::cout << "recv body 4:"<<std::endl;
	});
	
	// curl -v http://ip:port/json1
    svr.GET("/json1", [](const HttpReq *req, HttpResp *resp)
    {
        Json json;
        json["test"] = 123;
        json["json"] = "test json";
        resp->Json(json);
    });

    // curl -v http://ip:port/json2
    svr.GET("/json2", [](const HttpReq *req, HttpResp *resp)
    {
        std::string valid_text = R"(
        {
            "numbers": [1, 2, 3]
        }
        )";
        resp->Json(valid_text);
    });

    // curl -v http://ip:port/json3
    svr.GET("/json3", [](const HttpReq *req, HttpResp *resp)
    {
        std::string invalid_text = R"(
        {
            "strings": ["extra", "comma", ]
        }
        )";
        resp->Json(invalid_text);
    });

    // recieve json
    //   curl -X POST http://ip:port/json4
    //   -H 'Content-Type: application/json'
    //   -d '{"login":"my_login","password":"my_password"}'
    svr.POST("/json4", [](const HttpReq *req, HttpResp *resp)
    {
        if (req->content_type() != APPLICATION_JSON)
        {
            resp->String("NOT APPLICATION_JSON");
            return;
        }
        fprintf(stderr, "Json : %s", req->json().dump(4).c_str());
    });

    if (svr.start(8888) == 0)
    {
        wait_group.wait();
        svr.stop();
    } else
    {
        fprintf(stderr, "Cannot start server");
        exit(1);
    }
    return 0;
}


void tablefunc()
{
	int i=0;
	FILE *fp;                                    
    char filename[30]="pricetable.txt";
	                               
    if((fp=fopen(filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }       
    while(!feof(fp))                
    {
    	//fscanf(fp,"%s",planeprice[i].carrier);
    	
  		fscanf(fp,"%s",planetable[i].linetable); 
  		//printf("%s\n",planetable[i].linetable);
      	i++;
      	
    }
    fclose(fp);
	table_amount=i;
	//printf("%d",table_amount);
	//printf("%d",price_amount);
}

void seatfunc()
{
	int i=0;
	FILE *fp;                                    
    char filename[20]="seat.txt";
	                               
    if((fp=fopen(filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }       
    while(!feof(fp))                
    {
    	//fscanf(fp,"%s",planeprice[i].carrier);
    	
  		fscanf(fp,"%s%s%s%s%s%s%s%s",planeseat[i].company,planeseat[i].flightNo,planeseat[i].departure,planeseat[i].arrival,planeseat[i].departureDatime,planeseat[i].f_num,planeseat[i].c_num,planeseat[i].y_num); 
  		//printf("%s\n",planeseat[i].company);
      	i++;
      	
    }
    fclose(fp);
	seat_amount=i;
	//printf("%d",price_amount);
}

void pricefunc()
{
	int i=0;
	FILE *fp;                                    
    char filename[20]="price.txt";
	                               
    if((fp=fopen(filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }       
    while(!feof(fp))                
    {
    	//fscanf(fp,"%s",planeprice[i].carrier);
    	
  		fscanf(fp,"%s%s%s%s%s",planeprice[i].carrier,planeprice[i].departure,planeprice[i].arrival,planeprice[i].carbin,planeprice[i].amount); 
  		//printf("%s\n",planeprice[i].carrier);
      	i++;
      	
    }
    fclose(fp);
	price_amount=i;
	//printf("%d",price_amount);
}

void airfunc()
{
    FILE *air_fp;                                    
    char air_filename[20]="air.txt";
	                               
    if((air_fp=fopen(air_filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }     
	int i=0;  
    while(!feof(air_fp))                
    {
  		fscanf(air_fp,"%s%s%s%s%s%s",planeair[i].company,planeair[i].flightNo,planeair[i].departureDatime,planeair[i].arrivalDatetime,planeair[i].departure,planeair[i].arrival);
      	//airmessage_amount++;
      	i++;
    }
    fclose(air_fp);
	airmessage_amount=i;
	//printf("%s",planeair[airmessage_amount-1].company);
}

void BuildCarrier()
{
    for(int i=0;i<24;i++){
        string eair,cair;
        eair=air_e[i],cair=air_c[i];
        carrier_e.insert(pair<string,string>(cair,eair));
    }
    for(int i=0;i<24;i++){
        string eair,cair;
        eair=air_e[i],cair=air_c[i];
        carrier_c.insert(pair<string,string>(eair,cair));
    }
}

void BuildCity()
{
    for(int i=0;i<40;i++){
        string ecity,cctiy;
        ecity=city_e[i],cctiy=city_c[i];
        cityname_e.insert(pair<string,string>(cctiy,ecity));
    }
    for(int i=0;i<40;i++){
        string ecity,cctiy;
        ecity=city_e[i],cctiy=city_c[i];
        cityname_c.insert(pair<string,string>(ecity,cctiy));
    }
}

void BuildCabin()
{
    cabinname.insert(pair<string,string>("f","头等舱"));
    cabinname.insert(pair<string,string>("c","商务舱"));
    cabinname.insert(pair<string,string>("y","经济舱"));
}

void combine_airandseat()
{
    /*前提：airmessage和seat一一对应，顺序也相同*/
    //Air_Message tmp;
    for(int i=0;i<airmessage_amount;i++){
    	Air_Message tmp;
        tmp.carrier=planeair[i].company;
        tmp.acctime=planeair[i].departureDatime;
        tmp.arrivaltime=planeair[i].arrivalDatetime;
        tmp.flightNo=planeair[i].flightNo;
        tmp.departcity=planeair[i].departure;
        tmp.arivalcity=planeair[i].arrival;

        pair<char,char> tmpcabin;
        //tmp.seatnum='0';
        tmpcabin.first='F';tmpcabin.second=planeseat[i].f_num[0];tmp.cabin.push_back(tmpcabin);
        //cout<<planeseat[i].f_num[0];
        //cout<<tmpcabin.second;
        tmp.seatnum=tmpcabin.second;
        tmpcabin.first='C';tmpcabin.second=planeseat[i].c_num[0];tmp.cabin.push_back(tmpcabin);
        //cout<<planeseat[i].c_num[0];
        //cout<<tmpcabin.second;
        tmp.seatnum+=tmpcabin.second-'0';
        tmpcabin.first='Y';tmpcabin.second=planeseat[i].y_num[0];tmp.cabin.push_back(tmpcabin);
        //cout<<tmpcabin.second;
        tmp.seatnum+=tmpcabin.second-'0';
        if(tmp.seatnum>'9')tmp.seatnum='A';
        string str=planeair[i].departureDatime;
        tmp.date=str.substr(0,8);
        
        //cout<<tmp.cabin[0].second<<tmp.cabin[1].second<<tmp.cabin[2].second<<endl;
        All_Message.push_back(tmp);
    }



}

void dealtable()
{
    for(int i=0;i<table_amount;i++){
        PriceTable_Message tmp;
        //七条信息
        string tmptable=planetable[i].linetable;
        int pre_index=0;
        int index=tmptable.find(',',0);
        tmp.seqnum=tmptable.substr(0,index);

        pre_index=index+1;
        index=tmptable.find(',',pre_index);
        tmp.carrier=tmptable.substr(pre_index,index-pre_index);

        pre_index=index+1;
        index=tmptable.find(',',pre_index);
        tmp.departcity=tmptable.substr(pre_index,index-pre_index);

        pre_index=index+1;
        index=tmptable.find(',',pre_index);
        tmp.arivalcity=tmptable.substr(pre_index,index-pre_index);

        pre_index=index+1;
        index=tmptable.find(',',pre_index);
        tmp.nextcarrier=tmptable.substr(pre_index,index-pre_index);

        string tmpagency;
        pre_index=index+1;
        index=tmptable.find(',',pre_index);
        tmpagency=tmptable.substr(pre_index,index-pre_index);
        for(int i=0;i<tmpagency.size();i+=6){
            tmp.agency.push_back(tmpagency.substr(i,6));
        }

        
        pre_index=index+1;
        tmp.surcharge=stoi(tmptable.substr(pre_index,tmptable.size()-pre_index));
		All_Table.push_back(tmp);
    }
}

PriceTable_Message Match_PriceTable(Air_Message partmessage)
{//排序
//考虑找不到的情况
    for(int i=0;i<All_Table.size();i++){
        PriceTable_Message tmptable;
        if(tmptable.carrier==partmessage.carrier){
        	cout<<"yes"<<endl;
            if(tmptable.departcity==""||tmptable.departcity==partmessage.departcity){
                if(tmptable.arivalcity==""||tmptable.arivalcity==partmessage.arivalcity){
                    if(tmptable.surcharge!=-1){
                    	cout<<"yes"<<endl;
                        return tmptable;
                    }
                }
            }
        }
    }
    PriceTable_Message errortable;
	errortable.surcharge=0;
	errortable.nextcarrier="";
	//errortable.agency;
	return errortable; 
}

void Match_AirMessage(string date,string fromcity,string tocity,string passagenum)
{
    OnePart tmp;
    //cout<<date<<fromcity<<tocity<<passagenum<<endl;//
    for(int i=0;i<All_Message.size();i++){
        Air_Message tmpmessage=All_Message[i];
        //cout<<tmpmessage.date<<tmpmessage.departcity<<tmpmessage.arivalcity<<endl;
        if(tmpmessage.date==date&&tmpmessage.departcity==fromcity&&tmpmessage.arivalcity==tocity){
        	//cout<<"yes"<<endl;
            if(tmpmessage.seatnum>=passagenum[0]){
                tmp.flight.push_back(tmpmessage);
            }
        }
    }
    //cout<<tmp.flight.size()<<endl;
    All_Part.push_back(tmp);
}

void Match_Price(string from,string to,string carrier,tableflight& tmp)
{
	//cout<<price_amount<<endl;
    for(int i=0;i<price_amount;i++){
        if(planeprice[i].departure==from&&planeprice[i].arrival==to&&planeprice[i].carrier==carrier){
            if(planeprice[i].carbin[0]=='F')tmp.f_price=planeprice[i].amount;
            else if(planeprice[i].carbin[0]=='C')tmp.c_price=planeprice[i].amount;
            else tmp.y_price=planeprice[i].amount;
        }
    }
    //cout<<from<<" "<<to<<" "<<carrier<<endl;
    //cout<<tmp.c_price<<" "<<tmp.f_price<<" "<<tmp.y_price<<endl;
    //cout<<"pricedsf"<<endl;
    return;
}

int Search1(int task_num)
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
    return min_part;
}

int Find_Agency(vector<string> agencys)
{
    if(only_agency=="")return 1;
    if(agencys.size()==0)return 1;
    for(int i=0;i<agencys.size();i++){
        if(agencys[i]==only_agency){
            return 1;
        }
    }
    return ERROR2;
}

void Form_Part()
{
    for(int i=0;i<crequest.travelnum;i++){
    	//cout<<crequest.travelnum;
        Match_AirMessage(crequest.daytime[i],crequest.fromto_city[i].first,crequest.fromto_city[i].second,crequest.custnum);
    }
}

void Search3(string only_carrier,int floor,int lastfloor)
{
	//cout<<only_carrier<<" "<<floor<<" "<<lastfloor<<endl;

    if(floor==lastfloor){
        //cout<<lastfloor<<"0988"<<endl;
        path1.push_back(tmp_stack1);
        //tmp_stack1.pop();
        //cout<<path1.size()<<"sdfdf"<<endl;
        return;
    }
    //递归结束条件
    vector<tableflight> tmp_ans;
    vector<Air_Message> tmp_air;
    PriceTable_Message tmp_table;
    int tmp_price;

    //tmp_price=All_Part[floor].price.basic_price;
    tmp_air=All_Part[floor].flight;
    if(only_carrier!=""){  //若指定nextcarrier//多满足
        //cout<<"search3dd"<<endl;
        //cout<<only_carrier<<endl;
        for(int i=0;i<tmp_air.size();i++){
            if(tmp_air[i].carrier==only_carrier){
                /*查找运价规则*/
                tmp_table=Match_PriceTable(tmp_air[i]);
                /*没有运价规则该如何*/
                if(Find_Agency(tmp_table.agency)!=ERROR2){  //航班是否有该代理人
                    tableflight tmp_taf;

                    //tmp_taf.singleprice=
                    Match_Price(tmp_air[i].departcity,tmp_air[i].arivalcity,tmp_air[i].carrier,tmp_taf);
                    tmp_taf.carrier=tmp_air[i].carrier;
                    tmp_taf.surcharge=tmp_table.surcharge;

                    if(tmp_taf.surcharge==-1)continue;
                    tmp_taf.nextcarrier=tmp_table.nextcarrier;
                    tmp_taf.flightNo=tmp_air[i].flightNo;
                    tmp_taf.acctime=tmp_air[i].acctime;
                    tmp_taf.arrivaltime=tmp_air[i].arrivaltime;
                    /*选择每个舱位的数量*/
                    for(int j=0;j<tmp_air[i].cabin.size();j++){
                        if(tmp_air[i].cabin[j].first=='C')tmp_taf.c_num=tmp_air[i].cabin[j].second;
                        else if(tmp_air[i].cabin[j].first=='Y')tmp_taf.y_num=tmp_air[i].cabin[j].second;
                        else tmp_taf.f_num=tmp_air[i].cabin[j].second;
                    }

                   
                    

                    tmp_ans.push_back(tmp_taf);
                }
                
            }
            //else return;
        }
        //cout<<tmp_ans.size()<<"fgh"<<endl;
        int tmpsize=tmp_ans.size();
        //cout<<tmpsize<<floor<<endl;
        //if(tmp_ans.size()<=0)continue;
        for(int i=0;i<tmpsize;i++){
            //cout<<"hjgjj"<<endl;
            tmp_stack1.push(tmp_ans[i]);
            Search3(tmp_ans[i].nextcarrier,floor+1,lastfloor);
            tmp_stack1.pop();
            //if(Search3(tmp_ans[i].nextcarrier,floor+1)!=ERROR2){
                /*加入答案队列*/

            //}

        }
        return;
    }



    else{
        //cout<<"kjhjkhihiouuhiuogb"<<endl;
        for(int i=0;i<tmp_air.size();i++){           
            /*查找运价规则*/
            tmp_table=Match_PriceTable(tmp_air[i]);
            if(Find_Agency(tmp_table.agency)!=ERROR2){  //航班是否有该代理人
                tableflight tmp_taf;
                Match_Price(tmp_air[i].departcity,tmp_air[i].arivalcity,tmp_air[i].carrier,tmp_taf);
                tmp_taf.carrier=tmp_air[i].carrier;
                tmp_taf.surcharge=tmp_table.surcharge;
                if(tmp_taf.surcharge==-1)continue;

                tmp_taf.nextcarrier=tmp_table.nextcarrier;
                tmp_taf.flightNo=tmp_air[i].flightNo;
                tmp_taf.acctime=tmp_air[i].acctime;
                tmp_taf.arrivaltime=tmp_air[i].arrivaltime;
                /*选择每个舱位的数量*/

                for(int j=0;j<tmp_air[i].cabin.size();j++){
                    if(tmp_air[i].cabin[j].first=='C')tmp_taf.c_num=tmp_air[i].cabin[j].second;
                    else if(tmp_air[i].cabin[j].first=='Y')tmp_taf.y_num=tmp_air[i].cabin[j].second;
                    else tmp_taf.f_num=tmp_air[i].cabin[j].second;
                }

                tmp_ans.push_back(tmp_taf);
            }
                
            
            //else return;
        }
        
        int tmpsize=tmp_ans.size();
        //cout<<tmpsize<<floor<<endl;
        for(int i=0;i<tmpsize;i++){
            tmp_stack1.push(tmp_ans[i]);
            Search3(tmp_ans[i].nextcarrier,floor+1,lastfloor);
            tmp_stack1.pop();

        }
    }
}

int cul(char a_type,int a,int a_num,char b_type,int b,int b_num,char c_type,int c,int c_num,partinfo& info)
{
    cabininfo cabin;
    int people=traveller;
    int sum=0;
    if(a_num>=people){
        cabin.cabintype=a_type;cabin.num=to_string(traveller);cabin.singleprice=to_string(a);
        info.cabin.push_back(cabin);
        return a*traveller;
    }
    else{
        cabin.cabintype=a_type;cabin.num=to_string(a_num);cabin.singleprice=to_string(a);
        info.cabin.push_back(cabin);
        people-=a_num;sum+=a*a_num;
        if(b_num>=people){
            cabin.cabintype=b_type;cabin.num=to_string(people);cabin.singleprice=to_string(b);
            info.cabin.push_back(cabin);
            return sum+people*b;
        }
        else {
            cabin.cabintype=b_type;cabin.num=to_string(b_num);cabin.singleprice=to_string(b);
            info.cabin.push_back(cabin);
            sum+=b*b_num;
            cabin.cabintype=c_type;cabin.num=to_string(people-b_num);cabin.singleprice=to_string(c);
            info.cabin.push_back(cabin);
            return sum+(people-b_num)*c;
            
        }
    }
}

void culprice(partinfo& info,tableflight part)
{
    int sumprice=0;
    //cout<<part.c_price<<" "<<part.y_price<<" "<<part.f_price<<endl;
    
    int c_num=part.c_num[0]-'0';int c_price=stoi(part.c_price);
    int f_num=part.f_num[0]-'0';int f_price=stoi(part.f_price);
    int y_num=part.y_num[0]-'0';int y_price=stoi(part.y_price);
    
    if(y_price<c_price){
        if(y_price<f_price){
            if(c_price<f_price)info.partprice=cul('y',y_price,y_num,'c',c_price,c_num,'f',f_price,f_num,info);
            else info.partprice=cul('y',y_price,y_num,'f',f_price,f_num,'c',c_price,c_num,info);
        }
        else{
            info.partprice=cul('f',f_price,f_num,'y',y_price,y_num,'c',c_price,c_num,info);
        }
    }
    else{
        if(y_price<f_price)info.partprice=cul('c',c_price,c_num,'y',y_price,y_num,'f',f_price,f_num,info);
        else{
            if(c_price>f_price)info.partprice=cul('f',f_price,f_num,'c',c_price,c_num,'y',y_price,y_num,info);
            else info.partprice=cul('c',c_price,c_num,'f',f_price,f_num,'y',y_price,y_num,info);
        }
        
    }
    
    
}

bool CheakOne(string predate,string pretime,string backdate,string backtime)
{

    if(predate==previousdate){
        int time1=stoi(previoustime);
        int time2=stoi(pretime);
        previousdate=backdate;
        previoustime=backtime;
        if(time2-200>=time1){
            return true;
        }
        else return false;
    }
    else{
        previousdate=backdate;
        previoustime=backtime;
        return true;
    }
}

void Printcc(partans& oneans)
{
	//cout<<oneans.allprice<<endl<<oneans.anency<<endl;
	map<string,string>::iterator iter;
	for(int i=0;i<oneans.part.size();i++){
		if(oneans.part[i].carrier!="**"){
			iter=carrier_c.find(oneans.part[i].carrier);
			oneans.part[i].carrier=iter->second;
		}
		
		//cout<<oneans.part[i].carrier<<endl<<oneans.part[i].planetype<<endl;
		
		string year,month,day,hour,minute;
		year=oneans.part[i].endDate.substr(0,4);month=oneans.part[i].endDate.substr(4,2);
		day=oneans.part[i].endDate.substr(6,2);
		oneans.part[i].endDate=year+"年"+month+"月"+day+"日";
		hour=oneans.part[i].endTime.substr(0,2);
		minute=oneans.part[i].endTime.substr(2,2);
		oneans.part[i].endTime=hour+":"+minute;
        //cout<<oneans.part[i].endDate<<oneans.part[i].endTime<<endl;
        
        year=oneans.part[i].startDate.substr(0,4);month=oneans.part[i].startDate.substr(4,2);
		day=oneans.part[i].startDate.substr(6,2);
		oneans.part[i].startDate=year+"年"+month+"月"+day+"日";
		hour=oneans.part[i].startTime.substr(0,2);
		minute=oneans.part[i].startTime.substr(2,2);
		oneans.part[i].startTime=hour+":"+minute;
        //cout<<oneans.part[i].startDate<<oneans.part[i].startTime<<endl;
        
        //cout<<oneans.part[i].startCity<<oneans.part[i].endCity<<endl;
        for(int j=0;j<oneans.part[i].cabin.size();j++){
        	iter=cabinname.find(oneans.part[i].cabin[j].cabintype);
        	oneans.part[i].cabin[j].cabintype=iter->second;
            //cout<<oneans.part[i].cabin[j].cabintype<<oneans.part[i].cabin[j].num<<oneans.part[i].cabin[j].singleprice<<endl;
        }
	}
}
void Printdd(tableflight a)
{
	cout<<a.acctime<<endl<<a.arivalcity<<endl<<a.arrivaltime<<endl;
	cout<<a.carrier<<endl<<a.c_num<<endl<<a.c_price<<endl;
	cout<<a.departcity<<endl<<a.flightNo<<endl<<a.f_num<<endl<<a.f_price<<endl;
	cout<<a.nextcarrier<<endl<<a.surcharge<<endl<<a.y_num<<endl<<a.y_price<<endl;
}
void deal(PATHTYPE anspath)
{
	//cout<<anspath.size()<<"df"<<endl;
    for(int i=0;i<anspath.size();i++){
        stack<tableflight> onestack=anspath[i];
        partans oneans;
        int sumprice=0;
        oneans.anency=only_agency;
        //cout<<only_agency<<endl;
        int tmpsize=onestack.size();
        //cout<<onestack.size()<<endl;
         map<string,string>::iterator iter;
        for(int j=0;j<tmpsize;j++){
            tableflight tmp_part=onestack.top();onestack.pop();
            partinfo tmp_info;
            tmp_info.carrier=tmp_part.carrier;
            
            tmp_info.planetype=tmp_part.flightNo;
             
            iter=cityname_c.find(crequest.fromto_city[tmpsize-j-1].first);
			tmp_info.startCity=iter->second;
        	iter=cityname_c.find(crequest.fromto_city[tmpsize-j-1].second);
			tmp_info.endCity=iter->second;
		
            //=tmp_part.departcity;
            tmp_info.startDate=tmp_part.acctime.substr(0,8);
            tmp_info.startTime=tmp_part.acctime.substr(8,4);
            
            //=
            tmp_info.endDate=tmp_part.arrivaltime.substr(0,8);
            tmp_info.endTime=tmp_part.arrivaltime.substr(8,4);
            //cout<<tmp_info.carrier<<endl<<only_agency<<endl;
            //cout<<tmp_info.startDate<<tmp_info.endDate<<endl;
            if(CheakOne(tmp_info.startDate,tmp_info.startTime,tmp_info.endDate,tmp_info.endTime)){
                culprice(tmp_info,tmp_part);
                double rate=1.0*tmp_part.surcharge/100;
                sumprice+=tmp_info.partprice*(1+rate);//
                oneans.part.push_back(tmp_info);
            }
            
        }
        oneans.allprice=sumprice;
        if(oneans.allprice>0){
        	if(ans.size()<request_ans)ans.push(oneans);
        	else {ans.push(oneans);ans.pop();}
		}
		//Printcc(oneans);
        //cout<<"------------------"<<endl;
        //ans.push(oneans);//优先队列
        
    }
}

void Search6()
{
    PATHTYPE anspath;
    PATHTYPE tmpanspath;
    anspath=ALL_PATH[pathnum-1];
    //cout<<anspath[0].size();
    for(int i=pathnum-2;i>=0;i--){
        PATHTYPE tmp_path;
		//cout<<ALL_PATH[i][0].size()<<endl;
        for(int j=0;j<ALL_PATH[i].size();j++){
        	//cout<<"sd"<<endl;
            stack<tableflight> stack1;
            stack<tableflight> restack;
            stack1=ALL_PATH[i][j];
            int stack_size=stack1.size();

            for(int k=0;k<stack_size;k++){
                restack.push(stack1.top());stack1.pop();
            }
            //cout<<restack.size()<<endl;
            tmp_path.push_back(restack);
        }
        for(int j=0;j<tmp_path.size();j++){
            for(int k=0;k<anspath.size();k++){
                stack<tableflight> stack1,stack2;
                tableflight table1,table2; 
                stack1=tmp_path[j];stack2=anspath[k];
                table1=stack1.top();table2=stack2.top();
                if(table2.nextcarrier==table1.carrier||table2.nextcarrier==""){
                    int stacksize=stack1.size();
                    for(int p=0;p<stacksize;p++){
                        stack2.push(stack1.top());stack1.pop();
                    }
                    tmpanspath.push_back(stack2);
                    //cout<<stack2.size()<<endl;
                }
            }
        }
        anspath=tmpanspath;
        
        //for(int x=0;x<anspath.size();x++){
        //	stack<tableflight> tmp=anspath
		//}
        
        //cout<<"1"<<endl;
    }
    //cout<<"ok"<<endl;
    //cout<<anspath.size()<<endl;
    //for(int i=0;i<anspath[0].size();i++){
    	//Printdd(anspath[0].top());
    	//anspath[0].pop();
	//}
    
    deal(anspath);
}



void Search2(int startpart,int lastpart)
{
	//cout<<startpart<<lastpart<<"sdf"<<endl;
    if(lastpart<=0){
    	//cout<<pathnum<<endl;
    	vector<stack<tableflight> >tmp=ALL_PATH[0];
    	//cout<<tmp.size()<<endl;
    	//tableflight tmptable=tmp.top();
    	//cout<<tmptable.acctime<<endl;
        Search6();
        //pathnum=0;
        //cout<<"ok"<<endl;
        //for(int i=0;i<pathnum;i++){
        //	cout<<"ok"<<ALL_PATH[i].size()<<endl;
		//}
		return;
    }


    vector<Air_Message> tmp_air=All_Part[startpart].flight;
    //cout<<tmp_flight.size()<<"dsf"<<endl;
    PriceTable_Message tmp_table;

    if(only_agency==""){
        for(int i=0;i<tmp_air.size();i++){
        /*查找运价规则*/
            tmp_table=Match_PriceTable(tmp_air[i]);
			//cout<<tmp_table.surcharge<<endl; 
            if(request_agency.size()==0)request_agency=tmp_table.agency;
            for(int j=0;j<request_agency.size();j++){
                only_agency=request_agency[j];
                //cout<<"j"<<j<<endl; 
                //for(int k=0;k<tmp_table.agency.size();k++){
                    if(Find_Agency(tmp_table.agency)!=ERROR2){  //匹配成功
                        //request_agency[j]==tmp_table.agency[k]
                        //cout<<"fgfffff"<<endl;
                        tableflight tmp_taf;
                        Match_Price(tmp_air[i].departcity,tmp_air[i].arivalcity,tmp_air[i].carrier,tmp_taf);
                        tmp_taf.carrier=tmp_air[i].carrier;
                        tmp_taf.surcharge=tmp_table.surcharge;
                        
                        //cout<<"dfsf"<<endl;
                        if(tmp_taf.surcharge==-1)continue;
                        //cout<<"dfsf"<<endl;
                        tmp_taf.nextcarrier=tmp_table.nextcarrier;
                        tmp_taf.flightNo=tmp_air[i].flightNo;
                        tmp_taf.acctime=tmp_air[i].acctime;
                        tmp_taf.arrivaltime=tmp_air[i].arrivaltime;
                        /*选择每个舱位的数量*/

                        for(int j=0;j<tmp_air[i].cabin.size();j++){
                            if(tmp_air[i].cabin[j].first=='C')tmp_taf.c_num=tmp_air[i].cabin[j].second;
                            else if(tmp_air[i].cabin[j].first=='Y')tmp_taf.y_num=tmp_air[i].cabin[j].second;
                            else tmp_taf.f_num=tmp_air[i].cabin[j].second;
                        }
                        //Printdd(tmp_taf);
                        tmp_stack1.push(tmp_taf);

                        //cout<<"dfs"<<endl;
                        Search3(tmp_table.nextcarrier,startpart+1,lastpart);
                        //cout<<tmp_stack1.top().acctime<<"dfdiltjghiots"<<endl;
                        tmp_stack1.pop();
                        //Search4(tmp_flight[i].carrier,startpart-1,1);???往上搜可能用不到
                        int newstartpart=Search1(startpart);
                        ALL_PATH[pathnum++]=path1;
                        path1.clear();
                        Search2(newstartpart,startpart);
                        pathnum--;
                        only_agency="";
                    }
                //}

                
            }
        }
    }
    else{
        for(int i=0;i<tmp_air.size();i++){
        /*查找运价规则*/
        tmp_table=Match_PriceTable(tmp_air[i]);
		//cout<<tmp_table.surcharge<<endl; 

            //for(int j=0;j<request_agency.size();j++){
                //if(only_agency=="")only_agency=request_agency[j];
                //for(int k=0;k<tmp_table.agency.size();k++){
                    if(Find_Agency(tmp_table.agency)!=ERROR2){  //匹配成功
                        //request_agency[j]==tmp_table.agency[k]
                        //cout<<"fgfffff"<<endl;
                        tableflight tmp_taf;
                        Match_Price(tmp_air[i].departcity,tmp_air[i].arivalcity,tmp_air[i].carrier,tmp_taf);
                        tmp_taf.carrier=tmp_air[i].carrier;
                        tmp_taf.surcharge=tmp_table.surcharge;
                        if(tmp_taf.surcharge==-1)continue;
                        tmp_taf.nextcarrier=tmp_table.nextcarrier;
                        tmp_taf.flightNo=tmp_air[i].flightNo;
                        tmp_taf.acctime=tmp_air[i].acctime;
                        tmp_taf.arrivaltime=tmp_air[i].arrivaltime;
                        /*选择每个舱位的数量*/

                        for(int j=0;j<tmp_air[i].cabin.size();j++){
                            if(tmp_air[i].cabin[j].first=='C')tmp_taf.c_num=tmp_air[i].cabin[j].second;
                            else if(tmp_air[i].cabin[j].first=='Y')tmp_taf.y_num=tmp_air[i].cabin[j].second;
                            else tmp_taf.f_num=tmp_air[i].cabin[j].second;
                        }
                        tmp_stack1.push(tmp_taf);

                        //cout<<"dfs"<<endl;
                        Search3(tmp_table.nextcarrier,startpart+1,lastpart);
                        //cout<<tmp_stack1.top().acctime<<"dfdiltjghiots"<<endl;
                        tmp_stack1.pop();
                        //Search4(tmp_flight[i].carrier,startpart-1,1);???往上搜可能用不到
                        int newstartpart=Search1(startpart);
                        ALL_PATH[pathnum++]=path1; 
                        path1.clear();
                        Search2(newstartpart,startpart);
                        pathnum--;
                    }
                //}

                
            //}
        }
    }
    /*
    for(int i=0;i<tmp_air.size();i++){
        /*查找运价规则/*
        tmp_table=Match_PriceTable(tmp_air[i]);
		//cout<<tmp_table.surcharge<<endl; 

        for(int j=0;j<request_agency.size();j++){
        	if(only_agency=="")only_agency=request_agency[j];
            //for(int k=0;k<tmp_table.agency.size();k++){
                if(Find_Agency(tmp_table.agency)!=ERROR2){  //匹配成功
                    //request_agency[j]==tmp_table.agency[k]
					//cout<<"fgfffff"<<endl;
                    tableflight tmp_taf;
                    Match_Price(tmp_air[i].departcity,tmp_air[i].arivalcity,tmp_air[i].carrier,tmp_taf);
                    tmp_taf.carrier=tmp_air[i].carrier;
                    tmp_taf.surcharge=tmp_table.surcharge;
                    if(tmp_taf.surcharge==-1)continue;
                    tmp_taf.nextcarrier=tmp_table.nextcarrier;
                    tmp_taf.flightNo=tmp_air[i].flightNo;
                    tmp_taf.acctime=tmp_air[i].acctime;
                    /*选择每个舱位的数量/*

                     for(int j=0;j<tmp_air[i].cabin.size();j++){
                        if(tmp_air[i].cabin[j].first=='C')tmp_taf.c_num=tmp_air[i].cabin[j].second;
                        else if(tmp_air[i].cabin[j].first=='Y')tmp_taf.y_num=tmp_air[i].cabin[j].second;
                        else tmp_taf.f_num=tmp_air[i].cabin[j].second;
                    }
                    tmp_stack1.push(tmp_taf);

                    //cout<<"dfs"<<endl;
                    Search3(tmp_table.nextcarrier,startpart+1,lastpart);
                    //cout<<tmp_stack1.top().acctime<<"dfdiltjghiots"<<endl;
                    tmp_stack1.pop();
                    //Search4(tmp_flight[i].carrier,startpart-1,1);???往上搜可能用不到
                }
            //}

            int newstartpart=Search1(startpart);
            ALL_PATH[pathnum++]=path1;
            path1.clear();
            Search2(newstartpart,startpart);
            pathnum--;
        }
    }
    */
}





void Search4(string only_carrier,int floor,int firstfloor)
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
            if(Find_Agency(tmp_table.agency)!=ERROR2&&(tmp_table.nextcarrier==only_carrier||tmp_table.nextcarrier=="")){  //航班是否有该代理人
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
    if(tmp_ans.size()==0) return;
    for(int i=0;i<tmp_ans.size();i++){
        tmp_stack2.push(tmp_ans[i]);
        Search3(tmp_ans[i].nextcarrier,floor+1,firstfloor);
        tmp_stack2.pop();

    }
    
}





void Search5(int task_num)
{
    //if(task_num<=0)return;
    //cout<<"flaggg"<<endl;
    int startpart=Search1(task_num);
    //cout<<startpart<<"Dsf"<<endl;
    Search2(startpart,task_num);//??
    //ALL_PATH[pathnum++]=path1;
    //path1.clear();
    //Search5(startpart);//
    

}

void dealempty()
{
	partans tmpans;
	int tmpsize=crequest.fromto_city.size();
	map<string,string>::iterator iter;
	for(int i=0;i<tmpsize;i++){
		partinfo tmp_info;
	    //partinfo tmp_info;
	    tmp_info.carrier="**";
	    
	    tmp_info.planetype="****";
	     
	    iter=cityname_c.find(crequest.fromto_city[tmpsize-i-1].first);
		tmp_info.startCity=iter->second;
		iter=cityname_c.find(crequest.fromto_city[tmpsize-i-1].second);
		tmp_info.endCity=iter->second;
	
	    //=tmp_part.departcity;
	    tmp_info.startDate=crequest.daytime[tmpsize-i-1];
	    tmp_info.startTime="****";
	    
	    //=
	    tmp_info.endDate=crequest.daytime[tmpsize-i-1];
	    tmp_info.endTime="****";
	    //cout<<tmp_info.carrier<<endl<<only_agency<<endl;
	    //cout<<tmp_info.startDate<<tmp_info.endDate<<endl;
	    cabininfo tmpcabin;tmpcabin.cabintype="y";tmpcabin.singleprice="****";tmpcabin.num="0";
		tmp_info.cabin.push_back(tmpcabin); 
	    tmpans.part.push_back(tmp_info);
	}
	ans.push(tmpans);
	//cout<<ans.size();
}
void recover()
{
	//cout<<1<<endl;
	//All_Message.clear();
	//cout<<All_Message.size(); 
	//All_Table.clear();
	//All_Part.clear();
	crequest.daytime.clear();
	//cout<<crequest.daytime.size();
	crequest.fromto_city.clear();
	//cout<<crequest.fromto_city.size();
	//cout<<crequest.agency.size();
	//if(!crequest.agency.size())crequest.agency.pop();
	//request_agency.clear();
	//cout<<1<<endl;
	request_agency.clear();
	All_Part.clear();
	task=0;
	traveller=0;
	request_ans=0;
	while(!tmp_stack1.empty())tmp_stack1.pop();
	path1.clear();
	while(!tmp_stack2.empty())tmp_stack2.pop();
	path2.clear();
	while(!ans.empty())ans.pop();
	previousdate="0000";
	previoustime="";
	
}
