SELECT
	people.name
FROM
	people
	JOIN stars ON stars.movie_id = movies.id
	JOIN movies ON movies.id = stars.movie_id
WHERE
	movies.title LIKE "Toy Story"