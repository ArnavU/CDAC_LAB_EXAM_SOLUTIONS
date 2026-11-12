const express = require('express');
const multer = require('multer');
const cors = require('cors');
const fs = require('fs/promises')

const pool = require('./db/pool')

const app = express();
app.use(cors());
app.use(express.json());
app.use('/movieImages', express.static('MyMovieImages'))
const upload = multer({
    dest: "MyMovieImages"
})

// 1. add new movie
app.post('/movie', upload.single('image'), async (req, res) => {
    const {name, director, year, rating} = req.body;
    const {originalname, path, destination} = req.file;
    fs.rename(path, `${destination}/${originalname}`);
    const sql = 'INSERT INTO movies (movie_name, director, release_year, rating, image) VALUES(?,?,?,?,?);';

    try {
        const data = await pool.query(sql, [name, director, year, rating, originalname]);
        return res.status(201).json({
            status: "success",
            data: data[0]
        })

    } catch(error) {
        return res.status(500).json({
            status: "error"
        })
    }
})

// 2. display movies
app.get('/movies', async (req, res) => {
    const sql = "SELECT * FROM movies";
    try {
        const data = await pool.query(sql);
        return res.status(200).json({
            status: "success", 
            data: data[0]
        })
    } catch(error) {
        return res.status(500).json({
            status: "error"
        })
    }
})

// 3. get movies by name
app.get('/movies/:name', async (req, res) => {
    console.log("Api movies/:name called")
    const {name} = req.params;
    console.log("Data: ", name)
    const sql = 'SELECT * FROM movies WHERE movie_name LIKE "%"?"%";';
    try {
        const data = await pool.query(sql, [name]);
        return res.status(200).json({
            status: "success",
            data: data[0]
        })
    } catch(error) {
        return res.status(500).json({
            status: "error",
            data: error.message
        })
    }
})

// 4. update movie details -> {name, direcor, year, rating}
app.put('/movie', async (req, res) => {
    console.log("Movies updating")
    const {id, name, director, year, rating} = req.body;
    console.log("Body: ", req.body)
    const sql = "UPDATE movies SET movie_name=?, director=?, release_year=?, rating=? WHERE movie_id=?;";
    try {
        const data = await pool.query(sql, [name, director, year, rating, id]);
        console.log("data: ", data[0])
        return res.status(200).json({
            status: "success", 
            data: data[0]
        })
    } catch(error) {
        console.log("error: ", error)
        return res.status(500).json({
            status: "error",
            data: error.message
        })
    }
})

// 5. delete movie using id
app.delete('/movie/:id', async (req, res) => {
    const {id} = req.params;
    const sql = "DELETE FROM movies WHERE movie_id=?;";
    try {
        const data = await pool.query(sql, [id]);
        return res.status(201).json({
            status: "success",
            data: data[0]
        })
    } catch(error) {
       console.log("error: ", error)
        return res.status(500).json({
            status: "error",
            data: error.message
        }) 
    }
})



app.listen(4000, "localhost", () => {
    console.log("Server is up and running on portno.: 4000");
})