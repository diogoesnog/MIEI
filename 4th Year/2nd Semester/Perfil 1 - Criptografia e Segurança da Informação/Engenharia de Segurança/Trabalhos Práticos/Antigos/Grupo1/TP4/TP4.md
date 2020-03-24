# Trabalho Prático 4 - Resolução

## 1\. RGPD (Regulamento Geral de Proteção de Dados)

#### Pergunta P1.1

Quando falamos em princípios relativos ao tratamento de dados pessoais temos que ter alguns aspetos em conta. Sempre que se procede a uma recolha de dados, estes devem ter uma causa definida e efetiva para o qual são recolhidos, ou seja, não é permitido que sejam recolhidos dados sem uma razão de causa, para além disso, estes devem ser tratados de forma lícita, coerente e transparente no que diz respeito ao titular dos mesmos.

Os dados devem ser conservados apenas durante o tempo necessário para o intuito ao quais foram recolhidos. Por exemplo, uma empresa não deve guardar dados de clientes com quem já não estabelecem qualquer tipo de relação, exceto em situações de interesse público, como para fins de investigação científica ou histórica, ou para possíveis fins estatísticos. 

Quem quiser realizar um tratamento de dados deve garantir que existem medidas para que tal tratamento seja realizado de forma segura, incluindo tanto a proteção contra tratamentos não autorizados, como contra uma possível perda dos dados, destruição ou danificação acidental, assim devem ser adotadas medidas técnicas adequada para garantir a integridade e confidencialidade dos mesmos.

Além disso, deve sempre ter-se em conta o aspeto de minimizar os dados quando os recolhemos, ou seja, quem planear realizar um tratamento de dados tem de assegurar que só regista e trata os dados pessoais estritamente necessários para o fim estipulado.

Devem ainda ser garantidas formas de verificar a veracidade dos dados e a sua respectiva validade/atualidade - devendo ser tomadas sempre medidas pertinentes no âmbito de evitar dados imprecisos. Por exemplo, se uma empresa realizar um tratamento de dados, a mesma deve periodicamente garantir a atualização dos mesmos.


#### Pergunta P1.2

A pseudonimização é uma técnica para codificar dados pessoais e diminuir algumas das obrigações do RGPD. Deste modo, os _data controller_ podem estabelecer os seguintes objetivos:

D1: a partir do pseudónimo não deve ser possível, para um terceiro, identificar o indivíduo ao qual aquele pseudónimo diz respeito;

D2: não deve ser trivial, para qualquer terceiro, reproduzir os pseudónimos.

Analisemos algumas técnicas utilizadas na pseudonimização. Comece-se pelas técnicas baseadas em funções de hash: _hashing without key, hashing with key_ e _hashing with salt_.

As duas últimas técnicas baseiam-se na técnica _hashing without key_. Apesar das desvantagens desta técnica, note-se que o _hashing_ pode ser uma ferramenta útil para garantir a precisão dos dados, uma vez que as funções de hash permitem verificar a integridade dos dados e autenticar uma dada entidade.

No entanto, criar pseudónimos recorrendo ao _hashing_ simples de dados identificativos tem grandes desvantagens, uma vez que _inputs_ iguais originam o mesmo _output_, não se verificando as propriedades D1 e D2.

Por outro lado, no _hashing with key_ ou _salt_, _inputs_ iguais já não originam os mesmos _outputs_, pelo que as propriedades D1 e D2 são verificadas. Isto deve-se a usar-se uma chave ou um salt. Esta técnica é, normalmente, aplicada quando o _data controller_ precisa de rastrear os indivíduos sem armazenar os seus identificadores iniciais.

Na técnica _hashing com “salt”_, a utilização de “salts” para a proteção das funções de hash apresenta algumas desvantagens, uma vez que os “salts” são armazenados em conjunto com os valores de hash correspondentes.

A aplicação da criptografia simétrica aos dados identificadores de um dado indivíduo é também uma técnica eficiente na derivação de pseudónimos. Esta técnica é geralmente utilizada nos casos em que um _data controller_ precisa de rastrear os dados e conhecer os identificadores iniciais.

É também possível recorrer a criptografia assimétrica para derivar pseudónimos, no caso em que o data controler pretende que a entidade autorizada a executar a pseudonimização não seja a mesma que está autorizada a realizar a reidentificação e quando pretende gerar pseudónimos diferentes para o mesmo indíviduo.

Uma outra abordagem interessante é permitir que os utilizadores participantes gerem os seus próprios pseudónimos, mantendo-os na sua posse. No entanto, trata-se de uma técnica que não é trivial e que tem alguns problemas associados. 

A tokenização é outra técnica de pseudonimização. Trata-se de um processo em que os identificadores dos titulares de dados são substituídos por valores gerados aleatoriamente. É, no entanto, uma técnica difícil de implementar e, portanto, as técnicas baseadas em funções de hash e as técnicas criptográficas podem ser preferíveis, relativamente à redução da complexidade e do armazenamento.

Por fim, existem ainda outras abordagens para a criação de pseudónimos, nomeadamente, o _masking, o scrambling e o blurring_.

O _masking_ refere-se ao processo de ocultar parte do identificador de um indivíduo com caracteres aleatórios ou outros dados. Por outro lado, o _scrambling_ refere-se a técnicas gerais para misturar ou ofuscar as identidades. No entanto, ambas as técnicas são fracas na derivação de pseudónimos, pelo que o seu uso não é recomendado como uma boa prática no processamento de dados pessoais.

Relativamente ao _blurring_ trata-se de uma técnica que utiliza uma aproximação dos valores dos dados, de modo a reduzir a precisão dos mesmos, reduzindo a possibilidade de identificação dos indivíduos.


#### Pergunta P1.3

**1.** Para avaliar se um processamento de dados pessoais vai ou não resultar num risco elevado são usados os 9 critérios listados abaixo:
- _Evaluation/Scoring_ - Inclui avaliação dos perfis e definição de cada um dos aspectos relacionados com os perfis.
- _Automated-decision making with legal or similar significant effect_ - Toma decisões automáticas perante determinadas características do perfil que possam ter efeitos jurídicos.
- _Systematic monitoring_ - Refere-se ao controlo automático e ao processamento de dados recolhidos através de redes sociais ou em plataformas de acesso público.
- _Sensitive data or data of highly personal nature_ - Processar informação mais sensível, como opiniões políticas ou algo no âmbito.
- _Data processed on a large scale_ - Tendo em conta o número de dados a processar, isto é, o volume e o significado que analisá-los pode ter.
- _Matching or combining datasets_ - Através da inteligência artificial, por exemplo, prever como se comportarão determinados dados semelhantes a outros já processados.
- _Data concerning vulnerable data subjects_ - Por vezes, o processamento de dados tem de ser feito com consentimento dum titular dos mesmos que pode não ser o sujeito a quem se refere o conjunto de dados, se for um sujeito vulnerável, como crianças, idosos, pessoas com alguma deficiência, etc.
- _Innovative use or applying new techonological or organisational solutions_ - Se um sistema ou um processamento usar tecnologia inovadora e novas soluções tecnológicas, é necessário recorrer a esta avaliação e cuidado, como reconhecimento facial, etc.
- _Improvement recommendations_.

**2.** A título exemplificativo e com fim de preencher o relatório DPIA, iremos usar o exemplo de uma plataforma - ou site, ou aplicação - que, conforme certas preferências de um indíviduo e a sua localização, alerta para quando este se encontra a uma distância relativamente curta de um sítio/local que poderia ser do seu interesse.

Uma vez que estaríamos a lidar com a localização atual do utilizador e com os seus gostos pessoais, seria necessário ter uma forma de fazer login, isto é, exigiria um nome de utilizador e uma palavra passe, assim como associar um email à conta de usuário.

Num primeiro contacto com a aplicação, o indivíduo teria de responder a umas breves questões, por exemplo, a nível de eventos, se prefere musicais ou exposições, se prefere arte contemporânea ou abstrata, a nível de gastronomia, se é vegetariano ou omnívoro, a nível de locais frequentados, qual a idade que o utilizador tem, se prefere bares mais descontraídos ou mais formais, com música para dançar ou música de fundo, a nível de gastos monetários, se tem algum tipo de _upper bound_ que não deseja ultrapassar. Isto facilitaria uma selecção primária daquilo que poderiam ser bons locais a recomendar ao utilizador.

À medida que é feito uso da aplicação, vão surgindo notificações _push_ com sugestões, às quais o utilizador poderia responder como útil - interessado -, já frequentado ou sem interesse.

Desta forma, o processamento de dados pessoais satisfaz os critérios de _systematic monitoring_ - monotorização sistemática -, _sensitive data or data of highly personal nature_ - dados sensíveis e de carácter extremamente pessoal - e _matching or combining datasets_ - combinar dados -!

**3.** DPIA template [preenchido](https://github.com/uminho-miei-engseg-18-19/Grupo1/blob/master/TP4/DPIA%20-%20application.pdf).

#### Pergunta P1.4

PIA template [preenchido](https://github.com/uminho-miei-engseg-18-19/Grupo1/tree/master/TP4/Pergunta1_4).

*Observação:* O ficheiro encontra-se em formato json, uma vez que não conseguimos fazer a exportação do mesmo em formato pdf.
