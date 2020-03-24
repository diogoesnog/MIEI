# Pergunta 1.1

Os principais pontos do principio da precisão de dados são:
* O princípio da precisão dos dados deve ser implementado pelo controlador em todo o processamento operações.
* Os dados imprecisos devem ser apagados ou retificados sem demora.
* Os dados podem precisar ser verificados regularmente e mantidos atualizados para garantir a precisão.

Um controlodor pessoal que tenha informações pessoais não deve usar essas informações sem medidas que garantam que essa informação é precisa e atualizada. A obrigação de garantir a precisão dos dados deve estar no contexto do processamento de dados, isto é, os titulares de dados devem gozar do direito de acesso aos seus dados pessoais, a fim de verificar se os dados estão corretos.

Também pode haver casos em que a atualização dos dados armazenados é legalmente proibida, porque o objetivo de armazenar os dados é principalmente para documentar eventos como um histórico 'instantâneo'. Como por exemplo, é o registo de uma operação que não deve ser alterado, apenas acréscimos às observações seriam permitidos.

Por outro lado, existem situações em que é absolutamente necessário atualizar e verificar regularmente a precisão dos dados, devido ao dano potencial que pode ser causado ao detentor deste, se os dados permanecerem imprecisos.

Se alguêm estiver para concluir um contrato com o banco, e o banco vai a uma base de dados desatualizada, pode o contrato não ser realizado.

# Pergunta 1.2

**Design goals**

A pseudonimização pode contribui para esconder a verdadeira identidade de um indivíduo e também como suporte para desvinculação em diferentes domínios de processamento de dados.
A escolha da técnica de pseudonimização é essencial para os controladores. Para este fim, os seguintes objetivos de projeto podem ser definidos pelos controladores de dados para adotar técnicas, tendo em conta os riscos da operação específica de processamento de dados para os direitos e liberdades dos indivíduos.

As seguintes propiedades são a D1 e D2, respetivamente:
* Os pseudônimos não devem permitir uma re-identificação “fácil” por terceiros (ou seja, qualquer outro controlador ou processador) dentro de um contexto de processamento de dados específico (de modo a
identificadores em um contexto específico).
* Não deve ser trivial para qualquer terceiro (ou seja, qualquer outro que não o controlador ou processador) reproduzir os pseudônimos (para evitar o uso dos mesmos pseudônimos em diferentes dados domínios de processamento).

**Hashing without key** 

Hashing é uma técnica que pode ser usada para derivar pseudônimos, mas tem algumas desvantagens do que foi falado na secção anterior. Uma função de *hash* critográfica é uma função com propriendades especificas, esta pega numa mensagem inicial e tranforma no numero de bits que se pretende. Importante não utilizar o SHA-1 e o MD5 e utilizar SHA-2 e o SHA-3.

Em relação às propriedades D1 e D2, a D2 não é válida, pois qualquer terceiro que aplique a mesma função hash ao mesmo identificador recebe o mesmo pseudônimo. E a D1 também não necessariamente se mantém, uma vez que é trivial para qualquer terceiro verificar, para um determinado identificador, se um pseudônimo corresponde a esse identificador.


**Hashing with key or salt**

Uma boa abordagem para gerar pseudônimos é a utilização de uma hash com salt, não dependendo unicamente do algoritmo. A principal diferença das funções hash convencionais é que, para o mesmo input (um dado identificador), vários pseudônimos diferentes podem ser produzidos, de acordo com a escolha da chave específica - e, assim, a propriedade D2 é garantida. A propriedade D1 também é válida, um adversário não tem conhecimento da chave e, assim, não está em posição de verificar se um pseudônimo corresponde a um identificador conhecido específico.

Os dados não devem ser sempre computados com a mesma chave. Uma função de hash se a chave secreta for destruída com segurança e a função hash é criptograficamente forte, é computacionalmente difícil, mesmo para o controlador de dados,para inverter o pseudônimo para o identificador inicial, mesmo que o controlador tenha conhecimento do identificadores.

Outra abordagem pode ser a utilização de um salt escolhido aleatoriamente.

**Cifras como técnica de pseudonimização**

A utilização de cifas simétricas, é considerado um método eficiente de obter pseudónimos. Nos casos mais gerais, o identificador do indivíduo pode ser cifrado através de um algoritmo de encriptação simétrica, fornecendo assim um criptograma que será usado com pseudónimo. A mesma chave será necessária para a desincriptação. Tal pseudónimo satisfaz as propriedades de pseudonimização, desde que nenhuma terceira parte tenha acesso à chave.

Tal como acontece com as funções de *hash*, as chaves que são utilizadas tem um tamanho minimo de 256 bits, de forma a ser considerado um cifra de segurança adequada. Ao contrário do que acontece com as funções de *hash*, é que o controlador (dono da chave secreta) pode a qualquer momento recuperar os dados do indivíduo incialmente definidos a partir de processo de decifragem. Isto permite que seja mais díficil identificar os indivíduos, uma vez que estes não guardam os identicadores.

No entanto as cifras assimétricas também podem ser empregues nestes casos, a principal característica encriptação de chave pública, é que cada entidade participa no esquema com o seu par de chaves, pública e privada. A chave pública pode ser usada para cifrar dados, mas apenas a entidade específica pode decifrar os dados com a sua chave privada. Embora as chaves estejam matematicamente relacionadas, o conhecimento da chave pública não permite ter o conhecimento da chave privada. Para fornecer a propriedade de indistinguibilidade ao criptograma, os algoritmos de chave pública podem ser adequadamente implementados de uma forma probabilística, introduzindo aleatoriedade no processo de cifragem. Desta maneira, se a mesma mensagem for cifrada duas vezes com a mesma chave pública a cada vez, os dois criptogramas correspondentes serão diferentes.

As propriedades das crifras assimétricas também podem ser usado em vários outros contextos relacionados à ofusacação das identidades dos indivíduos. É de realçar que os algoritmos de cifra assimétrica requerem o uso de chaves muito grandes, que por sua vez pode dar origem a restrições de implementação, para além de serem menos eficientes que algoritmos de cifra simétrica. 

**Outras técnicas baseadas em criptografia**

Para além das técnicas de pseudominização apresentadas em cima, é possível combinar esquemas criptográficos e fornecer uma abordagem de pseudominização bastante robusta/segura.

Existem ainda outras soluções, tais como as soluções descentralizadas, que permite a cada utilizador gerar e controlar os próprios pseudónimos.

Por fim, é de salientar que um desafio comum à maior parte das técnicas criptográficas é gestão das chaves, uma vez que o seu processo não é trivial, dependendo da escalabilidade da aplicação, como também da técnica escolhida.

**Tokenisation** 

*Tokenisation* refere-se ao processo em que os dados dos indivíduos são substituídos por valores gerados aleatóriamente, mais conhecido como *tokens*, sem ter qualquer relação matemática com os indentificadores originais. Assim, o conhecimento de um token por parte de uma terceira parte é inútil, exceto para o controlador ou para o processador. Este tipo de técnica é geralmente usado para transições financeiras.

**Outras medidas**

Existem também diversas outras técnicas no contexto da pseudonimização, sendo estas um pouco restritas quanto à sua aplicação:

1. *Masking* - refere-se ao processo de esconder parte de um indenticador de um indivíduo com caracteres aleatórios ou outros dados. Esta tecnica pode não garantir as propriedades de pseudominização, e ainda para mais pode haver riscos, uma vez que se a técnica não for cuidadosamente implementada, pode atribuir o mesmo pseudónimo para diferentes utilizadores, gerando colisões.

2. *Scrambling* -  refere-se a um conjunto de técnicas de mistura e ofuscação de caracteres. Este processo pode ser reversível, de acordo com a técnica escolhida. Esta técnica pode ser considerada uma forma simples de cifra simétrica, não garantindo as propriedades de pseudonimização em certos casos específicos.

3. *Blurring* - esta técnica tem como objetivo o uso de valores aproximados, de modo a reduzir a precisão dos dados, reduzindo assim a possibilidade de identificar os indivíduos.  
 
# Pergunta 1.3 - 1

1. **Avaliação ou pontuação** - inclui criar um prefil ou prever, aspetos relacionados com dados de desempenho no trabalho, situações económicas, de saúde, preferências pessoas e intresses, confiabilidade ou comportamento, localização ou movimentos.

2. **Tomada de decisões automáticas com efeitos legais ou algo semelhante** - processo que envolve, que sejam tomadas decisões sobre os titulares dos dados com efeitos legais relativos à pessoa em causa.

3. **Monitorização sistemática** - processamento que se usa para observar, monitorizar ou controloar dados sobre indivíduos, incluindo dados coletados através da rede ou de uma monitorização sistemática de uma área de acesso público. Este tipo de monitorização estabelece-se como um critério, uma vez que os dados pessoais podem estar a ser coletados em circunstâncias que permite aos indivíduos não ter conhecimento de tal situação.

4. **Dados sensíveis ou de natureza altamente pessoal** - inclui categorias de dados pessoais definidos no artigo 9	como por exemplo convicções políticas, bem como outras cartegorias de dados pessoais presentes no artigo 10, como por exemplo convicções criminosas ou ofensas. Estes dados pessoais são considerados sensíveis, porque se encontram ligados ao seu agregado familiar e atividades privadas, ou porque influenciam o exercício ao direito fundamental, ou porque a sua violação produz um impacto sério no dia a dia do indivíduo em causa.

5. **Processamento de dados em larga escala** - o *RGPD* não define o constitui uma grande escala. No entanto é recomendável, através do *WP29* ter em conta os seguintes fatores, para determinar se um processamento é feito em grande escala:
												* i. número de indivíduos afetados.
												* ii. volume de dados e/ou o seu alcance a quando do seu processamento.
												* iii. duração ou permanência da atividade de processamento dos dados.
												* iv. extenção geográfica da atividade de processamento.


6. **Combinação de datasets** - de duas ou  mais operações de processamento de dados, realizados para diferentes propósitos e/ou por pessoas diferentes de modo a exceder as espectativas razoáveis para os quais foram criados.

7. **Dados relativos a indivíduos vulneravéis** - este tipo de processamento é considerado um critério devido ao desiquilíbrio de poder entre quem controla os dados e o títular dos mesmos, o que leva a que os individuos não conseguiam consentir, ou opor-se ao ao processamento dos seus dados ou exercer o seu direito. O tipo de indivíduos vulneráveis inclui crianças, empregados, elementos da população que necessitam de proteção especial (doentes mentais, idosos, etc...), ou em qualquer outro caso, que exista um desiquilíbrio entre os intervenientes.

8. **Uso inovador ou aplicação de nova tecnologia ou soluções organizacionais** - combinam o uso da impressão digital e do reconhecimento facial para melhorar o controlo do acesso físico. 

9. Quando o processamento em si **previne os indivíduos de exercer um direito ou usar um serviço ou contrato**. Isto inclui operações de processamento que tem como objetivo permitir, modificar ou recusar um contrato ou serviço por parte de um indivíduo.

# Pergunta 1.3 - 2

Um exemplo de um projeto que envolve a utilização de dados pessoais cujo processamento resulta num risco elevado, sujeito a uma *DPIA*, seria o desenvolvimento de uma aplicação para a marcação de consultas num posto médico, que permite aos utentes, para além do agendamento de consultas, ter acesso ao histórico de consultas realizadas, bem como as prescricões médicas receitadas em cada consulta e um breve resumo sobre as suas consultas, onde consta o que foi falado. 

As credenciais para os médicos são disponibilizados pelo respetivo posto médico em que trabalha, enquanto os utentes tem que registar na aplicação e indicar nome completo, nome de utilizador, idade, data de nascimento, posto médico que frequentam, doenças, password. Por outro lado os médicos tem apenas a si associado nome completo, nome de utilizador, passowrd, posto médico atual e os respetivos utentes a si associados.

Os postos médicos podem apagar a conta de um médico, caso este mude de estabelecimento, sendo neste caso gerado novas credencias pelo novo estabelecimento frequentado. Os utilizadores uma vez registados na aplicação não podem nunca apagar a sua conta.

Posto isto, este projeto proposto respeita os critérios 3 e 7 a cima mencionados, pelo que seria necessário efetuar uma *DPIA*.

# Pergunta 1.3 - 3

A resposta a esta questão encontra-se na mesma diretoria deste ficheiro, com o nome *dpia-1.3-3.pdf*.

# Pergunta 1.4

A resposta a esta questão encontra-se na mesma diretoria deste ficheiro, com o nome *dpia-1.4.pdf*.
