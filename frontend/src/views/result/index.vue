<template>
   <transition name="el-zoom-in-center">
          <div>
              <div 
               style="display: flex;
                justify-content: space-between;
                align-items: center;"
              >
              <el-button 
                type="primary" 
                @click="changeToHome()" 
                icon="el-icon-back"
                style="margin-bottom:5px"
                >
                重新查询
              </el-button>
              <el-radio-group v-model="type" @change="changeShow()">
                <el-radio-button label="全部结果"></el-radio-button>
                <el-radio-button label="0:00-8:00"></el-radio-button>
                <el-radio-button label="8:00-16:00"></el-radio-button>
                <el-radio-button label="16:00-24:00"></el-radio-button>
              </el-radio-group>
            </div>
            <el-scrollbar 
              style=
              "width:100%;
                height:580px;  
                margin-top:10px;
              "
            >    
             <div v-show="showList.length >0 && showList[0].part[0].planeInfo.companyName !== '**'" v-for="(item,id) in showList" 
                  :key="id" 
                  :style="{height:scrollHeight,backgroundColor:'#f2f6fc',borderRadius:'8px',marginTop:'20px',marginBottom:'20px',width:'100%',height:(returnList[0].part.length)*110 + 90 + 'px'}" 
                  >
                <div style="padding-top:10px;margin-left:47%;font-size:20px;color:#999">方案{{id+1}} <span v-for="(item2,id2) in selectAgent" :key="id2" style="font-size:7px">{{item2}}&nbsp;</span></div>
                <result v-for="(item1,id1) in item.part" :key="id1"
                      :planeInfo="item1.planeInfo"
                      :start="item1.start"
                      :end="item1.end"
                      :cabin="item1.cabin"
                      :partPrice="item1.partPrice"
                      style="margin-right:50px"
                ></result>
             </div>             
             <div v-show="showList.length === 0 || showList[0].part[0].planeInfo.companyName === '**'" class="error">
               <div style="padding-top:200px;margin-left:320px;color:#999">
                 很抱歉，没有找到合适的航班
               </div>
               <div style="margin-left:320px;color:#999;margin-top:20px">
                 请选择其他时间或增加代理人
               </div>
             </div>
            </el-scrollbar>
          </div>      
      </transition>
</template>

<script>
import result from '@/components/CommonResult.vue'
export default {
    data(){
        return {
            showList:[],
            type:"全部结果",
            returnList:[],
            selectAgent:[],
            returnList1:[],
            returnList2:[],
            returnList3:[],
            load:false,
        }
    },
    mounted(){
      this.returnList = this.$store.state.result.returnList;
      this.showList = this.returnList;
      this.selectAgent = this.$store.state.user.selectAgent;
    },
    computed:{
        scrollHeight(){
          return this.returnList.length*100 + 75 + 'px'
        }
    },
    methods:{
      checkTime(time){
      let arr = time.split(":");
      return arr[0] + arr[1];
      },
      changeToHome(){
        this.load = false
        this.$store.commit('clearInfo')
        this.$store.commit('changeVisit');
        this.$router.push({name:'home'})
      },
      changeShow(){
        if(this.load === false){
          this.returnList.forEach((item)=>{
            let times = this.checkTime(item.part[0].start.startTime);
            let time1 = this.checkTime("08:00");
            let time2 = this.checkTime("16:00");
            if(times < time1){
              this.returnList1.push(item)
            }
            else if(times >=time1 && times < time2){
              this.returnList2.push(item)
            }
            else{
              this.returnList3.push(item)
            }
          })
          this.load = true
        }
        console.log(this.returnList1);
        if(this.type === '全部结果'){
          this.showList = this.returnList;
        }
        else if(this.type === '0:00-8:00'){
          this.showList = this.returnList1;
        }
        else if(this.type === '8:00-16:00'){
          this.showList = this.returnList2;
        }
        else {
          this.showList = this.returnList3;
        }
      }
    },
    components:{
        result
    }
}
</script>

<style>
  .error{
    margin-top:20px;
    background-color:#f2f6fc;
    font-size:35px;
    border-radius:10px;
    width:1100px;
    height:550px;
    opacity: 0.9;
  }
</style>