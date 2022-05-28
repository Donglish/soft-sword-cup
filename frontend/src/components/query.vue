<template>
    <div>
        <div style="display:inline-block">
        <city></city>
        </div>
        <div class="dateContainer">
            <el-row 
                style=
                "margin-top:5px;
                margin-left:10px;
                margin-bottom:5px;"
            >
                <h6 style="font-weight:200">
                    出发日期
                </h6>
            </el-row>
            <el-row style="margin-left:5px">
                <div class="block">
                    <el-date-picker
                        v-model="value1"
                        type="date"
                        placeholder="选择日期"
                    >
                    </el-date-picker>
                </div>
            </el-row>
        </div>
        <div 
            style=
            "display:inline-block;
             position:relative;
             margin-left:30px;
             ">
             <el-button 
                class = "delete"  
                circle
                type="text"
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
</template>

<script>
import city from '@/components/city.vue'
export default {
    data(){
     
     return {
            value1:""
        }
    },
    components:{
        city
    }
}
</script>

<style>
    .dateContainer {
        border-radius: 6px;
        background-color:#ffffff;
        border: 1px solid #eee;
        box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
        width:330px;
        height: 65px;
        margin-left: 20px;
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
    }
    .delete:hover{
        background-color: #C0C4CC !important;
    }
</style>