# Pergunta 4 - Componentes Vulneráveis

Todas as imagens e outros ficheiros considerados relevantes para o entendimento complementar da resolução a todas as questões encontram-se listados na secção de [**Notas/Observações Finais**](#notasobservações-finais).

1. [**Pergunta  4.1**](#) - ***Vulnerable Components***

---

## Resolução da Pergunta 4

### Pergunta 4.1 - *Vulnerable Components*

Esta lição é sobre componentes vulneráveis e no slide 5 podemos confirmar que um componente do jQuery foi atualizado e a vulnerabilidade não acontece quando se efetua o `<alert>`

Ao analisar o código fonte do slide 12 podemos observar que o código-fonte do *WebGoat*, principalmente, esta [lição](https://github.com/WebGoat/WebGoat/blob/develop/webgoat-lessons/vulnerable-components/src/main/java/org/owasp/webgoat/vulnerable_components/VulnerableComponentsLesson.java) tem o seguinte:

```java

   try {
//        	System.out.println("Payload:" + payload);
            Contact expl = (Contact) xstream.fromXML(payload);
            return success(this).feedback("vulnerable-components.fromXML").feedbackArgs(expl.toString()).build();
        } catch (com.thoughtworks.xstream.converters.ConversionException ex) {
            if (ex.getMessage().contains("Integer")) {
                return success(this).feedback("vulnerable-components.success").build();
            }
            return failed(this).feedback("vulnerable-components.close").build();
        }

```

Logo se colocarmos esta porção de *input* podemos obter RCE de maneira correta.

```
<java.lang.Integer>
27
</java.lang.Integer> 
```

---

## Notas/Observações Finais

Não existem observações finais para este Trabalho Prático.