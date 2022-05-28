import Vue from 'vue'
import VueRouter from 'vue-router'
import ticketPage from '@/views/ticketPage'
import query from '@/components/query'
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
   path: '/query',
   component: query
 },
]

const router = new VueRouter({
  routes
})

export default router
