var mongoose = require("mongoose");
var Schema = mongoose.Schema;

// Schema de um Filme.
var filmeSchema = new Schema({
        _id: mongoose.Schema.Types.ObjectId,
        title: { 
            type: String, 
            required: true 
        },
        year: { 
            type: Number, 
            required: true 
        },
        cast: [String],
        genres: [String]
});

module.exports = mongoose.model("movies", filmeSchema, "movies");