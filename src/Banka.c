#include <stdlib.h>
#include "Banka.h"
Banka *yenibanka()
{
  Banka *b = (Banka *)malloc(sizeof(Banka));
  b->karzarar = 0;
  b->Sembol = (char *)malloc(sizeof(char) * 4);
  b->sonraki = NULL;
  return b;
}
