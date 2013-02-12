//Cached elements
var DOM = Backbone.Model.extend({});

//The basic element
var Cell = Backbone.Model.extend({});

//Board is a collection of cells
var Board = Backbone.Collection.extend({
    model: Cell,
});

var CellView = Backbone.View.extend({
    template: _.template($('#cellview').html());
});

var BoardView = Backbone.View.extend({
    el: '#question',
    initialize: function() {
	this.collection.fetch({
	    success: this.render,
	    error: this.error,
	});
    },
    reset: function() {
	this.$el.empty();
    },
    error: function() {
	this.reset();
	this.$el.html("Server Error. Could not retrieve data");
    },
    render: function() {
	var that = this;
	this.collection.each(function(i) {
	    that.$el.append(that.template(i.toJSON()));
	});
    },
});