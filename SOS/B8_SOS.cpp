#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<conio.h>

struct pemain{
	char nama[20];
	int giliran;
	int poin=0;
}p1,p2;

struct temp{
	char huruf;
	int kotak;
}temp;

int mode,level,n;
char papan[8][8];

void prep();
void start();
void finish();
void hitungPoin(pemain &p);
void cariPemenang();
void addNama(int mode);
void pilihGiliran(int mode);
void tampilPapan();
void addHuruf(int kotak,char huruf);
void cariIndex(int kotak, int &row, int &col);
void cekSOS(pemain &p);
void AI();
void tampilTutor();
int cariSS();
int cariSO();
int pilihMode();
int pilihLevel();
int cekInput(int kotak,char huruf);

int main(){	
	system("cls");
	
	int pilih;
	printf(" ####      ###      ####\n#         #   #    #\n#        #     #   #\n ####    #     #    ####\n     #   #     #        #\n     #    #   #         #\n ####      ###      ####\n\n");
	printf("Menu\n");
	printf("1. Mulai game\n");
	printf("2. Bantuan\n");
	printf("3. Exit\n");
	printf("Pilih menu : ");
	scanf("%d",&pilih);
	
	if(pilih==1){
		prep();
	}
	else if(pilih==2){
		tampilTutor();
	}
	else if(pilih==3){
		exit(0);
	}
	
	return 0;
}

void prep(){
	system("cls");
	mode = pilihMode();
	printf("\n");
	level = pilihLevel();
	addNama(mode);
	pilihGiliran(mode);
	
	if(level==1){
		n=3;
	}else if(level==2){
		n=5;
	}else{
		n=8;
	}
	
	start();
}

void start(){
	int turn=1,kotak,sos;
	char huruf;
	
	// jika multiplayer
	if(mode==2){	
		do{
			system("cls");
			tampilPapan();
			printf("\n%s : %d  ||  %s : %d\n",p1.nama,p1.poin,p2.nama,p2.poin);
			
			if(turn%2==0){ // giliran ke-2
				if(p1.giliran==2){
					do{
						printf("\nGILIRAN %s\n",p1.nama);
						printf("Pilih kotak : ");
						scanf("%d", &kotak);
						printf("Pilih huruf (S/O) : ");
						scanf(" %c", &huruf);
						
					}while(cekInput(kotak,huruf)==1);
					
					addHuruf(kotak,huruf);
					cekSOS(p1);
				}
				else if(p2.giliran==2){
					do{
						printf("\nGILIRAN %s\n",p2.nama);
						printf("Pilih kotak : ");
						scanf("%d", &kotak);
						printf("Pilih huruf (S/O) : ");
						scanf(" %c", &huruf);
						
					}while(cekInput(kotak,huruf)==1);
					
					addHuruf(kotak,huruf);
					cekSOS(p2);
				}
			}else{ // giliran ke-1
				if(p1.giliran==1){
					do{
						printf("\nGILIRAN %s\n",p1.nama);
						printf("Pilih kotak : ");
						scanf("%d", &kotak);
						printf("Pilih huruf (S/O) : ");
						scanf(" %c", &huruf);
						
					}while(cekInput(kotak,huruf)==1);
					
					addHuruf(kotak,huruf);
					cekSOS(p1);
				}
				else if(p2.giliran==1){
					do{
						printf("\nGILIRAN %s\n",p2.nama);
						printf("Pilih kotak : ");
						scanf("%d", &kotak);
						printf("Pilih huruf (S/O) : ");
						scanf(" %c", &huruf);
						
					}while(cekInput(kotak,huruf)==1);
					
					addHuruf(kotak,huruf);
					cekSOS(p2);
				}		
			}
			
			turn++;
		}while(turn<=n*n);
	}
	
	// LAWAN AI
	else {
		do{
			system("cls");
			tampilPapan();
			printf("\n%s : %d  ||  %s : %d\n",p1.nama,p1.poin,p2.nama,p2.poin);
			
			if(turn%2==0){ // GILIRAN KE-2 AI
				printf("\nGILIRAN %s\n",p2.nama);
				AI();
				sleep(3);
				cekSOS(p2);
			}
			else{ // GILIRAN KE-1 PLAYER
				do{
					printf("\nGILIRAN %s\n",p1.nama);
					printf("Pilih kotak : ");
					scanf("%d", &kotak);
					printf("Pilih huruf (S/O) : ");
					scanf(" %c", &huruf);
						
				}while(cekInput(kotak,huruf)==1);
				
				addHuruf(kotak,huruf);
				cekSOS(p1);
			}
			
			turn++;
		}while(turn<=n*n);
	}
	
	finish();
	
}

void finish(){
	system("cls");
	
	char c;
	
	printf("PERMAINAN BERAKHIR!!\n");
	
	tampilPapan();
	cariPemenang();
	
	printf("\n\nPOIN AKHIR\n%s : %d  ||  %s : %d",p1.nama,p1.poin,p2.nama,p2.poin);
	
	// untu kembali ke main menu
	printf("\n\nKlik ENTER untuk kembali ke menu utama");
    getchar();
    c = fgetc(stdin);
    if(c==0x0A){
    	main();
	}
}

int pilihMode(){
	int pilih;
	printf("PILIH MODE\n");
	printf("1. Solo (vs AI)\n");
	printf("2. Multiplayer\n");
	printf("Pilih angka : ");
	scanf("%d",&pilih);
	return pilih;
}

int pilihLevel(){
	int pilih;
	printf("PILIH LEVEL KESULITAN\n");
	printf("1. Easy\n");
	printf("2. Normal\n");
	printf("3. Hard\n");
	printf("Pilih angka : ");
	scanf("%d",&pilih);
	return pilih;
}

void addNama(int mode){
	char nama[20];
	if(mode==1){
		strcpy(p2.nama, "AI");
		printf("\nMasukan nama : ");
		scanf("%s",nama);
		strcpy(p1.nama, nama);
	}else{
		printf("\nMasukan nama P1 : ");
		scanf("%s",nama);
		strcpy(p1.nama, nama);
		getchar();
		
		printf("Masukan nama P2 : ");
		scanf("%s",nama);
		strcpy(p2.nama, nama);
	}
}

void pilihGiliran(int mode){
	int pilih;
	if(mode==1){
		p1.giliran=1;
		p2.giliran=2;
	}else{
		printf("\nPILIH GILIRAN\n");
		printf("1. Giliran pertama\n");
		printf("2. Giliran kedua\n");
		printf("P1 pilih giliran : ");
		scanf("%d",&pilih);
		
		p1.giliran=pilih;
		
		if(pilih==1){
			p2.giliran=2;
		}else{
			p2.giliran=1;
		}
	}
}

void tampilPapan(){
	int no=0;
	
	printf(" ");
	for(int k=0;k<n;k++){
		printf("------- ");
	}
	printf("\n");
	
	for(int i=0;i<n;i++){
		printf("| ");
		for(int j=0;j<n;j++){
			no++;
			if(papan[i][j]=='\0'){
				printf("%d\t| ",no);
			}else{
				printf("%c\t| ",papan[i][j]);
			}				
		}
		printf("\n ");
		for(int k=0;k<n;k++){
			printf("------- ");
		}
		printf("\n");
	}
}

void cariIndex(int kotak, int &row, int &col){
	int no=0,i,j;
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			no++;
			if(no==kotak){
				break;
			}
		}
		if(no==kotak){
			break;
		}
	}
	
	row=i;
	col=j;
}

void addHuruf(int kotak, char huruf){
	int row,col;
	
	cariIndex(kotak,row,col);
	papan[row][col]=toupper(huruf);
	
	temp.huruf=huruf;
	temp.kotak=kotak;
}

int cekInput(int kotak, char huruf){	
	/*
	VALID = 0
	INVALID = 1
	*/
	
	int row,col;
	
	cariIndex(kotak,row,col);
	
	if(toupper(huruf)=='S'|| toupper(huruf)=='O'){
		if(papan[row][col]=='\0'){			
			if(kotak>n*n){
				return 1;
			}else{
				return 0;	
			}
		}else{
			return 1;
		}
	}else{
		return 1;
	}

}

void cekSOS(pemain &p){
	int row, col;
	
	cariIndex(temp.kotak,row,col);
	
	if(tolower(temp.huruf)=='s'){
		if(papan[row-1][col-1]=='O'){
			if(papan[row-2][col-2]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row-1][col]=='O'){
			if(papan[row-2][col]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row][col-1]=='O'){
			if(papan[row][col-2]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row+1][col+1]=='O'){
			if(papan[row+2][col+2]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row+1][col]=='O'){
			if(papan[row+2][col]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row][col+1]=='O'){
			if(papan[row][col+2]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row-1][col+1]=='O'){
			if(papan[row-2][col+2]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row+1][col-1]=='O'){
			if(papan[row+2][col-2]=='S'){
				hitungPoin(p);
			}
		}
	}
	else if(tolower(temp.huruf)=='o'){
		if(papan[row][col-1]=='S'){
			if(papan[row][col+1]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row-1][col]=='S'){
			if(papan[row+1][col]=='S'){
				hitungPoin(p);
			}
		}
		if(papan[row-1][col-1]=='S'){
			if(papan[row+1][col+1]=='S'){
				hitungPoin(p);
			}
		}
	}
}

void hitungPoin(pemain &p){
	p.poin++;
}

void cariPemenang(){
	
	printf("\nPEMENANG ADALAH...\n");
	sleep(2);
	
	if(p1.poin>p2.poin){
		printf("SELAMAT %s",p1.nama);
	}else if(p1.poin<p2.poin){
		printf("SELAMAT %s",p2.nama);
	}else{
		printf("SERI");
	}
	
}

void AI(){
	int kotak;
	char huruf;
	
	int ss=cariSS(),so=cariSO();
	
	if(ss!=0){
		kotak=ss;
		huruf='O';
	}
	else if(so!=0){
		kotak=so;
		huruf='S';
	}else{
		int kanan=0;
		for(int k=temp.kotak;k<=n*n;k++){
			if(cekInput(k,temp.huruf)==0){
				kotak=k;
				huruf=temp.huruf;
				kanan=1;
				break;
			}
		}
		if(kanan==0){
			for(int k=temp.kotak;k>0;k--){
				if(cekInput(k,temp.huruf)==0){
					kotak=k;
					huruf=temp.huruf;
					break;
				}
			}
		}
	}
	
	addHuruf(kotak, huruf);
}

int cariSO(){
	int i,j,kotak=0;
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			kotak++;
			if(cekInput(kotak,'S')==0){
				if(papan[i][j+1]=='O' && papan[i][j+2]=='S'){
					return kotak;
				}
				else if(papan[i][j-1]=='O' && papan[i][j-2]=='S'){
					return kotak;
				}
				else if(papan[i+1][j]=='O' && papan[i+2][j]=='S'){
					return kotak;
				}
				else if(papan[i-1][j]=='O' && papan[i-2][j]=='S'){
					return kotak;
				}
				else if(papan[i+1][j+1]=='O' && papan[i+2][j+2]=='S'){
					return kotak;
				}
				else if(papan[i-1][j-1]=='O' && papan[i-2][j-2]=='S'){
					return kotak;
				}
				else if(papan[i+1][j-1]=='O' && papan[i+2][j-2]=='S'){
					return kotak;
				} // end if papan
			} // end if kotak
		}
	}
	
	return 0;
}

int cariSS(){
	int i,j,kotak=0;
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			kotak++;
			if(cekInput(kotak,'O')==0){
				if(papan[i][j+1]=='S' && papan[i][j-1]=='S'){
					return kotak;
				}
				else if(papan[i+1][j]=='S' && papan[i-1][j]=='S'){
					return kotak;
				}
				else if(papan[i+1][j+1]=='S' && papan[i-1][j-1]=='S'){
					return kotak;
				}
				else if(papan[i+1][j-1]=='S' && papan[i-1][j+1]=='S'){
					return kotak;
				} // end if papan
			} // end if kotak
		}
	}
	
	return 0;
}

void tampilTutor(){
	system("cls");
	
	FILE *FF;
	char CC,c;
	
	if((FF=fopen("bantuan.txt","r"))== NULL){
		printf("Pembukaan File Gagal !");
		exit(1); //keluar program
	}
	 
	while((CC=getc(FF))!=EOF){
		putch(CC); //baca dan tampilkan ke layar
	}
	fclose(FF);
    
    printf("\n\nKlik ENTER untuk kembali");
    getchar();
    c = fgetc(stdin);
    if(c==0x0A){
    	main();
	}
}
