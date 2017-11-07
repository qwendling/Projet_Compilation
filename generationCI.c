#include <stdlib.h>
#include "generationCI.h"


quad quad_add(quad q,quad_op op,Symbole s1,Symbole s2,Symbole s3){
  quad new= malloc(sizeof(std_quad));
  new->op=op;
  new->arg1=s1;
  new->arg2=s2;
  new->res=s3;
  new->next=q;
  return q;
}

void quad_free(quad q){
  if(q == NULL)
    return;
  quad_free(q->next);
  free(q);
}
