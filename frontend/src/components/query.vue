<template>
  <el-row>
        <el-col :span="60">
            <div class="container">      
                <el-row     
                >
                    <el-col 
                    :span="12"

                    >
                        <el-button 
                            style=
                            "width:35px;
                            height:35px;
                            background-color: #ffffff;
                            font-weight:700;
                            margin-top:8%;
                            margin-left:10px
                            "
                            circle>
                            1
                        </el-button>
                        <h5 style="font-weight:400">
                            出发地
                        </h5>    
                    </el-col>    
                    <el-col :span="12">
                        <h5 style="font-weight:400">
                            目的地
                        </h5>
                    </el-col>
                </el-row>                
            </div>
        </el-col>
        <!-- <el-col :span="60"      
        >
                <div class="dateContainer">
                <el-row 
                    style=
                    "margin-top:50px;
                    margin-left:50px;
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
        </el-col>
        <el-col 
        :span="1"
        >
            <el-button 
                class = "delete"  
                circle
                type="text"
            >
            <i 
            class="el-icon-close"
            style="color:#303133;
                    font-size:20px;
                    position:absolute;
                    "
            >
            </i>
            </el-button>
        </el-col> -->
    </el-row> 
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
    .container {
    flex-direction: row;
    justify-content: space-between;
    position: relative;
    border-radius: 6px;
    background-color:#ffffff;
    border: 1px solid #eee;
    box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
    width:400px;
    height: 80px;
    margin-left: 20px;
    }
    .container:hover{
    box-shadow: 0 0 12px 0 rgb(0 0 0 / 10%);
    }
    .dateContainer {
        flex-direction: row;
        justify-content: space-between;
        position: relative;
        border-radius: 6px;
        background-color:#ffffff;
        border: 1px solid #eee;
        box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
        width:500px;
        height: 80px;
        margin-left: 500px;
    }
    .dateContainer:hover{
        box-shadow: 0 0 12px 0 rgb(0 0 0 / 10%);
    }
    .delete{
        width:35px;
        height:35px;
        background-color: #ffffff;
    }
    .delete:hover{
        background-color: #eee !important;
    }
</style>