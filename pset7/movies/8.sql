-- Select the name of peoples that worked on Toy Story
select p.name from movies as m
inner join stars as s
-- Joinning
on s.movie_id = m.id
inner join people as p
on p.id = s.person_id
-- Conditions
where m.title = 'Toy Story'