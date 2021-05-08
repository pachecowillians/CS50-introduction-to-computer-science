-- Select the actors that worked with kevin bacon
select distinct p.name from movies as m
-- Joins
inner join stars as s
-- Join
on s.movie_id = m.id
inner join people as p
-- Join
on s.person_id = p.id
-- Don't consider kevin bacon
-- Conditions
where p.name != 'Kevin Bacon'
and m.id in
-- Select all the movies that kevin bacon worked
(select distinct m.id from movies as m
-- Joins
inner join stars as s
-- Join
on s.movie_id = m.id
inner join people as p
-- Join
on s.person_id = p.id
-- Conditions
where p.name = 'Kevin Bacon'
and p.birth = 1958)