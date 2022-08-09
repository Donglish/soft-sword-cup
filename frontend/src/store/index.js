<<<<<<< HEAD
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
=======
import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

const actions = {}

const mutations = {
 changeDate(state,newDate,id){
    if(state.date.length === 0){
        state.date.push(newDate);
    }
    else if(newDate === null){
       state.date.splice(state.date.indexOf(id),1);
    }
    else{
        if(state.date.length > 0 && newDate.getTime() > state.date[state.date.length-1].getTime()){
            state.date.push(newDate);
        }
    }
 },
 deleteDate(state,id){
    state.date.splice(state.date.indexOf(id),1);
 }
}

const state = {
    date:[],
}

export default new Vuex.Store({
    actions,
    mutations,
    state,
>>>>>>> d62925e61070a01079fd7979df1dcb1567a4f61a
})