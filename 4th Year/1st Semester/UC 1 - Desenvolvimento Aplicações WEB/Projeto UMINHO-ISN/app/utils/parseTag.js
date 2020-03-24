
module.exports.parse = (data, field) => {

    let dataJson = JSON.parse(data);

    let dataArr = [];

    dataJson.forEach(member => {
        dataArr.push(member[field])
    });

    return dataArr;
};