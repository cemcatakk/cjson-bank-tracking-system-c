#include <stdlib.h>
#include "Portfoy.h"

Portfoy *yeniportfoy()
{
  Portfoy *p = (Portfoy *)malloc(sizeof(Portfoy));
  p->id = (char *)malloc(sizeof(char) * 40);
  p->Sembol = (char *)malloc(sizeof(char) * 40);
  p->adet = 0;
  p->sonraki = NULL;
  return p;
}

