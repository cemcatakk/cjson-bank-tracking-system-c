#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "Banka.c"
#include "Emir.c"
#include "Hisse.c"
#include "Portfoy.c"
#define UZUNLUK 40

char *dosyadanJSON(char konum[])
{
  char *metin = (char *)malloc(sizeof(char) * (10000));
  FILE *fp = fopen(konum, "r");
  int i = 0;
  while (!feof(fp))
  {
    fscanf(fp, "%c", &metin[i++]);
  }
  fclose(fp);
  return metin;
}

Emir *EmirListesiGetir(char konum[])
{
  char *json = dosyadanJSON(konum);
  cJSON *json_gecici = cJSON_Parse(json);
  cJSON *emirJson = json_gecici->child->child;
  Emir *listebasi = NULL;
  Emir *last = NULL;
  while (emirJson != NULL)
  {
    Emir *yeniEmir = yeniemir();
    cJSON *emir = cJSON_GetArrayItem(emirJson, 0);
    strcpy(yeniEmir->id, emir->valuestring);
    emir = cJSON_GetArrayItem(emirJson, 1);
    strcpy(yeniEmir->Sembol, emir->valuestring);
    emir = cJSON_GetArrayItem(emirJson, 2);
    strcpy(yeniEmir->islem, emir->valuestring);
    emir = cJSON_GetArrayItem(emirJson, 3);
    yeniEmir->adet = emir->valueint;
    yeniEmir->sonraki = listebasi;
    listebasi = yeniEmir;
    emirJson = emirJson->next;
  }
  return listebasi;
}

Portfoy *PortfoyListesiGetir(char konum[])
{
  char *json = dosyadanJSON(konum);
  cJSON *portfoyJson = cJSON_Parse(json);
  portfoyJson = portfoyJson->child->child;
  Portfoy *listebasi = NULL;
  while (portfoyJson != NULL)
  {
    Portfoy *portfoyListe = yeniportfoy();
    cJSON *portfoy = cJSON_GetArrayItem(portfoyJson, 0);
    strcpy(portfoyListe->id, portfoy->valuestring);
    portfoy = cJSON_GetArrayItem(portfoyJson, 1);
    strcpy(portfoyListe->Sembol, portfoy->valuestring);
    portfoy = cJSON_GetArrayItem(portfoyJson, 2);
    portfoyListe->maliyet = portfoy->valuedouble;
    portfoy = cJSON_GetArrayItem(portfoyJson, 3);
    portfoyListe->adet = portfoy->valueint;
    portfoyListe->sonraki = listebasi;
    listebasi = portfoyListe;
    portfoyJson = portfoyJson->next;
  }
  return listebasi;
}

Hisse *HisseListesiGetir(char konum[])
{
  char *json = dosyadanJSON(konum);
  cJSON *hisseJson = cJSON_Parse(json);
  hisseJson = hisseJson->child->child;
  Hisse *listebasi = NULL;
  while (hisseJson != NULL)
  {
    Hisse *hisseListe = yenihisse();
    cJSON *hisse = cJSON_GetArrayItem(hisseJson, 0);
    strcpy(hisseListe->id, hisse->valuestring);
    hisse = cJSON_GetArrayItem(hisseJson, 1);
    strcpy(hisseListe->Sembol, hisse->valuestring);
    hisse = cJSON_GetArrayItem(hisseJson, 2);
    strcpy(hisseListe->ad, hisse->valuestring);
    hisse = cJSON_GetArrayItem(hisseJson, 3);
    hisseListe->fiyat = hisse->valuedouble;
    hisseListe->sonraki = listebasi;
    listebasi = hisseListe;
    hisseJson = hisseJson->next;
  }
  return listebasi;
}
Portfoy *PortfoyGetir(Portfoy *portfoyListe, char *Sembol)
{
  Portfoy *gecici = portfoyListe;
  while (gecici != NULL)
  {
    if (strcmp(gecici->Sembol, Sembol) == 0)
    {
      return gecici;
    }
    gecici = gecici->sonraki;
  }
  return NULL;
}
Hisse *HisseGetir(Hisse *hisseListe, char *Sembol)
{
  Hisse *gecici = hisseListe;
  while (gecici != NULL)
  {
    if (strcmp(gecici->Sembol, Sembol) == 0)
    {
      return gecici;
    }
    gecici = gecici->sonraki;
  }
  return NULL;
}
Portfoy *PortfoyTemizle(Portfoy *portfoyListe)
{
  Portfoy *listebasi = portfoyListe;
  while (listebasi != NULL)
  {
    Portfoy *gecici = listebasi, *onceki;
    while (gecici != NULL && gecici->adet != 0)
    {
      onceki = gecici;
      gecici = gecici->sonraki;
    }
    if (gecici == NULL)
      return portfoyListe;
    onceki->sonraki = gecici->sonraki;

    listebasi = listebasi->sonraki;
  }
  return portfoyListe;
}
Banka *BankaGetir(char *Sembol, Banka *bankaListe)
{
  Banka *gecici = bankaListe;
  while (gecici != NULL)
  {
    if (strcmp(gecici->Sembol, Sembol) == 0)
    {
      return gecici;
    }
    gecici = gecici->sonraki;
  }
  return NULL;
}
Banka *IslemeKoy(Emir *emirListe, Hisse *hisseListe, Portfoy *portfoyListe)
{
  Banka *listebasi = NULL;
  int i, j = 0, eklenecekmi = 0;
  Emir *gecici = emirListe;
  while (gecici != NULL)
  {
    eklenecekmi = 0;
    Hisse *guncelHisse = HisseGetir(hisseListe, gecici->Sembol);
    Portfoy *secilenPortfoy = PortfoyGetir(portfoyListe, gecici->Sembol);
    if (strcmp(gecici->islem, "SATIS") == 0)
    {
      Banka *banka = BankaGetir(gecici->Sembol, listebasi);
      if (banka == NULL)
      {
        banka = yenibanka();
        strcpy(banka->Sembol, gecici->Sembol);
        banka->sonraki = listebasi;
        listebasi = banka;
      }
      float guncelFiyat, maliyet, karzarar;
      if (secilenPortfoy->adet >= gecici->adet)
      {
        guncelFiyat = gecici->adet * guncelHisse->fiyat;
        maliyet = gecici->adet * secilenPortfoy->maliyet;
        karzarar = guncelFiyat - maliyet;
        secilenPortfoy->adet -= gecici->adet;
      }
      else
      {
        guncelFiyat = secilenPortfoy->adet * guncelHisse->fiyat;
        maliyet = secilenPortfoy->adet * secilenPortfoy->maliyet;
        karzarar = guncelFiyat - maliyet;
        secilenPortfoy->adet = 0;
      }
      banka->karzarar += karzarar;
    }
    else
    {
      if (secilenPortfoy == NULL)
      {
        secilenPortfoy = yeniportfoy();
        strcpy(secilenPortfoy->Sembol, guncelHisse->Sembol);
        eklenecekmi = 1;
      }
      float guncelFiyat = gecici->adet * guncelHisse->fiyat;
      float maliyet = secilenPortfoy->adet * secilenPortfoy->maliyet;
      secilenPortfoy->adet += gecici->adet;
      float yeniMaliyet = (guncelFiyat + maliyet) / secilenPortfoy->adet;
      secilenPortfoy->maliyet = yeniMaliyet;
      if (eklenecekmi == 1)
      {
        Portfoy *json_gecici = portfoyListe;
        while (json_gecici->sonraki != NULL)
        {
          json_gecici = json_gecici->sonraki;
        }
        json_gecici->sonraki = secilenPortfoy;
      }
    }
    gecici = gecici->sonraki;
  }
  portfoyListe = PortfoyTemizle(portfoyListe);
  return listebasi;
}
int main(int argc, char **argv)
{
  char hisseDosya[] = "./doc/hisseler.json";
  Hisse *hisseListe = HisseListesiGetir(hisseDosya);
  char emirDosya[] = "./doc/emirler.json";
  Emir *emirListe = EmirListesiGetir(emirDosya);
  char portfoyDosya[] = "./doc/portfoy.json";
  Portfoy *portfoyListe = PortfoyListesiGetir(portfoyDosya);
  Banka *bankaListe = IslemeKoy(emirListe, hisseListe, portfoyListe);
  printf("Satislar Kar/Zarar:\n");
  float toplam = 0;
  while (bankaListe != NULL)
  {
    printf("%s : %.2f TL ", bankaListe->Sembol, bankaListe->karzarar);
    if (bankaListe->karzarar > 0)
    {
      printf("Kar\n");
    }
    else
    {
      printf("Zarar\n");
    }
    toplam += bankaListe->karzarar;
    bankaListe = bankaListe->sonraki;
  }
  char smbl = '+';
  if (toplam < 0)
  {
    smbl = '-';
  }
  printf("Toplam Kar-zarar: %c %.1f TL\n\n", smbl, toplam);

  printf("Guncel Portfoy:\n");
  Portfoy *gecici = portfoyListe;
  while (gecici != NULL)
  {
    printf("Hisse: %s\nMiktar:%d\nMaliyet: %.2f TL\n---------------\n", gecici->Sembol, gecici->adet, gecici->maliyet);
    gecici = gecici->sonraki;
  }
}
