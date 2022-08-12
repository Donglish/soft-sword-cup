<template>
  <div class="relative min-h-screen flex">
            <div
                class="
                    flex flex-col
                    sm:flex-row
                    items-center
                    md:items-start
                    sm:justify-center
                    md:justify-start
                    flex-auto
                    min-w-0
                    bg-white
                "
            >
                <div
                    class="
                        sm:w-1/2
                        xl:w-3/5
                        h-full
                        hidden
                        md:flex
                        flex-auto
                        items-center
                        justify-center
                        p-10
                        overflow-hidden
                        bg-purple-900
                        text-white
                        bg-no-repeat bg-cover
                        relative
                    "
                     :style="{'background-image': 'url('+require('@/assets/images/img.jpg')+')'}"
                >
                    <div
                        class="
                            absolute
                            bg-gradient-to-b
                            from-indigo-600
                            to-blue-500
                            opacity-75
                            inset-0
                            z-0
                        "
                    ></div>
                    <div class="w-full max-w-md z-10">
                        <div class="sm:text-4xl xl:text-5xl font-bold leading-tight mb-6"
                            >有机可乘</div
                        >
                        <div class="sm:text-sm xl:text-md text-gray-200 font-normal"
                            >一种高性能民航旅客行程推荐系统&nbsp;&nbsp;(中南大学&nbsp; 做核酸要排队小队)</div
                        >
                    </div>
                    <ul class="circles">
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                        <li></li>
                    </ul>
                </div>
                <div
                    class="
                        md:flex md:items-center md:justify-center
                        w-full
                        sm:w-auto
                        md:h-full
                        w-2/5
                        xl:w-2/5
                        p-8
                        md:p-10
                        lg:p-14
                        sm:rounded-lg
                        md:rounded-none
                        bg-white
                    "
                >
                    <div class="max-w-md w-full mx-auto space-y-8">
                        <div class="text-center">
                            <h2 class="mt-6 text-3xl font-bold text-gray-900">欢迎使用</h2>
                            <p class="mt-2 text-sm text-gray-500">第三方登录</p>
                        </div>
                        <div class="flex flex-row justify-center items-center space-x-3">
                            <a
                                href=""
                                class="
                                    w-11
                                    h-11
                                    items-center
                                    justify-center
                                    inline-flex
                                    rounded-2xl
                                    font-bold
                                    text-lg
                                    bg-blue-900
                                    hover:shadow-lg
                                    cursor-pointer
                                    transition
                                    ease-in
                                    duration-300
                                "
                                ><img
                                    src="https://open.weixin.qq.com/zh_CN/htmledition/res/assets/res-design-download/icon64_appwx_logo.png"
                            /></a>
                            <a
                                href=""
                                class="
                                    w-11
                                    h-11
                                    items-center
                                    justify-center
                                    inline-flex
                                    rounded-2xl
                                    font-bold
                                    text-lg text-white
                                    bg-blue-400
                                    hover:shadow-lg
                                    cursor-pointer
                                    transition
                                    ease-in
                                    duration-300
                                "
                                ><img
                                    src="../../assets/images/支付宝logo.png"
                            /></a>
                            <a
                                href="javascript:"
                                class="
                                    w-11
                                    h-11
                                    items-center
                                    justify-center
                                    inline-flex
                                    rounded-2xl
                                    font-bold
                                    text-lg text-white
                                    bg-blue-500
                                    hover:shadow-lg
                                    cursor-pointer
                                    transition
                                    ease-in
                                    duration-300
                                "
                                ><img
                                    src="../../assets/images/QQ.png"
                            /></a>
                        </div>
                        <div class="flex items-center justify-center space-x-2">
                            <span class="h-px w-16 bg-gray-200"></span>
                            <span class="text-gray-300 font-normal">使用账号登录</span>
                            <span class="h-px w-16 bg-gray-200"></span>
                        </div>
                        <el-form class="mt-8 space-y-6" :rules="rules">
                            <input type="hidden" name="remember" value="true"/>
                            <div class="relative">
                                <label class="ml-3 text-sm font-bold text-gray-700 tracking-wide"
                                    >账号</label
                                >
                                <input
                                    class="
                                        w-full
                                        text-base
                                        px-4
                                        py-2
                                        border-b border-gray-300
                                        focus:outline-none
                                        rounded-2xl
                                        focus:border-indigo-500
                                    "
                                    type="input"
                                    placeholder="请输入账号"
                                    v-model="form.name"
                                />
                            </div>
                            <div class="mt-8 content-center">
                                <label class="ml-3 text-sm font-bold text-gray-700 tracking-wide"
                                    >密码</label
                                >
                                <input
                                    class="
                                        w-full
                                        content-center
                                        text-base
                                        px-4
                                        py-2
                                        border-b
                                        rounded-2xl
                                        border-gray-300
                                        focus:outline-none focus:border-indigo-500
                                    "
                                    type="password"
                                    v-model="form.password"
                                    placeholder="请输入密码"
                                />
                            </div>
                            <div class="flex items-center justify-between">
                                <div class="flex items-center">
                                    <input
                                        id="remember_me"
                                        name="remember_me"
                                        type="checkbox"
                                        class="
                                            h-4
                                            w-4
                                            bg-blue-500
                                            focus:ring-blue-400
                                            border-gray-300
                                            rounded
                                        "
                                    />
                                    <label
                                        for="remember_me"
                                        class="ml-2 block text-sm text-gray-900"
                                        >记住我</label
                                    >
                                </div>
                                <div class="text-sm">
                                    <div @click="visit()" class="text-indigo-400 hover:text-blue-500"
                                        >访客模式</div
                                    >
                                </div>
                            </div>
                            <div>
                                <button
                                    type="button"
                                    class="
                                        w-full
                                        flex
                                        justify-center
                                        bg-gradient-to-r
                                        from-indigo-500
                                        to-blue-600
                                        hover:bg-gradient-to-l
                                        hover:from-blue-500
                                        hover:to-indigo-600
                                        text-gray-100
                                        p-4
                                        rounded-full
                                        tracking-wide
                                        font-semibold
                                        shadow-lg
                                        cursor-pointer
                                        transition
                                        ease-in
                                        duration-500
                                    "
                                    @click="login()"
                                    >登 录
                                    </button>
                            </div>
                        </el-form>
                    </div>
                </div>
            </div>
        </div>
</template>

<script>
import {getMenu} from '../../api/data'
import {guid} from '@/utils/utils.js'
export default {
    name:'login',
    data(){
        return {
            form: {
                name:'',
                password:'',
            },
            rules:{
                name:[
                    {required:true,message:"请输入账号",trigger:"blur"},
                    {
                        min:3,
                        message:"用户名长度不能小于3位"
                    }
                ],
                password:[
                    {required:true,mesage:"请输入密码",trigger:"blur"}
                ]
            }
        }
    },
    methods:{
        guid,
        visit(){
            this.$store.commit('setToken',this.guid())
            this.$router.push({name:'home'})
        },
        login(){
            getMenu(this.form).then(({ data: res})=> {
                if(res.code === 20000){
                    this.$store.commit('setToken',res.data.token)
                    this.$store.commit('setInfo',res.data.info)
                    this.$router.push({name:'home'})
                }
                else{
                    this.$message.warning(res.data.mesage)
                }
            })
        }
    }
}
</script>

<style>
@import "../../assets/css/style.css";
@import "@/assets/css/tailwind.min.css";
</style>