<template>
  <div class="area-selector">
              <div class="tabs" ref="leftTabsRef" @click.stop>
                <div class="tab-item active" @click="switchCityArea">
                  国内
                </div>
                <div class="tab-item" @click="switchCityArea">
                  国际及中国港澳台
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
</template>

<script>
export default {
    data(){
        return{
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
    }
}
</script>

<style>

</style>