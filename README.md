# Wordament module

This is the C++ module for wordament.
This is in a separate branch - so that packaging for npm is possible in a simple manner.

# Installation

+ Install `node-gyp` as sudo user. `sudo npm install -g node-gyp`
+ Compile the binary. `node-gyp configure && node-gyp build`.

# Usage

```javascript
var wordament = require('./build/Release/wordament.node').Wordament; //require("wordament").Wordament; //if using via npm
var x = new wordament();
console.log(x.question); // <String>
console.log(x.solution); // <Array>
console.log(x.answer); // <Function>

if(x.answer("wordament"))
    console.log("Yay");
else
    console.log("Boo");
```




