<template>
  <div class="home">
       <div style="display:inline-block">
             <el-button 
                style=
                "width:35px;
                height:35px;
                background-color: #ffffff;
                margin-top:15px;
                margin-left:10px;
                margin-bottom:25px;
                "
                circle
                >
                <div
                    style="color:#303133;
                        font-size:25px;
                        position:absolute;
                        font-weight:400;
                        margin-top:-12px;
                        margin-left:-3.5px
                        "
                >
                {{this.id}}
                </div>
            </el-button>   
        </div>
    <div class="form">     
      <div class="starting" ref="startingRef">
        <label class="s-label">出发地</label>
        <div class="area-wrapper">
          <input id="start-input" type="text" ref="startInputRef" value="" placeholder="起点"
            style="margin-top:10px"
            @click.stop="addBeforeActiveAndDOMClick($event)"
            @focus="handleLeftVisible"
          >
          <div class="area start-area" :style="{display: leftVisible?'block':'none'}" ref="startAreaRef">
            <div class="area-selector">
              <div class="tabs" ref="leftTabsRef" @click.stop>
                <div class="tab-item active" @click="switchCityArea">
                  国内
                </div>
                <div class="tab-item" @click="switchCityArea">
                  国际及中国港澳台
                </div>
              </div>
            </div>
            <div class="city-wrraper" @click.stop>
                <el-tabs v-model="activeName" v-show="switchArea" style="margin-left:20px">
                    <el-tab-pane label="热门" name="热门">
                      <ul class="hot-city city-group">
                        <li class="city-item start-city-item" v-for="(city, i) in hotCities" :key="i"
                          @click="getCityName($event)"
                        >
                          {{city}}
                        </li>
                      </ul>
                    </el-tab-pane>
                    <el-tab-pane :label="key1" :name="key1" v-for="(value1, key1) in data" :key="key1">
                      <div class="character-city-wrapper">
                        <div class="character-city" v-for="(value2, key2) in value1" :key="key2">
                          <div class="character">{{key2}}</div>
                          <ul class="city-group">
                            <li class="city-item start-city-item" v-for="(city, i) of value2" :key="i"
                              @click="getCityName($event)"
                            >
                              {{city}}
                            </li>
                          </ul>
                        </div>
                      </div>
                    </el-tab-pane>
                </el-tabs>
                <el-tabs v-model="activeName" v-show="!switchArea" style="margin-left:10px">
                    <el-tab-pane :label="key" :name="key" v-for="(value, key) in data2" :key="key">
                      <ul class="hot-city city-group">
                        <li class="city-item start-city-item" v-for="(city, i) in value" :key="i"
                          @click="getCityName($event)"
                        >
                          {{city}}
                        </li>
                      </ul>
                    </el-tab-pane>
                </el-tabs>
            </div>
          </div>
          <div class="search-area" ref="searchAreaRef" v-show="leftSearchResultVisible">
            <div class="result-city start-city" :title="item.name" v-for="(item, i) of searchResult" :key="i"
              @mouseover="addBGColor($event)"
            >
              <span class="city-tag">城市</span>
              <span class="cityName">{{item.name}} {{item.spell}}</span>
            </div>
            <div style="color: red;line-height: 40px;font-size: 14px;margin-left: 15px;" v-show="!searchResult[0]">
              对不起，暂不支持该地点
            </div>
          </div>
        </div>
      </div>
      <div class="switch-icon" @click.stop="witchLocation($event)">
        <span class="iconfont icon-double-arrows">
          <img src="../assets/arrow.png" style="width:20px;height:20px"/>
        </span>
      </div>
      <div class="ending" ref="endingRef">
        <label class="d-label">目的地</label>
        <div class="area-wrapper">
          <input id="ending-input" type="text" ref="endInputRef" value="" placeholder="终点"
            style="margin-top:10px"
            @click.stop="addBeforeActiveAndDOMClick($event)"
            @focus="handleRightVisible"
           >
          <div class="area ending-area" :style="{display: rightVisible?'block':'none'}" ref="endingAreaRef">
            <div class="area-selector">
              <div class="tabs" ref="rightTabsRef" @click.stop>
                <div class="tab-item active" @click="switchCityArea($event)">
                  国内
                </div>
                <div class="tab-item" @click="switchCityArea($event)">
                  国际及中国港澳台
                </div>
              </div>
            </div>
            <div class="city-wrraper" @click.stop>
                <el-tabs v-model="activeName" v-show="switchArea" style="margin-left:20px">
                    <el-tab-pane label="热门" name="热门">
                      <ul class="hot-city city-group">
                        <li class="city-item ending-city-item" v-for="(city, i) in hotCities" :key="i"
                          @click="getCityName($event)"
                        >
                          {{city}}
                        </li>
                      </ul>
                    </el-tab-pane>
                    <el-tab-pane :label="key1" :name="key1" v-for="(value1, key1) in data" :key="key1">
                      <div class="character-city-wrapper">
                        <div class="character-city" v-for="(value2, key2) in value1" :key="key2">
                          <div class="character">{{key2}}</div>
                          <ul class="city-group">
                            <li class="city-item ending-city-item" v-for="(city, i) of value2" :key="i"
                              @click="getCityName($event)"
                            >
                              {{city}}
                            </li>
                          </ul>
                        </div>
                      </div>
                    </el-tab-pane>
                </el-tabs>
                <el-tabs v-model="activeName" v-show="!switchArea" style="margin-left:10px">
                    <el-tab-pane :label="key" :name="key" v-for="(value, key) in data2" :key="key">
                      <ul class="hot-city city-group">
                        <li class="city-item ending-city-item" v-for="(city, i) in value" :key="i"
                          @click="getCityName($event)"
                        >
                          {{city}}
                        </li>
                      </ul>
                    </el-tab-pane>
                </el-tabs>
            </div>
          </div>
          <div class="search-area" ref="searchEndingAreaRef" v-show="rightSearchResultVisible">
            <div class="result-city ending-city" :title="item.name" v-for="(item, i) of searchResult" :key="i"
              @mouseover="addBGColor"
            >
              <span class="city-tag">城市</span>
              <span class="cityName">{{item.name}} {{(item.spell)}}</span>
            </div>
            <div style="color: red;line-height: 40px;font-size: 14px;margin-left: 15px;" v-show="!searchResult[0]">
              对不起，暂不支持该地点
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    data() {
      return {
        // 互换地点图标旋转角度
        iconAngle: 0,
        leftVisible: false,
        rightVisible: false,
        // 控制右边栏城市显示与隐藏
        rightCityArea: true,
        // 切换国内、国际及中国港澳台地区
        switchArea: true,
        // 控制左边搜索区域的显示与隐藏
        leftSearchResultVisible: false,
        // 控制右边边搜索区域的显示与隐藏
        rightSearchResultVisible: false,
        activeName: '热门',
        // 控制起点和终点同步左边栏，默认国内
        commonName: '国内',
        localLabel: [],
        // 默认搜索选择城市
        defaultSearchValue: '',
        defaultSearchValue2: '',
        hotCities: ['北京', '上海', '广州', '深圳', '成都', '杭州', '武汉', '西安', '重庆', '青岛', '长沙', '南京', '厦门', '昆明', '大连', '天津', '郑州', '三亚', '济南', '福州'],
        characterCities: ['阿泰勒', '阿克苏', '鞍山', '安庆', '安顺', '阿拉善左', '中国澳门', '阿里', '阿拉善右', '阿尔山'],
        data: {
          'ABCDEF': {
            A: ['阿泰勒', '阿克苏',  '鞍山', '安庆'],
            B: ['包头', '毕节', '北海', '北京', '博乐'],
            C: ['昌都', '承德', '常德', '长春', '朝阳'],
            D: ['大同', '达州', '稻城', '丹东', '迪庆'],
            E: ['鄂尔多斯', '额济纳旗', '恩施', '二连浩特'],
            F: ['福州', '阜阳', '抚远', '富蕴', '佛山']
          },
          'GHIJ': {
            G: ['阿泰勒', '阿克苏', '包头', '毕节', '北海'],
            H: ['巴中', '百色', '鞍山', '安庆', '安顺'],
            I: ['昌都', '承德', '常德', '长春', '朝阳'],
            J: ['大同', '达州', '稻城', '丹东'],
          },
          'KLMN': {
            K: ['阿泰勒', '阿克苏', '包头', '毕节', '北海'],
            L: ['巴中', '百色', '鞍山', '安庆', '安顺'],
            M: ['昌都', '承德', '常德', '长春', '朝阳'],
            N: ['大同', '达州', '稻城', '丹东', '迪庆'],
          },
          'PQRSTUVW': {
            P: ['阿泰勒', '阿克苏', '包头', '毕节', '北海', '北京'],
            Q: ['巴中', '百色', '鞍山', '安庆', '安顺', '阿拉善左'],
            R: ['昌都', '承德', '常德', '长春', '朝阳', '赤峰'],
            S: ['大同', '达州', '稻城', '丹东', '迪庆', '敦煌'],
            T: ['鄂尔多斯', '额济纳旗', '恩施', '二连浩特'],
            U: ['福州', '阜阳', '抚远', '富蕴', '佛山'],
            V: ['昌都', '承德', '常德', '长春'],
            W: ['百色', '鞍山']
          },
          'XYZ': {
            X: ['阿泰勒', '阿克苏', '包头', '毕节', '北海'],
            Y: ['巴中', '百色', '鞍山', '安庆', '安顺'],
            Z: ['昌都', '承德', '常德', '长春', '朝阳'],
          }
        },
        data2: {
          '国际•中国港澳台热门': ['中国香港', '首尔', '中国台北', '东京', '新加坡', '中国澳门', '曼谷', '大阪', '胡志明市', '马尼拉', '名古屋', '伦敦', '吉隆坡', '釜山', '悉尼', '法兰克福', '温哥华', '巴黎', '纽约', '洛杉矶'],
          '亚洲': ['中国香港', '首尔', '中国台北', '东京'],
          '欧洲': ['中国澳门', '曼谷', '大阪', '胡志明市', '马尼拉', '名古屋'],
          '美洲': ['中国澳门', '曼谷', '大阪', '胡志明市', '马尼拉', '名古屋'],
          '非洲': ['首尔', '中国台北'],
          '大洋洲': ['中国香港']
        },
        data3: [
          { name: '中国澳门', spell: 'aomen' }, { name: '奥克兰', spell: 'aokelan' },
          { name: '北京', spell: 'beijing' }, { name: '巴黎', spell: 'bali' },
          { name: '广州', spell: 'guangzhou' }, { name: '成都', spell: 'chengdu' },
          { name: '大连', spell: 'dalian' }, { name: '大阪', spell: 'daban' },
          { name: '福州', spell: 'fuzhou' }, { name: '釜山', spell: 'fushan' },
        ],
        // 保存城市搜索结果
        searchResult: [],
      }
    },
    props:{
      id:{
        type:Number,
        required: true
      }
    },
    methods: {
      // 添加伪类和dom点击事件
      addBeforeActiveAndDOMClick(e) {
        var target = e.target
        var targetId = target.id
        target.select()
        if (targetId === 'start-input') {
          this.rightVisible = false
          if(!this.leftSearchResultVisible) {
            this.leftVisible = true
          }
          // 添加起点输入框伪类样式Class
          this.addInputBeforeClass(targetId)
        } else {
          this.leftVisible = false
          if(!this.rightSearchResultVisible) {
            this.rightVisible = true
          }
          // 添加终点输入框伪类样式Class
          this.addInputBeforeClass(targetId)
        }
        // 在城市区域显示时,给文档添加点击隐藏事件
        document.addEventListener('click', this.hideCityArea)
        
      },
      // 左边文本框聚焦显示城市区域
      handleLeftVisible() {
        this.rightSearchResultVisible = false
        this.listenStartInput()
      },
      // 右边文本框聚焦事件，显示城市区域
      handleRightVisible() {
        // 控制起点区域隐藏后展示默认值到输入框内
        // this.handleStartSearchHide()
        this.leftSearchResultVisible = false
        this.listenEndingInput()
      },
      witchLocation(e) {
        // 旋转箭头图标
        var startInput = this.$refs.startInputRef
        var endInput = this.$refs.endInputRef
        var middleValue = startInput.value
        var target = e.target
        target.style.transition = '.5s'
        target.style.transform = `rotate(${this.iconAngle+=180}deg)`
        // 判断是否有显示城市区域，有的话区域也互换
        if (this.leftVisible) {
          this.leftVisible = false
          this.rightVisible = true
        } else if (this.rightVisible) {
          this.leftVisible = true
          this.rightVisible = false
        }
        // 转换先去除所有伪类
        this.removeAllInputBeforeClass()
        // var starting = this.$refs.startingRef
        // var ending = this.$refs.endingRef
        // if (starting.className.indexOf('inputActive') !== -1) {
        //   starting.classList.remove('inputActive')
        //   ending.classList.add('inputActive')
        // } else {
        //   starting.classList.add('inputActive')
        //   ending.classList.remove('inputActive')
        // }
        startInput.value = endInput.value
        endInput.value = middleValue
      },
      
      // 隐藏城市区域
      hideCityArea() {
        if(!this.searchResult[0]) {
          // 没有收到城市时，隐藏时清空输入框内其他字符
          this.$refs.startInputRef.value = ''
          this.$refs.endInputRef.value = ''
        }
        this.leftVisible = false
        this.rightVisible = false
        this.removeAllInputBeforeClass()
        this.handleStartSearchHide()
        // this.leftSearchResultVisible = false
        // this.rightSearchResultVisible = false
        this.handleEndingSearchHide()
        document.removeEventListener('click', this.hideCityArea)
      },
      // 点击国内或其他地区切换右边栏的城市显示
      switchCityArea(e) {
        var target = e.target
        var siblingNodes = target.parentNode.children
        for(let i = 0; i < siblingNodes.length; i++) {
          siblingNodes[i].classList.remove('active')
        }
        target.classList.add('active')
        if (target.innerHTML.trim() === '国内') {
          this.switchArea = true
          this.activeName = '热门'
          this.commonName = '国内'
        } else {
          this.switchArea = false
          this.activeName = '国际•中国港澳台热门'
          this.commonName = '国际•中国港澳台热门'
        }
        
      },
      // 监听input内容变化,js控制的内容变化不会触发该函数
      listenStartInput() {
        var startInput = this.$refs.startInputRef
        var searArea = this.$refs.searchAreaRef
        var vm = this
        startInput.oninput = function(res) {
          // 查询当前输入的字符串
          vm.searchString(this.value)
          // 当展示搜索结果框时，获取默认值
          vm.leftSearchResultVisible = true
          vm.leftVisible = false
          // 当输入框内容为空时，显示城市区域
          if(!res.data) {
            vm.leftSearchResultVisible = false
            vm.leftVisible = true
          }
          setTimeout(() => {
            vm.addSearchAreaMouseoverBG(searArea, this)
          })
        }
      },
      // 监听input内容变化,js控制的内容变化不会触发该函数
      listenEndingInput() {
        var endInput = this.$refs.endInputRef
        var searArea = this.$refs.searchEndingAreaRef
        var vm = this
        endInput.oninput = function(res) {
          // 查询当前输入的字符串
          vm.searchString(this.value)
          
          vm.rightSearchResultVisible = true
          vm.rightVisible = false
          // 当输入框内容为空时，显示城市区域
          if(!res.data) {
            vm.rightSearchResultVisible = false
            vm.rightVisible = true
          }
          
          setTimeout(() => {
            vm.addSearchAreaMouseoverBG(searArea, this)
          })
        }
      },
      addSearchAreaMouseoverBG(searArea, target) {
        var ResultCities = searArea.getElementsByClassName('result-city')
        for(var i = 0; i < ResultCities.length; i++) {
          ResultCities[i].style.backgroundColor = ''
        }
        if(ResultCities[0]) {
          ResultCities[0].style.backgroundColor = '#F2F9FF'
        }
        
        // 当显示搜索结果区域时，获取默认值
        this.defaultValue(target)
      },
      // 添加起点或终点输入框伪类样式Class
      addInputBeforeClass(id) {
        var starting = this.$refs.startingRef
        var ending = this.$refs.endingRef
        if (id === 'start-input') {
          starting.classList.add('inputActive')
          if (ending.className.indexOf('inputActive') !== -1) {
            ending.classList.remove('inputActive')
          }
        } else {
          ending.classList.add('inputActive')
          if (starting.className.indexOf('inputActive') !== -1) {
            starting.classList.remove('inputActive')
          }
        }
      },
      // 去掉所有input标签的伪类Class
      removeAllInputBeforeClass() {
        var starting = this.$refs.startingRef
        var ending = this.$refs.endingRef
        starting.classList.remove('inputActive')
        ending.classList.remove('inputActive')
      },
      // 同步起点和终点的左边栏active样式
      commonLeftActive(className, name) {
        if (className.indexOf('starting') !== -1) {
          let tab = this.$refs.rightTabsRef
          commonSwitch(tab)
        } else {
          let tab = this.$refs.leftTabsRef
          commonSwitch(tab)
        }
        function commonSwitch(tab) {
          let tabItems = tab.getElementsByClassName('tab-item')
          if(name === '国内') {
            tabItems[1].classList.remove('active')
            tabItems[0].classList.add('active')
          } else {
            tabItems[0].classList.remove('active')
            tabItems[1].classList.add('active')
          }
        }
      },
      // 控制起点区域隐藏后，把默认值展示到输入框内
      handleStartSearchHide() {
        this.leftSearchResultVisible = false
        if(this.defaultSearchValue) {
          var startInput = this.$refs.startInputRef
          startInput.value = this.defaultSearchValue
        }
      },
      // 控制终点区域隐藏后展示默认值到输入框内
      handleEndingSearchHide() {
        this.rightSearchResultVisible = false
        if(this.defaultSearchValue2) {
          var endInput = this.$refs.endInputRef
          endInput.value = this.defaultSearchValue2
        }
      },
      defaultValue(target) {
        var inputLocation = target.getAttribute ? target.getAttribute('placeholder') : ''
        var mouseoverClassName = target.className ? target.className : ''
        // 判断传入的是起点输入框或者是起点div
        if (inputLocation === '起点' || mouseoverClassName.indexOf('start-city') !== -1) {
          let searArea = this.$refs.searchAreaRef
          // 没有传入参数时候执行，也就是第一次执行
          let cityName = searArea.getElementsByClassName('cityName')[0]
          if (inputLocation === '起点') {
            cityName = searArea.getElementsByClassName('cityName')[0]
          } else {
            cityName = target.getElementsByClassName('cityName')[0]
          }
          // 如果搜索不到设置为空
          let val = cityName ? cityName.innerHTML : ''
          this.defaultSearchValue = val
        }
         else {
          let searArea = this.$refs.searchEndingAreaRef
          // 没有传入参数时候执行，也就是第一次执行
          let cityName = searArea.getElementsByClassName('cityName')[0]
          if (inputLocation === '终点') {
            cityName = searArea.getElementsByClassName('cityName')[0]
          } else {
            cityName = target.getElementsByClassName('cityName')[0]
          }
          // 如果搜索不到设置为空
          let val = cityName ? cityName.innerHTML : ''
          this.defaultSearchValue2 = val
        }
      },
      addBGColor(e) {
        var target = e.target
        if (target.className.indexOf('start-city') !== -1) {
          // target.title 存在时再执行，防止子元素的mouseover冒泡
          if (target.title) {
            let searArea = this.$refs.searchAreaRef
            let ResultCities = searArea.getElementsByClassName('result-city')
            for(let i = 0; i < ResultCities.length; i++) {
              ResultCities[i].style.backgroundColor = ''
            }
            e.target.style.backgroundColor = '#F2F9FF'
            this.defaultValue(e.target)
          }
        } else {
          // target.title 存在时再执行，防止子元素的mouseover冒泡
          if (target.title) {
            let searArea = this.$refs.searchEndingAreaRef
            let ResultCities = searArea.getElementsByClassName('result-city')
            for(let i = 0; i < ResultCities.length; i++) {
              ResultCities[i].style.backgroundColor = ''
            }
            target.style.backgroundColor = '#F2F9FF'
            this.defaultValue(e.target)
          }
        }
      },
      // 查询字符串方法
      searchString(name) {
        var searchResult = []
        var pattern3 = new RegExp('^' + name.toLowerCase())
        // 验证是否是中文
        var pattern = new RegExp("[\u4E00-\u9FA5]+");
        if(pattern.test(name)){
          for(let i = 0; i < this.data3.length; i++) {
            if(this.data3[i].name.match(pattern3)) {
              searchResult.push(this.data3[i])
            }
          }
        }
        //验证是否是英文
        var pattern2 = new RegExp("[A-Za-z]+")
        if(pattern2.test(name)){
          for(let i = 0; i < this.data3.length; i++) {
            if(this.data3[i].spell.match(pattern3)) {
              searchResult.push(this.data3[i])
            }
          }
        }
        this.searchResult = searchResult
      },
      // 点击起点各个城市的点击事件，获取标签文本,传入输入框内
      getCityName(e) {
        var target = e.target
        // 保存获取到的城市名字
        var val = null
        if (target.className.indexOf('start-city-item') !== -1) {
          var starting = this.$refs.startingRef
          this.leftVisible = false
          this.rightVisible = true
          val = target.innerHTML
          this.$refs.startInputRef.value = val
          // 把点击城市名获取到的值赋值给默认值
          this.defaultSearchValue = val
          // 选择完城市自动打开终点城市选择区域时，添加终点输入框伪类样式
          this.addInputBeforeClass()
          this.commonLeftActive(starting.className, this.commonName)
        } else {
          var ending = this.$refs.endingRef
          this.rightVisible = false
          val = target.innerHTML
          this.$refs.endInputRef.value = val
          // 把点击城市名获取到的值赋值给默认值
          this.defaultSearchValue2 = val
          // 获取完终点值去掉伪类样式
          ending.classList.remove('inputActive')
          this.commonLeftActive(ending.className, this.commonName)
        }
      },
    }
  }
</script>

<style scoped lang="less">
  .home{
      margin-left: 50px;
      border-radius: 5px;
      background-color: white;
      border: 1px solid gainsboro;
      height: 65px;
      width: 570px;
      position: relative;
      vertical-align: middle;
      box-shadow: 0 0 12px 0 rgb(0 0 0 / 6%);
    .form{
      vertical-align: middle;
      display: inline-block;
      position: absolute;
      margin-left: 10px;
      width: 508px;
      .switch-icon{
        position: absolute;
        top: 0;
        right: 0;
        bottom: 0;
        left: 0;
        margin-top: 15px;
        margin-left: 242px;
        width: 32px;
        height: 32px;
        background-color: white;
        border: 1px solid gainsboro;
        border-radius: 50%;
        box-sizing: border-box;
        z-index: 2;
        cursor: pointer;
        .icon-double-arrows{
          position: absolute;
          z-index: 3;
          display: block;
          width: 100%;
          height: 100%;
          border-radius: 50%;
          font-size: 20px;
          text-align: center;
          line-height: 32px;
          background-color: white;
        }
        .icon-double-arrows:hover{
          background-color: ghostwhite;
        }
      }
      .switch-icon:after{
        content: '';
        width: 1px;
        height: 62px;
        position: absolute;
        left: 15px;
        top: -15px;
        background: url(//pic.c-ctrip.com/fltcommon/index/ico/input-liner.png);
      }
      .starting{
        position: absolute;
        left: 0;
        width: 230px;
        height: 100%;
      }
      .starting:before{
        content: '';
        position: absolute;
        top: 0px;
        left: 0px;
        height: 1px;
        width: 254px;
        background: #fff;
        border-top: 2px solid #0086F6;
        border-radius: 16px 0 0 0;
        z-index: 3;
        display: none;
      }
      .ending{
        position: absolute;
        right: 0;
        width: 230px;
        height: 100%;
      }
      .ending::before{
        content: '';
        position: absolute;
        top: 0px;
        left: -16px;
        height: 1px;
        width: 254px;
        background: #fff;
        border-top: 2px solid #0086F6;
        border-radius: 16px 0 0 0;
        z-index: 3;
        display: none;
      }
      .inputActive:before{
        display: block;
        animation: beformMove .1s;
      }
    }
    .hot-city{
      padding: 24px 32px;
    }
    .character-city-wrapper{
      padding-top: 24px;
      padding-left: 32px;
      .character{
        width: 26px;
        display: inline-block;
        line-height: 32px;
        vertical-align: top;
        font-size: 14px;
        font-weight: 600;
      }
    }
    .city-group{
      display: inline-block;
      max-width: 570px;
      .city-item{
        float: left;
        padding: 0 2px 0 8px;
        width: 84px;
        height: 32px;
        line-height: 32px;
        font-size: 14px;
        color: #333333;
        cursor: pointer;
      }
      .city-item:hover{
        background: rgba(0,134,246,0.05);
        color: #0086F6;
      }
    }
  }
  .home:hover{
    box-shadow: 0 0 15px 0 rgb(0 0 0 / 15%);
    }
  label{
    display: block;
    position: absolute;
    left: 16px;
    top: 10px;
    z-index: 1;
    font-size: 12px;
    color: #999;
  }
  input{
    position: absolute;
    height: 100%;
    width: 100%;
    box-sizing: border-box;
    font-size: 16px;
    padding: 29px 0 14px 16px;
    border: none;
    border-radius: 10px;
    // 取消input标签的默认选中状态样式
    outline: none;
  }
  // 起点城市区域和终点区域共同样式
  .area{
    position: absolute;
    top: 75px;
    width: 736px;
    // min-height: 200px;
    background-color: #F4F4F4;
    border: 1px solid gainsboro;
    // width: 0px;
    display: none;
    z-index: 10;
  }
  .search-area{
    position: absolute;
    top: 75px;
    width: 550px;
    // height: 200px;
    max-height: 300px;
    overflow-y: auto;
    // border: 1px solid gainsboro;
    border-radius: 3px;
    box-shadow: 0 0 10px gainsboro;
    .result-city{
      height: 32px;
      line-height: 32px;
      margin: 10px 0;
      padding-left: 20px;
      font-size: 14px;
      cursor: pointer;
      .city-tag{
        width: 40px;
        height: 25px;
        line-height: 25px;
        text-align: center;
        background-color: #53A6FF;
        border-radius: 3px;
        padding: 2px 4px;
        color: white;
        font-size: 12px;
      }
      .cityName{
        margin-left: 6px;
      }
    }
    .result-city:hover{
      background-color: #F2F9FF;
    }
  }
  // 搜索结果区域滚动条样式
  .search-area::-webkit-scrollbar{
    width: 3px;     /*高宽分别对应横竖滚动条的尺寸*/
    height: 1px;
  }
  .search-area::-webkit-scrollbar-thumb {/*滚动条里面小方块*/
    border-radius: 10px;
    -webkit-box-shadow: inset 0 0 5px rgba(204,204,204,0.8);
    background: #535353;
  }
  .search-area::-webkit-scrollbar-track {/*滚动条里面轨道*/
    -webkit-box-shadow: inset 0 0 5px rgba(204,204,204,0.8);
    border-radius: 10px;
    background: #EDEDED;
  }
  .area-selector{
    float: left;
    // position: absolute;
    width: 106px;
    height: 100%;
    box-sizing: border-box;
    .tabs{
      padding: 13px 6px;
      .tab-item{
        padding: 6px 10px;
        cursor: pointer;
        font-size: 14px;
      }
    }
    .active{
      background: #0086F6;
      border-radius: 5px;
      font-size: 14px;
      color: #FFFFFF;
    }
  }
  .city-wrraper{
    float: right;
    position: relative;
    // position: absolute;
    // right: 0;
    width: 630px;
    min-height: 200px;
    border-left: 1px solid gainsboro;
    box-sizing: border-box;
    background-color: white;
    z-index: 10;

  }
  @keyframes beformMove {
    0%{
      width: 0;
    }
    100%{
      width: 254px;
    }
  }
</style>
