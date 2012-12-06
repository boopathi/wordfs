# Wordfs module [![Build Status](https://secure.travis-ci.org/boopathi/wordfs.png?branch=pack-for-npm)](https://travis-ci.org/boopathi/wordfs)

This is the C++ module for wordfs.
This is in a separate branch - so that packaging for npm is possible in a simple manner.

# Installation

+ Install `node-gyp` as sudo user. `sudo npm install -g node-gyp`
+ Compile the binary. `node-gyp configure && node-gyp build`.

# Usage

```javascript
var wordfs = require('./build/Release/wordfs.node').Wordfs; //require("wordfs").Wordfs; //if using via npm
var x = new wordfs();
console.log(x.question); // <String>
console.log(x.solution); // <Array>
console.log(x.answer); // <Function>

if(x.answer("wordfs"))
    console.log("Yay");
else
    console.log("Boo");
```




