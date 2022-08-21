SELECT name FROM people
JOIN stars ON people.id = person_id
JOIN movies ON movie_id = movies.id
WHERE movies.id IN (SELECT movies.id FROM movies
JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE name = "Kevin Bacon" and birth = 1958) AND
name != "Kevin Bacon";