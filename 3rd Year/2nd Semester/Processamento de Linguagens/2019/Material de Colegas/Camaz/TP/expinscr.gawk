BEGIN { FS="\t"; IGNORECASE=1}

$10 ~/individual/ && $12 ~ /Valongo/ {print $1}
END { print "Fim do documento" }