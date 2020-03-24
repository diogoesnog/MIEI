BEGIN {FS="\""; IGNORECASE=1}

/<a.*?href.*?>/ { 
		
		for(i=1; i <= NF; i++){

			if($i ~ /href/){

				print $(i+1);
			}
		}
	}

END {
	print "FIM FICHEIRO"
}
