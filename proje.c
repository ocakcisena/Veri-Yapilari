#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SONSUZ 10000
struct actor{
	char firstname[50];
	char lastname[50];
	int kbnum;	//kenar agirligi
};
struct movie{
	char name[100];
	char year[8];
	struct actor actor[100];
	int kbnum;		//kenar agirligi
};
struct actornode{
	struct actor* data;
	struct actornode* next;
};
struct movienode{
	struct movie* data;
	struct movienode* next;
};
struct movienode* firstm=NULL;
struct movienode* lastm=NULL;
struct actornode* firsta=NULL;
struct actornode* lasta=NULL;
struct movienode* mq_enqueue(struct movie*);
struct actornode* aq_enqueue(struct actor*);
struct actornode* aq_dequeue();
struct movienode* mq_dequeue();
struct movie* breadthfirst(struct movie*,int);
void print(char* , char* , struct movie* , int );


struct movienode* mq_enqueue(struct movie* x){	//moviequeue_enqueue parametre olarak aldigi bir movie yi queueya ekler ve movienode tipinde sonuc dondurur.
	struct movienode* newNode= (struct movienode*)malloc(sizeof(struct movienode));	//yer actik
	newNode->data=x;	//filmi newNode un datasýna ekledik
	newNode->next=NULL;		//newnode un nexti NULL olacak
	if(firstm==NULL){	//ilk eleman icin  (queuenin first u null yani eklenen,ilk eleman ise)
		firstm=newNode;	//firstm ve lastm newnode a esit olacak
		lastm=newNode;
	}else{	//queuenin devami icin yani ilk eleman degilse
		lastm->next=newNode;	//lastm ve lastm in nextini newNode yaptýk
		lastm=newNode;
	}
	return firstm;	//firstm i dondurmeliyiz queue daki ilk eleman FIFO
}

struct actornode* aq_enqueue(struct actor* x){	//actorqueue_enqueue parametre olarak aldigi bir aktoru queueya ekler ve actornode tipinde sonuc dondurur.
	struct actornode* newNode= (struct actornode*)malloc(sizeof(struct actornode));	//yer actik
	newNode->data=x;	//filmi newNode un datasýna ekledik
	newNode->next=NULL;		//newnode un nexti NULL olacak
	if(firsta==NULL){	//ilk eleman icin  (queuenin first u null yani eklenen,ilk eleman ise)
		firsta=newNode;	//firstm ve lastm newnode a esit olacak
		lasta=newNode;
	}else{	//queuenin devami icin yani ilk eleman degilse
		lasta->next=newNode;	//lastm ve lastm in nextini newNode yaptýk
		lasta=newNode;
	}
	return firsta;	//firsta yi dondurmeliyiz queue daki ilk eleman FIFO
}

struct actornode* aq_dequeue(){	//actorqueue_dequeue bir aktoru queue dan cikarir ve cikardigi actornode tipindeki elemani return eder.
	if(firsta==NULL){	//queueda hic eleman kalmadi... queue bos uyarisi versin
		printf("\n Your queue is already empty");
		return NULL;
	}
	else if(firsta->next==NULL){	//son elemana gelmisiz
		firsta=NULL;
		lasta=NULL; //first ve last null oluyor yani queue bosaliyor
		return NULL;
	}else{	//first u ve first unun nexti null a esit olmadikca (queue hala dolu ise) 
		firsta=firsta->next;	//first u ilerletiyorum
		return firsta;
	}
}


struct movienode* mq_dequeue(){	//moviequeue_dequeue bir movieyi queuedan cikarir ve cikardigi movienode tipindeki elemani return eder.
	if(firstm==NULL){	//queueda hic eleman kalmadi... queue bos uyarisi versin
		printf("\n Your queue is already empty");
		return NULL;
	}
	else if(firstm->next==NULL){	//son elemana gelmisiz
		firstm=NULL;	//first ve last null oluyor yani queue bosaliyor
		lastm=NULL;
		return NULL;
	}else{	//first u ve first unun nexti null a esit olmadikca (queue hala dolu ise)
		firstm=firstm->next;	//first u ilerletiyorum
		return firstm;
	}
}

struct movie* breadthfirst(struct movie* filmdizisi,int sayac){ // fonksiyon filmdizisi ve bu filmdizisinin boyutunu alarak bfs enine arama algoritmasi uygular.
	int i,j,isEmpty,h=0,bacon,count; //i film için, j aktör için, isempty bos/dolu kontrolu icin, h da hesaplanmisfilmdizisinin iterasyonu için
									//bacon, actorqueuedeki kbnumlarýný kontrol etmek, count ise kac tane o aktordenoldugunu saymak icin
	struct movie* hesaplanmisfilmdizisi=(struct movie*)malloc(sayac*sizeof(struct movie));//kb numaralarine gore siraladigimiz queue elemanlarýný kaybetmemek icin
	struct movienode* iter;	//iterasyon icin
	struct actornode* actorqueue=(struct actornode*)malloc(sizeof(struct actornode));
	actorqueue->data=(struct actor*)malloc(sizeof(struct actor));
	strcpy(actorqueue->data->firstname,"Kevin");
	strcpy(actorqueue->data->lastname,"Bacon");
	actorqueue->data->kbnum=0;	//kevin baconýn kevin bacon sayisi 0
	firsta=actorqueue;
	lasta=actorqueue;
	struct movienode* moviequeue=(struct movienode*)malloc(sizeof(struct movienode));
	moviequeue->data=(struct movie*)malloc(sizeof(struct movie));
	bacon = 0;
	count = 0;
	isEmpty=0;	//empty bos demek. bos=0 dolu demek yani:
	while(isEmpty==0){ //dolu oldugu surece:
		for(i=0;i<sayac;i++){	//film sayisi  kadar donuyor
			if(filmdizisi[i].kbnum==SONSUZ){	//tum film dizisi sonsuzdu basta
				j=0;
				while(filmdizisi[i].actor[j].firstname[0]!=0){	//filmdizisinin actoru oldugu surece(actorun adinin ilk harfine bakiyoruz)
					if(strcmp(actorqueue->data->firstname,filmdizisi[i].actor[j].firstname)==0 && 	
						strcmp(actorqueue->data->lastname,filmdizisi[i].actor[j].lastname)==0){ //filmdizisindeki aktorun adý/soyadi queuedaki ada/soyada esit mi
							filmdizisi[i].kbnum=actorqueue->data->kbnum+1;	//kevin bacon numarasini 1 artiriyoruz(0+1)
							moviequeue = mq_enqueue(&filmdizisi[i]);	//oyuncunun oynadigi diziyi queue ya ekliyoruz.
							//printf("\n%s filmi eklendi. Bacon : %d\n", filmdizisi[i].name, filmdizisi[i].kbnum);
							
						}
					j++;	//actor iterasyonunu ilerletiyoruz
				}
			}
		}
		iter=moviequeue;	//movie queuesunu dolasacagiz iter ile
		while(iter!=NULL){	//queue bosalmadigi surece
			//printf("%s filmine bakiliyor\n", iter->data->name);
			j=0;
			while(iter->data->actor[j].firstname[0]!=0){
				if(strcmp(iter->data->actor[j].firstname,actorqueue->data->firstname)!=0 || 
					strcmp(iter->data->actor[j].lastname,actorqueue->data->lastname)!=0){//moviequeuedaki aktorun adý/soyadi queuedaki ada/soyada esit mi
						iter->data->actor[j].kbnum=iter->data->kbnum;	//queuedeki aktorun kbnumarasý moviequeuedaki filmin kbsine esit
						actorqueue = aq_enqueue(&iter->data->actor[j]);//moviequeuedaki filmin aktorunu actorqueueya ekliyoruz
						//printf("%s %s aktoru eklendi. Bacon : %d\n", iter->data->actor[j].firstname, iter->data->actor[j].lastname,
						//												iter->data->actor[j].kbnum);
					}
				j++;	//actor iterasyonunu ilerletiyoruz
			}
			//printf("%s filmi cikarildi\n", moviequeue->data->name);	//cikaracagimz filmin adini basiyoruz ekrana
			hesaplanmisfilmdizisi[h]=*moviequeue->data;	//kaybetmemek icin filmi bu diziye yaziyoruz
			h++;
			moviequeue = mq_dequeue();	//filmi queuedan cikariyoruz
			iter = iter->next;		//iterasyonu ilerletiyoruz NULL olana kadar
		}
		//printf("%s %s aktoru cikarildi\n", actorqueue->data->firstname, actorqueue->data->lastname);
		
		if(bacon!=actorqueue->data->kbnum){	//yukarida tum actorlerin kbnumlarini bulduk. bacon diye bir degiskenle kontrol edecegiz.
		//esit degilse count ý artýracagiz. yani kbnum'ý o kadar olandan count tane var demek.kbnum ý 2 olan film varsa 2 tane olacak count.
			printf("Kevin Bacon sayisi %d olan oyuncu sayisi : %d\n", bacon, count);	
			bacon++;	//bacon sayilari esitse 1 artirdik 
			count=0;	//count 'ý her seferinde 0lýyoruz siradaki kbnumlý actore temiz bir sekilde gecmek icin.
		}
		count++;
		actorqueue=aq_dequeue();	//aktoru queuedan cikariyoruz
		if(actorqueue==NULL)	//queue bosaldi mi?
			isEmpty=1;	//hic eleman kalmadi yani bos.
	}
	printf("Kevin Bacon sayisi %d olan oyuncu sayisi : %d\n", bacon, count);
	
	for(i=0;i<sayac;i++){	//film sayisi kadar donecek
		if(filmdizisi[i].kbnum==SONSUZ){	//sonsuz mu diye kontrol ediyoruz. sonsuzsa yani kevin baconla hic baglantisi yoksa 
			hesaplanmisfilmdizisi[h]=filmdizisi[i];	//hesaplanmisfilmdizimizein sonuna bu alakasiz filmi de ekleyecek
			h++;
		}
	}
	return hesaplanmisfilmdizisi;
}

void print(char* rootf, char* rootl, struct movie* filmdizisi, int sayac){	//adý verilen bir aktörün Kevin Bacon sayýsýný bulan ve baðlantýyý yazdirma
																	//Kevin Bacon numarasi aranacak oyuncu adi/soyadi, filmdizisi ve filmdizisinin boyutunu paremetre alir
	int i, j, k;	//i film için, j aktör için, k rootm in actor iterasyonu icin
	struct movie* rootm = NULL;	//movie icin root
	struct actor* roota = NULL;	//actor icin root
	while(strcmp(rootf, "Kevin")!=0 || strcmp(rootl, "Bacon")!=0){	//root for firstname ve lastname kevin bacon a esit olmadikca
		i=0;
		while(i<sayac && rootm==NULL){	//i<sayac yani satir sayisi ve movie root null
			j=0;
			while(filmdizisi[i].actor[j].firstname[0]!=0 && rootm==NULL){
				if(strcmp(rootf, filmdizisi[i].actor[j].firstname)==0 && strcmp(rootl, filmdizisi[i].actor[j].lastname)==0){
					if(filmdizisi[i].kbnum==SONSUZ){	//kbnum ý sonsuz ise actorun adý soyadý ve yanina da sonsuz yazilsin.
						printf("%s %s (sonsuz)\n", filmdizisi[i].actor[j].firstname, filmdizisi[i].actor[j].lastname);
						return;
					}
					rootm=&filmdizisi[i];	//sonsuz degilse filmdizisinin i. elemani movie rootuna atanir
					printf("%s %s :\n", rootm->name, rootm->year);	//ve movie nin adý ve yýlý yazilir
				}
				j++;
			}
			i++;
		}
		if(rootm==NULL){	//rootm null ise oyle bir film yok dolayisiyla oyuncu yok 
			printf("Oyuncu bulunamadi!\n");
			return;
		}
		k=0;
		while(rootm->actor[k].firstname[0]!=0 && roota==NULL){ //firstname[0]!=0 ise oyuncu var. ==0 olsa alt satira gecmis oldugunu yani oyuncularin bittigini anlardik.
			if(strcmp(rootm->actor[k].firstname, "Kevin")==0 && strcmp(rootm->actor[k].lastname, "Bacon")==0){ //bacon a hemen 1 uzaklikta ise
				printf("%s %s (%d) - ", rootf, rootl, rootm->kbnum); //girdigimizin adi soyadi ve yanina kevin bacon sayisi
				roota = &rootm->actor[k];
				printf("%s %s (0)\n", roota->firstname, roota->lastname);	//son olarak bu printler isletilecek.
			}
			if(strcmp(rootm->actor[k].firstname, rootf)==0 && strcmp(rootm->actor[k].lastname, rootl)==0)
				k++;	//actoru ilerletiyoruz
			i=0;
			while(i<sayac && roota==NULL && &filmdizisi[i]!=rootm){	//film dizisi bitmediyse 
				j=0;
				while(filmdizisi[i].actor[j].firstname[0]!=0 && roota==NULL){
					if(strcmp(rootm->actor[k].firstname, filmdizisi[i].actor[j].firstname)==0 && 
						strcmp(rootm->actor[k].lastname, filmdizisi[i].actor[j].lastname)==0){
						//ilk bu kisim yazilir
						printf("%s %s (%d) - ", rootf, rootl, rootm->kbnum);	
						roota = &rootm->actor[k];	//movienin k. actorunu rootactor e esitliyoruz 
						printf("%s %s (%d)\n\n", roota->firstname, roota->lastname, filmdizisi[i].kbnum);
					}
					j++;
				}
				i++;
			}
			k++;
		}
		strcpy(rootf, roota->firstname);	//roota firstnameyi rootf e kopyaliyoruz sonraki iterasyonda bir yanindakinin rootf olmasini istedigimizden
		strcpy(rootl, roota->lastname);	//roota lastnameyi rootl e kopyaliyoruz sonraki iterasyonda bir yanindakinin rootl olmasini istedigimizden

		roota=NULL;
		rootm=NULL;	
	}
}

int main() {
	struct movie* filmdizisi;
	int i=0,j=0,k=0,sayac=0;//i yi film için, j yi aktör için ve k yý aktörün ad/soyadýnýn harfleri için,sayac'ý satýr yani film sayisini bulmak icin kullanýyoruz. 
	char ch,file_name[25];	//ch text dosyasindaki karakterlerin iterasyonu icin, file_name ise kullanýcýdan alýnacak dosyanin adi
	FILE *datafile;
	printf("Name of the text file :");
    gets(file_name);
    datafile = fopen(file_name, "r");//Dosya okuma islevi	//filmin uzunlugunu bulmak icin
    if (datafile == NULL)
    {
        printf("cannot open file...\n");
    	exit(EXIT_FAILURE);
	}
	while ((ch = fgetc(datafile)) != EOF){
		if(ch==10)	//her satirda 1 dizi var. satirlari sayiyoruz if(ch=='\n') ile ayni
			sayac++;
	}
	fclose(datafile);
	
	filmdizisi=(struct movie*)malloc(sayac*sizeof(struct movie));	//film sayisi kadar yer actik
	datafile = fopen(file_name, "r");	//Dosya okuma iþlevi
    if (datafile == NULL)
    {
        printf("cannot open file...\n");
    	exit(EXIT_FAILURE);
	}
    while ((ch = fgetc(datafile)) != EOF){
		j=0;
    	k=0;
    	while(ch!='('){		//paranteze gelene kadari moviename
//    		printf("%c", ch);
			filmdizisi[i].name[k]=ch;
    		ch = fgetc(datafile); //harf harf ilerletiyoruz.
    		k++;
		}
		filmdizisi[i].name[k]='\0';	//sonuna bir null ekliyoruz name stringinin.
		//printf("%s\n",filmdizisi[i].name);
		k=0;
    	while(ch!='/'){	// slash a gelene kadari yýl
//    		printf("%c", ch);
			filmdizisi[i].year[k]=ch;
    		ch = fgetc(datafile);	//harf harf ilerletiyoruz.
			k++;	
		}
		filmdizisi[i].year[k]='\0';	//sonuna bir null ekliyoruz year stringinin.
		//printf("%s\n",filmdizisi[i].year);
		ch = fgetc(datafile);	// year sonunda actor basindaki slash i atlamak icin 1 karakter ilerletiyoruz
		while(ch!=10){	//alt satira gecmedigi surece devami aktorler
			k=0;
    		while(ch!=','){	// virgule gelene kadari soyadi
//	    		printf("%c", ch);
				filmdizisi[i].actor[j].lastname[k]=ch;
	    		ch = fgetc(datafile);	//harf harf ilerletiyoruz.
	    		k++;
			}
			filmdizisi[i].actor[j].lastname[k]='\0';	//sonuna bir null ekliyoruz lastname stringinin.
			ch = fgetc(datafile);	//virgulu atlamak icin bir ileri
			ch = fgetc(datafile);	//virgulden sonraki boslugu atlamak icin bir ileri
			k=0;
    		while(ch!='/' && ch!=10){	//satir sonu degilse ve slasha esit degilse aktorlerin devamý var 
//	    		printf("%c", ch);
				filmdizisi[i].actor[j].firstname[k]=ch;
	    		ch = fgetc(datafile);	//harf harf ilerletiyoruz.	
	    		k++;
			}
			filmdizisi[i].actor[j].firstname[k]='\0';	//sonuna bir null ekliyoruz firstname stringinin.	
    		if(ch=='/'){	// slash ý almak istemedigimizden
    			ch = fgetc(datafile);	//bir harf ilerletiyoruz.
			}
			
			//printf("%s %s\n",filmdizisi[i].actor[j].firstname,filmdizisi[i].actor[j].lastname);
			j++;	//actoru ilerletiyorum
		}
		filmdizisi[i].kbnum=SONSUZ;	//tum filmdizisine sonsuz veriyoruz baslangicta
		filmdizisi[i].actor[j].firstname[0]=0;
		i++;	//filmdizisini ilerletiyorum
		//printf("\n");
	}
	
	filmdizisi = breadthfirst(filmdizisi,sayac);	//filmdizisindeki elemanlara breadthfirstsearch uyguluyorum
//	printf("\n");printf("\n");printf("______________________________________\n");printf("\n");
//	for(i=0;i<sayac;i++){	
//		printf("%s %d\n",filmdizisi[i].name, filmdizisi[i].kbnum);	//bfs ile siralanmis filmleri ve kbnumlarini ekrana yazdiriyorum...
//	}
	printf("\n");
	char rootf[20];	//root for firstname
	char rootl[20];	//root for lastname
	printf("Kevin Bacon numarasi aranacak oyuncu adi :");
	gets(rootf);
	printf("Kevin Bacon numarasi aranacak oyuncu soyadi :");
	gets(rootl);
	printf("\n");
	print(rootf, rootl, filmdizisi, sayac);

	return 0;
}
