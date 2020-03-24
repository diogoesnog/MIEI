<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">

    <xsl:output method="xml" indent="yes" encoding="UTF-8"/>

    <xsl:template match="ARQELEM">
        <xsl:result-document href="dataset/arq{count(preceding-sibling::*)+1}.xml">
            <xsl:processing-instruction name="xml-stylesheet">type="text/xsl" href="arq2html.xsl"</xsl:processing-instruction>
            <xsl:copy-of select="."/>
        </xsl:result-document>
    </xsl:template>

</xsl:stylesheet>