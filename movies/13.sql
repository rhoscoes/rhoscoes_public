-- Selecciona los nombres de las personas
SELECT DISTINCT p.name
-- Combina las tablas de personas y estrellas usando los IDs correspondientes
FROM people p
JOIN stars s ON p.id = s.person_id
-- Combina la tabla de películas usando el ID de la película
JOIN movies m ON s.movie_id = m.id
-- Filtra las personas que participaron en películas en las que Kevin Bacon también actuó
WHERE m.id IN (
    -- Selecciona las IDs de las películas en las que Kevin Bacon actuó
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        -- Selecciona el ID de Kevin Bacon
        SELECT id
        FROM people
        WHERE name = 'Kevin Bacon' AND birth = 1958
    )
) AND p.name != 'Kevin Bacon';

