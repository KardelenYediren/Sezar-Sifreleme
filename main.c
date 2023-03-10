#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



struct kullanici
{
char isim[50];
char soyisim[50];
int okulno;
};



void ana_menu();
void kullanici_olustur(struct kullanici *);
void kullanici_girisi();
void sezar_sifrele(struct kullanici *);
void sezar_desifrele(char* sifreli_metin);



int asal_carpan_hesapla(int hesaplanacak);
int dosya_yazdir(char* yazdirilacak_metin,int yazdirilacak_numara);
int dosya_kontrol();
int dosya_oku(struct kullanici *);
int en_buyuk_asal_carpan_hesapla(int sayi);
int son_basamak_hesapla(int sayi);



int kaydirma_sayisi = 3; /* Kaydirma sayisi degiskeni GLOBAL Degisken*/



int main()
{
ana_menu();
return 0;
}
void ana_menu()
{
struct kullanici yeni, *ptr=&yeni; /* Bos kullanici deklare ediliyor*/
int file_kontrol;
char secim;
printf("\n-------------\n");
printf("ANA MENU\n\n");
printf("1 - Yeni Kullanici Olustur\n");
printf("2 - Kullanici Girisi\n");
printf("\nSeciminiz(1/2) : "); scanf("%s",&secim);
/*Kullan�c� se�imi i�in switch case*/
switch(secim)
{
case '1':
kullanici_olustur(ptr); /*Kullan�c� olustur fonksiyonuna deklare dilmis yeni kullan�c�s� pointer kullanarak cagr�l�yor*/
ana_menu();
break;
case '2':
file_kontrol=dosya_kontrol(); /*Kullan�c� girisi se�ilmi�sse dosya varm� yokmu kontrol ediliyor*/
if(file_kontrol==1) /*Eger kontrol degiskeni 1 atanm�ssa kontrol basar�l�d�r Degil ise hata vard�r ana menuye d�n!*/
kullanici_girisi();
else
ana_menu();
break;
default:
printf("\nHatali Giris ! Lutfen tekrar deneyiniz\n\n");
ana_menu();
}
}
void kullanici_olustur(struct kullanici *klnc)
{
/*Kullanici bilgileri girilen fonksiyon klnc pointeri ile*/
printf("\nIsim giriniz:"); scanf("%s",&klnc->isim);
printf("\nSoyisim giriniz:"); scanf("%s",&klnc->soyisim);
printf("\nOkulno giriniz :"); scanf("%d",&klnc->okulno);
while(klnc->okulno <= 0)
{
printf("Okul no 0 dan kucuk olamaz!\nOkulno giriniz:"); scanf("%d",&klnc->okulno);
}
/*Bilgiler girildikten sonra sifreleme fonksiyonu cagr�l�yor i�ine klnc aktar�l�yor*/
sezar_sifrele(klnc);
}
void sezar_sifrele(struct kullanici *klnc)
{
kaydirma_sayisi=son_basamak_hesapla(klnc->okulno); /*Kayd�rma say�s� hesaplan�yor klnc nin okulnumaras�na g�re*/
printf("\nKaydirma Sayisi=%d\n",kaydirma_sayisi);



char sifreli_metin[110]={};
int i,ch;
/*Sifrelenecek metin birlestirliyor!*/
strcat(sifreli_metin,klnc->isim);
strcat(sifreli_metin,"."); /*�sim ve soy isim aras�na . koydum dosyadan okurken ay�rt etmek i�in*/
strcat(sifreli_metin,klnc->soyisim);
/*Sezar sifreleme
/*Sifreli metin boyunca bir for dong�s�nde her karateri ch degiskenine ata*/
/*ch degiskenini ascii tablosunda kaydirma sayisi kadar kaydir*/
/*Eger ch alfabanin d�s�na tasm��sa kalan say� kadar a ya d�n�p devam et*/
for(i = 0; sifreli_metin[i] != '\0'; ++i)
{
ch = sifreli_metin[i];
if(ch >= 'a' && ch <= 'z')
{
ch = ch + kaydirma_sayisi;
if(ch > 'z')
{
ch = ch - 'z' + 'a' - 1;
}
sifreli_metin[i] = ch;
}
else if(ch >= 'A' && ch <= 'Z')
{
ch = ch + kaydirma_sayisi;
if(ch > 'Z')
{
ch = ch - 'Z' + 'A' - 1;
}
sifreli_metin[i] = ch;
}
}
/*Dosya yazd�r fonksiyonu 1 basar�l� demek!*/
int sonuc = dosya_yazdir(sifreli_metin,klnc->okulno);/*Sifrelenmis metini ve okulno yazd�r*/
if(sonuc==1)
{
printf("Dosya yazma islemi basarili");
}
else
printf("Bir hata var dosyaya yazd�r�lamad�!");



}
int dosya_yazdir(char* yazdirilacak_metin,int yazdirilacak_numara)
{
/*Dosya pointeri*/
FILE *dosya;
/*Dosyay� ac eger yoksa olusturur!*/
if((dosya = fopen("sifrelimetin.txt","w")) == NULL)
{
printf("Dosya Bulunamad�!\n");
return -1;
}
else
{
fprintf(dosya,"%s %d",yazdirilacak_metin,yazdirilacak_numara); /*Dosya i�erisine yaz */
fclose(dosya); /*Dosyay� Kapat*/
return 1;
}
}
void kullanici_girisi()
{
struct kullanici *yeni; /*Yeni kullan�c� olustur*/
dosya_oku(yeni); /*Dosyay� oku , okunan verileri yeni kullan�c�ya ata*/



int cevap,sonuc;
sonuc=en_buyuk_asal_carpan_hesapla(yeni->okulno); /*En b�y�k asal carpan� hesapla sonu� degiskenine esitle*/



printf("\n\nOgrenci numaranizin en buyuk asal carpani nedir?\n"); scanf("%d",&cevap);
/*Kullan�c�n�n cevab� sonuca esit olana kadar sor*/
while(cevap!=sonuc)
{
printf("\nHatali bir parola girdiniz! Tekrar Deneyiniz\n"); scanf("%d",&cevap);
}
/*Sifreli metini ekrana yazd�r*/
printf("\nSifreli Metin : %s%s",yeni->isim,yeni->soyisim);
/*isim ve soy isimi desifrele*/
sezar_desifrele(yeni->isim);
sezar_desifrele(yeni->soyisim);
/*Son cevab� ekrana yazd�r ana menuye don*/
printf("\n-------------");
printf("\nDesifre Edildi:\n-------------\nIsim:%s\nSoyisim:%s\nNumara:%d",yeni->isim,yeni->soyisim,yeni->okulno);
ana_menu();
}
int dosya_kontrol()
{
/*Dosya varm� yokmu diye kontrol eden fonksiyon
Eger dosya bulunamad�ysa -1 eger dosya bulunmussa 1 return ediyor*/
FILE *dosya;
if((dosya = fopen("sifrelimetin.txt","r")) == NULL)
{
printf("Kay�tl� bir dosya bulunamad�! L�tfen yeni kullan�c� olusturun!\n");
return -1;
}
else
{
fclose(dosya);
return 1;
}
}
int dosya_oku(struct kullanici *klnc)
{
/*isim ve soyisime bos karater ata*/
strcpy(klnc->isim,"");
strcpy(klnc->soyisim,"");



FILE *dosya;
int i,nokta;
char sifreli_metin[110],okunan;
int okunan_numara;
/*Dosyay� oku*/
if((dosya = fopen("sifrelimetin.txt","r")) == NULL)
{
printf("Dosya okuma sirasinda hata olustu!\n");
return -1;
}
else
{
fscanf(dosya,"%s %d",sifreli_metin,&okunan_numara); /*Okunan verileri ata*/
fclose(dosya); /*Dosyay� kapat*/
klnc->okulno=okunan_numara; /*kullan�c�n�n okul numaras� okunan numarad�r*/
int uzunluk=strlen(sifreli_metin); /*Sifreli metinin uzunlugunu ata*/
for(i=0 ; i < uzunluk; i++)
{
/*uzunluk boyunca ilerle okunan her karakteri okunan degiskenine ata*/
okunan = sifreli_metin[i];
if(okunan == '.') /*Eger okunan . ise kald�g� yeri nokta degiskenine ata d�ng�den ��k*/
{
nokta=i;
break;
}
else
{
klnc->isim[i]=okunan; /*Okunan karakteri klnc nin isimine ata*/
}
}
i=0;
/*Noktay� atlayarak okumaya devam et ayn� i�lemi soyisim i�in yap*/
for(nokta=nokta+1 ; nokta < uzunluk; nokta++)
{
okunan = sifreli_metin[nokta];
klnc->soyisim[i]=okunan;
i++;
}
kaydirma_sayisi=son_basamak_hesapla(klnc->okulno); /* Klnc okul numaras�na g�re kayd�rma say�s�n� hesapla */
return 1;
}



}
void sezar_desifrele(char* sifreli_metin)
{
/*Sezar �ifreleme fonksiyonunun tersi!
Kayd�rma say�s� kadar ascii tablosunda geri kayd�r
Eger a dan k���kse z ye git devam et*/
int i,ch;
for(i = 0; sifreli_metin[i] != '\0'; ++i)
{
ch = sifreli_metin[i];
if(ch >= 'a' && ch <= 'z')
{
ch = ch - kaydirma_sayisi;
if(ch < 'a')
{
ch = ch + 'z' - 'a' + 1;
}
sifreli_metin[i] = ch;
}
else if(ch >= 'A' && ch <= 'Z')
{
ch = ch - kaydirma_sayisi;
if(ch < 'A')
{
ch = ch + 'Z' - 'A' + 1;
}
sifreli_metin[i] = ch;
}
}
}
int en_buyuk_asal_carpan_hesapla(int sayi)
{
/*En b�y�k asal carpan hesaplayan fonksiyon
verilen sayi degiskenin en b�y�k asal carpan�n� return eder*/
int i, asal_carpan = -1;
while(sayi % 2 == 0) /*Sayi 2 ye tam b�l�n�rken b�lerek ilerle*/
{
asal_carpan = 2;
sayi = sayi/2;
}
for(i = 3; i <= sqrt(sayi); i=i+2) /*i 3ten ba�lay�p iki�er art�cak asal tek say�larla ilerlemek i�in*/
{
while(sayi % i == 0)
{
asal_carpan = i; /*Sayiyi asal b�lerek ilerle kalan� 0 olduk�a*/
sayi = sayi/i;
}
}
if(sayi > 2) /*kalan sayi ikiden b�y�kse asal �arpan kalan sayidir*/
{
asal_carpan = sayi;
}
return asal_carpan;
}
int son_basamak_hesapla(int sayi)
{
/*Son basamak hesaplayan fonksiyon*/
int kalan = sayi % 10; /*Kalan� verilen sayinin son basamag�na esitle*/
while(kalan == 0) /*Kalan 0 iken bir basamak sil ve kalan son basamaga bak*/
{
sayi = sayi/10;
kalan = sayi%10;
}
/*Kalan 0 degilse return et */
return kalan;
}
