#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <interface.h>
/*
Data chartoDataV2 (char* a){
    char aux[30]; //2010-09-13T19:17:17.917
    strcpy(aux,a);
      int year = atoi(strtok(aux,"-"));
    int month = atoi(strtok(NULL, "-"));
    int day = atoi(strtok(NULL, "T"));
    int hour = atoi(strtok(NULL, ":"));
    int min = atoi(strtok(NULL, ":"));
    float sec = atof(strtok(NULL, "\0"));
    Data data = createDataV2(year,month,day,hour,min,sec);
    return data;
}*/



int main (int argc, char **argv) {
/*

char aux[100] ;

char* p;
strcpy(aux,ola);
p = strtok(aux, ">");
printf("%s\n",p+1 );
p = strtok(NULL, ">");
printf("%s\n",p+1 );

*/


TAD_community com = init();
  
 load(com,argv[1]);


 //info_from_post(com,796430);
 //printf("%s\n",kapa );
     /*  
       info3 infoss = (info3) malloc(sizeof(struct info3));
       infoss->count = 0;
       printf("YAAA\n");
     // g_tree_foreach(h->TreeRes,ola1,infoss);
      printf("YA\n");
      printf("yooo %d\n",infoss->count );
/*
 guint k = g_hash_table_size(h->androidPosts);
 guint kg = g_hash_table_size(h->androidUsers);
 info_from_post(h,2);
 top_most_active(h,4);

 total_posts(h,oli,olis);
 int li = g_list_length (h->UsersPostslist);*/
 Date oli = createDate(01,07,2016);
 Date olis = createDate(31,07,2018);

 Date oli1 = createDate(01,01,2014);
 Date olis1 = createDate(31,12,2014);
     printf("dia: %d mes: %d ano %d\n",get_day(olis1),get_month(olis1),get_year(olis1));
 Date q4i = createDate(01,03,2013);
 Date q4f = createDate(31,03,2013);
  Date q6i = createDate(01,11,2015);
 Date q6f = createDate(30,11,2015);
 Date q7i = createDate(01,8,2014);
Date q7f = createDate(11,8,2014);
Date q11i = createDate(01,11,2013);
Date q11f = createDate(30,11,2013);


 info_from_post(com,801049);
 //info_from_post(com,796430);
  //top_most_active(com,10);
 top_most_active(com,100);
 //total_posts(com,oli,olis);
  total_posts(com,oli1,olis1);
    //questions_with_tag(com,"package-management",oli,olis);
   questions_with_tag(com,"nautilus",q4i,q4f);
  //get_user_info(com,15811);
   get_user_info(com,449);
 //most_voted_answers(com,5,q6i,q6f);
 most_voted_answers(com,50,oli1,olis1);
 //most_answered_questions(com,100,q7i,q7f);
 most_answered_questions(com,100,oli1,olis1);
  //contains_word(com,"kde",15) ;
  contains_word(com,"glib",10) ;
   //both_participated(com,87,5691,10);
   both_participated(com,253,455,5);
  //better_answer(com,30334); 
   // better_answer(com,5942);
 most_used_best_rep(com,5,q11i,q11f);

clean(com);
 //ola(com,1);
 //both_participated(com,87,5691,10);
//top_most_active(com,10);
  
 //questions_with_tag(com,"<package-management>",oli,olis);

//most_answered_questions(com,100,oli,olis);

 //top_most_active(h,100);
 //total_posts(h,oli,olis);
/*

 UsersAtr uh = g_hash_table_lookup(h->androidUsers,"1");
 PostsAtr post =  g_hash_table_lookup(h->androidPosts,"2");
  PostsAtr posts =  g_hash_table_lookup(h->androidPosts,"144530");
 UsersAtr ul = g_list_nth_data (h->UsersPostslist,1);
//144530
 //UsersAtr uh = g_hash_table_lookup(h->androidUsers,"1");
 //UsersAtr ul = g_list_nth_data (h->UsersPostslist,1);

    int lop = g_tree_nnodes (h->TreeRes);
      int lopa = g_tree_nnodes (h->TreePer);
      printf("%s\n",(char*)post->creationDate );
      Date b = chartodata((char*) post->creationDate);

      PostsAtr ki = g_tree_lookup (h->TreePer,b);
      Date c = chartodata((char*) ki->creationDate);
      printf("day %d, month %d year%d , repedifo %d \n",get_day(c),get_month(c),get_year(c), ki->ndataigual);
      printf("numro de datas %d\n",ki->ndataigual );
      //printf(" mes %d ano %d hora %d\n",year,month,day);
      printf("tem %d rtespostas\n",post->nrespostas );
      if(g_tree_lookup_extended(h->TreePer,b,NULL,NULL)) printf("encontrouuuuuu\n"); else printf("FODEUUU\n");
      printf("%d joker23\n",joker23);

 //     printf("%d olla %d res : %d\n",info->i,joker,joker2 ); 
printf("aqui esta %d  posts e %d Users e uma lista com %d elementos, ja agora arvore Res com :%d e Arvore Per : %d\n",k,kg,li,lop,lopa );
printf("HASH NAME%d\n LIST NAME %d", uh->nposts, ul->nposts);
return 0;*/
}