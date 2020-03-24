# **Resolução PL07 - Bases de Dados de Grafos (Neo4J)**



Criando-se um *Graph* no próprio Neo4J, consegue-se depois criar uma conexão e com isso fazer o restantes dos exercícios. Feito o *import* da *database movies*, e executando o código da página 2, obtém-se o segguinte grafo.



![image-20191113101129226](C:\Users\diogo\AppData\Roaming\Typora\typora-user-images\image-20191113101129226.png) 



### Resolução dos Exercícios



####  1.	Return a list of all the characters in the movie The Matrix. 

```sql
MATCH (name)-[r:ACTED_IN]->(filme:Movie)
WHERE filme.title = 'The Matrix'
RETURN r.roles
```



####  2.	Find all of the movies that Tom Hanks acted in.

```sql
MATCH (ator:Person)-[:ACTED_IN]->(filme:Movie)
WHERE ator.name = 'Tom Hanks'
RETURN filme.title
```



####  3.	Limit that to movies which were released after 2000? Note that there is a released property on Movie. 

```sql
MATCH (ator:Person)-[:ACTED_IN]->(filme:Movie)
WHERE ator.name = 'Tom Hanks' AND filme.released>2000
RETURN filme.title
```



####  4.  Find directors acting in their movies.

```sql
Alternativa 1

MATCH (diretor:Person)-[:DIRECTED]->(filme:Movie)
WHERE (diretor)-[:ACTED_IN]->(filme)
RETURN diretor.name

Alternativa 2

MATCH (diretor:Person)-[:DIRECTED]->(filme:Movie)<-[:ACTED_IN]-(diretor)
RETURN diretor.name
```



####  5.	Find all movies in which Keanu Reeves played the role Neo.

```sql
MATCH (ator:Person)-[r:ACTED_IN]->(filme:Movie)
WHERE (ator.name = 'Keanu Reeves') AND ('Neo' IN r.roles)
RETURN filme.title
```



####  6.	Return the names of all the directors each actor has worked with. 

```sql
MATCH (diretor:Person)-[:DIRECTED]->(filme:Movie)<-[:ACTED_IN]-(ator:Person)
RETURN ator.name AS Ator, collect(DISTINCT diretor.name) AS Diretor
```



####  7.	Return the count of movies in which each actor has acted. 

```sql
MATCH (ator:Person)-[:ACTED_IN]->(filme:Movie)
RETURN ator.name AS Ator, count(filme) AS NFilmes
```



####  8.	Return the count of movies in which an actor and director have jointly worked. 

```sql
MATCH (diretor:Person)-[:DIRECTED]->(filme:Movie)<-[:ACTED_IN]-(ator:Person)
RETURN ator.name AS Ator, diretor.name AS Diretor, count(filme) AS NFilmes
```



####  9.	Write a query that will display the five (5) busiest actors, i.e. the ones who have been in the most movies. 

```sql
MATCH (diretor:Person)-[:DIRECTED]->(filme:Movie)<-[:ACTED_IN]-(ator:Person)
RETURN ator.name AS Ator, count(filme) AS NFilmes
ORDER BY NFilmes DESC LIMIT 5
```





