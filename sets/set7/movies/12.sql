SELECT title FROM movies
JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE name = "Johnny Depp"
INTERSECT
SELECT title FROM movies
JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE name = "Helena Bonham Carter";