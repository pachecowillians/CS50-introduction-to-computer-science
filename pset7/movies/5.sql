-- select all the films that begins with Harry Potter
select title, year from movies
-- Conditions
where title like 'Harry Potter%'
order by year