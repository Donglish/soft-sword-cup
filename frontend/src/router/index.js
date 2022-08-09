import Vue from 'vue'
import VueRouter from 'vue-router'
Vue.use(VueRouter)

const originalPush = VueRouter.prototype.push
VueRouter.prototype.push = function push(location){
  return originalPush.call(this,location).catch(err => err)
}

const routes = [
  {
    path: '/',
    name: 'Main',
    component: () => import("../views/Main.vue"),
    redirect:'/home',
    children:[
      {
        path:'/home',
        name:'home',
        component: ()=> import("../views/home")
      },
      {
        path:'/result',
        name:'result',
        component: ()=> import("../views/result")
      }
    ]
  },
  {
    path:'/login',
    name:'login',
    component: ()=> import("../views/Login/login")
  }
]

const router = new VueRouter({
  routes
})

export default router
