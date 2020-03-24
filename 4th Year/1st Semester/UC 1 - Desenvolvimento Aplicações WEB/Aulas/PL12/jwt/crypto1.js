var bcrypt = require('bcryptjs');
var salt = bcrypt.genSaltSync(6);
var hash = bcrypt.hashSync("222", salt);

console.log(bcrypt.compareSync("222", hash))