import Mock from 'mockjs'
import permissionApi from './mockServerData/permission'
Mock.mock(/permission\/getMenu/,'post',permissionApi.getMenu)