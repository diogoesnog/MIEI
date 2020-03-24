const createError = require("http-errors")
const express = require("express")
const path = require("path")
const logger = require("morgan")

let app = express()

/* View engine setup */
app.set("views", path.join(__dirname, "views"))
app.set("view engine", "pug")

/* Pretty JSON setup */
app.set("json spaces", 4)

app.use(logger("dev"))
app.use(express.json())
app.use(express.urlencoded({ extended: false }))
app.use(express.static(path.join(__dirname, "public")))

var indexRouter = require('./routes/index');
var entRouter = require('./routes/entidades');

app.use('/', indexRouter);
app.use('/entidades', entRouter);

/* Catch 404 and forward to error handler */
app.use((_req, _res, next) => {
    next(createError(404))
})

/* Error handler */
app.use((err, req, res, _next) => {
    // set locals, only providing error in development
    res.locals.message = err.message
    res.locals.error = req.app.get("env") === "development" ? err : {}

    // render the error page
    res.status(err.status || 500)
})

module.exports = app