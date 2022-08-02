#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <jsoncpp/json/json.h> 
#include <sstream>
#include "json.hpp"
#include "search.h"
#include "match.h"
#include "readtxt.h"
#include "preprocessing.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "customer.h"
using namespace std;


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
    
    //inJson提取 
    while(1){
    	
	
    //crequest.custnum=inJson["passengerNum"];
    cin>>crequest.custnum;
    //crequest.ansnum=stoi(inJson["planeNum"]);
    cin>>crequest.travelnum;
    //crequest.travelnum=inJson["planeList"].size();
    cin>>crequest.ansnum;
    
    request_ans=crequest.ansnum;
    traveller=stoi(crequest.custnum);
    
    for(int i=0;i<crequest.travelnum;i++){
    	string datetime;
    	//datetime=inJson["planeList"][i]["date"];
    	cin>>datetime;
		datetime=datetime.erase(4,1); datetime=datetime.erase(6,1);
		datetime=datetime.substr(0,8);
		crequest.daytime.push_back(datetime);
		pair<string,string> tmpcity;
		
		string fromcity,tocity;
		//fromcity=inJson["planeList"][i]["fromCityAndToCity"]["fromCity"];
		//tocity=inJson["planeList"][i]["fromCityAndToCity"]["toCity"];
		cin>>fromcity;
		cin>>tocity;
		map<string,string>::iterator iter=cityname_e.find(fromcity);
		tmpcity.first=iter->second;
        iter=cityname_e.find(tocity);
		tmpcity.second=iter->second;
        crequest.fromto_city.push_back(tmpcity);
	}
  
    int agencynum=1;
    string tmpstr;
    //tmpstr=inJson["agentList"][0];
    cin>>tmpstr;
    request_agency.push_back(tmpstr);
   
    Form_Part();
    
	//cout<<All_Message.size()<<"-----------------"<<endl;
    Search5(crequest.travelnum);
    if(ans.size()==0)dealempty(); 
    int anssize=ans.size();
    
	//返回json的构造 
	 
	//Json json;
	for(int i=0;i<anssize;i++){
		partans tmpans=ans.top();
    	Printcc(tmpans);
		ans.pop();
		for(int j=0;j<tmpans.part.size();j++){
			partinfo tmpinfo=tmpans.part[tmpans.part.size()-j-1];
			//json["returnList"][i]["part"][j]["planeInfo"]["companyName"]=tmpinfo.carrier;
			cout<<tmpinfo.carrier<<endl;
			//json["returnList"][i]["part"][j]["planeInfo"]["planeType"]=tmpinfo.planetype;
			cout<<tmpinfo.planetype<<endl;
			//json["returnList"][i]["part"][j]["start"]["startDate"]=tmpinfo.startDate;
			cout<<tmpinfo.startDate<<endl;
			//json["returnList"][i]["part"][j]["start"]["startTime"]=tmpinfo.startTime;
			cout<<tmpinfo.startTime<<endl;
			//json["returnList"][i]["part"][j]["start"]["startCity"]=tmpinfo.startCity;
			cout<<tmpinfo.startCity<<endl;
			//json["returnList"][i]["part"][j]["end"]["endDate"]=tmpinfo.endDate;
			cout<<tmpinfo.endDate<<endl;
			//json["returnList"][i]["part"][j]["end"]["endTime"]=tmpinfo.endTime;
			cout<<tmpinfo.endTime<<endl;
			//json["returnList"][i]["part"][j]["end"]["endCity"]=tmpinfo.endCity;
			cout<<tmpinfo.endCity<<endl;
			for(int k=0;k<tmpinfo.cabin.size();k++){
				//json["returnList"][i]["part"][j]["cabin"][k]["cabinType"]=tmpinfo.cabin[k].cabintype;
				cout<<tmpinfo.cabin[k].cabintype<<endl;
				//json["returnList"][i]["part"][j]["cabin"][k]["num"]=tmpinfo.cabin[k].num;
				cout<<tmpinfo.cabin[k].num<<endl;
				//json["returnList"][i]["part"][j]["cabin"][k]["singlePrice"]=tmpinfo.cabin[k].singleprice;
				cout<<tmpinfo.cabin[k].singleprice<<endl;
			}
			//json["returnList"][i]["part"][j]["partPrice"]=tmpinfo.partprice;
			cout<<tmpinfo.partprice<<endl;
		}
		
	}
	recover();
	}
}
 








