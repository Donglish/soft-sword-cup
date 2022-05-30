<template>
  <div class="result">
      <div class="airCompany">
          <div style="margin-top:5px">
            {{this.information.planeInfo.companyName}}
          </div>
          <div style="margin-top:6px;color:#409EFF;font-size:13px">
            {{this.information.planeInfo.planeType}}
          </div>
      </div>
      <div class="timeInfo">
        <div style="display:inline-block">
          <div style="font-size:30px;font-weight:600">
              {{this.information.timeInfo.start.startTime}}
          </div>
          <div style="font-size:13px;text-align:center" >
              {{this.information.timeInfo.start.startCity}}
          </div>
        </div>
        <div style="display:inline-block;margin-left:10px;">
          <img src="../assets/arrow1.png" alt="" style="width:150px;height:20px">
        </div>
        <div style="display:inline-block;margin-left:10px;margin-top:10px">
           <div style="font-size:30px;font-weight:600">
              {{this.information.timeInfo.end.endTime}}
          </div>
          <div style="font-size:13px;text-align:center"> 
              {{this.information.timeInfo.end.endCity}}
          </div>
        </div>
      </div>
      <div class="priceInfo">
        <div style="color: #409EFF;">
           <div style="display:inline-block;font-size:20px">
            ￥
          </div>
           <div style="display:inline-block;font-size:35px;font-weight:500">
            {{this.information.price}}
           </div>
        </div>
        <div style="font-size:13px;margin-top:-3px;margin-left:65px">
          价格
        </div>
      </div>
  </div>
</template>

<script>
export default {
    data(){
      return{
        information:{
          planeInfo:{
            companyName:"南方航空",
            planeType:"CZ3825 波音737(中)"
          },
          timeInfo:{
            start:{
              startTime:"20:40",
              startCity:"长沙"
            },
            end:{
              endTime:"22:40",
              endCity:"南京"
            }
          },
          price:"1000",
        }
      }
    }
}
</script>

<style>
  .result{
    margin-left: 50px;
    background-color: white;
    border: 1px solid gainsboro;
    height: 85px;
    width: 900px;
    position: relative;
    box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
    margin-bottom: 10px;
  }
  .result:hover{
    box-shadow: 0 0 15px 0 rgb(0 0 0 / 15%);
  }
  .airCompany{
    display: inline-block;
    margin-left: 20px;
    width: 300px;
  }
  .timeInfo{
    display: inline-block;
    /* vertical-align: middle; */
    width: 400px;
  }
  .priceInfo{
    display: inline-block;
    margin-left: 30px;
    width:150px;
  }
</style>