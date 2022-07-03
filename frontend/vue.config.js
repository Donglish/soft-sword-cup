module.exports = {
  devServer: {
    port: 8080,
    open: true,
    proxy:{
      '/api':{
        target:'http://120.24.85.165:8999/',
        changeOrigin:true,
        pathRewrite:{
          '^/api':''
        }
      }
    }
  },
  // css:{
  //   loaderOptions:{
  //     postcss:{
  //       plugins:[
  //         require('postcss-px2rem')({remUnit:192}),
  //       ]
  //     }
  //   }
  // },
  lintOnSave: false
}