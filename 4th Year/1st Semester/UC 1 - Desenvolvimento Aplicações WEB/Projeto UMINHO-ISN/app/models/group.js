/**
 * Group Schema
 * Contributors: Diogo Nogueira, Mateus Silva, Miguel R. Solans
 */


const mongoose = require('mongoose');

const groupSchema = new mongoose.Schema({
    _id: {
        type: mongoose.Types.ObjectId,
        auto: true
    },
    name: {
        type: String,
        required: true
    },
    description: {
        type: String,
        default: "No description provided upon creation..."
    },
    creator: {
        type: String,
        required: true
    },
    audience: {
        type: Boolean
    },
    members: { // gardar aqui ou no user ou em ambos?
        type: [String]
    }
});


const Group = mongoose.model('groups', groupSchema, 'groups');

module.exports = Group;