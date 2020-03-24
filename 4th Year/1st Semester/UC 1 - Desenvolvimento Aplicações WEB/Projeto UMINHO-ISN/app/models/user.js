/**
 * User Schema
 * Contributors: Diogo Nogueira, Mateus Silva, Miguel R. Solans
 */

const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');
const crypto = require('crypto');

//const widgetSchema = new mongoose.Schema({
//  title: String,
//  content: String,
//  display: Boolean
//});

// const groupSchema = new mongoose.Schema({
//   groupId: mongoose.Types.ObjectId,
//   groupName: String,
//   groupSigla: String
// });

const userSchema = new mongoose.Schema({
  _id: {
    type: mongoose.Types.ObjectId,
    auto: true
  },
  username: {
    type: String,
    required: true
  },
  fullName: {
    type: String,
    required: true
  },
  password: {
    type: String,
    required: true,
    minlength: 8,
    select: false
  },
  email: {
    type: String,
    required: true,
    unique: true,
    match: /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/
  },
  bio: {
    type: String,
    default: ""
  },
  courses: {
    type: Array
  },
  groups: [String],
  likes: {
    type: [String]
  },
  createdAt: {
    type: Date,
    default: Date.now
  },
  photo: {
    type: String,
    default: '/images/UserDefault.png'
  },
  birthdate: {
    type: Date
  },
  resetPasswordToken: String,
  resetPasswordExpire: Date,
  instagram: {
    type: String,
    default: ""
  },
  twitter: {
    type: String,
    default: ""
  },
  linkedIn: {
    type: String,
    default: ""
  },
  github: {
    type: String,
    default: ""
  },
  facebook: {
    type: String,
    default: ""
  }
});

// Encrypt password using bccrypt
userSchema.pre('save', async function (next) {
  if (!this.isModified('password')) {
    next();
  }

  const salt = await bcrypt.genSalt(10);
  this.password = await bcrypt.hash(this.password, salt);
});

// gerar e hash do token de reset da password
userSchema.methods.getResetPasswordToken = function () {
  // gerar token --- sequencia aleatoria de bytes
  const resetToken = crypto.randomBytes(20).toString('hex');

  // hash token e colocar no campo do user
  this.resetPasswordToken = crypto
    .createHash('sha256')
    .update(resetToken)
    .digest('hex');

  // definir o expire ---- 20 minutos
  this.resetPasswordExpire = Date.now() + 10 * 60 * 1000;

  return resetToken;
};

const User = mongoose.model('users', userSchema, 'users');

module.exports = User;