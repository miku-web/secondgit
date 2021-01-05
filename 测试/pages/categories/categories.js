// pages/categories/categories.js
const app=getApp();

Page({

  /**
   * 页面的初始数据
   */
  data: {
    cate_nav_list:[
      {name:"外套",id:"coat"},
      {name:"抱枕",id:"pillow"},
      {name:"睡衣",id:"pajamas"},
      {name:"耳机",id:"headset"},
      {name:"卫衣",id:"fleece"},
      {name:"海报",id:"posters"},
      {name:"挂件",id:"pendant"},
      {name:"手表",id:"watch"},
      {name:"鞋类",id:"shoes"},
      {name:"裙子",id:"skirt"}
    ],
    curIndex:0,
    toView:"new",
    detail:[]
  },

  /**
   * 生命周期函数--监听页面加载
   */
  switchCategory(e){
    // console.log(e.currentTarget.dataset.id);
    const curIndex=e.currentTarget.dataset.index?e.currentTarget.dataset.index:0;
    this.setData({
      toView:e.currentTarget.dataset.id,
      curIndex
    });
  },
  onLoad: function (options) {
    const detail=app.globalData.category;
    this.setData({
      detail
    });
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
  
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
  
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
  
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
  
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
  
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {
  
  }
})