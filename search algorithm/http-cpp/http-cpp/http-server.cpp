#include "workflow/WFFacilities.h"
#include <csignal>
#include "wfrest/HttpServer.h"
#include "wfrest/json.hpp"
#include <iostream>
using namespace wfrest;
using Json = nlohmann::json;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
    wait_group.done();
}

int main()
{
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
		
		std::cout << "passengerNum:" << inJson["passengerNum"]<<std::endl;
		std::cout << "date:" << inJson["planeList"][0]["date"]<<std::endl;

		//TODO::在此处添加业务处理逻辑

		//返回json数据
		Json json = {
			{
				"returnList",{
					{
						{
							"part",{
								{
									{"planeInfo",{{"companyName","国航"},{"planeType","0100"}}},
									{"timeInfo",{
										{"start",{{"startDate","2022年7月11日"},{"startTime","12:00"},{"startCity","长沙"}}},
										{"end",{{"endDate","2022年7月11日"},{"endTime","15:00"},{"endCity","南京"}}}}
									},
									{"cabin",{{{"cabinType","F"},{"num","1"},{"singlePrice","1000"}}}},
									{"partPrice","1000"}
								}
							}


						}
					}
				}
		    }
		};
		resp->Json(json);
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
