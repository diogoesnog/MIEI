#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <parse.h>
#include <date.h>
#include <hashUser.h>
#include <hashTag.h>
#include <interface.h>
//funço que faz parse de do ficheiro posts.xml e atualzia as estrutura TAD community.
void parsePosts (xmlDocPtr doc, xmlNodePtr cur, GHashTable* hashPosts, GHashTable* hashUsers, GTree* TreePerg, GTree* TreeRes) {
    xmlAttr* attribute = cur->properties;
    PostsAtr p = inicializaPostsAtr();
    xmlChar* ID = xmlNodeListGetString(cur->doc, attribute->children, 1);
    xmlChar* value = xmlNodeListGetString(cur->doc, attribute->children, 1);
    int typeID = -1;
    char* ownerid;
    while(attribute){		

        value = xmlNodeListGetString(cur->doc, attribute->children, 1);

        if(!(strcmp((char*)attribute->name,"PostTypeId"))){
        	            p->postTypeId = value; 
                      typeID = atoi((char*)value);
                      if(typeID!=1 && typeID !=2){
                            xmlFree(value); 
                            return;
                      }
        }
        else if(!(strcmp((char*)attribute->name,"Id")))
            p->id = value; 

        else if(!(strcmp((char*)attribute->name,"Title")))
      		 	p->title = value; 


      	else if(!(strcmp((char*)attribute->name,"OwnerUserId"))){
      			p->ownerUserId = value;
      			adicionaUsernPosts(hashUsers,(char*)value);
            ownerid = (char*)value;
      	}
 				else if(!(strcmp((char*)attribute->name,"CreationDate")))
      			     p->creationDate = value;	

        else if(!(strcmp((char*)attribute->name,"Tags")))
                p->tag = value;

        else if(!(strcmp((char*)attribute->name,"Score")))
                p->score = value;

        else if(!(strcmp((char*)attribute->name,"ParentId")))
                p->parentId = value;

        else if(!(strcmp((char*)attribute->name,"CommentCount")))
                p->commentCount = value;

         attribute = attribute->next;
        }

    xmlFree(value);      
    char* key = ((char*) ID);

    gpointer* foundpost= NULL;
    if(g_hash_table_lookup_extended(hashPosts,key,NULL,(gpointer*)&foundpost)){
        PostsAtr fpost= (PostsAtr)foundpost;
        p->postTreeResp = fpost->postTreeResp;
        g_hash_table_replace(hashPosts,key,p);
    }
    else{
        g_hash_table_insert(hashPosts,key,p);
    }
        Date data = chartodata((char*)p->creationDate);
        adicionaUserPosttree(hashUsers,ownerid,p,data);
    
    if(typeID==1){
        gpointer* foundvalue = NULL;
        if(g_tree_lookup_extended(TreePerg,data,NULL,(gpointer*)&foundvalue)){
            PostsAtr post= (PostsAtr)foundvalue;
            post->ndataigual += 1;
            post->datalistperg = g_slist_insert_before(post->datalistperg,post->datalistperg,p);

            } 
           else
              g_tree_insert(TreePerg,data,p);
              


        }
	 else if(typeID == 2) {
       adicionaPostTreeRes(hashPosts,p);
        gpointer* foundvalue = NULL;
        if(g_tree_lookup_extended(TreeRes,data,NULL,(gpointer*)&foundvalue)){
            PostsAtr post= (PostsAtr)foundvalue;
            post->ndataigual += 1;
            post->datalistres = g_slist_insert_before(post->datalistres,post->datalistres,p);
        }
           else
	     g_tree_insert (TreeRes,data,p);
  }


}

//funço que faz parse de do ficheiro users.xml e atualzia as estrutura TAD community.
void parseUsers (xmlDocPtr doc, xmlNodePtr cur, GHashTable* HashUsers) {

  xmlAttr* attribute = cur->properties;
  
  UsersAtr u = inicializaUsersAtr();

  xmlChar* ID = xmlNodeListGetString(cur->doc, attribute->children, 1);
  xmlChar* value = xmlNodeListGetString(cur->doc, attribute->children, 1);
  while(attribute){		

		value = xmlNodeListGetString(cur->doc, attribute->children, 1);
      	if(!(strcmp((char*)attribute->name,"Id")))
      		u->id = value; 
		
		else if(!(strcmp((char*)attribute->name,"DisplayName")))
      			u->displayName = value; 

		else if(!(strcmp((char*)attribute->name,"AboutMe")))
            u->aboutMe = value;

    else if(!(strcmp((char*)attribute->name,"Reputation")))
            u->reputation = value;
          
		
     	attribute = attribute->next;
    }
	xmlFree(value);

         char* key = ((char*) ID);
         g_hash_table_insert(HashUsers,key,u);

}
//funço que faz parse de do ficheiro tags.xml e atualzia as estrutura TAD community.
void parseTags (xmlDocPtr doc, xmlNodePtr cur, GHashTable* hashTags) {

  xmlAttr* attribute = cur->properties;
  xmlChar* ID ;
  tagAtr t = inicializatagAtr();

  xmlChar* value = xmlNodeListGetString(cur->doc, attribute->children, 1);
  while(attribute){   


    value = xmlNodeListGetString(cur->doc, attribute->children, 1);
        if(!(strcmp((char*)attribute->name,"Id")))
          t->id = value; 

    else if(!(strcmp((char*)attribute->name,"TagName"))){
            ID = value;
            t->tagname = value;
          }
          
      attribute = attribute->next;
    }
  xmlFree(value);
         char* key = ((char*) ID);
         g_hash_table_insert(hashTags,key,t);

}

//funçao que faz parse dos ficheiros .xml e atuliza  a estrutura TAD community.
void parseDocs(char *docname, GHashTable* HashPosts, GHashTable* HashUsers, GHashTable* HashTags, GTree* TreePerg, GTree* TreeRes) {

  xmlDocPtr doc;
  xmlNodePtr cur;

  doc = xmlReadFile(docname,NULL,0);
  
  if (doc == NULL) {
    fprintf(stderr,"Document not parsed successfully. \n");
    return;
  }
  cur = xmlDocGetRootElement(doc);
  if (cur == NULL) {
    fprintf(stderr,"Documento vazio\n");
    xmlFreeDoc(doc);
    return;
  }
  

  cur = cur->xmlChildrenNode;
  cur = cur->next;
  

  if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))){

      if(strcmp(docname,"Posts.xml") == 0 ) {
        printf("Parse dos Posts\n"); 
        while (cur != NULL) {
            parsePosts (doc, cur,HashPosts,HashUsers,TreePerg, TreeRes);
            cur = cur->next->next;
        }
      }

      else if(strcmp(docname,"Users.xml") == 0 ) {
        printf("Parse dos Users\n"); 
        while (cur != NULL) {
            parseUsers (doc, cur,HashUsers);
            cur = cur->next->next;
        }
      }

      else if(strcmp(docname,"Tags.xml") == 0 ){
        printf("Parse das Tags\n"); 
        while (cur != NULL) {
            parseTags (doc, cur,HashTags);
            cur = cur->next->next;
        }
      }

    }
  xmlFreeDoc(doc);
  return;
}