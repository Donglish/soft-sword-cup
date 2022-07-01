<template>
  <div class="body">
    <div class="container">
      <el-collapse-transition>
        <div v-show="this.query">
          <el-input v-model="passengerNum" placeholder="请输入乘客人数" style="width:150px;margin-top:30px;margin-left:50px"/>
          <el-select
           v-model="selectAgent"
           multiple
           collapse-tags
           placeholder="请选择合适的代理人"
           style="margin-left:57%"
          >
            <el-option
              v-for="item in agentList"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
          <el-scrollbar 
            style=
            "width:100%;
              height:440px;
              margin-top:8px;
              margin-bottom:10px;            
              "
          >      
            <div v-for="(item,id) in num" :key="id">
            <query :id="id+1" ref="query" v-on:increment="changeNum"></query>
            </div>
          </el-scrollbar >
          <el-button 
              type="primary"  
              style=
              " margin-left:5%;
                margin-top:5px
              "
              icon="el-icon-plus"
              @click="addAnother()"
            >
              再加一程
            </el-button>
          <el-button 
              style=
              " background-color: var(--blue);
                background-image: linear-gradient(90deg, var(--blue) 0%, var(--lightblue) 74%);
                border-radius: 20px;
                border: 1px solid var(--blue);
                color: var(--white);
                cursor: pointer;
                font-size: 0.8rem;
                font-weight: bold;
                letter-spacing: 0.1rem;
                padding: 0.9rem 4rem;
                text-transform: uppercase;
                transition: transform 80ms ease-in;
                top:590px;
                left:430px;
                position:absolute;
                z-index:10;
                " 
              icon="el-icon-search"
              @click="visible = true"
            >
              搜索
            </el-button>
            <el-dialog 
              title="请输入要返回的最多航班方案数"
              :visible.sync="visible"
              width="30%"  
            >
              <span>
                <el-input
                  v-model="planeNum"
                  style="margin-left:20%;width:250px"
                  :before-close="handleClose"
                  placeholder="请输入要返回的最多航班方案数"
                >
                </el-input>
              </span>
              <span slot="footer" class="dialog-footer">
                <el-button type="primary" @click="nextstep">确 定</el-button>
                <el-button @click="visible = false">取 消</el-button>
              </span>
            </el-dialog>
        </div>       
        </el-collapse-transition>
        <el-collapse-transition>
          <div v-show="this.res" style="margin-top:10px;margin-left:30px">
            <el-button 
              type="primary" 
              @click="query = !query;res = !res" 
              style="margin-left:30px;margin-top:10px"
              icon="el-icon-back"
              >
              重新查询
              </el-button>
            <el-scrollbar 
              style=
              "width:100%;
                height:500px;  
                margin-top:10px      
              "
            >    
             <div v-for="(item,id) in num" :key="id">
              <result></result>
            </div>
            </el-scrollbar>
          </div>      
      </el-collapse-transition>
      </div>
  </div>
</template>

<script>
import query from '@/components/query.vue'
import result from '@/components/result.vue'
export default {
  data(){
    return{
      num: 1,
      passengerNum:"",
      query:true,
      res:false,
      queryNum:"",
      agent:"",
      planeNum:"",
      visible:false,
      agentList:[{
        value: '1',
        label:"携程",
        },
        {
        value: '2',
        label:"美团",
        },
        {
        value: '3',
        label: "滴滴",
        },
        {
        value: '4',
        label:"去哪儿",
        },
        {
        value: '5',
        label:"美亚",
        },
        {
        value: '6',
        label:"纵横天地",
        },
        {
        value: '7',
        label:"今日天下通",
        },
        {
        value: '8',
        label:"51BOOK",
        },
        {
        value: '9',
        label:"票盟",
        },
        {
        value: '10',
        label:"国航",
        },
        {
        value: '11',
        label:"南航",
        },
        {
        value: '12',
        label:"东航",
        },
        {
        value: '13',
        label:"海航",
        },
        {
        value: '14',
        label:"山航",
        },
        {
        value: '15',
        label:"上航",
        },
        {
        value: '16',
        label:"厦航",
        },
        {
        value: '17',
        label:"川航",
        },
        {
        value: '18',
        label:"幸福航空",
        },
        {
        value: '19',
        label:"吉祥航空",
        },
        {
        value: '20',
        label:"春秋航空"
        },
    ],
      selectAgent:[],    
      selectAll: false  
    }
  },
  components:{
    query,
    result
  },
  methods:{
    addAnother(){
      if(this.num < 8){
          if(this.$refs.query[this.num-1].value1 === ""){
          this.$alert('请输入前组行程的日期','错 误',{
              confirmButtonText:'确定',
          })
          }else{
            this.num = this.num + 1;
          }
      }
      else{
        this.$alert('最大支持输入八组行程','错误',{
          confirmButtonText:'确定',
        })
      }
    },
    changeNum(val){
      this.num += val;
    },
    nextstep(){
      let ansList = {
        passengerNum: "",
        planeNum:"",
        agentList:[],
        planeList:[],
      }
      if(this.passengerNum != ""){
        if(Number(this.passengerNum) > 0){
          ansList.passengerNum = this.passengerNum
        }
      }else{
         this.$alert('请输入乘客人数','错 误',{
            confirmButtonText:'确定',
          })
      }
      ansList.planeNum = this.planeNum;
      ansList.agentList = this.selectAgent;
      for(var i = 0 ;i<this.num;i++){
        let tmp = {
          date:"",
          fromCityAndToCity:""
        }
        tmp.date = this.$refs.query[i].value1;
        tmp.fromCityAndToCity = this.$refs.query[i].getFromCityAndToCity();
        ansList.planeList.push(tmp);
      }
      console.log(ansList);
      this.axios.post("/api",...ansList).then((response) => {
        console.log(response);
      })
      this.visible = false;
      this.query = !this.query,
      this.res = !this.res;
    },  
    handleClose(done){
      done();
    },
  }
}
</script>

<style>
     :root {
      /* COLORS */
      --white: #e9e9e9;
      --gray: #333;
      --blue: #0367a6;
      --lightblue: #008997;

      /* RADII */
      --button-radius: 0.7rem;

      /* SIZES */
      --max-width: 758px;
      --max-height: 420px;

      font-size: 16px;
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Oxygen,
        Ubuntu, Cantarell, "Open Sans", "Helvetica Neue", sans-serif;
    }
    * {
        margin: 0;
        padding: 0;
    }
    .body{
      align-items: center;
      background-color: var(--white);
      background: url("../assets/loginImage.jpg");
      background-attachment: fixed;
      background-position: center;
      background-repeat: no-repeat;
      background-size: cover;
      display: grid;
      height: 100vh;
      place-items: center;
      position: relative;
    }
    .container {
      background-color: var(--white);
      border-radius: var(--button-radius);
      box-shadow: 0 0.9rem 1.7rem rgba(0, 0, 0, 0.25),
        0 0.7rem 0.7rem rgba(0, 0, 0, 0.22);
      height: 80%;
      max-width: 70%;
      position: relative;
      width: 100%;
      /* opacity: 0.8; */
    }
    .el-scrollbar__wrap {
    overflow-x: hidden !important;
    }
  .el-scrollbar__bar{
     opacity: 1 !important;
   }
   .el-scrollbar__thumb{
     background: #dbd9d9 !important;     
     border-radius: 3px !important;
   }
</style>