-- Selecciona el título de las películas lanzadas en 2018 o después
SELECT title
-- Filtra las películas cuyo año es mayor o igual a 2018
FROM movies
WHERE year >= 2018
-- Ordena los resultados alfabéticamente por título
ORDER BY title;

