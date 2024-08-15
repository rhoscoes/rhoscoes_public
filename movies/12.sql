-- Selecciona el título de las películas
SELECT m.title
-- Combina las tablas de películas y estrellas usando los IDs correspondientes
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
-- Combina la tabla de personas usando el ID de la primera persona
JOIN people p1 ON s1.person_id = p1.id
-- Combina la tabla de estrellas nuevamente usando el ID de la película
JOIN stars s2 ON m.id = s2.movie_id
-- Combina la tabla de personas nuevamente usando el ID de la segunda persona
JOIN people p2 ON s2.person_id = p2.id
-- Filtra las películas en las que participaron Johnny Depp y Helena Bonham Carter
WHERE p1.name = 'Johnny Depp' AND p2.name = 'Helena Bonham Carter';

