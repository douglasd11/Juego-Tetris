#include <iostream>
#include <windows.h>
#include "time.h"
#include "stdlib.h"

using namespace std;

//--------------------------Globales-----------------------------------//
int matriz[20][10];
int fig[4][4];
int colores[]={48,32,64,80,96,112};
int ix=15, iy=12, velocidad;
				 
int fig1[4][4] = {{0,0,0,0},
				  {0,1,1,0},
				  {0,1,1,0},
				  {0,0,0,0}};			 
int fig2[4][4] = {{0,2,0,0},
				  {0,2,0,0},
				  {0,2,0,0},
				  {0,2,0,0}};
int fig3[4][4] = {{0,3,0,0},
				  {3,3,0,0},
				  {0,3,0,0},
				  {0,0,0,0}};			  
int fig4[4][4] = {{0,0,0,0},
				  {4,0,0,0},
				  {4,4,4,0},
				  {0,0,0,0}};			  
int fig5[4][4] = {{0,0,0,0},
				  {0,5,5,0},
				  {5,5,0,0},
				  {0,0,0,0}};
int fig6[4][4] = {{0,0,0,0},
				  {6,6,0,0},
				  {0,6,6,0},
				  {0,0,0,0}};
int fig7[4][4] = {{0,0,0,0},
				  {0,7,0,0},
				  {0,0,0,0},
				  {0,0,0,0}};
int fig8[4][4] = {{0,0,0,0},
				  {0,1,0,0},
				  {0,0,0,0},
				  {0,0,0,0}};
//------------------------------Color----------------------------------//				 				 
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}				 
void equivaleColor(int c){
	color(c);
	cout<<" ";
	color(15);
}
void gotoxy(int x,int y){//pinta en la consola
	 HANDLE ventana;
	 ventana =GetStdHandle(STD_OUTPUT_HANDLE);//identificador de la ventana
	 COORD pos;//objeto con las posiciones
	 pos.X=x;
	 pos.Y=y;
	 SetConsoleCursorPosition(ventana,pos);
}
//------------------------------Extra----------------------------------//				 
void mostrarCursor(bool tf){
	 HANDLE cursor;
	 cursor = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_CURSOR_INFO cci;
	 cci.dwSize=20;
	 cci.bVisible=tf; 
	 SetConsoleCursorInfo(cursor,&cci);
}

//-------------------------Dibujar tetris------------------------------//
void dibujarTetris(){
	cout<<"  |===============================================================|\n";
	cout<<"  | OOOOOOOOOOO  OOOOOOOO OOOOOOOOOOO  OOOOOOO   OOOO OOOOOOOOOO  |\n";
	cout<<"  | OOOOOOOOOOO OOOOOOOOO OOOOOOOOOOO OOO   OOO  OOOO OOOOOOOOOOO |\n";
	cout<<"  |     OOO     OOO           OOO     OOO   OOO        OOOO       |\n";
	cout<<"  |     OOO     OOOOOOOOO     OOO     OOOOOOOO    OO     OOOO     |\n";
	cout<<"  |     OOO     OOOOOOOOO     OOO     OOOOOO     OOOO      OOOO   |\n";
	cout<<"  |     OOO     OOO           OOO     OOO OOO    OOOO       OOOO  |\n";
	cout<<"  |     OOO     OOOOOOOOO     OOO     OOO  OOO   OOOO  OOOOOOOOOO |\n";
	cout<<"  |     OOO      OOOOOOOO     OOO     OOO   OOO  OOOO OOOOOOOOOOO |\n";
	cout<<"  |===============================================================|\n\n";
}
			 
//-------------------------Dibujar matriz------------------------------//
void dibujarJuego(int puntos){
	gotoxy(ix+34,iy+1);
	color(16); cout<<" Nivel: "<<(puntos/6)<<" "; color(15);
	gotoxy(ix-3,iy-1); cout<<"-------------------------------";
	for(int i=0; i<20; i++){
		gotoxy(ix-3,i+iy);
		cout<<"|";
		for(int j=0; j<10; j++){
			if(matriz[i][j]==0){
				cout<<"  |";
			}else{
				equivaleColor(matriz[i][j]);
				equivaleColor(matriz[i][j]);
				if(j<9){
					if(matriz[i][j+1]!=0){
						equivaleColor(matriz[i][j]);	
					}
					else{
						cout<<"|";
					}
				}else cout<<"|";
			}
		}
	}
	gotoxy(ix-3,20+iy); cout<<"-------------------------------";
	cout<<"\n\n\t\t   | USE LAS FLECHAS DEL TECLADO |";
	cout<<"\n\t\t\t    | Puntos: "<<puntos<<" |";
}
void dibujarFigura(int x,int y,int x_, int y_){
	
	for(int i=x_; i<x_+4; i++){
		for(int j=y_; j<y_+4; j++){
			if(!(j<0 or j>10 or i<0 or i>19)){
				if(fig[i-x_][j-y_]!=0){
					gotoxy(ix+(j*3-2),i+iy); cout<<"  |";
				}
			}
		}
	}
	
	for(int i=x; i<x+4; i++){
		for(int j=y; j<y+4; j++){
			if(!(j<0 or j>10 or i<0 or i>19)){
				if(fig[i-x][j-y]!=0){		
					gotoxy(ix+(j*3-2),i+iy);
					equivaleColor(matriz[i][j]);
					equivaleColor(matriz[i][j]);
					if(j-y<9){
						if(fig[i-x][j-y+1]!=0){	
							equivaleColor(matriz[i][j]);
						}
					}
				}	
			}
		}
	}
}

//---------------------frame anterior sin rotar------------------------//
void previousFrame(int x, int y){
	for(int i=x; i<x+4; i++){
		for(int j=y; j<y+4; j++){
			if(!(j<0 or j>10 or i<0 or i>19)){
				if(fig[i-x][j-y]!=0){
					matriz[i][j]=0;
				}	
			}
		}
	}
}

//------------------------frame siguiente------------------------------//
void nextFrame(int x, int y){
	
	for(int i=x; i<x+4; i++){
		for(int j=y; j<y+4; j++){
			if(!(j<0 or j>10 or i<0 or i>19)){
				if(fig[i-x][j-y]!=0){
					matriz[i][j]= fig[i-x][j-y];
				}	
			}
		}
	}
}

//-------------------------funcion rotar-------------------------------//
int equivale(int cont,int N){
	int contAux= 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(contAux == cont){
				return fig[i][j];
			}
			contAux++;
		}
	}
	return 0;
}

void rotar(int N){
	int rotada[N][N], cont=0;
	for(int i=N-1; i>=0; i--){
		for(int j=0; j<N; j++){
			rotada[j][i] = equivale(cont,N);
			cont++;
		}
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			fig[i][j] = rotada[i][j];
		}
	}
}

void rotate(int x, int y, int nFig, int puntos){
	if(nFig==1 or nFig==2) rotar(4);
	else rotar(3);
	bool est= false;
	for(int i=x; i<x+4; i++){
		for(int j=y; j<y+4; j++){
			if(fig[i-x][j-y]!=0 and (j<0 or j>9 or i<0 or i>19)){
				est= true;
			}
			if(i<20 and j<10){
				if(fig[i-x][j-y]!=0 and matriz[i][j]!=0){
					est= true;
				}
			}
		}
	}
	if(est){
		if(nFig==1 or nFig==2){
			rotar(4); rotar(4); rotar(4);	
		} 
		else{
			rotar(3); rotar(3); rotar(3);
		} 
	}
	else{
		dibujarJuego(puntos);
	}
}
//-----------------------eliminar fila llena---------------------------//
int deleteRows(){
	bool est;
	int puntos = 0;
	for(int i=0; i<20; i++){
		est = true;
		for(int j=0; j<10; j++){
			if(matriz[i][j]==0){
				est = false;
			}
		}
		if(est){
			for(int j=0; j<10; j++){
				matriz[i][j]=0;
			}
			for(int x=i; x>1; x--){
				for(int y=0; y<10; y++){
					matriz[x][y] = matriz[x-1][y];
				}
			}
			puntos++;
		}
	}
	return puntos;
}
//------------------------figura ramdow---------------------------------//
void figRamdow(int mat[][4], bool est){
	if(est){
		int colorFig= rand()%6;
		for(int i=0; i<4; i++){
			for(int j=0; j<4 ;j++){
				if(mat[i][j] == 0) fig[i][j] = 0;
				else fig[i][j] = colores[colorFig];
			}
		}
	}
	else{
		gotoxy(ix+32,iy+3);
		cout<<"-------------";
		for(int i=0; i<4; i++){
			gotoxy(ix+32,iy+4+i);
			cout<<"|";
			for(int j=0; j<4; j++){
				if(mat[i][j]!=0){		
					equivaleColor(16);
					equivaleColor(16);
					if(j<9){
						if(mat[i][j+1]!=0){	
							equivaleColor(16);
						}
						else cout<<"|";
					}
					else cout<<"|";
				}
				else cout<<"  |";	
			}
		}
		gotoxy(ix+32,iy+8);
		cout<<"-------------";
	}	
}

void asignarMat(int rw, bool est){
	if(rw==1) figRamdow(fig1,est);
	if(rw==2) figRamdow(fig2,est);
	if(rw==3) figRamdow(fig3,est);
	if(rw==4) figRamdow(fig4,est);
	if(rw==5) figRamdow(fig5,est);
	if(rw==6) figRamdow(fig6,est);
	if(rw==7) figRamdow(fig7,est);
	if(rw==8) figRamdow(fig8,est);
}

//----------------------colision hacia abajo----------------------------//
bool figCollision(int x, int y){
	for(int i=x; i<x+4; i++){
		for(int j=y; j<y+4; j++){
			if(!(j<0 or j>10 or i<0 or i>19)){
				if(fig[i-x][j-y]!=0 and matriz[i][j]!=0){
					return false;
				}
			}
			if(fig[i-x][j-y]!=0 and (i>19)){
				return false;
			}
		}
	}
	return true;
}

//-----------------------colision laterales----------------------------//
bool limits(int x, int y){
	for(int i=x; i<x+4; i++){
		for(int j=y; j<y+4; j++){
			if(!(j<0 or j>10 or i<0 or i>19)){
				if(fig[i-x][j-y]!=0 and matriz[i][j]!=0){
					return false;
				}
			}
			if(fig[i-x][j-y]!=0 and (j>9 or j<0)){
				return false;
			}
		}
	}
	return true;
}

//------------------------final del juego------------------------------//
bool endGame(){
	for(int i=0; i<10; i++){
		if(matriz[0][i]!=0){
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------------------// 
int main(){
	srand(time(NULL));
	system("MODE CON COLS=70 LINES=45");
	mostrarCursor(false);
	int puntos = 0, rw=1+rand()%7;
	dibujarTetris();
	
	while(endGame()){
		int j=0+rand()%6 ,nFig=1+rand()%7;
		asignarMat(rw,true);
		asignarMat(nFig,false);
		dibujarJuego(puntos);
		
		for(int i=-4; i<20; i++){
			int opcion = 0, j_= j;
			velocidad= 120-(puntos*1.3);
			
			previousFrame(i-1 ,j_);
			
			if(GetAsyncKeyState(0x25)){
				if(limits(i,j-1)) j--;
			}
			if(GetAsyncKeyState(0x27)){
				if(limits(i,j+1)) j++;
			}
			if(GetAsyncKeyState(0x28)){
				velocidad=40;
			}
			
 			Sleep(velocidad/2);
			if(GetAsyncKeyState(0x26)){
				rotate(i, j, rw, puntos);
			}
		
			if(figCollision(i,j)){
				nextFrame(i,j);
			}else{
				nextFrame(i-1,j_);
				puntos += deleteRows();
				dibujarJuego(puntos);
				break;
			}
			dibujarFigura(i,j,i-1,j_);
			Sleep(velocidad);
		}
		rw = nFig;
	}
	gotoxy(0,iy+20);
	dibujarTetris();
	cout<<"\t  | FIN de juego gracias por jugar | puntos: "<<puntos<<" |"<<endl;
	system("pause"); system("pause");
	return 0;
}
