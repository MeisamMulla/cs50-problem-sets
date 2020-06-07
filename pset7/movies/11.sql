SELECT
	movies.title
FROM
	movies
	JOIN stars ON stars.movie_id = movies.id
	JOIN people ON people.id = stars.person_id
	JOIN ratings ON ratings.movie_id = movies.id
WHERE
	people.name = "Chadwick Boseman"
GROUP BY
	movies.title
ORDER BY
	ratings.rating desc
LIMIT 5