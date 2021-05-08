-- Find the movies from 2018 to now and sort by name in alphabetical order
select title from movies
-- Conditions
where year >= 2018
order by title