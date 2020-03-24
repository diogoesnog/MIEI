BEGIN {FS="::"; IGNORECASE=1}

$5 ~ /mp3/ { print "Título: " $3}

END {
	print "FIM FICHEIRO"
}
