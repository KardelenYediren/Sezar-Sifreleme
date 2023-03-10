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
/*Kullanýcý seçimi için switch case*/
switch(secim)
{
case '1':
kullanici_olustur(ptr); /*Kullanýcý olustur fonksiyonuna deklare dilmis yeni kullanýcýsý pointer kullanarak cagrýlýyor*/
ana_menu();
break;
case '2':
file_kontrol=dosya_kontrol(); /*Kullanýcý girisi seçilmiþsse dosya varmý yokmu kontrol ediliyor*/
if(file_kontrol==1) /*Eger kontrol degiskeni 1 atanmýssa kontrol basarýlýdýr Degil ise hata vardýr ana menuye dön!*/
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
/*Bilgiler girildikten sonra sifreleme fonksiyonu cagrýlýyor içine klnc aktarýlýyor*/
sezar_sifrele(klnc);
}
void sezar_sifrele(struct kullanici *klnc)
{
kaydirma_sayisi=son_basamak_hesapla(klnc->okulno); /*Kaydýrma sayýsý hesaplanýyor klnc nin okulnumarasýna göre*/
printf("\nKaydirma Sayisi=%d\n",kaydirma_sayisi);



char sifreli_metin[110]={};
int i,ch;
/*Sifrelenecek metin birlestirliyor!*/
strcat(sifreli_metin,klnc->isim);
strcat(sifreli_metin,"."); /*Ýsim ve soy isim arasýna . koydum dosyadan okurken ayýrt etmek için*/
strcat(sifreli_metin,klnc->soyisim);
/*Sezar sifreleme
/*Sifreli metin boyunca bir for dongüsünde her karateri ch degiskenine ata*/
/*ch degiskenini ascii tablosunda kaydirma sayisi kadar kaydir*/
/*Eger ch alfabanin dýsýna tasmýþsa kalan sayý kadar a ya dönüp devam et*/
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
/*Dosya yazdýr fonksiyonu 1 basarýlý demek!*/
int sonuc = dosya_yazdir(sifreli_metin,klnc->okulno);/*Sifrelenmis metini ve okulno yazdýr*/
if(sonuc==1)
{
printf("Dosya yazma islemi basarili");
}
else
printf("Bir hata var dosyaya yazdýrýlamadý!");



}
int dosya_yazdir(char* yazdirilacak_metin,int yazdirilacak_numara)
{
/*Dosya pointeri*/
FILE *dosya;
/*Dosyayý ac eger yoksa olusturur!*/
if((dosya = fopen("sifrelimetin.txt","w")) == NULL)
{
printf("Dosya Bulunamadý!\n");
return -1;
}
else
{
fprintf(dosya,"%s %d",yazdirilacak_metin,yazdirilacak_numara); /*Dosya içerisine yaz */
fclose(dosya); /*Dosyayý Kapat*/
return 1;
}
}
void kullanici_girisi()
{
struct kullanici *yeni; /*Yeni kullanýcý olustur*/
dosya_oku(yeni); /*Dosyayý oku , okunan verileri yeni kullanýcýya ata*/



int cevap,sonuc;
sonuc=en_buyuk_asal_carpan_hesapla(yeni->okulno); /*En büyük asal carpaný hesapla sonuç degiskenine esitle*/



printf("\n\nOgrenci numaranizin en buyuk asal carpani nedir?\n"); scanf("%d",&cevap);
/*Kullanýcýnýn cevabý sonuca esit olana kadar sor*/
while(cevap!=sonuc)
{
printf("\nHatali bir parola girdiniz! Tekrar Deneyiniz\n"); scanf("%d",&cevap);
}
/*Sifreli metini ekrana yazdýr*/
printf("\nSifreli Metin : %s%s",yeni->isim,yeni->soyisim);
/*isim ve soy isimi desifrele*/
sezar_desifrele(yeni->isim);
sezar_desifrele(yeni->soyisim);
/*Son cevabý ekrana yazdýr ana menuye don*/
printf("\n-------------");
printf("\nDesifre Edildi:\n-------------\nIsim:%s\nSoyisim:%s\nNumara:%d",yeni->isim,yeni->soyisim,yeni->okulno);
ana_menu();
}
int dosya_kontrol()
{
/*Dosya varmý yokmu diye kontrol eden fonksiyon
Eger dosya bulunamadýysa -1 eger dosya bulunmussa 1 return ediyor*/
FILE *dosya;
if((dosya = fopen("sifrelimetin.txt","r")) == NULL)
{
printf("Kayýtlý bir dosya bulunamadý! Lütfen yeni kullanýcý olusturun!\n");
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
/*Dosyayý oku*/
if((dosya = fopen("sifrelimetin.txt","r")) == NULL)
{
printf("Dosya okuma sirasinda hata olustu!\n");
return -1;
}
else
{
fscanf(dosya,"%s %d",sifreli_metin,&okunan_numara); /*Okunan verileri ata*/
fclose(dosya); /*Dosyayý kapat*/
klnc->okulno=okunan_numara; /*kullanýcýnýn okul numarasý okunan numaradýr*/
int uzunluk=strlen(sifreli_metin); /*Sifreli metinin uzunlugunu ata*/
for(i=0 ; i < uzunluk; i++)
{
/*uzunluk boyunca ilerle okunan her karakteri okunan degiskenine ata*/
okunan = sifreli_metin[i];
if(okunan == '.') /*Eger okunan . ise kaldýgý yeri nokta degiskenine ata döngüden çýk*/
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
/*Noktayý atlayarak okumaya devam et ayný iþlemi soyisim için yap*/
for(nokta=nokta+1 ; nokta < uzunluk; nokta++)
{
okunan = sifreli_metin[nokta];
klnc->soyisim[i]=okunan;
i++;
}
kaydirma_sayisi=son_basamak_hesapla(klnc->okulno); /* Klnc okul numarasýna göre kaydýrma sayýsýný hesapla */
return 1;
}



}
void sezar_desifrele(char* sifreli_metin)
{
/*Sezar þifreleme fonksiyonunun tersi!
Kaydýrma sayýsý kadar ascii tablosunda geri kaydýr
Eger a dan küçükse z ye git devam et*/
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
/*En büyük asal carpan hesaplayan fonksiyon
verilen sayi degiskenin en büyük asal carpanýný return eder*/
int i, asal_carpan = -1;
while(sayi % 2 == 0) /*Sayi 2 ye tam bölünürken bölerek ilerle*/
{
asal_carpan = 2;
sayi = sayi/2;
}
for(i = 3; i <= sqrt(sayi); i=i+2) /*i 3ten baþlayýp ikiþer artýcak asal tek sayýlarla ilerlemek için*/
{
while(sayi % i == 0)
{
asal_carpan = i; /*Sayiyi asal bölerek ilerle kalaný 0 oldukça*/
sayi = sayi/i;
}
}
if(sayi > 2) /*kalan sayi ikiden büyükse asal çarpan kalan sayidir*/
{
asal_carpan = sayi;
}
return asal_carpan;
}
int son_basamak_hesapla(int sayi)
{
/*Son basamak hesaplayan fonksiyon*/
int kalan = sayi % 10; /*Kalaný verilen sayinin son basamagýna esitle*/
while(kalan == 0) /*Kalan 0 iken bir basamak sil ve kalan son basamaga bak*/
{
sayi = sayi/10;
kalan = sayi%10;
}
/*Kalan 0 degilse return et */
return kalan;
}
