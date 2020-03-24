BEGIN {FS="::"; IGNORECASE=1}

$3 ~ /Jesus/ { print "Título: " $3;
			conta++;
				}

END {
	print "São " conta " vezes!"
}
