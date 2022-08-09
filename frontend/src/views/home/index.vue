<template>
  <div class="body">
    <div class="container">
       <div>
          <div class="forms">
            <el-input 
            v-model="passengerNum" 
            placeholder="请输入乘客人数" 
            style="width:150px;margin-left:50px;opacity:1;"
            />
          <el-select
           v-model="selectAgent"
           multiple
           collapse-tags
           placeholder="请选择合适的代理人"
           style="margin-right:40px;opacity:1;"
          >
            <el-option
              v-for="item in agentList"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
        </div>
          <el-scrollbar 
            style=
            "width:100%;
              height:440px;
              margin-top:8px;
              margin-bottom:10px;            
              "
            ref="scrollbar"
          >      
            <div v-for="(item,id) in num" :key="id">
            <query :id="id+1" ref="query" v-on:increment="changeNum"></query>
            </div>
          </el-scrollbar>
          <el-button 
              type="primary"  
              style=
              " margin-left:5%;
                margin-bottom:3%;
                opacity:1;
              "
              icon="el-icon-plus"
              @click="addAnother()"
            >
              再加一程
            </el-button>
          <el-button
              type="primary" 
              style=
              "  
                border-radius: 20px;
                cursor: pointer;
                font-size: 1rem;
                font-weight: bold;
                letter-spacing: 0.1rem;
                padding: 0.9rem 3.5rem;
                text-transform: uppercase;
                transition: transform 80ms ease-in;
                position:absolute;
                z-index:10;
                margin-left:28%;
                margin-top:3.5%;
                opacity:1;
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
              style="margin-top:10%"
              append-to-body
            >
              <span>
                <el-input
                  v-model="planeNum"
                  style="margin-left:20%;margin-top:3%;width:250px"
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
      </div>
  </div>
</template>
<script>
import query from '@/components/query.vue'
import {pageMixins} from '@/mixins/pageMixins'
export default {
  mixins:[pageMixins],
  data(){
    return{
      num: 1,
      passengerNum:"",
      queryNum:"",
      planeNum:"",
      visible:false,
      agentList:[
      ],
      selectAgent:[],    
    }
  },
  components:{
    query
  },
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
      background-attachment: fixed;
      background-position: center;
      background-repeat: no-repeat;
      background-size: cover;
      display: grid;
      place-items: center;
      position: relative;
    }
    .forms{
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-top:20px;
        margin-bottom: 20px;
    }
    .container {
      margin-top:50px;
      background-color: var(--white);
      border-radius: var(--button-radius);
      box-shadow: 0 0.9rem 1.7rem rgba(0, 0, 0, 0.25),
        0 0.7rem 0.7rem rgba(0, 0, 0, 0.22);
      height: 90%;
      max-width: 110%;
      position: relative;
      width: 110%;
      opacity: 0.9;
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