var wordament = require("./build/Release/wordament.node");

console.log(wordament.getMatrix());

var solution = wordament.solution();
var ss = "";
for(var i=0;i<solution.length;i++)
    ss = ss + ", "+ solution[i];
console.log(ss);
