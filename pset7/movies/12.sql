-- Selecting the movies that was starred by Jonny Depp and Helena Carter
select title from movies
where id in
-- Subselect
-- Search jonny dep
(select distinct m.id from movies as m
inner join stars as s
-- Join
on s.movie_id = m.id
inner join people as p
-- Join
on s.person_id = p.id
-- Conditions
where p.name = 'Johnny Depp')
and id in
-- Search helena
(select distinct m.id from movies as m
inner join stars as s
-- Join
on s.movie_id = m.id
inner join people as p
-- Join
on s.person_id = p.id
-- Conditions
where p.name = 'Helena Bonham Carter')