-- Calcula el promedio de las calificaciones de las películas lanzadas en 2012
SELECT AVG(rating)
-- Filtra las calificaciones de las películas cuyo ID está en la lista de películas de 2012
FROM ratings
WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

