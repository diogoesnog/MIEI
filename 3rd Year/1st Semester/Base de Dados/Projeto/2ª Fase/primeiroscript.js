db.bilhete.aggregate(
	// Pipeline
	[
		// Fase do Match
		{
			$match: {Filme: "Beauty and the Beast"}
		},
		// Fase do Group e Sum
		{
			$group: {
			_id: "$Filme",
			ReceitaTotal: {$sum: "$Preco"}
			}
		},
	]
);