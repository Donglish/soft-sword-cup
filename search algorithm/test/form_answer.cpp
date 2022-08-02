#include"form_answer.h"

//vector<partans> ans;


bool operator<(partans a,partans b){
    return a.allprice<b.allprice;
}
priority_queue<partans> ans;

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

string previousdate="0000";
string previoustime;
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
        for(int j=0;j<tmpsize;j++){
            tableflight tmp_part=onestack.top();onestack.pop();
            partinfo tmp_info;
            tmp_info.carrier=tmp_part.carrier;
            
            tmp_info.planetype=tmp_part.flightNo;
            tmp_info.startCity=tmp_part.departcity;
            tmp_info.startDate=tmp_part.acctime.substr(0,8);
            tmp_info.startTime=tmp_part.acctime.substr(8,4);
            tmp_info.endCity=tmp_part.arivalcity;
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
        //Printcc(oneans);
        //cout<<"------------------"<<endl;
        
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
        
    }
    deal(anspath);
}