BEGIN {FS="::"; IGNORECASE=1}

	{ vezes[$1]++; }

END {
	for(x in vezes){
		print x " -> " vezes[x]
	}
}
