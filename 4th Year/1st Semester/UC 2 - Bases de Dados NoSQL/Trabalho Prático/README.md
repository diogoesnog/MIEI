# SAKILA Database Queries

## Lista de Queries a ser testada para cada modelo de Base de Dados.

1. Nome e Sobrenome de todos os Atores existentes.

```sql
SELECT 
	first_name AS FirstName,
    last_name AS LastName
FROM actor
```

```sql
db.getCollection('customers').find(
    {}, 
    {
    	"_id": 0, 
    	"First Name": 1, 
    	"Last Name": 1
    }
)
```

```sql
MATCH (actor:Actor)
RETURN actor.FirstName AS FirstName, actor.LastName AS LastName
```

2. Lista dos Títulos dos Filme e respetivo Número de Atores que dele fazem parte.

```sql
SELECT 
	film.title AS Title, 
	count(*) AS NumberActors
FROM film

INNER JOIN film_actor ON film.film_id = film_actor.film_id

GROUP BY film.title
ORDER BY NumberActors DESC
```

```sql
db.getCollection("films").aggregate(
    [
        { 
            "$project" : { 
                "_id" : 0.0, 
                "Title" : 1.0, 
                "NumberActors" : {"$size" : "$Actors"}
            }
        }
    ]
)
```

```sql
MATCH (actor:Actor)-[:ATUA_EM]->(film:Film)
RETURN film.Title AS Title, count(actor) AS NumberActors
```

3. Lista dos Nomes (Primeiro e Último)  dos Atores que aparecem no Filme de nome "African Egg".

```sql
SELECT 
	first_name AS FirstName,
    last_name AS LastName
FROM actor

INNER JOIN film_actor ON film_actor.actor_id = actor.actor_id
INNER JOIN film ON film.film_id = film_actor.film_id

WHERE film.title = 'AFRICAN EGG';
```

```sql
db.getCollection("films").find(
    {"Title" : "AFRICAN EGG"}, 
    { 
        "_id" : 0,
        "Actors.First Name" : 1, 
        "Actors.Last Name" : 1
    }
)
```

```sql
MATCH (actor:Actor)-[:ATUA_EM]->(film:Film)
WHERE film.Title = "AFRICAN EGG"
RETURN actor.FirstName, actor.LastName
```

4. Lista dos Nomes (Primeiro e Último) e Email dos Clientes originais da Argentina. 

```sql
SELECT 
	customer.first_name AS FirstName, 
    customer.last_name AS LastName, 
    customer.email AS Email
FROM customer

INNER JOIN address ON customer.address_id = address.address_id
INNER JOIN city ON address.city_id = city.city_id
INNER JOIN country ON city.country_id = country.country_id

WHERE country.country = 'Argentina'
```

```sql
db.getCollection("customers").find(
    {"Country" : "Argentina"}, 
    { 
        "First Name" : 1, 
        "Last Name" : 1, 
        "Email" : 1
    }
)
```

```sql
MATCH (customer:Customer)-[:VIVE_EM]->(address:Address)
WHERE address.Country = "Argentina"
RETURN customer.FirstName, customer.LastName, customer.Email
```

Ao fazermos esta querie percebemos que ao colocar no Address logo o Country e a Cidade, simplificamos logo o processo em si, poupando o número de nodos.

5. Lista dos 5 primeiros Géneros/Categorias e sua respetiva Receita Bruta, por ordem descendente.

```sql
SELECT category.name AS Category, SUM(payment.amount) AS TotalVendas
FROM category

INNER JOIN film_category ON category.category_id = film_category.category_id
INNER JOIN film ON film_category.film_id = film.film_id
INNER JOIN inventory ON film.film_id = inventory.film_id
INNER JOIN rental ON inventory.inventory_id = rental.inventory_id
INNER JOIN payment ON rental.rental_id = payment.rental_id

GROUP BY category.name
ORDER BY TotalVendas DESC
FETCH FIRST 5 ROWS ONLY;
```

```sql


```


```sql
MATCH (category:Category)<-[:TIPO]-(film:Film)<-[:CONTEM]-(inventory:Inventory)<-[:PERTENCE_AO]-(rental:Rental)<-[:ALUGADO]-(payment:Payment)

RETURN category.Name AS Category, sum(toFloat(payment.Amount)) AS TotalVendas
ORDER BY TotalVendas DESC 
LIMIT 5
```

6. Lista dos Filmes alugados com mais frequência, por ordem decrescente.

```sql
SELECT film.title AS Title, Rental.NumberRented AS CountRented
FROM film

INNER JOIN (
	SELECT inventory.film_id AS idFilm, count(rental.rental_id) AS NumberRented
	FROM rental

	INNER JOIN inventory ON rental.inventory_id = inventory.inventory_id

	GROUP BY inventory.film_id
) Rental
ON film.film_id = Rental.idFilm

ORDER BY Rental.NumberRented DESC
```

```SQL

```

```sql
MATCH (film:Film)<-[:CONTEM]-(inventory:Inventory)<-[:PERTENCE_AO]-(rental:Rental)

RETURN film.Title AS Title, count(rental.idRental) AS CountRented
ORDER BY CountRented DESC
```

7. Total de cópias em Inventário do filme de nome "Connecticut Tramp".

```sql
SELECT film.title AS Title, count(*) TotalCopys
FROM film

INNER JOIN inventory ON film.film_id = inventory.film_id

WHERE film.title = 'CONNECTICUT TRAMP'
GROUP BY film.title;
```

```sql
db.stores.aggregate(
    [ 
        {
            $unwind: "$Inventory" 
        }, 
        {
            $match: {"Inventory.Title":"CONNECTICUT TRAMP"}
        },
        {
            $group: {_id: "$Inventory" , numFilms:  {$sum: 1}}
        }
    ])
```

```sql
MATCH (inventory:Inventory)-[:CONTEM]->(film:Film)
WHERE film.Title = "CONNECTICUT TRAMP"

RETURN film.Title AS Title, count(film.idFilm) AS TotalCopys
```

8. Lista dos Nomes (Primeiro e Último) dos Clientes e o total pago por cada um deles ao sistema em si, ordenados alfabeticamente consoante o Primeiro Nome.

```sql
SELECT customer.first_name AS FirstName, customer.last_name AS LastName, sum(payment.amount) AS TotalPago
FROM payment

INNER JOIN customer ON payment.customer_id = customer.customer_id

GROUP BY customer.first_name, customer.last_name
ORDER BY customer.FIRST_NAME;
```

```sql
db.customers.aggregate([{ "$project": {"First Name": 1,"TotalSpent": {"$sum": {$toInt: {"$Payments.Amount"}}}}])
```

```sql
MATCH (customer:Customer)<-[:FEITO_POR]-(payment:Payment)

RETURN customer.FirstName AS FirstName, customer.LastName AS LastName, sum(toFloat(payment.Amount)) AS TotalPago
ORDER BY FirstName
```

9. Lista de todos os Filmes da Categoria "Action", bem como seu Ano de Lançamento e Rating.

```sql
SELECT title AS Title, release_year AS ReleaseYear, rating AS Rental
FROM film

INNER JOIN film_category ON film.film_id = film_category.film_id
INNER JOIN category ON category.category_id = film_category.category_id

WHERE category.name = 'Action'
ORDER BY Title;
```

```sql
db.films.find({Category: "Action"}, {"Title": 1,"Release year": 1 , Rating: 1, _id:0}) 
```

```sql
MATCH (category:Category)<-[:TIPO]-(film:Film)
WHERE category.Name = "Action"

RETURN film.Title AS Title, film.ReleaseYear AS ReleaseYear, film.Rating AS Rating
ORDER BY Title
```

10. Lista das Cidades mais populares em termos de pagamentos por parte dos seus moradores.

```sql
SELECT country.country AS Name, count(payment.payment_id) AS TotalPayments
FROM country

INNER JOIN city ON city.country_id = country.country_id
INNER JOIN address ON address.city_id = city.city_id
INNER JOIN customer ON customer.address_id = address.address_id
INNER JOIN payment ON payment.customer_id = customer.customer_id

GROUP BY country.country
ORDER BY TotalPayments DESC;
```

```sql

```

```sql
MATCH (address:Address)<-[:VIVE_EM]-(customer:Customer)<-[:FEITO_POR]-(payment:Payment)

RETURN address.Country AS Name, count(payment.idPayment) AS TotalPayments
ORDER BY TotalPayments DESC
```

