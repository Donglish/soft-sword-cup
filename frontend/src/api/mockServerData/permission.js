import Mock from 'mockjs'
export default {
  getMenu: config => {
    const { name, password } = JSON.parse(config.body)
    if (name === '123456' && password === '123456') {
      return {
        code: 20000,
        data: {
          info:{
            name: Mock.Random.name(),
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
              },
            ],
          },
          token: Mock.Random.guid(),
          message: '获取成功'
        }
      }
    } else {
      return {
        code: -999,
        data: {
          message: '密码错误'
        }
      }
    }
  }
}