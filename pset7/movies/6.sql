-- Calc the average rating from movies of 2012
select avg(r.rating) as average from movies as m
-- Joinning
inner join ratings as r
on m.id = r.movie_id
-- Conditions
where m.year = 2012