-- Join the ratings and movies tables to find the title and rating of the movies of 2010
select m.title, r.rating from movies as m
inner join ratings as r
-- Joinning
on m.id = r.movie_id
-- Conditions
where m.year = 2010
order by r.rating desc, m.title asc