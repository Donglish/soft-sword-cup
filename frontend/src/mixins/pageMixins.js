export const pageMixins = {
    watch:{
        num:{
           handler(val,oldVal){
                if(val === 1){
                    this.$store.state.date = []
                }
            }
        }
      },
    mounted(){
      this.agentList = this.$store.state.user.info.agentList
    },
    methods:{
        addAnother(){
            if(this.num < 8 && this.num > 0){
                if(this.$refs.query[this.num-1].value1 === ""){
                this.$alert('请输入前组行程的日期','错 误',{
                    confirmButtonText:'确定',
                })
                }else{
                  if(this.num === this.$store.state.result.returnList.length){
                     let param = { 
                      companyName:"",
                      planeType:"",
                      startTime:"",
                      startCity:"",
                      endTime:"",
                      endCity:"",
                      price:"",
                      ticketType:""
                      };
                    this.$store.state.result.returnList.push(param);
                  }
                  this.num = this.num + 1;
                  let div = this.$refs["scrollbar"].$refs["wrap"];
                  this.$nextTick(() => {
                    div.scrollTop = div.scrollHeight;
                  })
                }
            }
            else if(this.num === 0 ){
              this.num = this.num + 1;
            }
            else{
              this.$alert('最大支持输入八组行程','错误',{
                confirmButtonText:'确定',
              })
            }
          },
          changeNum(val){
            this.num += val;
            if(val === -1){
              this.$store.state.result.returnList.pop();
            }
          },
          nextstep(){
            let ansList = {
              passengerNum: "",
              planeNum:"",
              agentList:[],
              planeList:[],
            }
            if(this.passengerNum != ""){
              if(Number(this.passengerNum) > 0){
                ansList.passengerNum = this.passengerNum
              }
            }else{
               this.$alert('请输入乘客人数','错 误',{
                  confirmButtonText:'确定',
                })
            }
            ansList.planeNum = this.planeNum;
            ansList.agentList = this.selectAgent;
            for(var i = 0 ;i<this.num;i++){
              let tmp = {
                date:"",
                fromCityAndToCity:""
              }
              tmp.date = this.timeChange(this.$refs.query[i].value1);
              tmp.fromCityAndToCity = this.$refs.query[i].getFromCityAndToCity();
              ansList.planeList.push(tmp);
            }
          this.$store.state.date = [];
          let that = this;     
            this.axios.post("/api/test",{...ansList}).then((response) => {
              that.$store.state.result.returnList = response.data.returnList.reverse();
              that.$router.push({name:'result'});
            })
            this.visible = false;
            this.$store.commit('changeVisit');
          },  
          handleClose(done){
            done();
          },
        timeChange(date) {
            var year = date.getFullYear(); 
            var month = date.getMonth(); 
            var data = date.getDate(); 
            var hours = date.getHours(); 
            var minute = date.getMinutes(); 
            var second = date.getSeconds(); 
            var time =
              year +
              "-" +
              this.checkTime(month + 1) +
              "-" +
              this.checkTime(data) +
              this.checkTime(hours) +
              ":" +
              this.checkTime(minute) +
              ":" +
              this.checkTime(second);
            return time;
          },
          checkTime(time){
            if(time>=0 && time <=9){
              return "0"+ time;
            }
            return time;
          }, 
    }
}