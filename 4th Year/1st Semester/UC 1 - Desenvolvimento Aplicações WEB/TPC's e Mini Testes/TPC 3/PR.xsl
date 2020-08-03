<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">

    <xsl:output method="html" encoding="UTF-8" indent="yes"/>
    
    <xsl:template match="/"> 
        <html>
            <head>
                <div class="container">
                    <hr/>
                    <title>Registo de Projetos</title>
                    <meta charset="UTF-8"/>
                    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"/>
                </div>
            </head>
            
            <body>
                <div class="container">
                        <xsl:apply-templates/>
                </div>
            </body>    
        </html>
    </xsl:template>
    
    <xsl:template match="/RegistoProjetos">
        
        <h1 align="center"><b><xsl:value-of select="Informacoes/Titulo"/></b></h1>
        <h3 align="center"><xsl:value-of select="Informacoes/Subtitulo"/></h3>
        <hr/>
        
        <table align="center" width="50%">
            <!-- "tr" significa coluna e "td" linha. -->
            <!-- Primeira coluna com 3 linhas. -->
            <tr>
                <td>
                    <b>Keyname: </b>
                    <xsl:value-of select="@keyname"/>
                </td>
                <td>
                    <b>Título: </b>
                    <xsl:value-of select="Informacoes/Titulo"/>
                </td>
            </tr>
            <tr>
                <td>
                    <b>Data Início: </b>
                    <xsl:value-of select="Informacoes/DataInicio"/>
                </td>
                <td>
                    <b>Data Fim: </b>
                    <xsl:value-of select="Informacoes/DataFim"/>
                </td>
            </tr>
            <tr>
                <td>
                    <b>Supervisor: </b>
                    <a href = "{Informacoes/Supervisor/Nome/@PáginaInicial}"><xsl:value-of select="Informacoes/Supervisor/Nome"/></a>
                </td>
                <td>
                    <b>Email Supervisor: </b>
                    <xsl:value-of select="Informacoes/Supervisor/Email"/>
                </td>
            </tr>
        </table>
        
        <hr/>
        
        <h3>Equipa</h3>
        <ul>
            <xsl:for-each select="Equipa/Estudante">
                <li>
                    <b><xsl:value-of select="IdentEstudante"/></b>
                    <xsl:text> - </xsl:text>
                    <xsl:value-of select="Nome"/>
                    <xsl:text> - </xsl:text>
                    <xsl:value-of select="Email"/>
                </li>
            </xsl:for-each>
        </ul>
        
        <hr/>
        
        <h3>Resumo</h3>
        
        <xsl:for-each select="Resumo/P">
            <p>
                <xsl:choose>
                    <xsl:when test="Negrito">
                        <b><xsl:value-of select="current()"/></b>
                    </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="current()"/>
                </xsl:otherwise>
                </xsl:choose>
            </p>
        </xsl:for-each>
        
        <hr/>
        
        <h3>Entregas</h3>
        
        <ul>
            <xsl:for-each select="Entregas/Trabalho">
                <li>
                    <a href="{@Caminho}"><xsl:value-of select="current()"/></a>
                </li>
            </xsl:for-each>
        </ul>
    </xsl:template>
    
</xsl:stylesheet>