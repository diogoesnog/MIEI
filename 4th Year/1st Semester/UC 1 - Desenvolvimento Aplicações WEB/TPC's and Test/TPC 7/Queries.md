# Resolução das Queries

1. **Listar os Géneros de Filmes e indicar quantos há de cada um.**

```sql
db.filmes.aggregate([ 
    {$group: {
    	_id: "$genres", 
    	numFilmes: {$sum: 1}
    }}, 
    {$sort: {numFilmes:-1}} 
])
```

2. **Quais os títulos dos Filmes do Género "Drama"?**

```sql
db.filmes.aggregate([ 
    {$unwind: "$genres"}, 
    {$match: {genres: "Drama"}}, 
    {$project: {title: true}} 
])
```

3. **Que atores participaram em Filmes do Género "Comedy"?**

```sql
db.filmes.aggregate([ 
    {$unwind: "$genres"}, 
    {$unwind: "$cast"}, 
    {$match: {genres: "Comedy"}}, 	
    {$group: {_id: "$cast"}} 
])
```