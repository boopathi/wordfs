
$(function() {
(function(d){d.each(["backgroundColor","borderBottomColor","borderLeftColor","borderRightColor","borderTopColor","color","outlineColor"],function(f,e){d.fx.step[e]=function(g){if(!g.colorInit){g.start=c(g.elem,e);g.end=b(g.end);g.colorInit=true}g.elem.style[e]="rgb("+[Math.max(Math.min(parseInt((g.pos*(g.end[0]-g.start[0]))+g.start[0]),255),0),Math.max(Math.min(parseInt((g.pos*(g.end[1]-g.start[1]))+g.start[1]),255),0),Math.max(Math.min(parseInt((g.pos*(g.end[2]-g.start[2]))+g.start[2]),255),0)].join(",")+")"}});function b(f){var e;if(f&&f.constructor==Array&&f.length==3){return f}if(e=/rgb\(\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*\)/.exec(f)){return[parseInt(e[1]),parseInt(e[2]),parseInt(e[3])]}if(e=/rgb\(\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*\)/.exec(f)){return[parseFloat(e[1])*2.55,parseFloat(e[2])*2.55,parseFloat(e[3])*2.55]}if(e=/#([a-fA-F0-9]{2})([a-fA-F0-9]{2})([a-fA-F0-9]{2})/.exec(f)){return[parseInt(e[1],16),parseInt(e[2],16),parseInt(e[3],16)]}if(e=/#([a-fA-F0-9])([a-fA-F0-9])([a-fA-F0-9])/.exec(f)){return[parseInt(e[1]+e[1],16),parseInt(e[2]+e[2],16),parseInt(e[3]+e[3],16)]}if(e=/rgba\(0, 0, 0, 0\)/.exec(f)){return a.transparent}return a[d.trim(f).toLowerCase()]}function c(g,e){var f;do{f=d.css(g,e);if(f!=""&&f!="transparent"||d.nodeName(g,"body")){break}e="backgroundColor"}while(g=g.parentNode);return b(f)}var a={aqua:[0,255,255],azure:[240,255,255],beige:[245,245,220],black:[0,0,0],blue:[0,0,255],brown:[165,42,42],cyan:[0,255,255],darkblue:[0,0,139],darkcyan:[0,139,139],darkgrey:[169,169,169],darkgreen:[0,100,0],darkkhaki:[189,183,107],darkmagenta:[139,0,139],darkolivegreen:[85,107,47],darkorange:[255,140,0],darkorchid:[153,50,204],darkred:[139,0,0],darksalmon:[233,150,122],darkviolet:[148,0,211],fuchsia:[255,0,255],gold:[255,215,0],green:[0,128,0],indigo:[75,0,130],khaki:[240,230,140],lightblue:[173,216,230],lightcyan:[224,255,255],lightgreen:[144,238,144],lightgrey:[211,211,211],lightpink:[255,182,193],lightyellow:[255,255,224],lime:[0,255,0],magenta:[255,0,255],maroon:[128,0,0],navy:[0,0,128],olive:[128,128,0],orange:[255,165,0],pink:[255,192,203],purple:[128,0,128],violet:[128,0,128],red:[255,0,0],silver:[192,192,192],white:[255,255,255],yellow:[255,255,0],transparent:[255,255,255]}})(jQuery);
});


//Now start using proper design patters
//It means that is done :P

//The board model
var Board = {
    //size = 16
    _collection: {},
    _container: $("#question"),
    _highlight_color: "green",
    _normal_color: "",

    //now defining the model
    //don't care about stuff below, 
    //they are often termed as "INTERNALS" :P
    _string: [],
    cell: function(ch,i,j) { //constructor
        var _ch=ch,_i=i,_j=j;
        Board._string.push(ch.toUpperCase());
        this.ch = function() { return _ch; };
        this.i = function() { return i; };
        this.j = function() { return j; };
        //now the fucking DOM part
        var e = $("<div/>", {
            "class": "qid",
            id: "q"+_i+""+_j,
            text: ch,
        });
        this.e = e;
        Board._container.append(e);
        Board._collection[ch] = this;
    },
    get: function(ch) {
        //convert ASCII to character
        ch = String.fromCharCode(ch).toLowerCase();
        for(var i=0;i<Board._string.length;i++)
            if(Board._string[i].toLowerCase() === ch) return true;
        return false;
    },
    select: function(ch) {
        Board._collection[ch].e.css("background", Board._highlight_color);
    },
    unselectall: function() {
        for(var i in Board._collection)
            Board._collection[i].e.css("background", Board._normal_color);
    },
    unselect: function(ch) {
        Board._collection[ch].e.css("background", Board._normal_color);
    },
};

var Queue = {
    _collection: {},
    exists: function(a) {
        if(typeof Queue._collection[a] === "undefined")
            return false;
        return true;
    },
    append: function(a) {
        return Queue._collection[a] = true;
    },
}

$( function() {

    var socket = io.connect("http://localhost");
    socket.on('question', function(data) {
        for(var i=0;i<4;i++) {
            for(var j=0;j<4;j++) {
                new Board.cell(data.question[i][j],i,j);
                //$("#q"+i+""+j).html(data.question[i][j].toUpperCase());
                //Board.push({ch: data.question[i][j].toLowerCase(),i: i, j: j});
            }
        }
    });
    socket.on('result', function(data) {
        if(data.correct) {
            Queue.append(data.answer);
            $("#queue").append("<li>"+$("#answer").val()+"</li>");
            $("#answer").val("").css("background","#050").stop().animate({
                backgroundColor: "#000"
            },750);
            Board.unselectall();
        }
        else $("#answer").css("background","#500").stop().animate({
            backgroundColor: "#000"
        },250);

    });
    $("#answer").keypress(function(e) {
        $(this).css("background", "#000");
        if(e.which >=32 && e.which <=126 && !e.ctrlKey && !e.altKey) //printable chars
            if(false === Board.get(e.which) )
                return false && e.preventDefault();
            else
                Board.select(String.fromCharCode(e.which).toLowerCase());
    }).keyup(function(e) {
        this.value = this.value.toUpperCase();
        if(e.which == 13){
            if(Queue.exists(this.value.toLowerCase()))
                return;
            else
                socket.emit('answer', this.value.toLowerCase());
        }
    }).focus();
});
