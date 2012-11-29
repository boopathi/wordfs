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
    io = require('socket.io').listen(server),
    _validate = require('validator'),
    wordament = require("./build/Release/wordament.node").Wordament;

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

io.sockets.on('connection', function(socket) {
    console.log("Connected boopathi" + socket);
    var game = new wordament();
    socket.emit('question', { question: game.question.split(',').splice(0,4) });
    socket.on('answer', function(answer) {
        socket.emit('result', {
            correct: game.search(answer),
            answer: answer,
        });
    });
});

app.get('/', function(req,res) {
    res.render('index');
});

