<template>
    <div>
        <div class="Container">  
            <el-button 
                style=
                "width:35px;
                height:35px;
                background-color: #ffffff;
                margin-top:25px;
                margin-left:10px;
                margin-bottom:25px;
                "
                circle
                >
                <div
                    style="color:#303133;
                        font-size:25px;
                        position:absolute;
                        font-weight:400;
                        margin-top:-12px;
                        margin-left:-4px
                        "
                >
                1
                </div>
            </el-button>    
            <div 
                style=
                    "display:inline-block;
                     width:220px"
            >
                <h5 style="font-weight:400;margin-left:20px">
                    出发地
                </h5> 
            </div>
            <div 
                style="display:inline-block;">
                <el-button 
                  style=
                    "width:35px;
                    height:35px;
                    background-color: #ffffff;
                    "  
                    circle
                >
                <i 
                    class="el-icon-sort"
                    style=
                        "color:#303133;
                        font-size:20px;
                        position:absolute;
                        font-weight:300;
                        margin-top:-10px;
                        margin-left:-10px;
                        transform:rotate(90deg)
                        "
                >
                </i>
            </el-button>
            </div>
            <div 
                style=
                    "display:inline-block;
                     width:220px"
            >
                <h5 
                    style=
                        "font-weight:400;
                        margin-left:20px"
                >
                        目的地
                </h5>  
            </div>  
        </div>
        <div class="dateContainer">
            <el-row 
                style=
                "margin-top:10px;
                margin-left:10px;
                margin-bottom:5px;"
            >
                <h5 style="font-weight:300">
                    出发日期
                </h5>
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
export default {
    data(){
        return {
            value1:""
        }
    }
}
</script>

<style>

    .Container {
        border-radius: 6px;
        background-color:#ffffff;
        border: 1px solid #eee;
        box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
        width:560px;
        height: 85x;
        margin-left: 40px;
        display:inline-block;
        vertical-align: middle;
    }
    .Container:hover{
    box-shadow: 0 0 15px 0 rgb(0 0 0 / 15%);
    }
    .dateContainer {
        border-radius: 6px;
        background-color:#ffffff;
        border: 1px solid #eee;
        box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
        width:330px;
        height: 85px;
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