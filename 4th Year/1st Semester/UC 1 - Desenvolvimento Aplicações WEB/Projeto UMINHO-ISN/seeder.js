const fs = require('fs');
const mongoose = require('mongoose');
const colores = require('colors');
const dotenv = require('dotenv').config();


// load models
const Group = require('./app/models/group');


// Connection to Database
mongoose.connect(`${process.env.MONGO_LOCAL}`, {
        useNewUrlParser: true,
        useUnifiedTopology: true
    })
    .then(() => console.log("Connection to MongoDB successfully established.".cyan.bold))
    .catch(() => onsole.log("Couldn't connect to MongoDB".red));

// read JSON files
const groups = JSON.parse(
    fs.readFileSync(`${__dirname}/_data/groups.json`, 'utf-8')
);



// import into DB
const importData = async () => {
    try {
        await Group.create(groups);

        console.log('Data Imported'.green.inverse);
        process.exit();
    } catch (err) {
        console.error(err);
    }
};

// delete data
const deleteData = async () => {
    try {
        await Group.deleteMany();
        console.log('Data destroyed'.red.inverse);
        process.exit();
    } catch (err) {
        console.error(err);
    }
};

if (process.argv[2] == '-i') {
    importData();
} else if (process.argv[2] == '-d') {
    deleteData();
}