#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TAM 100


void BubbleSort(int *v, int tam) {
	int i;
	
    int a, b, aux;
    for (a = tam -1; a>=1; a--) {
        for (b=0; b<a; b++) {
            if (v[b]>v[b+1]) {
                aux = v[b];
                v[b] = v[b+1];
                v[b+1] = aux;
            }
        }
    }
    
}

void QuickSort(int *v, int E, int D){
	int i, j, pivot, temp;
	
	for(i=0;i<D;i++)
		v[i] = v[i];
	
	if(E < D){
		pivot=E;
		i=E;
		j=D;
		
	while(i<j){
		while(v[i]<=v[pivot]&&i<D)
			i++;
		while(v[j]>v[pivot])
			j--;
		if(i<j){
			temp=v[i];
			v[i]=v[j];
			v[j]=temp;
		}
	}
	
	temp=v[pivot];
	v[pivot]=v[j];
	v[j]=temp;
	QuickSort(v, E, j-1);
	QuickSort(v, j+1,D);
		
	}
}


void InsertionSort(int *v, int tam){
	
	int i, j, tmp;
	  
	 for(i = 1; i < tam; i++){
	  tmp = v[i];
	  for(j = i-1; j >= 0 && tmp < v[j]; j--){
	   v[j+1] = v[j];
	  }
	  v[j+1] = tmp;
	 }
}

int BinarySearch(int *v, int item, int low, int high){
	if(high <= low){
		return (item > v[low])? (low + 1): low;
	}
	
	int mid = (low + high)/2;
	
	if(item == v[mid]){
		return mid+1;
	}
	
	if(item > v[mid]){
		return BinarySearch(v, item, mid+1, high);
	}
	return BinarySearch(v, item, low, mid-1);
}

void BinaryInsertionSort(int *v, int tam){
	int i, loc, j, k, selected;
	
	for(i = 1; i < tam; i++){
		j = i - 1;
		selected = v[i];
		loc = BinarySearch(v, selected, 0, j);
		while(j >= loc){
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = selected;
	}
}

void SelectionSort(int *v, int tam){
	int vMenor, vAux, vTemp, vTroca;
	
	for(vAux = 0; vAux < tam-1; vAux++){
		vMenor = vAux;
		for(vTemp = vAux + 1; vTemp < tam; vTemp++){
			if(v[vTemp] < v[vMenor]){
				vMenor = vTemp;
			}
						
			if(vMenor != vAux){
				vTroca = v[vAux];
				v[vAux] = v[vMenor];
				v[vMenor] = vTroca;
			}
		}
	}	
}

void criaHeap(int *vet, int i, int f){
    int aux = vet[i];
    int j = 2*i + 1;
    
    while(j <= f){
        if(j < f){
            if(vet[j] < vet[j + 1]){
                j = j + 1;
            }
        }
        
        if(aux < vet[j]){
            vet[i] = vet[j];
            i = j;
            j = 2 * i + 1;
        }else{
            j = f + 1;
        }
        vet[i] = aux;
    }
}

void HeapSort(int *vet, int n){
    int i, aux;
    for(i = (n - 1)/2; i >= 0; i--){
        criaHeap(vet, i, n-1);
    }
    
    for(i = n - 1; i >= 1; i--){
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        criaHeap(vet, 0, i - 1);
    }
}

void merge(int *vet, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim-inicio+1;
    p1 = inicio;
    p2 = meio+1;
    temp = (int *) malloc(tamanho*sizeof(int));
    if(temp != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(vet[p1] < vet[p2]){
                    temp[i] = vet[p1++];
                }else{
                    temp[i] = vet[p2++];
                }
                
                if(p1 > meio) fim1 = 1;
                if(p2 > fim) fim2 = 1;
            }else{
                if(!fim1){
                    temp[i] = vet[p1++];
                }else{
                    temp[i] = vet[p2++];
                }
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++){
            vet[k] = temp[j];
        }
    }
    free(temp);
}

void MergeSort(int *vet, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        MergeSort(vet, inicio,meio);
        MergeSort(vet, meio+1,fim);
        merge(vet, inicio,meio,fim);
    }
    
}

struct balde
{
    int qtd;
    int vl[TAM];
};

void bubble(int *v,int tam)
{
    int i,j,temp,flag;
    if(tam)
        for(j=0; j<tam-1; j++)
        {
            flag=0;
            for(i=0; i<tam-1; i++)
            {
                if(v[i+1]<v[i])
                {
                    temp=v[i];
                    v[i]=v[i+1];
                    v[i+1]=temp;
                    flag=1;
                }
            }
            if(!flag)
                break;
        }
}

void BucketSort(int *v, int n){
    int i,j,maior,menor,nbaldes,pos;
    struct balde *bd;
    maior=menor=v[0];

    for(i=1; i<n; i++)
    {
        if(v[i]>maior)
        {
            maior = v[i];
        }
        if(v[i]<menor)
        {
            menor = v[i];
        }
    }

    nbaldes = (maior-menor) / TAM + 1;

    bd = (struct balde *)malloc(nbaldes * sizeof(struct balde));

    for(i=0; i<nbaldes; i++)
    {
        bd[i].qtd=0;
    }

    for(i=0; i<n; i++)
    {
        pos=(v[i]-menor)/TAM;
        bd[pos].vl[bd[pos].qtd]=v[i];
        bd[pos].qtd++;
    }
    pos = 0;
    for(i=0; i<nbaldes; i++)
    {
        bubble(bd[i].vl,bd[i].qtd);
        for(j=0; j<bd[i].qtd; j++)
        {
            v[pos] = bd[i].vl[j];
            pos++;
        }
    }
    free(bd);
}

void imprimeVetor(int *v, int tam){
	int i;
		for(i=0;i<tam;i++)
			printf("\nv[%d]: %d", i,v[i]);
}

void copiaVetor(int *v1, int *v2, int tam){
    int i;
    for(i = 0; i < tam; i++){
        v2[i] = v1[i];
    }
}

int main(int argc, char *argv[])
{
  // ======== Declaração de Variaveis
  int i, tam;
  
  
  // ======== Entrando com o tamanho do vetor
  printf("Digite o tamanho do vetor: ");
  scanf("%d", &tam);
    int *vetor1;
    int *vetor2;
    

  // ======== Alocando o tamanho do vetor em um ponteiro
  vetor1 = (int *)(malloc(tam * sizeof(int)));
  vetor2 = (int *)(malloc(tam * sizeof(int)));
  
  if( vetor1 == NULL || vetor2 == NULL)
  {
  	printf("\nErro de alocacao de memoria");
  	system("pause");
  	exit(1);
  }
  
  printf("\n");
  
  
  // ======== Gera valores aleatorios para o vetor
  for( i = 0; i < tam; i++)
  {
  	vetor1[i] = rand() % tam;
  }
  copiaVetor(vetor1, vetor2, tam);
  
  
   // ======== Printa o vetor desordenado
	//imprimeVetor(vetor2, tam);
  	printf("\n\n");
	 
	 
	 // ======== Chamadas dos algoritimos de ordenação
	 clock_t begin;
	 clock_t end;
	 	
	//BubbleSort
	begin = clock();
	BubbleSort(vetor2, tam);
	end = clock();
	printf("Tempo de Execucao BubbleSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    copiaVetor(vetor1, vetor2,tam);
    
	// QuickSort
	begin = clock();
	QuickSort(vetor2, 0, tam);
	end = clock();
	printf("Tempo de Execucao QuickSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	
	copiaVetor(vetor1, vetor2,tam);
	
	// InsertionSort
	begin = clock();
	InsertionSort(vetor2, tam);
	end = clock();
	printf("Tempo de Execucao InsertionSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	
	copiaVetor(vetor1, vetor2,tam);
	
	// BinaryInsertionSort
	begin = clock();
	BinaryInsertionSort(vetor2, tam);
	end = clock();
	printf("Tempo de Execucao BinaryInsertionSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	
	copiaVetor(vetor1, vetor2,tam);

	// SelectionSort
	begin = clock();
	SelectionSort(vetor2, tam);
	end = clock();
	printf("Tempo de Execucao SelectionSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	
	copiaVetor(vetor1, vetor2,tam);
	
	// HeapSort
	begin = clock();
	HeapSort(vetor2, tam);
	end = clock();
	printf("Tempo de Execucao HeapSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	
	copiaVetor(vetor1, vetor2,tam);
	
	// MergeSort
	begin = clock();
	MergeSort(vetor2, 0, tam-1);
	end = clock();
	printf("Tempo de Execucao MergeSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	
	copiaVetor(vetor1, vetor2,tam);
	
	// BucketSort
	begin = clock();
	BucketSort(vetor2, tam);
	end = clock();
	printf("Tempo de Execucao BucketSort: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
	

	//imprimeVetor(vetor2, tam);
	printf("\n\n");
	
	free(vetor1);
  	free(vetor2);
  	
  	system("pause");
  	return 0;
}


