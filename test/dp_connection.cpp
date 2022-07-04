#include"connection_pool.h"
#include<string>
#include<iostream>
#include<vector>
#include<map>
using namespace std;
ConnPool *connpoool = ConnPool::GetInstance();
Connection *con;
Statement *state;
ResultSet *result;
void init(){
	con = connpool->GetConnection();
	state = con->createStatement();
	state->execute("use flightdb");
}
vector<map<string,string>> selectPlane(string departure,string arrival,string daytime){
	result = state->executeQuery("select seatF,seatC,seatY,flightNo,departureDatetime,arrivalDatetime,carrier,from flightinfo where departue="+departure+" and arrival="+arrival+" and departureDate=" + datetime);
	vector<map<string,string>> res;
	while(result->next()){
		map<string,string> tmp;
		tmp.insert(pair<string,string>("departureDatetime",result->getString("departureDatetime")));
		tmp.insert(pair<string,string>("arrivalDatetime",result->getString("arrivalDatetime")));
		tmp.insert(pair<string,string>("carrier",result->getString("carrier")));	
		tmp.insert(pair<string,string>("flightNo",result->getString("flightNo")));
		tmp.insert(pair<string,string>("seatF",result->getString("seatF")));
		tmp.insert(pair<string,string>("seatC",result->getString("seatC")));
		tmp.insert(pair<string,string>("seatY",result->getString("seatY")));
		res.push_back(tmp);
	}
	return res;
}
map<string,string> selectRule(string carrier,string departure_arrival){
	result = state->executeQuery("select agencies,surcharge,nextCarrier from pirce_rule_info where carrier=" +carrier+" and departure_arrival="+departue_arrival);
	map<string,string> res;
	while(result->next){
		res.insert(pair<string,string>("agencies",result->getString("agencies")));
		res.insert(pair<string,string>("surcharge",std::to_string(result->getInt("surcharge"))));
		res.insert(pair<string,string>("nextCarrier",result->getStrng("nextCarrier")));
		break;
	}
	return res;
}
map<string,string> selectPrice(string departure,string arrival,string carrier){
	map<string,string> res;
	result = state->executeQuery("select cabin,amount from priceinfo where departure=" +departure+" and arrival="+arrival+" and carrier=" +carrier);
	while(result->next()){
		char ch = result->getChar("cabin");
		string cabin(1,ch);
		res.insert(pair<string,string>("cabin",cabin));
		res.insert(pair<string,string>("amount",res->getString("amount")));
		break;
	}
	return res;
}
