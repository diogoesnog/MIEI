package engine;

import estruturas.*;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Iterator;

/**
 * Classe que define o Parse de todos os documentos XML necessários
 * para a realização das várias queries.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 6.0
 * @since   2018-05-25
 * @see LocalDate
 * @see LocalDateTime
 */

class Parse {

    /**
     * Método que trata de ler os ficheiros XML, passando aos métodos criados para o efeito o xml
     * e a estrutura apropriada para se iniciar o Parse de todos estes ficheiros.
     * @param fileName Nome do ficheiro XML.
     * @param posts Estrutura HashPosts.
     * @param tags Estrutura HashTags.
     * @param users Estrutura HashUsers.
     * @param treePerg Tree das perguntas.
     * @param treeRes Tree das respostas.
     */
    public static void parseDocs(String fileName, HashPosts posts, HashTags tags, HashUsers users, TreePosts treePerg, TreePosts treeRes) {
        try {
            XMLInputFactory inputFactory = XMLInputFactory.newInstance();
            InputStream in = new FileInputStream(fileName);
            XMLEventReader eventReader = inputFactory.createXMLEventReader(in);


            while (eventReader.hasNext()) {
                XMLEvent event = eventReader.nextEvent();

                if (event.isStartElement()) {
                    StartElement startElement = event.asStartElement();

                    if (startElement.getName().getLocalPart().equals("row")) {
                        if (fileName.contains("Posts.xml"))
                            parsePosts(startElement, posts, users, treePerg, treeRes);
                        else if (fileName.contains("Users.xml"))
                            parseUsers(startElement, users);
                        else if (fileName.contains("Tags.xml"))
                            parseTags(startElement, tags);
                    }

                }
            }
        } catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }
    }

    /**
     * Método que trata o Parse do ficheiro XML referente aos Posts.
     * @param startElement O parâmetro que inidica o início de cada row do ficheiro XML.
     * @param posts Estrutura HashPosts.
     * @param users Estrutura HashUsers.
     * @param treePerg Tree das perguntas.
     * @param treeRes Tree das respostas.
     */
    private static void parsePosts(StartElement startElement, HashPosts posts, HashUsers users, TreePosts treePerg, TreePosts treeRes) {
        int typeID;
        long ownerID;
        Post post = new Post();
        typeID = -2;
        ownerID = -2;

        Iterator<Attribute> attributes = startElement.getAttributes();

        while (attributes.hasNext()) {
            Attribute attribute = attributes.next();

            if (attribute.getName().toString().equals("PostTypeId")) {
                typeID = Integer.valueOf(attribute.getValue());

                if (typeID != 1 && typeID != 2) {
                    return;

                } else
                    post.setTypeID(typeID);
            }

            if (attribute.getName().toString().equals("Id")) {
                post.setID(Long.valueOf(attribute.getValue()));
            }

            if (attribute.getName().toString().equals("ParentId")) {
                post.setParentID(Long.valueOf(attribute.getValue()));
            }
            if (attribute.getName().toString().equals("OwnerUserId")) {
                ownerID = Long.valueOf(attribute.getValue());
                post.setOwnerUserID(ownerID);
            }
            if (attribute.getName().toString().equals("Title")) {
                post.setTitle(attribute.getValue());

            }
            if (attribute.getName().toString().equals("Tags")) {
                post.setTags(attribute.getValue());

            }
            if (attribute.getName().toString().equals("Score")) {
                post.setScore(Long.valueOf(attribute.getValue()));

            }
            if (attribute.getName().toString().equals("CreationDate")) {
                LocalDateTime localDateTime = LocalDateTime.parse(attribute.getValue());
                LocalDate localDate = localDateTime.toLocalDate();
                post.setDate(localDate);
            }
            if (attribute.getName().toString().equals("CommentCount")) {
                post.setCommentCount(Integer.valueOf(attribute.getValue()));
            }
        }
        Post auxp;
        if (posts.contemPost(post)) {
            auxp = posts.obtemPost(post.getID());
            post.setRespostas(auxp.getRespostas());
        }

        users.adicionaUserNPost(ownerID);
        users.adicionaPostUserTree(post, ownerID);
        posts.adicionarPost(post);
        if (typeID == 1) {
            treePerg.adicionarPost(post);
        } else if (typeID == 2) {
            posts.adicionaPostResTree(post);

            treeRes.adicionarPost(post);
        }
    }

    /**
     * Método que trata o Parse do ficheiro XML referente aos Users.
     * @param startElement O parâmetro que inidica o início de cada row do ficheiro XML.
     * @param users Estrutura HashUsers.
     */
    private static void parseUsers(StartElement startElement, HashUsers users) {

        User user = new User();

        Iterator<Attribute> attributes = startElement.getAttributes();

        while (attributes.hasNext()) {
            Attribute attribute = attributes.next();

            if (attribute.getName().toString().equals("Id")) {
                user.setID(Long.valueOf(attribute.getValue()));
            }

            if (attribute.getName().toString().equals("DisplayName")) {
                user.setName(attribute.getValue());
            }
            if (attribute.getName().toString().equals("AboutMe")) {
                user.setBio(attribute.getValue());
            }
            if (attribute.getName().toString().equals("Reputation")) {
                user.setReputation(Integer.valueOf(attribute.getValue()));
            }
        }
        users.adicionarUser(user);
    }

    /**
     * Método que trata o Parse do ficheiro XML referente às Tags.
     * @param startElement O parâmetro que inidica o início de cada row do ficheiro XML.
     * @param tags Estrutura HashTags.
     */
    private static void parseTags(StartElement startElement, HashTags tags) {

        Tag tag = new Tag();

        Iterator<Attribute> attributes = startElement.getAttributes();

        while (attributes.hasNext()) {
            Attribute attribute = attributes.next();

            if (attribute.getName().toString().equals("Id")) {
                tag.setID(Long.valueOf(attribute.getValue()));
            }

            if (attribute.getName().toString().equals("TagName")) {
                tag.setName(attribute.getValue());
            }
        }
        tags.adicionarTag(tag);
    }
}
