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
  lintOnSave: false
}