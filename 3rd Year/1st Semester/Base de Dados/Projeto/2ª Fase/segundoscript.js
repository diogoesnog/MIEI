db.bilhete.aggregate(
	[
		// Fase de Outer Join com Cliente
		{
			$lookup: {
			    from: "cliente",
			    localField: "NIF",
			    foreignField: "_id",
			    as: "ClienteInfo"
			}
		},
		// Transformar o array ClienteInfo em apenas um field documento
		{
			$unwind: {path : "$ClienteInfo"}
		},
		// Agrupar por NIF, somando o gasto total e mostrando o nome também
		{
			$group: {
			 _id: "$NIF",
			 Nome: {$first: "$ClienteInfo.Nome"},
			 GastoTotal: {$sum: "$Preco"}
			}
		},
		// Colocando por ordem descendente do GastoTotal
		{
			$sort: {GastoTotal: -1}
		}
	]
);
