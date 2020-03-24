-- Nome dos jogadores que vivem em Tondela e joguem pelo mesmo. --

SELECT j.nome FROM
	Equipa e, Jogador j, Localidade l
    WHERE
    j.Equipa = e.Id and
    j.LocalNascimento = l.Id and
    l.Designacao = "Tondela" and
    e.Designacao = "Clube Desportivo Tondela";