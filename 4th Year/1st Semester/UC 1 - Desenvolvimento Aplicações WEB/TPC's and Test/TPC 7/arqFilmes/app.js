const createError = require("http-errors")
const express = require("express")
const path = require("path")
const logger = require("morgan")
const mongoose = require("mongoose")

mongoose.connect("mongodb://localhost:27017/movies", {useNewUrlParser: true, useUnifiedTopology: true})
    .then(() => console.log("Conexão com a Base de Dados concluída com sucesso."))
    .catch(() => console.log("Não foi possível conectar com a Base de Dados."))

var movieRoute = require("./routes/filme")
var app = express()

/* View engine setup */
app.set("views", path.join(__dirname, "views"))
app.set("view engine", "pug")

app.use(logger("dev"))
app.use(express.json())
app.use(express.urlencoded({ extended: false }))
app.use(express.static(path.join(__dirname, "public")))

app.use("/filmes", movieRoute)

/* Catch 404 and forward to error handler */
app.use(function (req, res, next) {
    next(createError(404))
})

/* Error handler */
app.use(function (err, req, res, next) {
    // set locals, only providing error in development
    res.locals.message = err.message
    res.locals.error = req.app.get("env") === "development" ? err : {}

    // render the error page
    res.status(err.status || 500)
    res.render("paginaErro")
})

/* Module export */
module.exports = app;