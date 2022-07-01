module.exports = {
  devServer: {
    port: 8080,
    open: true,
    proxy:{
      '/api':{
        target:'http://localhost:8081',
        changeOrigin:true
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