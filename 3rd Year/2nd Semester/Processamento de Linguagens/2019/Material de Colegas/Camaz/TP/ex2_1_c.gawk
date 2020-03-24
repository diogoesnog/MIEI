BEGIN { FS="\""; IGNORECASE=1 }

/<A.*?href=.*?>/ {
	for(i = 1; i <= NF; i++){
		if($i ~/href/){
			print $(i+1);
		}
	}
} # percorrer com o ciclo for e quando encontrar o href imprime campo seguinte

END {print "Encontradas " conta " ocorrências de linha com tag html.";}
