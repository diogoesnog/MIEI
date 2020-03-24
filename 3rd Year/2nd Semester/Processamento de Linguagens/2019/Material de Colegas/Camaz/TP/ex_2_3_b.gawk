BEGIN {FS="::"; IGNORECASE=1}

	{
		for(i = 3; i <= 5; i++){

			x = split($i, aux, " ");

			for(j=0; j <= x; j++){

				vezes[aux[j]]++;
			}
		}
	}

END {
	 
		for(x in vezes){

			print x " -> " vezes[x] " vezes!";
		}


}

