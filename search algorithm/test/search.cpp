#include"search.h"

int Find_Agency(vector<string> agencys)
{
    if(only_agency=="")return 1;
    if(agencys.size()==0)return 1;
    for(int i=0;i<agencys.size();i++){
        if(agencys[i]==only_agency){
            return 1;
        }
    }
    return -2;
}

int Search1(int task_num)
{
    int minnum_flight=10000;
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
int pathnum;





void Search2(int startpart,int lastpart)
{
	//cout<<startpart<<lastpart<<"sdf"<<endl;
    if(lastpart<=0){
    	//cout<<pathnum<<endl;
    	vector<stack<tableflight> >tmp=ALL_PATH[0];	
        Search6();
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
    
}









void Search5(int task_num)
{
    int startpart=Search1(task_num);
    Search2(startpart,task_num);//??
}
