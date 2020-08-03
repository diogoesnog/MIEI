#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <hashUser.h>
//função que compara o nº de posts de 2 users.
gint my_comparatorNPost(gconstpointer UsersAtr1, gconstpointer UsersAtr2) {
 	UsersAtr u1 = (UsersAtr)UsersAtr1;
	UsersAtr u2 = (UsersAtr)UsersAtr2;
   gint i = u2->nposts - u1->nposts;
 return i;
}
