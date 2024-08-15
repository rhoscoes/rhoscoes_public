-- Selecciona el título y el año de las películas de Harry Potter
SELECT title, year
-- Filtra las películas cuyo título comienza con 'Harry Potter'
FROM movies
WHERE title LIKE '%Harry Potter%' or title LIKE '%Fantastic Beasts%'
-- Ordena los resultados por año de lanzamiento
ORDER BY year;
