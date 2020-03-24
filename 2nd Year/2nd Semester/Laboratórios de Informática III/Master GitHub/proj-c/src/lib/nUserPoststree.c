#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <hashUser.h>
#include <nUserPoststree.h>
//Função que será aplicada a todos os Users de uma hashtable e irá inseri-los numa arvore ordenados pelo seu nº de posts. 
void nUserPoststreeinsert(gpointer key, gpointer value, gpointer data) {
    UsersAtr u = (UsersAtr) value;
    GTree* tree = data;
    gpointer* foundvalue = NULL;
    if(g_tree_lookup_extended(tree,(gconstpointer)u->nposts,NULL,(gpointer*)&foundvalue)){
        UsersAtr user = (UsersAtr) foundvalue;
       user ->npostslist = g_slist_insert_before(user ->npostslist,user ->npostslist,u);
     }
     else
     g_tree_insert(tree,(gpointer)u->nposts,u);
}
//Função que recebe uma hashtable de users e uma arvore e organiza os users da hash numa arvore ordenados pelo seu nº de posts. 
void initnUserPoststree(GHashTable* hashuser, GTree* nUserPoststree){
   g_hash_table_foreach(hashuser,nUserPoststreeinsert,nUserPoststree);
}


//Função que será aplicada a N os elementos (users) lista e vai colocar-los  noutra lista associada á estrutura Info. 
void listGetfirstNUsersaux(gpointer u1, gpointer inf){
	UsersAtr u = (UsersAtr) u1;
	Info info = (Info) inf;
	if(info->N > 0) {
		info->list = g_slist_insert_before(info->list,info->list,u);
		info->N--;
	}
}
//Função que será aplicada a N os elementos (users) de uma arvore e vai colocar-los numa lista associada á estrutura Info. 
int TreeGetfirstNUsersaux(gpointer key, gpointer value, gpointer data){
	Info info = (Info) data;
	UsersAtr u = (UsersAtr) value;

	if(info->N <= 0) return 1;
		info->list = g_slist_insert_before(info->list,info->list,u);
		info->N--;
	if(u->npostslist!=NULL){
		g_slist_foreach(u->npostslist,listGetfirstNUsersaux,info);
  }
	return 0;
}

//Função que recebe uma arvore e uma estrutura Info e coloca os primeiros 10 elementos da arvore numa lista associada à estrutura Info.
void TreeGetfirstNUsers(GTree* tree, Info info){
	g_tree_foreach(tree,TreeGetfirstNUsersaux,info);
}



//Função que dados 2 posts compara as suas datas de criação.
gint my_comparatorQuerry9(gconstpointer da1, gconstpointer da2) {
   PostsAtr p1 = (PostsAtr) da1;
   PostsAtr p2 = (PostsAtr) da2;
   
   Date d1 = chartodata((char*)p1->creationDate);
   Date d2 = chartodata((char*)p2->creationDate);

   if(testaDatamaior(d1,d2)) return -1;
   if(testaDatamenor(d1,d2)) return 1;
   if(testaDataIgual(d1,d2)) return 0;
   return 0;
}


//função que testa se os ids de 2 posts são iguais.
void ListForEachQuerry9(gpointer value, gpointer inf){
    PostsAtr p2 = (PostsAtr) value;
    Info info = inf;
    if(atoi((char*)p2->id) == atoi((char*)info->foundpost->id))
    	info->N = 1;

}
//função que será aplicada a todos os elementos de uma lista tal que dados 2 posts testa se sao resposta um do outro ou se ambos respondem a mesma pergunta.
void ForEachListBothP2(gpointer value, gpointer inf){
    PostsAtr p1 = (PostsAtr) value;
    Info info = inf;
    if(atoi((char*)p1->postTypeId) == 1){
        if(atoi((char*)info->post2->postTypeId) == 2)
            if(atoi((char*)info->post2->parentId) == atoi((char*)p1->id)) {
                info->foundpost = g_hash_table_lookup (info->hashposts,(char*)p1->id);
                g_slist_foreach(info->list,ListForEachQuerry9,info);
                if(!(info->N)){

                	info->list = g_slist_insert_sorted(info->list,info->foundpost,my_comparatorQuerry9);
                }
                else info->N = 0;
              }
    		}
    else if(atoi((char*)p1->postTypeId) == 2){
              if(atoi((char*)info->post2->postTypeId) == 2){
                  if(atoi((char*)info->post2->parentId) == atoi((char*)p1->parentId)){
                  	  info->foundpost = g_hash_table_lookup (info->hashposts,(char*)p1->parentId);
                  	  g_slist_foreach(info->list,ListForEachQuerry9,info);
                	  if(!(info->N)){
                	 		info->list = g_slist_insert_sorted(info->list,info->foundpost,my_comparatorQuerry9);	
                		}
                	  else info->N = 0;	
                   	 }
                  }
              else if(atoi((char*)info->post2->postTypeId) == 1){
                        if(atoi((char*)p1->parentId) == atoi((char*)info->post2->id)){
                  	  		info->foundpost = g_hash_table_lookup (info->hashposts,(char*)info->post2->postTypeId);
                  	  		g_slist_foreach(info->list,ListForEachQuerry9,info);
                	  		if(!(info->N)){
                	 			info->list = g_slist_insert_sorted(info->list,info->foundpost,my_comparatorQuerry9);
                    }
                    else info->N = 0;
    			}
			} 
	   }
	}
//função que será aplicada a todos os elementos de uma arvore tal que dados 2 posts testa se sao resposta um do outro ou se ambos respondem a mesma pergunta.
int ForEachTreeBothP2(gpointer key, gpointer value, gpointer inf){
    PostsAtr p1 = (PostsAtr) value;
    Info info = inf;
        
    if(atoi((char*)p1->postTypeId) == 1){
        if(atoi((char*)info->post2->postTypeId) == 2)
            if(atoi((char*)info->post2->parentId) == atoi((char*)p1->id)) {
                info->foundpost = g_hash_table_lookup (info->hashposts,(char*)p1->id);
                g_slist_foreach(info->list,ListForEachQuerry9,info);
                if(!(info->N)){

                	info->list = g_slist_insert_sorted(info->list,info->foundpost,my_comparatorQuerry9);
                }
                else info->N = 0;
              }
    		}
    else if(atoi((char*)p1->postTypeId) == 2){
              if(atoi((char*)info->post2->postTypeId) == 2){
                  if(atoi((char*)info->post2->parentId) == atoi((char*)p1->parentId)){
                  	  info->foundpost = g_hash_table_lookup(info->hashposts,(char*)p1->parentId);
                  	  g_slist_foreach(info->list,ListForEachQuerry9,info);
                	  if(!(info->N)){
                	 		info->list = g_slist_insert_sorted(info->list,info->foundpost,my_comparatorQuerry9);	
                		}
                	  else info->N = 0;	
                   	 }
                  }
              else if(atoi((char*)info->post2->postTypeId) == 1){
                        if(atoi((char*)p1->parentId) == atoi((char*)info->post2->id)){
                  	  		info->foundpost = g_hash_table_lookup (info->hashposts,(char*)info->post2->postTypeId);
                  	  		g_slist_foreach(info->list,ListForEachQuerry9,info);
                	  		if(!(info->N)){
                	 			info->list = g_slist_insert_sorted(info->list,info->foundpost,my_comparatorQuerry9);
                    }
                    else info->N = 0;
    			}
			} 
	   }

   if(p1->userPostlist!=NULL)
        g_slist_foreach(p1->userPostlist,ForEachListBothP2,info);
  return 0;
}

//Função que  será aplicada a todos os elementos de uma lista de Posts a fim de comparar todos os elementos dessa lista com os elementos de uma arvore.
void ForEachListBothP1(gpointer value, gpointer inf){
    PostsAtr p2 = (PostsAtr) value;
    Info info = inf;
    info->post2 = p2;
    
    g_tree_foreach(info->u1->userPostTree,ForEachTreeBothP2,info);
}

//Função que  será aplicada a todos os elementos de uma arvore de Posts a fim de comparar todos os elementos dessa arvore com os elementos de outra arvore.
int ForEachTreeBothP1aux(gpointer key, gpointer value, gpointer inf){
    PostsAtr p2 = (PostsAtr) value;
    Info info = inf;
    info->post2 = p2;

    g_tree_foreach(info->u1->userPostTree,ForEachTreeBothP2,info);

    if(p2->userPostlist!=NULL)
      g_slist_foreach(p2->userPostlist,ForEachListBothP1,info);
    return 0;
}
//função que dado 2 arvores de posts de 2 users diferentes encontra as perguntas em que ambos participaram.
void forEachTreeBothP1(GTree* userPostTree, Info info){
	g_tree_foreach(userPostTree,ForEachTreeBothP1aux,info); 
}