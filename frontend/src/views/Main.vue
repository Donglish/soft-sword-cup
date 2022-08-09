<template>
  <el-container style="height: 100%">
      <el-aside width="auto">
          <common-aside></common-aside>
      </el-aside>
    <el-container>
        <el-header>
            <common-header></common-header>
        </el-header>
        <el-main>
            <router-view/>
        </el-main>
    </el-container>
  </el-container>
</template>

<script>
import CommonAside from '@/components/CommonAside.vue'
import CommonHeader from '@/components/CommonHeader.vue'
export default {
    name:'Home',
    components: {
        CommonAside,
        CommonHeader,
    }
}
</script>

<style lang = "less" scoped>
.el-header {
    background-color: #DCDFE6;
}
.el-main {
    padding-top: 0;
    align-items: center;
    background-color: var(--white);
    background: url("../assets/images/loginImage.jpg");
    background-attachment: fixed;
    background-position: center;
    background-repeat: no-repeat;
    background-size: cover;
    display: grid;
    height: 100vh;
    place-items: center;
    position: relative;
}
</style>