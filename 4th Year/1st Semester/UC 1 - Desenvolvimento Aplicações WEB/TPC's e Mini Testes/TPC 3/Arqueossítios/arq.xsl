<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
    
    <xsl:output method="html" encoding="UTF-8" indent="yes"/>
    
    <xsl:template match="/">
        <xsl:result-document href="website/indice.html">
            <html>
                
                <head>
                    <hr/>
                    <title>Arqueossítios do Nordeste Português</title>
                    <meta charset="UTF-8"/>
                    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"/>
                </head>
                
                <body>
                    <div class="container-fluid">
                        <h1 align="center"><b>Arqueossítios do Nordeste Português</b></h1>
                        <hr/>
                        <ol>
                            <xsl:apply-templates mode="indice"/>
                        </ol>
                    </div>
                </body> 
                
            </html>
        </xsl:result-document>
        <xsl:apply-templates/>
    </xsl:template>

    <xsl:template match="ARQELEM" mode="indice">
        <li>
            <!-- Importante definir isto para depois localizar o ID
            quando se tentar voltar ao início. -->
            <a name="{generate-id()}"/>
            <a href="docs/arq-{generate-id()}.html">
                <xsl:value-of select="IDENTI"/>
            </a>
        </li>
    </xsl:template>
    
    <xsl:template match="ARQELEM">
        <xsl:result-document href="website/docs/arq-{generate-id()}.html">
            <html>
                
                <head>
                    <hr/>
                    <title>Arqueossítios do Nordeste Português</title>
                    <meta charset="UTF-8"/>
                    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"/>
                </head>
                
                <body>
                    <h1 align="center">
                        <b>Arqueossítio</b>
                    </h1>
                    <h2 align="center">
                        <xsl:value-of select="IDENTI"/>
                    </h2>
                    
                    <hr/>
                    
                    <div class="container-fluid">
                        <table class="table table-condensed">
                            <tr>
                                <th scope="row">Cronologia</th>
                                <td>
                                    <xsl:choose>
                                        <xsl:when test="not(empty(CRONO))">
                                            <xsl:value-of select="CRONO"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            Não existem dados para este parâmetro
                                        </xsl:otherwise>
                                    </xsl:choose>
                                </td>
                            </tr>
                            
                            <tr>
                                <th scope="row">Descrição</th>
                                <td>
                                    <xsl:choose>
                                        <xsl:when test="not(empty(DESCRI))">
                                            <xsl:value-of select="DESCRI"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            Não existem dados para este parâmetro
                                        </xsl:otherwise>
                                    </xsl:choose>
                                </td>
                            </tr>
                            
                            <tr>
                                <th scope="row">Lugar</th>
                                <td>
                                    <xsl:choose>
                                        <xsl:when test="not(empty(LUGAR))">
                                            <xsl:value-of select="LUGAR"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            Não existem dados para este parâmetro
                                        </xsl:otherwise>
                                    </xsl:choose>
                                </td>
                            </tr>
                            
                            <tr>
                                <th scope="row">Freguesia</th>
                                <td>
                                    <xsl:choose>
                                        <xsl:when test="not(empty(FREGUESIA))">
                                            <xsl:value-of select="FREGUESIA"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            Não existem dados para este parâmetro
                                        </xsl:otherwise>
                                    </xsl:choose>
                                </td>
                            </tr>
                        </table> 
                    </div>
                    
                    <adress>
                        <center>
                            <a href="../indice.html#{generate-id()}">Voltar ao Início</a>
                        </center>
                    </adress>
                </body>
                
            </html>
        </xsl:result-document>
    </xsl:template>
    
</xsl:stylesheet>