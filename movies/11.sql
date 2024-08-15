-- Selecciona el título de las películas
SELECT m.title
-- Combina las tablas de películas y estrellas usando los IDs correspondientes
FROM movies m
JOIN stars s ON m.id = s.movie_id
-- Combina la tabla de personas usando el ID de la persona
JOIN people p ON s.person_id = p.id
-- Combina la tabla de calificaciones usando el ID de la película
JOIN ratings r ON m.id = r.movie_id
-- Filtra las películas en las que participó Chadwick Boseman
WHERE p.name = 'Chadwick Boseman'
-- Ordena los resultados por calificación descendente
ORDER BY r.rating DESC
-- Limita los resultados a las 5 mejores películas
LIMIT 5;

