<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="2.0">
    
    <xsl:output method="html" encoding="UTF-8" indent="yes"/>
    
    <xsl:template match="/">
        <xsl:result-document href="html/index.html">
            <html>
                <head>
                    <title>Arquivo Sonoro Ernesto Oliveira</title>
                    <meta charset="UTF-8"/>
                    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css"/>
                </head>
                <body>
                    <h1>Arquivo Sonoro Ernesto Oliveira</h1>
                    <h3>Índice de Músicas</h3>
                    <ol>
                        <xsl:apply-templates mode="indice"/>
                    </ol>
                </body>
            </html>
        </xsl:result-document>        
        <xsl:apply-templates/>
    </xsl:template>
    
    <xsl:template match="doc" mode="indice">
        <li>
            <a name="{generate-id()}"/>
            <a href="arqson-{generate-id()}.html"><xsl:value-of select="tit"/></a>
            <xsl:choose>
                <xsl:when test="contains(prov,'Alentejo')">
                    - A música é Alentejana.
                </xsl:when>
                <xsl:otherwise>
                    - A música não é Alentejana.
                </xsl:otherwise>
            </xsl:choose>
        </li>
    </xsl:template>
    
    <xsl:template match="doc">
        <xsl:result-document href="html/arqson-{generate-id()}.html">
            <html>
                <head>
                    <title>Arquivo Sonoro Ernesto Oliveira: Página de Música</title>
                    <meta charset="UTF-8"/>
                    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css"/>
                </head>
                <body>
                    <table class="w3-table">                       
                        <tr>
                            <th>Título</th><td><xsl:value-of select="tit"/></td>
                        </tr>
                        <tr>
                            <th>Local</th><td><xsl:value-of select="local"/></td>
                        </tr>
                        <tr>
                            <th>Província</th><td><xsl:value-of select="prov"/></td>
                        </tr>
                        <tr>
                            <th>Músico</th><td><xsl:value-of select="prov"/></td>
                        </tr>
                        <tr>
                            <th>Duração</th><td><xsl:value-of select="duracao"/></td>
                        </tr>
                        <xsl:apply-templates select="file"/>    
                    </table>
                    <hr/>
                    <address>
                        <a href="index.html#{generate-id()}">Voltar ao Início</a>
                    </address>
                </body>
            </html>
        </xsl:result-document>
    </xsl:template>
    
    <xsl:template match="file">
        <tr>
            <th>Aúdio</th>
            <td>
                <a href="{.}">Ficheiro <xsl:value-of select="@t"/></a>
            </td>
        </tr>
    </xsl:template>
    
</xsl:stylesheet>