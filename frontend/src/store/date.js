export default {
    state: {
        date:[],
        length:0,
    },
    mutations:{
        changeDate(state,newDate,id){
            if(state.length === 0){
                state.date.push(newDate);
                state.length++;
            }
            else if(newDate === null){
               state.date.splice(state.date.indexOf(id),1);
               state.length--;
            }
            else{
                if(state.length > 0 && newDate.getTime() >= state.date[state.length-1].getTime()){
                    state.date.push(newDate);
                    state.length++;
                }
            }
         },
         deleteDate(state,id){
            state.date.splice(state.date.indexOf(id),1);
            state.length--;
        },
        clearInfo(state){
            state.date = [],
            state.length = 0
        }
    }
}