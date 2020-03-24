BEGIN { FS="::";
	nome[0]="Pai";
	nome[1]="Mae";
	nome[2]="Avo";
	nome[3]="Tio";
	nome[4]="Sobrinho";
	nome[5]="Primo";
	nome[6]="Filho";
	nome[7]="Neto";

	for(i in nome){
		ocor[nome[i]]=0;
	}

}


NF>0 && $(NF-1) ~ nome[k] { ocor[nome[k]]++; }



END { for(i in nome){
	
	print nome[i] "->" ocor[nome[i]]
	
	}
}