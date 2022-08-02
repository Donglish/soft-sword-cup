#include<iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include<stack>
using namespace std;

typedef struct deal
{
    char ename_main[40];
    char cname_main[40];
    char place_main[20];
    char dir_main[40];
    char act_main[40];
    char price_main[40];
    char num_main[3];
    char time_main[20];

    char ename_vice[40];
    char cname_vice[40];
    char place_vice[20];
    char dir_vice[40];
    char act_vice[40];
    char price_vice[40];
    char num_vice[3];
    char time_vice[20];
    int diff;
}deal;

deal record[2000];
int record_num;

string pair_deal[12]={"ag2210-ag2302","OI209-OI301","FG209-FG301","SA209-SA301","FG209-SA209","pp2209-l2209","m2209-a2209","sp2209-sp2301","c2209-cs2209","rb2210-hc2210","ag2212-ag2302","ag2211-ag2302"};
int co[12]=[15,10,20,20,20,10,10,10,10,10,15,15];

stack<deal> deal_stack[12];

int find_pair(string str)
{
    for(int i=0;i<12;i++){
        if(str==pair_deal[i])return i;
    }
    return -1;
}

void adjust(int num)
{
    string str1=record[num].ename_main;
    string str2=record[num].ename_vice;
    string str=str1+"-"+str2;
    int seq=find_pair(str);
    if(find_pair(str)==-1){
        
        swap(record[num].act_main,record[num].act_vice);
        swap(record[num].cname_main,record[num].cname_vice);

        swap(record[num].dir_main,record[num].dir_vice);
        swap(record[num].ename_main,record[num].ename_vice);
        swap(record[num].num_main,record[num].num_vice);
        swap(record[num].place_main,record[num].place_vice);
        swap(record[num].price_main,record[num].price_vice);
        swap(record[num].time_main,record[num].time_vice);

    }
    swap(str1,str2);
    str=str1+"-"+str2;
    seq=find_pair(str);

    int p1=stoi(record[num].price_main);
    int p2=stoi(record[num].price_vice);
    
    if(record[num].dir_main=="买入"){
        record[num].diff=-p1+p2;
    }
    else{
        record[num].diff=p1-p2;
    }


    if(record[num].act_main=="开仓"){
        deal_stack[seq].push(record[num]);
    }
    else{
        deal tmp=deal_stack[seq].top();
        int profit=(record[num].diff-tmp.diff)*co[seq];
        deal_stack[seq].pop();
    }

}

void read()
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
    	
  		fscanf(fp,"%s",record[i].ename_main); 
        fscanf(fp,"%s",record[i].cname_main); 
        fscanf(fp,"%s",record[i].place_main); 
        fscanf(fp,"%s",record[i].dir_main); 
        fscanf(fp,"%s",record[i].act_main); 
        fscanf(fp,"%s",record[i].place_main); 
        fscanf(fp,"%s",record[i].num_main); 
        fscanf(fp,"%s",record[i].time_main); 

        fscanf(fp,"%s",record[i].ename_vice); 
        fscanf(fp,"%s",record[i].cname_vice); 
        fscanf(fp,"%s",record[i].place_vice); 
        fscanf(fp,"%s",record[i].dir_vice); 
        fscanf(fp,"%s",record[i].act_vice); 
        fscanf(fp,"%s",record[i].price_vice); 
        fscanf(fp,"%s",record[i].num_vice); 
        fscanf(fp,"%s",record[i].time_vice); 
  		//printf("%s\n",planetable[i].linetable);
      	i++;
      	//adjust(i);
    }
    fclose(fp);
	record_num=i;
    for(int j=i-1;j>=0;j--)adjust(j);
	//printf("%d",table_amount);
	//printf("%d",price_amount);
}

int main()
{

}