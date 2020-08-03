#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <libxml/parser.h>

typedef struct tagAtr{
	xmlChar* id; 
  	GSList* samecountlist;
  	xmlChar* count;
  	xmlChar* tagname;
  	int nused;
  	GSList* tagsamecountlist;
}* tagAtr;

tagAtr inicializatagAtr();