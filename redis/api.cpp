#include<hirluster.h>
#include<stdio.h>
#include<stdlib.h>
#include<string> 

using namespace std;

redisClusterContext *cc;
redusReply *reply;

void init(){
	struct timeval timeout = {1,500000};
	*cc = redisClusterContextInit();
	for(int i = 7000;i<=7005;i++)
		redisClusterSetOptionAddNodes(cc,"127.0.0.1:" + i);
	redisClusterSetOptionConnectTimeout(cc,timeout);
	redisClusterSetOptionRouteUseSlots(cc);
	redisClusterConnect2(cc);
	if(cc && cc->err){
		cout<<"Error: "<<cc->errstr<<endl;
	}
}

string get(string key,string field){
	*reply = (redisReply *)redisClusterCommand(cc,"Hget %s %s",key,field);
	return reply->str;
}

void set(string key,string field,string value){
	*reply = (redisReply *)redisClusterCommand(cc,"HSET %s %s %s %s",key,field,value);
	return;
}

void end(){
	freeReplyObject(reply);
	redisClusterFree(cc);
}
