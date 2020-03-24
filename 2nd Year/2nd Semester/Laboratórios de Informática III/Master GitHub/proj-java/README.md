# Estruturação do Repositório
Este projeto está dividido em 3 packages: `common`, `engine` e `li3`. Caso o grupo opte por não criar mais packages para além dos listados, cada um dos packages deverá conter:
- `common`: classes utilitárias;
- `engine`: classes que implementam as queries e funcionalidades relacionadas;
- `li3`: definição da interface do sistema de queries e código de testes;


# Compilação do Projeto
Em primeiro lugar, deve-se instalar a ferramenta **Maven**, responsável pela gestão do projeto. 
Esta ferramenta é normalmente disponibilizada nos gestores de pacotes com o nome `mvn`.
Para compilar o projeto e corrê-lo com a *class* **Main** fornecida, deve-se executar o comando

```bash
./run.sh [DUMP_PATH]
```

