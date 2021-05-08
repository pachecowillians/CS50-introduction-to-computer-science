-- The top 5 films of chadwick ordered by rate
select m.title from movies as m
inner join ratings as r
-- Join
on r.movie_id = m.id
inner join stars as s
-- Join
on s.movie_id = m.id
inner join people as p
-- Join
on p.id = s.person_id
-- Conditions
where p.name = 'Chadwick Boseman'
order by r.rating desc limit 5