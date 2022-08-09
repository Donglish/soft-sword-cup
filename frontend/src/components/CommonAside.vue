<template>
  <el-menu 
    default-active="1-4-1" 
    class="el-menu-vertical-demo" 
    background-color="#EBEEF5" 
    text-color="#606266" 
    active-text-color="#606266" 
    @close="handleClose" 
    :collapse="isCollapse"
    style="opacity:0.9"
  >
    <h3>{{isCollapse ? '' : '有机可乘'}}</h3>
  <el-menu-item @click="clickMenu(item)" v-for="(item,val) in noChildren" :key="val" :disabled="item.canVisit">
    <i :class="'el-icon-' + item.icon"></i>
    <span slot="title">{{item.label}}</span>
  </el-menu-item>
</el-menu>
</template>

<script>
export default {
     data() {
      return {  
      };
    },
    methods: {
      handleOpen(key, keyPath) {
        console.log(key, keyPath);
      },
      handleClose(key, keyPath) {
        console.log(key, keyPath);
      },
      clickMenu(item) {
        this.$router.push({
          name: item.name
        })
        this.$store.commit('selectMenu',item);
      }
    },
    computed: {
      noChildren(){
        return this.asyncMenu.filter(item => !item.children);
      },
      isCollapse() {
        return this.$store.state.tab.isCollapse
      },
      asyncMenu() {
        return this.$store.state.tab.menu
      }
    }
}
</script>

<style lang="less" scoped>
  .el-menu-vertical-demo:not(.el-menu--collapse) {
    width: 200px;
    min-height: 400px;
  }
  .el-menu {
    color : #fff;
    text-align: center;
    height: 100%;
    border:none;
    h3 {
      margin-top:12px;
      color: #606266;
      text-align: center;
      font-size:18px;
      line-height: 48px;
    }
  }
</style>