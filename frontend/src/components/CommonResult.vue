<template>
  <div class="result">
      <div class="airCompany">
          <div style="margin-top:5px;font-size:20px">
            {{this.planeInfo.companyName}}
          </div>
          <div style="margin-top:6px;color:#409EFF;font-size:17px">
            {{this.planeInfo.planeType}}
          </div>
      </div>
      <div class="timeInfo">
        <div>
          <div style="font-size:13px;color:#999;text-align:center">
              {{this.start.startDate}}
          </div>
          <div style="font-size:25px;font-weight:600;text-align:center">
              {{this.start.startTime}}
          </div>
          <div style="font-size:13px;text-align:center;color:#999" >
              {{this.start.startCity}}
          </div>
        </div>
        <div>
          <div style="color: #409EFF;font-size:9px; text-align:center" v-for="(item,id) in cabin" :key="id">
            {{item.cabinType}}*{{item.num}}
          </div>
          <img src="../assets/images/arrow1.png" alt="" style="width:150px;height:20px">
        </div>
        <div>
           <div style="font-size:13px;color:#999;text-align:center">
              {{this.end.endDate}}
           </div>
           <div style="font-size:25px;font-weight:600;text-align:center">
              {{this.end.endTime}}
          </div>
          <div style="font-size:13px;text-align:center;color:#999;"> 
              {{this.end.endCity}}
          </div>
        </div>
      </div>
      <div class="priceInfo">
        <div style="color: #409EFF;">
           <div style="display:inline-block;font-size:20px">
            ￥
          </div>
           <div style="display:inline-block;font-size:35px;font-weight:500">
            {{this.partPrice}}
           </div>
        </div>
        <div style="font-size:13px;margin-left:20px;margin-top:-3px;color: #999">
          价格
        </div>
      </div>
  </div>
</template>

<script>
export default {
    data(){
      return{
      }
    },
    props:{
      planeInfo:{
        required:true
      },
      start:{
        required:true
      },
      end:{
        required:true
      },
      cabin:{
        required:true
      },
      partPrice:{
        required:true
      }
    }
}
</script>

<style scoped>
  .result{
    margin-left: 50px;
    margin-right:50px;
    background-color: white;
    border: 1px solid gainsboro;
    height: 100px;
    width: 1100px;
    position: relative;
    box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
    margin-top: 10px;
    display: flex;
    justify-content: space-between;
    align-items: center;
  }
  .result:hover{
    box-shadow: 0 0 15px 0 rgb(0 0 0 / 15%);
  }
  .airCompany{
    margin-left: 20px;
    width: 300px;
  }
  .timeInfo{
    width: 380px;
    margin-left: -150px;
    display: flex;
    justify-content: space-between;
    align-items: center;
  }
  .priceInfo{
    margin-left: 30px;
    width:150px;
  }
</style>