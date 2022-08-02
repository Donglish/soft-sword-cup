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
})