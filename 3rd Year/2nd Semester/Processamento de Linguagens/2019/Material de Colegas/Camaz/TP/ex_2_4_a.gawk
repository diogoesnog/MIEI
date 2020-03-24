BEGIN {FS="::"; IGNORECASE=1}

$1 ~ /alentejo/ { print "Título: " $3}

END {
	print "FIM FICHEIRO"
}
