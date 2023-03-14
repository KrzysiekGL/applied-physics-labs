#include <iostream>

int * search(int * T, int n, int p) {
	if(n>=2) {
		search(T, n/2, p);
		search(T+n/2, n-n/2, p);
	}
	else if(T[0]==p) return T;
	return NULL;
}

int binary_search(int * T, int n, int p){
	// znajdź wynik, jako pozycję liczby p w tablicy T
	//(licząc od 0), lub -1, gdy liczba ta nie występuje w tablicy
	int index = -1;

	int * offset = search(T, n, p);
	if(offset!=NULL)
		index = offset - T;

	return index;
}

int main(int argc, char ** argv) {
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int b[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	binary_search((int*)a,

	return 0;
}
