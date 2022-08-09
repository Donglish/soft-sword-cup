import Vue from 'vue'
import Vuex from 'vuex'
import tab from './tab'
import date from './date'
import result from './result'
import user from './user'
Vue.use(Vuex)

export default new Vuex.Store({
  modules:{
    tab,
    date,
    result,
    user
  }
})