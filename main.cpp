#include <iostream>
#include <cstdlib>
using namespace std;
const int n = 200;
struct Kont{
	int h;//высота
	int w;//ширина
};
const int localw=8;

Kont pers[n];

void input(){
	for (int i = 0; i < n; i++){
		pers[i].h = rand() % 10 + 1; 
		pers[i].w= rand() % 4 + 1;		
	}
}

void output(){ 
	cout << "h  w" << endl;
	for (int i = 0; i < n; i++)
	cout << pers[i].h << " " << pers[i].w << endl;
}

void sort(){
	int fw = 0; int fh = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++)
			if (pers[j].h < pers[j + 1].h){
				fh = pers[j].h; fw = pers[j].w;
				pers[j].h = pers[j + 1].h; pers[j].w = pers[j + 1].w;
				pers[j + 1].h = fh; pers[j + 1].w = fw;
			}
}

void NFDH(){
	int level = pers[0].h; int modweight = localw - pers[0].w; //поместили первый элемент посчитали остаток ширины
	for (int i = 1; i < n; i++)
		if (pers[i].w <= modweight) // если ширина прямоугольника меньше остатка, то мы можем поместить прямоугольник
			modweight = modweight - pers[i].w;
		else{ //а если нет, то организуем новый уровень
			level = level + pers[i].h;
			modweight = localw - pers[i].w;
		}
		cout << level << endl;
}

void FFDH(){	
	int modweight[100]; int level = pers[0].h; int j = 0; modweight[0] = localw - pers[0].w;
	for (int i = 1; i < n; i++){		
		int kk = 0;
		for (int k = 0; k <= j;k++){
			if (modweight[k] >= pers[i].w){
			modweight[k] = modweight[k] - pers[i].w;			
			kk = 1;
			break;
			}
		}
		if (kk == 0) {
			level = level + pers[i].h;
			j = j + 1;
			modweight[j] = localw - pers[i].w;
		}			
	}	
	cout << level << endl;
	//непонятно почему работает слишком идеально
}
void BFDH(){
	int modweight[n]; int smallestmod = 99999; int nsm = 0; int level = pers[0].h; int j = 0; modweight[0] = localw - pers[0].w;
	for (int i = 1; i < n; i++){
		int kk = 0;
		smallestmod = 99999;
		for (int k = 0; k <= j; k++){			
			if (modweight[k] >= pers[i].w){ //если помещается
				if (modweight[k] - pers[i].w < smallestmod){  //то ищем лучший
					nsm = k; smallestmod = modweight[k] - pers[i].w; //присваиваем номер текущего лучшего и его значение
				}				
				kk = 1;				
			}
		}
		if (kk==1) modweight[nsm] = modweight[nsm] - pers[i].w; //
		if (kk == 0) {
			level = level + pers[i].h;
			j = j + 1;
			modweight[j] = localw - pers[i].w;
		}
	}
	cout << level << endl;
}
void FCNR(){
	int modweight[n]; int smallestmod = 99999; int nsm = 0; int level = pers[0].h; int j = 0; modweight[0] = localw - pers[0].w;
	for (int i = 1; i < n; i++){
		int kk = 0;
		smallestmod = 99999;
		for (int k = 0; k <= j; k++){
			if (modweight[k] >= pers[i].w){ //если помещается
				if (modweight[k] - pers[i].w < smallestmod){  //то ищем лучший
					nsm = k; smallestmod = modweight[k] - pers[i].w; //присваиваем номер текущего лучшего и его значение
				}
				kk = 1;
			}
		}
		if (kk == 1) modweight[nsm] = modweight[nsm] - pers[i].w; //
		if (kk == 0) {
			level = level + pers[i].h;
			j = j + 1;
			modweight[j] = localw - pers[i].w;
		}
	}
	cout << level << endl;
}

void main(){
	
	input();		
	sort();
	output();

	NFDH();
	FFDH();
	BFDH();
	FCNR();
	
	cin.get();
};