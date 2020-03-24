module.exports.timeMinutes = (d1, d2) => {
    let diff = Math.abs(d1 - d2);
    return Math.floor((diff / 1000) / 60);
};

module.exports.timeHours = (d1, d2) => {
    return parseInt(Math.abs(d1 - d2) / (60 * 60 * 1000));
};

module.exports.timeDays = (d1, d2) => {
    let t2 = d2.getTime();
    let t1 = d1.getTime();

    return parseInt((t2 - t1) / (24 * 3600 * 1000));
};

module.exports.timeWeeks = (d1, d2) => {
    let t2 = d2.getTime();
    let t1 = d1.getTime();

    return parseInt((t2 - t1) / (24 * 3600 * 1000 * 7));
};

module.exports.timeMonth = (d1, d2) => {
    let d1Y = d1.getFullYear();
    let d2Y = d2.getFullYear();
    let d1M = d1.getMonth();
    let d2M = d2.getMonth();

    return (d2M + 12 * d2Y) - (d1M + 12 * d1Y);
};

module.exports.timeYears = (d1, d2) => {
    return d2.getFullYear() - d1.getFullYear();
};