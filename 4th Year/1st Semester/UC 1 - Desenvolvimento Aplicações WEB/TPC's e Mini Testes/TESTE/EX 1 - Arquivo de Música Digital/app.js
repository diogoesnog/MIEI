const createError = require("http-errors")
const express = require("express")
const path = require("path")
const logger = require("morgan")
const mongoose = require("mongoose")

/* Mongoose connection */
mongoose.connect("mongodb://localhost:27017/obras", { useNewUrlParser: true, useUnifiedTopology: true })
    .then(() => console.log("MongoDB pronto: " + mongoose.connection.readyState))
    .catch(() => console.log("Impossível connectar ao MongoDB."))

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

let API_Router = require("./routes/api")

app.use("/api", API_Router)

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