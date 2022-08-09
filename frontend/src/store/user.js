import Cookies from "js-cookie"
export default {
    state: {
        token: '',
        info: {
            name:'',
            agentList:[],
            agentList:[{
                value: 'HKG001',
                label:"HKG001",
                },
                {
                value: 'BJS001',
                label:"BJS001",
                },
                {
                value: 'TSN001',
                label: "TSN001",
                },
                {
                value: 'SHA001',
                label:"SHA001",
                },
                {
                value: 'CAN001',
                label:"CAN001",
                },
                {
                value: 'SZX001',
                label:"SZX001",
                },
                {
                value: 'NKG001',
                label:"NKG001",
                },
                {
                value: 'CTU001',
                label:"CTU001",
                },
                {
                value: 'CKG001',
                label:"CKG001",
                },
                {
                value: 'KMG001',
                label:"KMG001",
                },
                {
                value: 'HGH001',
                label:"HGH001",
                },
                {
                value: 'XIY001',
                label:"XIY001",
                },
                {
                value: 'WUH001',
                label:"WUH001",
                },
                {
                value: 'CGO001',
                label:"CGO001",
                },
                {
                value: 'CGQ001',
                label:"CGQ001",
                },
                {
                value: 'CSX001',
                label:"CSX001",
                },
                {
                value: 'TYN001',
                label:"TYN001",
                },
                {
                value: 'DLC001',
                label:"DLC001",
                },
                {
                value: 'FOC001',
                label:"FOC001",
                },
                {
                value: 'XMN001',
                label:"XMN001"
                },],
        }
    },
    mutations:{
        setToken(state,val){
            state.token = val;
            Cookies.set('token',val);
        },
        clearToken(state){
            state.token = '',
            Cookies.remove('token')
        },
        getToken(state){
            state.token = state.token || Cookies.get('token')
        },
        setInfo(state,info){
            state.info = info
        },
    }
}