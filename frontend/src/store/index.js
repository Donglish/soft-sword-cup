import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

const actions = {}

const mutations = {
 changeDate(state,newDate){
    if(state.date === ""){
        state.date = newDate;
    }
    else{
        if(newDate.getTime() > state.date.getTime()){
            state.date = newDate;
        }
    }
 }   
}

const state = {
    date:"",
}

export default new Vuex.Store({
    actions,
    mutations,
    state,
})