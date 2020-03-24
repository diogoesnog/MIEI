
SELECT COUNT (ID_TITULO) FROM TITULO

SELECT COUNT (ID_MUSICA) FROM MUSICA

SELECT COUNT (ID_AUTOR) FROM AUTOR

SELECT DISTINCT COUNT (ID_EDITORA) FROM EDITORA

SELECT COUNT (ID_TITULO) FROM TITULO
    INNER JOIN AUTOR ON TITULO.ID_AUTOR=AUTOR.ID_AUTOR
    WHERE AUTOR.NOME='Max Changmin'

SELECT AUTOR.NOME FROM TITULO
    INNER JOIN AUTOR ON TITULO.ID_AUTOR=AUTOR.ID_AUTOR
    WHERE DTA_COMPRA=to_date('01-02-2010', 'dd-mm-yyyy') AND PRECO=12

SELECT EDITORA.NOME FROM TITULO
    INNER JOIN AUTOR ON TITULO.ID_AUTOR=AUTOR.ID_AUTOR
    INNER JOIN EDITORA ON TITULO.ID_EDITORA=EDITORA.ID_EDITORA
    WHERE DTA_COMPRA=to_date('01-02-2010', 'dd-mm-yyyy') AND PRECO=12

SELECT DTA_REVIEW,CONTEUDO FROM REVIEW
    INNER JOIN TITULO ON REVIEW.ID_TITULO=TITULO.ID_TITULO
    WHERE TITULO.TITULO='oh whoa oh'

SELECT DTA_REVIEW,CONTEUDO FROM REVIEW
    INNER JOIN TITULO ON REVIEW.ID_TITULO=TITULO.ID_TITULO
    WHERE TITULO.TITULO='pump'
    ORDER BY DTA_REVIEW ASC

SELECT AUTOR.NOME FROM AUTOR
    INNER JOIN MUSICA ON AUTOR.ID_AUTOR=MUSICA.ID_AUTOR
    INNER JOIN TITULO ON MUSICA.ID_TITULO=TITULO.ID_TITULO
    WHERE DTA_COMPRA=to_date('04-04-1970','dd-mm-yyyy') AND PRECO=20

SELECT SUM(PRECO) FROM TITULO
    INNER JOIN EDITORA ON EDITORA.ID_EDITORA=TITULO.ID_EDITORA
    WHERE EDITORA.NOME='EMI'

SELECT * FROM (SELECT TITULO FROM TITULO WHERE PRECO=20 ORDER BY DTA_COMPRA ASC) WHERE ROWNUM=1

SELECT COUNT(ID_MUSICA) FROM MUSICA
    INNER JOIN TITULO ON MUSICA.ID_TITULO=TITULO.ID_TITULO
    INNER JOIN SUPORTE ON TITULO.ID_SUPORTE=SUPORTE.ID_SUPORTE
    WHERE SUPORTE.NOME='MP3'

SELECT COUNT(ID_MUSICA) FROM MUSICA
    INNER JOIN TITULO ON MUSICA.ID_TITULO=TITULO.ID_TITULO
    INNER JOIN SUPORTE ON TITULO.ID_SUPORTE=SUPORTE.ID_SUPORTE
    INNER JOIN GENERO ON TITULO.ID_GENERO=GENERO.ID_GENERO
    WHERE SUPORTE.NOME='MP3' AND GENERO.NOME='Pop Rock'

SELECT SUM(PRECO) FROM TITULO
    INNER JOIN SUPORTE ON TITULO.ID_SUPORTE=SUPORTE.ID_SUPORTE
    WHERE SUPORTE.NOME='Blue-Ray'

SELECT SUM(PRECO) FROM TITULO
    INNER JOIN SUPORTE ON TITULO.ID_SUPORTE=SUPORTE.ID_SUPORTE
    INNER JOIN EDITORA ON TITULO.ID_EDITORA=EDITORA.ID_EDITORA
    WHERE SUPORTE.NOME='Blue-Ray' AND EDITORA.NOME='EMI'

SELECT SUM(PRECO) FROM TITULO

SELECT NOME FROM
(SELECT EDITORA.NOME , SUM(PRECO) AS GastoTotal FROM TITULO 
    INNER JOIN EDITORA ON EDITORA.ID_EDITORA=TITULO.ID_EDITORA
    GROUP BY EDITORA.NOME
    ORDER BY GastoTotal DESC)
WHERE ROWNUM=1


SELECT resintermedio.ID_EDITORA, COUNT(TITULO.ID_TITULO) from (

SELECT EDITORA.ID_EDITORA, SUM(TITULO.ID_TITULO) AS TitulosHeavyMetal FROM EDITORA 
    INNER JOIN TITULO ON TITULO.ID_EDITORA=EDITORA.ID_EDITORA
    INNER JOIN GENERO ON GENERO.ID_GENERO=TITULO.ID_GENERO
    WHERE GENERO.NOME='Heavy Metal' 
    GROUP BY EDITORA.ID_EDITORA
    ORDER BY TitulosHeavyMetal DESC
) resintermedio

INNER JOIN TITULO ON resintermedio.ID_EDITORA = TITULO.ID_EDITORA
GROUP BY resintermedio.ID_EDITORA