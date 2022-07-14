module.exports = {
  devServer: {
    host:'localhost',
    port: 8089,
    open: true,
    proxy:{
      '/api':{
        target:'http://120.24.85.165:8990',
        changeOrigin:true,
        pathRewrite:{
          '^/api':''
        }
      }
    }
  },
  lintOnSave: false
}