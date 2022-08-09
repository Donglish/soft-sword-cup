import Vue from 'vue'
import App from './App.vue'
import router from './router'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import axios from 'axios'
import './api/mock'
import store from './store/index'
import './assets/less/index.less'
Vue.prototype.axios = axios
Vue.config.productionTip = false
Vue.use(ElementUI)
router.beforeEach((to,from,next) => {
  store.commit('getToken')
  const token = store.state.user.token;
  if(!token && to.name !='login'){
    next({name:'login'})
  }
  else{
    next()
  }
})
new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
