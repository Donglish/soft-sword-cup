# frontend前端部分

# 详细信息:
    组件:./src/components,共有city.vue,query.vue,result.vue三个组件
```
使用npm配置前端项目
```
## 开发环境配置指令
```
npm install
```

### 开发环境运行指令
```
npm run serve
```

### 打包指令
```
npm run build
```
路由选择vue-router，详细配置在./src/router/index.js中

## 前端向后端发送post请求
```
全局引入axios组件
request参数:
    {
        passengerNum : "1",
        planeNum : "1",
        agentList:[
            "SHA001"
        ],
        planeList:[
            {
                date:"2022-07-11 00:00:00",
                fromCityAndToCity:{
                    fromCity:"长沙",
                    toCity:"南京"
                }
            }
        ]
    }
response参数:
     returnList:[
          { 
           part:[
             {
               planeInfo:{
                 companyName:"国航",
                 planeType:"0100"
                },
                timeInfo:{
                  start:{
                    startDate:"2022年7月11日",
                    startTime:"12:00",
                    startCity:"长沙"
                  },
                  end:{
                    endDate:"2022年7月11日",
                    endTime:"15:00",
                    endCity:"南京"
                  }
                },
                cabin:[
                  {
                    cabinType:"F",
                    num:"1",
                    singlePrice:"1000"
                  },
                ],
                partPrice:"1000"
             },
           ],
          },
          ],
```
