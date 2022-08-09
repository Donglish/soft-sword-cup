<template>
  <header>
      <div class="l-content">
          <el-button @click="handleMenu()" plain icon="el-icon-menu" size="mini"></el-button>
            <el-breadcrumb separator="/">
                <el-breadcrumb-item v-for="item in tags" :key="item.path" :to="{ path: item.path }">{{item.label}}</el-breadcrumb-item>
            </el-breadcrumb>
      </div>
      <div class="r-content">
          <el-dropdown trigger="click" szie="mini">
              <span>
                  <img class="user" src="../assets/images/user-default.png"/>
              </span>
              <el-dropdown-menu slot="dropdown">
                  <el-dropdown-item @click.native="logOut">
                      退出
                  </el-dropdown-item>
              </el-dropdown-menu>
          </el-dropdown>
      </div>
  </header>
</template>

<script>
import { mapState } from 'vuex'
export default {
    name: 'CommonHeader',
    data(){
        return {
        }
    },
    methods: {
        handleMenu() {
            this.$store.commit('collapseMenu')
        },
        logOut() {
            this.$store.commit('clearToken')
            this.$router.push("/login")
        }
    },
    computed: {
        ...mapState({
            tags:state => state.tab.tabsList
        })
    }
}
</script>
<style lang="less" scoped>
header {
    display: flex;
    height : 100%;
    justify-content: space-between;
    align-items: center;
}
.l-content {
    display: flex;
    align-items: center;
    .el-button {
        margin-right: 20px;
    }
}
.r-content {
    .user {
        width: 40px;
        height: 40px;
        border-radius: 50%;
    }
}
</style>