```sql
-- Question 1)
SELECT
    book_name
    , publish_date
FROM
    books
WHERE
    YEAR(publish_date) > 2000
ORDER BY
    publish_date ASC;

-- Question 2)
SELECT
    UPPER(book_name)
    , LENGTH(REPLACE(book_name, " ", "")) AS length_without_spaces
FROM
    books;

-- Question 3)
SELECT
    book_name
    , price
FROM
    books
ORDER BY
    price DESC;

-- Question 4)
SELECT
    category
    , COUNT(book_id)
FROM
    books
GROUP BY
    category
ORDER BY
    COUNT(book_id) DESC;

-- Question 5)
SELECT
    category
    , COUNT(book_id) AS count
    , AVG(price) AS avgPrice
    , MAX(price) AS maxPrice
FROM
    books
GROUP BY
    category
ORDER BY
    AVG(price) DESC;

-- Question 6)
SELECT
    category
    , COUNT(book_id)
FROM
    books
GROUP BY
    category
HAVING
    COUNT(book_id) >= 2
ORDER BY
    COUNT(book_id) DESC;

-- Question 7)
SELECT
    author_name
    , COUNT(b.book_id) AS countOfBooks
FROM
    authors AS a
LEFT JOIN
    books AS b
ON
    a.author_id = b.author_id
GROUP BY
    a.author_id, a.author_name;

-- Question 8)
SELECT
    *
FROM
    books AS b
WHERE
    b.price > (SELECT AVG(price) FROM books);

-- Question 9)
SELECT
    *
FROM
    books AS b
WHERE
    b.price < (SELECT MAX(price) FROM books)
ORDER BY
    b.price DESC;

-- Question 10)
SELECT
    m.member_name
    , bks.book_name
    , b.borrow_date
    , b.status
FROM
    borrowings AS b
INNER JOIN
    members AS m
ON
    b.member_id = m.member_id
INNER JOIN
    books AS bks
ON
    b.book_id = bks.book_id
INNER JOIN
    authors AS a
ON
    a.author_id = bks.author_id
WHERE
    b.return_date IS NULL;

-- Question 11)
SELECT
    a.author_name
    , AVG(price)
FROM
    authors AS a
INNER JOIN
    books AS b
ON
    a.author_id = b.author_id
GROUP BY
    b.author_id, a.author_name
HAVING
    AVG(price) > 500
ORDER BY
    AVG(price) DESC;

-- Question 12)
SELECT
    a.author_name
    , COUNT(b.book_id)
    , AVG(price)
FROM
    authors AS a
INNER JOIN
    books AS b
ON
    a.author_id = b.author_id
GROUP BY
    b.author_id, a.author_name
HAVING
    AVG(price) > (SELECT AVG(b1.price) FROM books AS b1)
ORDER BY
    AVG(price) DESC;

-- stored procedure
DROP PROCEDURE IF EXISTS CompareAuthor;
DELIMITER $$
CREATE PROCEDURE CompareAuthor(p_authorID INT)
BEGIN
    DECLARE v_author_name VARCHAR(40);
    DECLARE v_total_books_per_author INT;
    DECLARE v_avg_price_per_author DOUBLE;
    DECLARE v_avg_all_books DOUBLE;
    DECLARE msg VARCHAR(40);
    SELECT
        Author_name
        , COUNT(book_id)
        , AVG(price)
        , (SELECT AVG(b1.price) FROM books AS b1)
    INTO
        V_author_name
        , v_total_books_per_author
        , v_avg_price_per_author
        , v_avg_all_books
    FROM
       	Authors AS  a
    INNER JOIN
        Books AS  b
    ON
        a.author_id = b.author_id
    WHERE
        a.author_id = p_authorID
    GROUP BY
        a.author_id, a.author_name;

    SELECT v_author_name, v_total_books_per_author, v_avg_price_per_author, v_avg_all_books;

    IF v_avg_price_per_author > v_avg_all_books THEN
    	SET msg = 'Above_Average';
    ELSE
        SET msg = 'Below_Average';
    END IF;

    SELECT msg as msg;

END $$
DELIMITER ;
CALL CompareAuthor(102);
```
