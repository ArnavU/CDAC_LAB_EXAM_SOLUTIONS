const mysql2 = require('mysql2/promise');

const pool = mysql2.createPool({
    host: "localhost",
    user: "root",
    password: "Arnav@123",
    database: "movie_db"
})

module.exports = pool