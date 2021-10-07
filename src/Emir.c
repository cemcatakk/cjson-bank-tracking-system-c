#include <stdlib.h>
#include "Emir.h"
Emir *yeniemir()
{
  Emir *e = (Emir *)malloc(sizeof(Emir));
  e->id = (char *)malloc(sizeof(char) * 40);
  e->Sembol = (char *)malloc(sizeof(char) * 40);
  e->islem = (char *)malloc(sizeof(char) * 40);
  e->adet = 0;
  e->sonraki = NULL;
  return e;
}