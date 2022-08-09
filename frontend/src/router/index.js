import Vue from 'vue'
import VueRouter from 'vue-router'
import ticketPage from '@/views/ticketPage'
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
]

const router = new VueRouter({
  routes
})

export default router
