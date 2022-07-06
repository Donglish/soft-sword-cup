module.exports = {
  devServer: {
    port: 8080,
    open: true,
    proxy:{
      '/api':{
        target:'http://120.24.85.165:12345',
        changeOrigin:true,
        pathRewrite:{
          '^/api':''
        }
      }
    }
  },
  lintOnSave: false
}