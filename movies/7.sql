-- Selecciona el título de la película y su calificación
SELECT m.title, r.rating
-- Combina las tablas de películas y calificaciones usando el ID de la película
FROM movies m
JOIN ratings r ON m.id = r.movie_id
-- Filtra las películas lanzadas en 2010
WHERE m.year = 2010
-- Ordena los resultados por calificación descendente y luego por título
ORDER BY r.rating DESC, m.title;
