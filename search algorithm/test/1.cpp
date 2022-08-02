#include <string>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include<jsoncpp/json/json.h> 
#include<sstream>
#include"json.hpp"
using namespace std;
using namespace Json;
void readStrJson(); //从字符串中读取JSON
void readStrProJson(); //从字符串中读取JSON（内容复杂些）
 
int main(int argc, char *argv[]) 
{
    readStrJson();
    
    cout << "\n\n";
    readStrProJson();
    
    return 0;
}
 
//从字符串中读取JSON
void readStrJson() 
{
    //字符串
  const char* str = 
      "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","
      "\"born\":-100,\"died\":-44}";
      
  /*
  //json内容如下：
  {
        "praenomen":"Gaius",
        "nomen":"Julius",
        "cognomen":"Caezar",
        "born":-100,
        "died":-44 
    }
  */
 
  Json::Reader reader;
  Json::Value root;
 
  //从字符串中读取数据
  if(reader.parse(str,root))
  {
      string praenomen = root["praenomen"].asString();
      string nomen = root["nomen"].asString();
      string cognomen = root["cognomen"].asString();
      int born = root["born"].asInt();
      int died = root["died"].asInt();
 
      cout << praenomen + " " + nomen + " " + cognomen
          << " was born in year " << born 
          << ", died in year " << died << endl;
  }
  
}
 
//从字符串中读取JSON（内容复杂些）
void readStrProJson() 
{
    string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";
    /*
    //json内容如下：
    {
    "name": "json″,
    "array": [
        {
            "cpp": "jsoncpp"
        },
        {
            "java": "jsoninjava"
        },
        {
            "php": "support"
        }
    ]
    }
    */
 
 
    Json::Reader reader;
    Json::Value value;
 
    if (reader.parse(strValue, value))
    {
        string out = value["name"].asString();
        cout << out << endl;
        const Json::Value arrayObj = value["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            if (!arrayObj[i].isMember("cpp")) 
                continue;
            out = arrayObj[i]["cpp"].asString();
            cout << out;
            if (i != (arrayObj.size() - 1))
                cout << endl;
        }
    }
}



PartInformation:{
    "planeInfo":{
        "companyName":"南航",
        "planeType":"0100"
    },
    "timeInfo":{
        "start":{
            "startDate":"2022年02月02日"
            "startTime":"20:20",
            "startCity":"长沙"
        },
        "end":{
            "endDate":"2022年02月03日"
            "endTime":"10:20",
            "endCity":"南京"
        }
    },
    "cabin":[],        //数组存放是cabinInfo对象
    //"partprice":"5000",//一段航程的所有人的总价钱
}

cabinInfo:{
    "cabintype":"头等舱",//F头等舱 C商务舱 Y经济舱
    "num":"3",
    "singleprice":"0230"
}

AllInfomation:{
    "Part":[], //PartInformation对象
    "Agency":""
    //"sumprice":"9000" //所有人所有航程总价钱
}

Program:{
    "means":[] //AllInfomation对象
}

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
    /* data */
}partinfo;

typedef struct partans
{
    vector<partinfo> part;
    string anency;
}partans;

vector<partans> ans;

{"passengerNum":"1","planeNum":"1","agentList":["BJS001"],"planeList":[{"date":"2022-07-11 00:00:00","fromCityAndToCity":{"fromCity":" 台北 ","toCity":" 澳门 "}}]}
