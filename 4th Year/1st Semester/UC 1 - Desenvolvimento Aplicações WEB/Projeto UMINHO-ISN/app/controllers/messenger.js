const Messenger = require('../models/chatroom');
const mongoose = require('mongoose');

module.exports.getChatBox = (username) => {

    return Messenger.aggregate([
        { $match: { participants: username }},
        { $unwind: { path: "$messages", preserveNullAndEmptyArrays: true }},
        { $sort: { "messages.date": -1 } },
        { $addFields: { by: "$messages.by" }},
        {
            $group: {
                _id: "$_id",
                name: { "$first": "$name"},
                by: {
                    "$first": "$by"
                },
                date: {
                    $first: "$messages.date"
                }
            }
        }
    ]);
};

module.exports.newRoom = (chatroom) => {
    let newRoom = new Messenger(chatroom);

    return newRoom.save();

};

module.exports.getMessages = (chatId) => {
    return Messenger.findById(chatId);
};

module.exports.getMessages1 = (idChat) => {
    return Messenger.aggregate([
        { $match: { '_id': mongoose.Types.ObjectId(idChat) }}, 
        { $unwind: { path: '$messages', preserveNullAndEmptyArrays: true }}, 
        {
          $lookup: {
            from: 'users', 
            localField: 'messages.by', 
            foreignField: 'username', 
            as: 'messages.InfoUser'
          }
        }, {
          $group: {
            _id: '$_id', 
            'Messages': {
              $push: '$messages'
            }
          }
        }, {
          $project: {
            'Messages.by': 1, 
            'Messages.text': 1, 
            'Messages.InfoUser.fullName': 1, 
            'Messages.InfoUser.photo': 1
          }
        }
    ]);
};

module.exports.sendMessage = ({chatId, text, date, by}) => {
    return Messenger.findByIdAndUpdate( chatId, {
        $push: {
            messages: {
                by: by,
                text: text,
                date: date
            }
        }
    });

};

module.exports.removeFromConversation = ({chatId, username}) => {
    return Messenger.findOneAndUpdate( { _id: chatId }, {
        $pull: {
            participants: username
        }
    })
};