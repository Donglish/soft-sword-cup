import Cookie from 'js-cookie'
export default {
    state: {
        isCollapse: false,
        tabList: [
            {
                path:'/',
                name:'home',
                label:'首页',
                icon:'home',
                canVisit:false
            },
            {
                path:'/result',
                name:'result',
                label:'查询结果',
                icon:'tickets',
                canVisit:true,
            }
        ],
        currentMenu:null,
        menu:[
            {
                path:'/',
                label: '首页',
                icon:'s-home',
                name:'home',
                url:'home/index',
                canVisit:false
            },
            {
                path:'/result',
                label:'查询结果',
                icon:'tickets',
                name:'result',
                url:'result/index',
                canVisit:true
            }
        ]
    },
    mutations: {
        changeVisit(state){
            state.menu[1].canVisit = !state.menu[1].canVisit;
        },
        collapseMenu(state){
            state.isCollapse = !state.isCollapse;
        },
        selectMenu(state,val){
            if(val.name !== 'home'){
                state.currentMenu = val;
                const result = state.tabsList.findIndex(item => item.name === val.name);
                if(result === -1){
                    state.tabsList.push(val);
                }
            } else{
                state.currentMenu = null
            }
        },
        closeTag(state,val){
            const result = state.tabsList.findIndex(item => item.name === val.name);
            state.tabsList.splice(result,1);
        },
        setMenu(state,val){
            state.menu = val
            Cookie.set('menu',JSON.stringify(val))
        },
        clearMenu(state){
            state.menu = [],
            Cookie.remove('menu')
        },
        addMenu(state,router){
            if(!Cookie.get('menu')){
                return;
            }
            const menu = JSON.parse(Cookie.get('menu'))
            state.menu = menu
            const menuArray = []
            menu.forEach(item => {
                item.component = () => import(`../views/${item.url}`);
                menuArray.push(item);
            });
            menuArray.forEach(item => {
                router.addRoute('Main', item)
            })
        }
    }
}