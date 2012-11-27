/*
 *
 *
 * @author Boopathi Rajaa <http://boopathi.in/>
 * @description app main-file
 * @copyright Copyright (c) 2012 Boopathi Rajaa <http://boopathi.in/>
 * @license <http://www.opensource.org/licenses/mit-license.html>
 *
 *
 */

//boiler-plates
var express = require('express'),
    app = express(),
    connect = require('connect'),
    params = require('express-params'),
    server = require('http').createServer(app).listen(process.env.PORT || 8080),
    ejs = require('ejs'),
    socketio = require('socketio'),
    _validate = require('validator'),
    wordament = require("./build/Release/wordament.node");

app.configure( function () {
    app.use(connect.compress());
    app.use(express.bodyParser());
    app.use(express.cookieParser());
    app.use(express.session({secret: "WORDAMENT :P" }));
    app.use("/static", express.static(__dirname + "/static"));
    app.set("view engine", 'ejs');
    app.param(function(name, fn){
        if (fn instanceof RegExp) {
            return function(req, res, next, val){
                var captures;
                if (captures = fn.exec(String(val))) {
                    req.params[name] = captures;
                    next();
                } else next('route');
            }
        }
    }); 
});

app.get('/', function(req,res) {
    res.render('index', {
        question: wordament.getMatrix();
    });
})

var solution = wordament.solution();
var ss = "";
for(var i=0;i<solution.length;i++)
    ss = ss + ", "+ solution[i];
console.log(ss);


