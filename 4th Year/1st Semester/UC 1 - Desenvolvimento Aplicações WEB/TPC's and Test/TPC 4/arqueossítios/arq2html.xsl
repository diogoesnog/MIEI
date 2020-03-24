<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    
    <xsl:output method="html" encoding="UTF-8" indent="yes"/>
    
    <xsl:template match="ARQELEM">
        
        <html>              
            <head>
                <title>Arqueossítio</title>
                <meta charset="UTF-8"/>
                <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"/>
            </head>
            
            <body>
                <hr/>
                
                <h1 align="center">
                    <b><font color="#dc3545">Arqueossítio do Nordeste Português</font></b>
                </h1>
                <h3 align="center">
                    <font color="#454d55"><xsl:value-of select="IDENTI"/></font>
                </h3>
                
                <hr/>
                <hr/>
                
                <div class="container">
                    <table  class="table table-hover">                        
                        <tr>
                            <th>Descrição</th>
                            <td><xsl:value-of select="DESCRI"/></td>
                        </tr>
                        
                        <xsl:if test="CRONO">
                            <tr>
                                <th>Cronologia</th>
                                <td><xsl:value-of select="CRONO"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="LUGAR">
                            <tr>
                                <th>Lugar</th>
                                <td><xsl:value-of select="LUGAR"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="FREGUESIA">
                            <tr>
                                <th>Freguesia</th>
                                <td><xsl:value-of select="FREGUESIA"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="CONCELHO">
                            <tr>
                                <th>Concelho</th>
                                <td><xsl:value-of select="CONCELHO"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="CODADM">
                            <tr>
                                <th>Código Administrativo</th>
                                <td><xsl:value-of select="CODADM"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="LATITU">
                            <tr>
                                <th>Latitude</th>
                                <td><xsl:value-of select="LATITU"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="LONGIT">
                            <tr>
                                <th>Longitude</th>
                                <td><xsl:value-of select="LONGIT"/></td>
                            </tr>
                        </xsl:if>
                        
                        <xsl:if test="ALTIT">
                            <tr>
                                <th>Altitude</th>
                                <td><xsl:value-of select="ALTIT"/></td>
                            </tr>
                        </xsl:if>
                    </table>
                </div>

                <hr/>
                <hr/>

                <div class="container">
                    <dl>
                        <xsl:if test="ACESSO">
                            <dt>Acesso</dt>
                            <dd><p class="text-justify"><xsl:value-of select="ACESSO"/></p></dd>
                        </xsl:if>
                        
                        <xsl:if test="QUADRO">
                            <dt>Quadro</dt>
                            <dd><p class="text-justify"><xsl:value-of select="QUADRO"/></p></dd>
                        </xsl:if>
                        
                        <dt>Descrição</dt>
                        <dd><p class="text-justify"><xsl:value-of select="DESARQ"/></p></dd>
                        
                        <xsl:if test="INTERP">
                            <dt>Interpretação</dt>
                            <dd><p class="text-justify"><xsl:value-of select="INTERP"/></p></dd>
                        </xsl:if>
                        
                        <xsl:if test="DEPOSI">
                            <dt>Depósito</dt>
                            <dd><p class="text-justify"><xsl:value-of select="DEPOSI"/></p></dd>
                        </xsl:if>
                        
                        <xsl:if test="INTERE">
                            <dt>Interesse</dt>
                            <dd><p class="text-justify"><xsl:value-of select="INTERE"/></p></dd>
                        </xsl:if>

                        <hr/>

                        <xsl:if test="BIBLIO">
                            <dt>Bibliografia</dt>
                            <dd><p class="text-justify">
                                <ol><xsl:for-each select="BIBLIO">
                                    <li>
                                        <p class="text-justify"><xsl:value-of select="current()"/></p>
                                    </li>
                                </xsl:for-each></ol>
                            </p></dd>
                        </xsl:if>
                    </dl>      
                </div>      
                
                <hr/>
                <hr/>
                
                <h5 align="center">
                    <p>
                        <b><font color="#dc3545">Autor: </font></b>
                        <font color="#454d55"><xsl:value-of select="AUTOR"/></font>
                        <br/> 
                        <b><font color="#dc3545">Data: </font></b>
                        <font color="#454d55"><xsl:value-of select="DATA"/></font>
                    </p>
                </h5>
            </body>
        </html>
        
    </xsl:template>
    
</xsl:stylesheet>