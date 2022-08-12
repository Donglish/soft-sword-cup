<template>
    <el-collapse-transition>
        <div v-show="showTotal" class="total">
            <city :id="id" ref="city"></city>
            <div class="dateContainer">
                <el-row 
                    style=
                    "margin-top:5px;
                    margin-left:10px;
                    margin-bottom:5px;"
                >
                    <h4 style="font-weight:200;margin-top:17px;margin-left:10px;color: #999;" @click="change" v-show="!showDate">
                        出发日期
                    </h4>
                </el-row>
                <el-row style="margin-left:10px;" v-show="showDate">
                    <div class="block">
                        <el-date-picker
                            v-model="value1"
                            type="date"
                            placeholder="选择日期"   
                            :picker-options="pickerOptions"
                        >
                        </el-date-picker>
                    </div>
                </el-row>
            </div>
            <div 
                style=
                "display:inline-block;
                position:relative;
                ">
                <el-button 
                    class = "delete"  
                    circle
                    type="text"
                    @click="deleteItem()"
                >
                    <i 
                    class="el-icon-close"
                    style="color:#303133;
                            font-size:30px;
                            position:absolute;
                            font-weight:700;
                            margin-top:-14.5px;
                            margin-left:-14.5px
                            "
                    >
                    </i>
                </el-button>
            </div>    
        </div>
    </el-collapse-transition>
</template>

<script>
import city from '@/components/CommonCity.vue'
export default {
    data(){
     return {
            value1:"",
            showDate:false,
            showTotal:true,
        }
    },
    components:{
        city
    },
    computed:{
        pickerOptions(){
            var that = this;
            return {
                disabledDate(time) {
                    if(that.$store.state.date.length === 0){
                        return false;
                    }
                    else if(that.$store.state.date.length > 0){
                        return time.getTime() < that.$store.state.date.date[that.$store.state.date.length-1].getTime();
                    }
                    else{
                        return false;
                    }
                },
            }
        }
    },
    methods:{
        deleteItem(){
            if(this.$store.state.date.length === 0){
                 this.$alert('输入的行程数最少为一','错 误',{
                  confirmButtonText:'确定',
                })   
            }
            else{
                this.showTotal = false;
                this.$store.commit('deleteDate',this.id-1);
                this.$emit('increment',-1);
            }
        },
        change(){
            this.showDate = !this.showDate;
        },
        getFromCityAndToCity(){
            let param = {
                fromCity:"",
                toCity:""
            }
            param.fromCity = this.$refs.city.defaultSearchValue.replace(/^\s*|\s*$/g,'');;
            param.toCity = this.$refs.city.defaultSearchValue2.replace(/^\s*|\s*$/g,'');;
            return param;
        },
    },
    props:{
        id:{
            type:Number,
            required:true
        }
    },
    watch:{
        value1:{
            handler(val){
                this.$store.commit('changeDate',val,this.id-1);
            }
        }
    }
}
</script>

<style>
    .total{
        display: flex;
        justify-content: space-between;
        align-items: center;
        margin-bottom: 20px;
        opacity:1;
    }   
    .dateContainer {
        border-radius: 6px;
        background-color:#ffffff;
        border: 1px solid #eee;
        box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
        width:330px;
        height: 65px;
        display: inline-block;
        vertical-align: middle;
    }
    .dateContainer:hover{
        box-shadow: 0 0 15px 0 rgb(0 0 0 / 15%);
    }
    .delete{
        width:35px;
        height:35px;
        background-color: #ffffff;
        margin-right: 50px;
    }
    .delete:hover{
        background-color: #C0C4CC !important;
    }
</style>