-- Selecciona el nombre de las personas
SELECT p.name
-- Combina las tablas de personas y estrellas usando los IDs correspondientes
FROM people p
JOIN stars s ON p.id = s.person_id
-- Combina la tabla de películas usando el ID de la película
JOIN movies m ON s.movie_id = m.id
-- Filtra las personas que participaron en películas lanzadas en 2004
WHERE m.year = 2004
-- Ordena los resultados por fecha de nacimiento
ORDER BY p.birth;

