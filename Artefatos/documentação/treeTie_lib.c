//Implementacao arvore Trie
//Equipe C
//Isabela Romeiro S. C. Rosa
//Tayrone Cordeiro de M. Marques
//Thaynnara Luciano dos Santos

#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 26

typedef struct Trie{
	int folha;	//1 quando o no e folha
	struct Trie* caractere[CHAR_SIZE];
}no;

no* novoNo(){
	no* novo = (no*)malloc(sizeof(no));
	novo->folha = 0;

	for (int i = 0; i < CHAR_SIZE; i++)
		novo->caractere[i] = NULL;

	return novo;
}

void inserir(no* *head, char* str){
	no* atual = *head;
	while (*str){
		//cria um novo no se caminho nao existir
		//*str-'a' normaliza a posicao do vetor
		if (atual->caractere[*str - 'a'] == NULL)
			atual->caractere[*str - 'a'] = novoNo();

		//vai para o proximo no
		atual = atual->caractere[*str - 'a'];

		//vai para o proximo caractere
		str++;
	}

	//marca o no atual como folha
	atual->folha = 1;
}

//retorna 1 se encontra a string e 0 se nao 
int pesquisa(no* head, char* str){
	//retorna 0 se esta vazia
	if (head == NULL)
		return 0;

	no* atual = head;
	while (*str){
		//vai para o proximo no
		atual = atual->caractere[*str - 'a'];

		//se a string nao existe
		if (atual == NULL)
			return 0;

		str++;
	}


	//se o no atual e folha, achou a string entao retorna 1
	return atual->folha;
}

//retorna 1 se o no atual tem algum filho
int temFilho(no* atual){
	for (int i = 0; i < CHAR_SIZE; i++)
		if (atual->caractere[i])
			return 1;

	return 0;
}

int excluir(no* *atual, char* str){
	//retorna 0 se esta vazia
	if (*atual == NULL)
		return 0;

	//se nao esta no fim da string
	if (*str){
		//chamada recursiva para o no correspondente ao proximo caractere na string e se retorna 1, apaga o no atual (se nao e folha) 
		if (*atual != NULL && (*atual)->caractere[*str - 'a'] != NULL &&
			excluir(&((*atual)->caractere[*str - 'a']), str + 1) &&
			(*atual)->folha == 0){
			if (!temFilho(*atual)){
				free(*atual);
				(*atual) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	//se esta no fim da string
	if (*str == '\0' && (*atual)->folha){
		//se no atual nao tem filho
		if (!temFilho(*atual)){
			free(*atual); //exclui no atual
			(*atual) = NULL;
			return 1; //exclui nos pais nao folha
		}

		//se no atual e folha, mas tem filho
		else{
			//marca o no atual como nao folha
			(*atual)->folha = 0;
			return 0; //nao exclui seus nos pais
		}
	}

	return 0;
}

int main(){
	no* head = novoNo();

	inserir(&head, "hello");
	printf("%d ", pesquisa(head, "hello"));   	// print 1

	inserir(&head, "helloworld");
	printf("%d ", pesquisa(head, "helloworld"));  // print 1

	printf("%d ", pesquisa(head, "helll"));   	// print 0 (Not present)

	inserir(&head, "hell");
	printf("%d ", pesquisa(head, "hell"));		// print 1

	inserir(&head, "h");
	printf("%d \n", pesquisa(head, "h")); 		// print 1 + newline

	excluir(&head, "hello");
	printf("%d ", pesquisa(head, "hello"));   	// print 0 (hello deleted)
	printf("%d ", pesquisa(head, "helloworld"));  // print 1
	printf("%d \n", pesquisa(head, "hell"));  	// print 1 

	excluir(&head, "h");
	printf("%d ", pesquisa(head, "h"));   		// print 0 (h deleted)
	printf("%d ", pesquisa(head, "hell"));		// print 1
	printf("%d\n", pesquisa(head, "helloworld")); // print 1

	excluir(&head, "helloworld");
	printf("%d ", pesquisa(head, "helloworld"));  // print 0
	printf("%d ", pesquisa(head, "hell"));		// print 1

	excluir(&head, "hell");
	printf("%d\n", pesquisa(head, "hell"));   	// print 0

	if (head == NULL)
		printf("Trie empty!!\n");

	printf("%d ", pesquisa(head, "hell"));		// print 0

	return 0;
}