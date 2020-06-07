SELECT
	title,
	ratings.rating
FROM
	movies
	JOIN ratings ON ratings.movie_id = movies.id
WHERE
	movies.year = 2010
ORDER BY
	ratings.rating DESC,
	title ASC