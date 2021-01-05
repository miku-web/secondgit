// pages/component/Star/star.js
Component({
  /**
   * 组件的属性列表
   */
  properties: {
      rate:{
        type:Number,
        value:'',
        observer(){
          this.changeRate();
        }
      }
  },

  /**
   * 组件的初始数据
   */
  data: {

  },

  /**
   * 组件的方法列表
   */
  methods: {
    // var obj = this;
    changeRate:function(){//调用changeRate方法
      var light = [];
      var half = [];
      var gray = [];

      var rate = this.properties.rate;
      var lightNumber = parseInt(rate/2);
      for(var i = 0;i<lightNumber;i++)light.push(i);

      var halfNumber = rate%2>0?1:0;
      for(var i=0;i<halfNumber;i++)half.push(i);

      var grayNumber = 5-lightNumber-halfNumber;
      for(var i=0;i<grayNumber;i++)gray.push(i);

    this.setData({
      rate:this.properties.rate,
      light:light,
      half:half,
      gray:gray
    });
}

  }
})
