#include <stdlib.h>
#include "Hisse.h"
Hisse *yenihisse()
{
  Hisse *h = (Hisse *)malloc(sizeof(Hisse));
  h->id = (char *)malloc(sizeof(char) * 40);
  h->Sembol = (char *)malloc(sizeof(char) * 40);
  h->ad = (char *)malloc(sizeof(char) * 40);
  h->fiyat = 0;
  h->sonraki = NULL;
  return h;
}
