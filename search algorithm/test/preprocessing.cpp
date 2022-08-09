#include"preprocessing.h"
#include"readtxt.h"
#include"search.h"
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



void dealjson(string ss)
{
	
	Json::Reader reader;
	Json::Value planeInfo;
	vector<string> requestAgency;
	vector<string> date;
	vector<pair<string,string> >from_to_city;
	string passengerNum;
	string planeNum;
	
	if(reader.parse(ss,planeInfo)){
		passengerNum=planeInfo["passengerNum"].asString();
		planeNum=planeInfo["planeNum"].asString();
		
		const Json::Value agentList=planeInfo["agentList"];
		for(unsigned int i=0;i<agentList.size();i++)
		{
			string tmpstr;
			tmpstr=agentList[i].asString();
			requestAgency.push_back(tmpstr);
		}
		const Json::Value planeList=planeInfo["planeList"];
		for(unsigned int i=0;i<planeList.size();i++)
		{
			Json::Value tmp;
			tmp=planeList[i];
			string tmpdate;
			tmpdate=tmp["date"].asString();
			date.push_back(tmpdate);
			Json::Value fromto;
			fromto=tmp["fromCityAndToCity"];
			pair<string,string> param;
			param.first=fromto["fromCity"].asString();
			param.second=fromto["toCity"].asString();
			from_to_city.push_back(param);
		}
	}
	//cout<<passengerNum<<endl<<planeNum<<endl;
	for(int i=0;i<requestAgency.size();i++){
		//cout<<requestAgency[i]<<endl;
	}
	for(int i=0;i<date.size();i++){
		//cout<<date[0]<<" "<<from_to_city[i].first<<" "<<from_to_city[i].second<<endl;
	}
	
	//Json::StreamWriterBuilder builder;
    //const string res_body = Json::writeString(builder, planeInfo);
	//cout<<res_body<<endl;
	
	//Json::StreamWriterBuilder writerBuilder;
	//std::unique_ptr<Json::StreamWriter> json_write(writerBuilder.newStreamWriter());
	//std::ostringstream ss;
	//json_write->write(planeInfo, &ss);
	//std::string strContent = ss.str();
	//string laser = "{\"data\":[{\"createdAt\":\"2016-08-11 04:08:30\",\"dataFileName\":\"40dd8fcd-5e6d-4890-b620-88882d9d3977.data\",\"id\":0,\"mapInfo\":{\"gridHeight\":992,\"gridWidth\":992,\"originX\":-24.8,\"originY\":-24.8,\"resolution\":0.05000000074505806},\"name\":\"demo\",\"status\":4}],\"successed\":true}";
	//Json::Value tree;
	//Json::String err;
	//Json::CharReaderBuilder reader;
	//std::unique_ptr<Json::CharReader>const json_read(reader.newCharReader());
	//json_read->parse(ss.c_str(), ss.c_str() + ss.length(), &tree);

	//std::cout << strContent << std::endl;

	
}