import Vue from 'vue'
import VueRouter from 'vue-router'
import ticketPage from '@/views/ticketPage'
import result from '@/components/result'
Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    redirect: '/home'
  },
 {
   path: '/home',
   component: ticketPage
 },
 {
   path:'/result',
   component: result,
 }
]

const router = new VueRouter({
  routes
})

export default router
