-- Selecciona el nombre de las personas
SELECT p.name
-- Combina las tablas de personas y directores usando los IDs correspondientes
FROM people p
JOIN directors d ON p.id = d.person_id
-- Combina la tabla de calificaciones usando el ID de la película
JOIN ratings r ON d.movie_id = r.movie_id
-- Filtra las personas que dirigieron películas con una calificación de 9.0 o superior
WHERE r.rating >= 9.0;

