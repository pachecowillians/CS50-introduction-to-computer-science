-- Select the name from people that worked in movies that had datings greather than 9
select distinct p.name from people as p
inner join directors as d
-- Joinning
on p.id = d.person_id
inner join movies as m
-- Join
on m.id = d.movie_id
inner join ratings as r
-- Join
on r.movie_id = m.id
-- Conditions
where r.rating >= 9.0