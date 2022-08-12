const S4 = function() {
    return (((1 + Math.random()) * 0x10000) | 0).toString(16).substring(1);
  };
  export function guid() {
    return (S4() + S4() +'-' +S4() +'-' +S4() +'-' +S4() +'-' +S4() +S4() +S4()
    );
  }
  export function timeChange(date) {
    var year = date.getFullYear(); 
    var month = date.getMonth(); 
    var data = date.getDate(); 
    var hours = date.getHours(); 
    var minute = date.getMinutes(); 
    var second = date.getSeconds(); 
    var time =
      year +
      "-" +
      checkTime(month + 1) +
      "-" +
      checkTime(data) +
      checkTime(hours) +
      ":" +
      checkTime(minute) +
      ":" +
      checkTime(second);
    return time;
  }
  function checkTime(time){
    if(time>=0 && time <=9){
      return "0"+ time;
    }
    return time;
  }