<template>
  <div class="body">
      <div class="container">
        <el-scrollbar 
          style=
           "width:100%;
            height:440px;
            margin-top:70px;
            margin-bottom:10px;            
            "
        >      
          <div v-for="(item,id) in num" :key="id">
          <query :id="id+1"></query>
          </div>
        </el-scrollbar >
        <el-button 
            type="primary"  
            style=
            " margin-left:3%;
            "
            icon="el-icon-plus"
            @click="num = num + 1"
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
          >
            搜索
          </el-button>
      </div>
  </div>
</template>

<script>
import query from '@/components/query.vue'
export default {
  data(){
    return{
      num: 1,
    }
  },
  components:{
    query
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