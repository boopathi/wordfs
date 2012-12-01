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
    wordament = require("wordament").Wordament;

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

var start_time = "2:00";
var minute = parseInt(start_time.split(":")[0])*60;
var second = parseInt(start_time.split(":")[1]);
var previous_correct_word_time = (minute+second);
var current_time = previous_correct_word_time;
var score = 0;
var game_status = 0;

io.sockets.on('connection', function(socket) {
    console.log("Connected boopathi" + socket);
    var game = new wordament();
    socket.emit('question', { question: game.question.split(',').splice(0,4) });
	socket.emit('timer', { start : start_time.split(":")});
	game_status=1;
	var timer = setInterval(function(){current_time=current_time-1;if(current_time==0){clearInterval(timer);game_status=0;}},1000);
    socket.on('answer', function(answer) {
		if(game_status){
		if(game.search(answer)){
			score= (score+Math.floor(1000/(previous_correct_word_time-current_time)))*answer.length;
			previous_correct_word_time=current_time;
		}
	}
        socket.emit('result', {
            correct: game.search(answer),
			score : score
        });
    });
});

app.get('/', function(req,res) {
    res.render('index');
});

