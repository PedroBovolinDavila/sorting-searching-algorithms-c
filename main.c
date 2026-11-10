#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void swap(int* x, int* y);
void bubble(int* v, int n, int* comp, int* trocas);
void selection(int* v, int n, int* comp, int* trocas);
void insertion(int* v, int n, int* comp, int* trocas);

int busca_sequencial(int* v, int n, int alvo, int* comp);
int busca_binaria(int* v, int n, int alvo, int* comp);

void mostrar_vetor(int* v, int n);
void copiar_vetor(int* v, int* w, int n);
void preencher_vetor(int* v, int n);

int main() {
	srand(time(NULL));

	int n;

	printf("Informe a quantidade de elementos do vetor: ");
	scanf_s("%d", &n);

	if (n <= 0) return 1;

	/*
	* v é o vetor original digitado pelo usuario
	*/
	int* v = malloc(n * sizeof(*v));
	if (v == NULL) return 1;

	if (n > 10) {
		for (int i = 0; i < n; i++) {
			v[i] = rand() % 100 + 1;
		}
	} else {
		preencher_vetor(v, n);
	}

	int* v1 = malloc(n * sizeof(*v1));
	if (v1 == NULL) {
		free(v);
		return 1;
	}

	copiar_vetor(v, v1, n);

	int b_comp, b_trocas;
	bubble(v1, n, &b_comp, &b_trocas);

	int* v2 = malloc(n * sizeof(*v2));
	if (v2 == NULL) {
		free(v);
		free(v1);
		return 1;
	}

	copiar_vetor(v, v2, n);

	int s_comp, s_trocas;
	selection(v2, n, &s_comp, &s_trocas);

	int* v3 = malloc(n * sizeof(*v3));
	if (v3 == NULL) {
		free(v);
		free(v1);
		free(v2);
		return 1;
	}

	copiar_vetor(v, v3, n);

	int i_comp, i_trocas;
	insertion(v3, n, &i_comp, &i_trocas);

	printf("\nAlgoritimo\tN\tComparacoes\tTrocas\n");
	printf("Bubble\t\t%d\t%d\t\t%d\n", n, b_comp, b_trocas);
	printf("Selection\t%d\t%d\t\t%d\n", n, s_comp, s_trocas);
	printf("Insertion\t%d\t%d\t\t%d\n", n, i_comp, i_trocas);

	printf("\nVetor original: ");
	mostrar_vetor(v, n);
	printf("Vetor ordenado: ");
	mostrar_vetor(v1, n);

	int alvo;

	printf("\nInforme o valor que deseja procurar no vetor: ");
	scanf_s("%d", &alvo);

	int seq_comp, bin_comp;
	int s_indice = busca_sequencial(v1, n, alvo, &seq_comp);
	int b_indice = busca_binaria(v1, n, alvo, &bin_comp);

	printf("\nAlgoritimo\tN\tIndice\tAlvo\tComparacoes\n");
	printf("Sequencial\t%d\t%d\t%d\t%d\n", n, s_indice, alvo, seq_comp);
	printf("Binaria\t\t%d\t%d\t%d\t%d\n", n, b_indice, alvo, bin_comp);

	free(v);
	free(v1);
	free(v2);
	free(v3);

	return 0;
}

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubble(int* v, int n, int* comp, int* trocas) {
	*comp = *trocas = 0;

	for (int i = 0; i < n - 1; i++) {
		int houve_troca = 0;

		for (int j = 0; j < n - 1 - i; j++) {
			(*comp)++;
			if (v[j] > v[j + 1]) {
				swap(&v[j], &v[j + 1]);
				houve_troca = 1;
				(*trocas)++;
			}
		}

		if (!houve_troca) break;
	}
}

void selection(int* v, int n, int* comp, int* trocas) {
	*comp = *trocas = 0;

	for (int i = 0; i < n - 1; i++) {
		int indice_menor = i;

		for (int j = i + 1; j < n; j++) {
			(*comp)++;
			if (v[j] < v[indice_menor]) indice_menor = j;
		}

		if (indice_menor != i) {
			(*trocas)++;
			swap(&v[i], &v[indice_menor]);
		}
	}
}

void insertion(int* v, int n, int* comp, int* trocas) {
	*comp = *trocas = 0;

	for (int i = 1; i < n; i++) {
		int chave = v[i];
		int j = i - 1;

		while (j >= 0) {
			(*comp)++;
			if (!(v[j] > chave)) break;

			v[j + 1] = v[j];
			(*trocas)++;
			j--;
		}

		v[j + 1] = chave;
	}
}

int busca_sequencial(int* v, int n, int alvo, int* comp) {
	*comp = 0;

	for (int i = 0; i < n; i++) {
		(*comp)++;
		if (v[i] == alvo) return i;
	}

	return -1;
}

/*
* 1, 2, 3, 4, 5, 6, 7
*/
int busca_binaria(int* v, int n, int alvo, int* comp) {
	*comp = 0;
	int inicio = 0, fim = n - 1;

	while (inicio <= fim) {
		int meio = (inicio + fim) / 2;

		(*comp)++;
		if (v[meio] == alvo) return meio;
		if (v[meio] > alvo) fim = meio - 1;
		if (v[meio] < alvo) inicio = meio + 1;
	}

	return -1;
}

void mostrar_vetor(int* v, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\t", v[i]);
	}
	printf("\n");
}

/*
* Copia o vetor v para o vetor w
*/
void copiar_vetor(int* v, int* w, int n) {
	for (int i = 0; i < n; i++) {
		w[i] = v[i];
	}
}

void preencher_vetor(int* v, int n) {
	for (int i = 0; i < n; i++) {
		printf("Informe o valor %d: ", i + 1);
		scanf_s("%d", &v[i]);
	}
	printf("\n");
}
