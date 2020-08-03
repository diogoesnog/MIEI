# Pergunta 1 - Assinaturas cegas (*Blind signatures*) baseadas no Elliptic Curve Discrete Logarithm Problem (ECDLP)

Para iniciar todo o processo das assinaturas cegas é necessário existirem os ficheiros correspondentes à *Private Key* e ao Certificado em si (**Experiência 1.1**). Com estes dois ficheiros prontos consegue-se exeutar a assinatura cega pelas suas diversas fases, chegando a um resultado concreto no que toca à validade da mesma sobre a mensagem original que se pretende enviar.

A remodelação do código surge com o objetivo de simplificar tanto o input como o output, poupando trabalho desnecessário a copiar os componentes que vão sendo necessários no decorrer de cada fase. Além das simplificações pedidas no enunciado, foram desenvolvidas outras ideias para tornar a execução da assinatura o mais simples e intuitiva possível.

**Dessa forma, criou-se uma tabela totalmente dividida por Fases, que permite compreender quem é o participante responsável por cada uma delas e de que forma podemos executá-las:**

---

## Resolução da Pergunta 1

| Fases         | Programa                | Executor    | Input                                                        | Output                                                       |
| ------------- | ----------------------- | ----------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Inicialização | `init-app.py`           | Assinante   | **Comando 1** python init-app.py<br />**Comando 2** python init-app.py -init | **Comando 1** Imprime no Ecrã *pRDashComponents* <br />**Comando 2** Guarda em **ficheiroAssinante.txt** *InitComponents* e *pRDashComponents* |
| Ofuscação     | `ofusca-app.py`         | Requerente  | **Comando 1** python ofusca-app.py -msg <Mensagem a Assinar><br />**Comando 2** python ofusca-app.py -msg <Mensagem a Assinar> -RDash <pRDashComponents> | Ambos os comandos imprimem no ecrã a *BlindMessage* e guardam no **ficheiroRequerente.txt** os *BlindComponents*, *pRComponents* e a mesma |
| Assinatura    | `blindSignature-app.py` | Assinante   | **Comando 1** python blindSignature-app.py -key <PrivateKey> <br />**Comando 2** python blindSignature-app.py -key <PrivateKey> -bmsg <BlindMessage> | Ambos os comandos imprimem no ecrã a *BlindSignature* e guardam no fim do **ficheiroAssinante.txt** a mesma |
| Desofuscação  | `desofusca-app.py`      | Requerente  | **Comando 1** python desofusca-app.py<br />**Comando 2** pyton desofusca-app.py -s <BlindSignature> -RDash <pRDashComponents> | Ambos os comandos imprimem no ecrã a *Signature* e guardam no fim do **ficheiroRequerente.txt** a mesma |
| Verificação   | `verify-app.py`         | Verificador | **Comando 1** python verify-app.py -cert <Certificado> -msg <Mensagem Original a Assinar><br />**Comando 2** python verify-app.py -cert <Certificado> -msg <Mensagem Original a Assinar> -sDash <Signature> -f <Ficheiro Requerente> | Ambos os comandos validam a assinatura sDash sobre a mensagem em si, imprimindo no ecrã o resultado dessa validação |



---

## Notas/Observações Finais

- **Ficheiros Assinante**
  - Ficheiro [init-app.py](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P1%20-%20Assinaturas%20Cegas%20baseadas%20no%20ECDLP/BlindSignature/init-app.py) que permite efetuar a fase de **Inicialização** (1), devolvendo o *pRDashComponents* e *InitComponents*.
  - Ficheiro [blindSignature-app.py](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P1%20-%20Assinaturas%20Cegas%20baseadas%20no%20ECDLP/BlindSignature/blindSignature-app.py) que permite efetuar a fase **Assinatura** (3), devolvendo a *BlindSignature*.
- **Ficheiros Requerente**
  - Ficheiro [ofusca-app.py](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P1%20-%20Assinaturas%20Cegas%20baseadas%20no%20ECDLP/BlindSignature/ofusca-app.py) que permite efetuar a fase de **Ofuscação** (2), devolvendo a *BlindMessage*, *BlindComponents* e *pRComponents*.
  - Ficheiro [desofusca-app.py](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P1%20-%20Assinaturas%20Cegas%20baseadas%20no%20ECDLP/BlindSignature/desofusca-app.py) que permite efetuar a fase **Desofuscação** (4), devolvendo a *Signature*.
- **Ficheiros Verificador**
  - Ficheiro [verify-app.py](https://github.com/uminho-miei-engseg-19-20/Grupo5/blob/master/Trabalhos%20Pr%C3%A1ticos/TP2/P1%20-%20Assinaturas%20Cegas%20baseadas%20no%20ECDLP/BlindSignature/verify-app.py) que permite efetuar a fase de **Verificação** (5), devolvendo o resultado da validação da assinatura sobre a mensagem original.

- Estes três participantes permitem entender melhor o modo com as assinaturas cegas operam. 