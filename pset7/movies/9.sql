-- Using the select inside a select to find people that work on the moviees of 2004
select name from people
where id in
-- Subselect
(select distinct s.person_id from stars as s
inner join movies as m
-- Joinning
on s.movie_id = m.id
-- Conditions
where m.year = 2004)
order by birth