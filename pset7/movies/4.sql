-- count the movies with rate 10
-- For it, join the table movies and ratings
select count(*) as movieNumber from movies as m
inner join ratings as r
-- Joinning
on m.id = r.movie_id
-- Conditions
where r.rating = 10.0