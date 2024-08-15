-- Selecciona el nombre de las personas
SELECT p.name
-- Combina las tablas de personas, estrellas y películas usando los IDs correspondientes
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
-- Filtra las personas que participaron en la película 'Toy Story'
WHERE m.title = 'Toy Story';
