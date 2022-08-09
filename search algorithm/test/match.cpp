#include"match.h"

PriceTable_Message Match_PriceTable(Air_Message partmessage)
{//排序
//考虑找不到的情况
    for(int i=0;i<All_Table.size();i++){
        PriceTable_Message tmptable;
        if(tmptable.carrier==partmessage.carrier){
        	//cout<<"yes"<<endl;
            if(tmptable.departcity==""||tmptable.departcity==partmessage.departcity){
                if(tmptable.arivalcity==""||tmptable.arivalcity==partmessage.arivalcity){
                    if(tmptable.surcharge!=-1){
                    	//cout<<"yes"<<endl;
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