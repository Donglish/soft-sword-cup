import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

const actions = {}

const mutations = {
    changeDate(state, newDate) {
        if (state.date.length === 0) {
            state.date.push(newDate);
        } else {
            if (newDate.getTime() > state.date[state.date.length - 1].getTime()) {
                state.date.push(newDate);
            }
        }
    },
    deleteDate(state) {
        state.date.pop();
    }
}

const state = {
    date: [],
}

export default new Vuex.Store({
    actions,
    mutations,
    state,
})