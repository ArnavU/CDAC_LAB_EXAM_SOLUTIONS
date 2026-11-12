CREATE DATABASE IF NOT EXISTS movie_db;

USE movie_db;

CREATE TABLE IF NOT EXISTS movies (
    movie_id INT PRIMARY KEY AUTO_INCREMENT,
    movie_name VARCHAR(100),
    director VARCHAR(100),
    release_year INT,
    rating DECIMAL(2,1),
    image VARCHAR(255)
);
