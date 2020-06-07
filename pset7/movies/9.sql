SELECT distinct
	people.name
FROM
	people
	JOIN stars ON stars.person_id = people.id
	JOIN movies ON movies.id = stars.movie_id
WHERE
	movies.year = 2004
order by people.birth asc