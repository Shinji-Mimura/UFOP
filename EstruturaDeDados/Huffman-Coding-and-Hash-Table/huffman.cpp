#include "huffman.hpp"

struct minimo{
    char simb;
    unsigned freq;
    Minimo *esquerda, *direita;

};

struct heap{
    unsigned size;
    unsigned capacity;
    Minimo** array;
};

Minimo* cria_no(char caracter, unsigned freq){
    Minimo* temp = new Minimo;
    temp->esquerda = temp->direita = NULL;
    temp->simb = caracter;
    temp->freq = freq;
    return temp;
}

Heap* cria_heap(unsigned capacity){
    Heap* aux = new Heap;
    aux->size = 0;
    aux->capacity = capacity;
    aux->array = new Minimo*[capacity];
    return aux;
}

void troca_no(Minimo** a, Minimo** b){
    Minimo* aux = *a;
    *a = *b;
    *b = aux;
}

void heapificar(Heap* heapmin, int idx){
    int menor = idx;
    unsigned esq = 2*idx+1;
    unsigned dir = 2*idx+2;

    if (esq < getSize(heapmin) && getFreq(heapmin->array[esq]) < getFreq(heapmin->array[menor])){
        menor = esq;
    }

    if (dir < getSize(heapmin) && getFreq(heapmin->array[dir]) < getFreq(heapmin->array[menor])){
        menor = dir;
    }

    if (menor != idx){
        troca_no(&heapmin->array[menor],&heapmin->array[idx]);
        heapificar(heapmin,menor);
    }

}

int tam_um(Heap* heapmin){
    return(heapmin->size == 1);
}

Minimo* extrai_menor(Heap* heapmin){
    Minimo* temp = heapmin->array[0];
    heapmin->array[0] = heapmin->array[heapmin->size-1];

    --heapmin->size;
    heapificar(heapmin,0);
    return temp;

}

void insere_heap(Heap* heapmin, Minimo* no){
    ++heapmin->size;
    int i = getSize(heapmin) - 1;
    while (i && getFreq(no) < getFreq(heapmin->array[(i-1)/2])){
        heapmin->array[i] = heapmin->array[(i-1)/2];
        i = (i-1)/2;
    }
    heapmin->array[i] = no;
}

void cria_heap_minimo(Heap* heapmin){
    int n = getSize(heapmin) - 1;
    int i;
    for (i = (n-1)/2; i >= 0; --i){
        heapificar(heapmin,i);
    }
}

void imprime(int arr[], int n){
    int i;
    for ( i = 0; i < n; i++){
        cout<<arr[i];
    }
    cout<<endl;
}

int check_folha(Minimo* root){
    return !(root->esquerda) && !(root->direita);
}

Heap* constroi(char data[], int freq[],int size){
    Heap* aux = cria_heap(size);
    for(int i = 0; i < size; i++){
        aux->array[i] = cria_no(data[i],freq[i]);
    }
    aux->size = size;
    cria_heap_minimo(aux);

    return aux;


}

Minimo* arvore_huffman(char data[], int freq[], int size){
    Minimo *esq, *dir, *cima;
    Heap* aux = constroi(data,freq,size);
    while (!tam_um(aux)){
        esq = extrai_menor(aux);
        dir = extrai_menor(aux);
        cima = cria_no('$',getFreq(esq) + getFreq(dir));

        cima->esquerda = esq;
        cima->direita = dir;

        insere_heap(aux,cima);
    }

    return extrai_menor(aux);

}

void imprime_codigo(Minimo* root, int arr[], int cima){
    if (root->esquerda){
        arr[cima] = 0;
        imprime_codigo(root->esquerda,arr,cima+1);
    }

    if (root->direita){
        arr[cima] = 1;
        imprime_codigo(root->direita,arr,cima+1);
    }

    if (check_folha(root)){
        if((int)getSimb(root)!= 10&&(int)getSimb(root)!=32){
          cout<<"\t"<<getSimb(root)<<" == \t"<<(int)getSimb(root)<<"\t----->";
        }
        else{
          if((int)getSimb(root)==10)
            cout<<"   [ENDL] == \t"<<(int)getSimb(root)<<"\t----->";
          else
            cout<<"  [SPACE] == \t"<<(int)getSimb(root)<<"\t----->";
        }
        imprime(arr,cima);
    }

}

void huffman_cod(char data[], int freq[], int size){

    Minimo* root = arvore_huffman(data,freq,size);
    int arr[100], cima = 0;
    imprime_codigo(root,arr,cima);
}

int sweep(char arr[], int freq[]){
  ifstream arq("texto.txt");
  char x;
  int qtd = 0;
  for(int i=0;arq.get(x); ){
    bool flag = 0;

    for(int j=0; arr[j]!='/'; j++){
      if(arr[j]==x){
        freq[j]++;
        flag = 1;
        break;
      }
    }
    if(flag==0){
      arr[i]=x;
      freq[i]++;
      i++;
      qtd++;
    }
  }
  arq.close();
  return qtd;
}

//SETs & GETs//////////////////////////////////////////////////////////////////////

char getSimb(Minimo *a){
  return a->simb;
}
unsigned getFreq(Minimo *a){
  return a->freq;
}
unsigned getSize(Heap *a){
  return a->size;
}
unsigned getCapacity(Heap *a){
  return a->capacity;
}
void setSimb(Minimo *a, char b){
  a->simb = b;
}
void setFreq(Minimo *a, unsigned b){
  a->freq = b;
}
void setSize(Heap *a, unsigned b){
  a->size = b;
}
void setCapacity(Heap *a, unsigned b){
  a->capacity = b;
}

//Questao A////////////////////////////////////////////////////////////////////////
void A(){
    char arr[100];
    int freq[100];
    for(int i=0; i<=100; i++){
      freq[i] = 0;
      arr[i] = '/';
    }
    int qtd = sweep(arr, freq);
    char *arr2 = new char[qtd];
    int *freq2 = new int[qtd];
    for(int i=0; i<qtd; i++){
      arr2[i] = arr[i];
      freq2[i] = freq[i];
    }
    huffman_cod(arr2,freq,qtd);

}
