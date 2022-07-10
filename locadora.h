#ifndef LOCAR_H_INCLUDED
#define LOCAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura veiculo
typedef struct veiculo{
    int id;
	int id_cliente;
	char modelo[100];
	char placa[20];
	char ano[6];
	float preco;
} t_veiculo;

// Estrutura endereco do cliente
typedef struct {
    char rua[50];
    char numero[5];
    char bairro[50];
}ender;

// Estrutura cliente
typedef struct cliente{
	int id;
	char nome[100];
	char cpf[12];
	char telefone[9];
	ender endereco;
} t_cliente;

// ************************* Prot�tipos das fun��es menu *************************

char menu(); //Exibe o menu com todas as op��es do programa, retorna um caractere do n�mero correspondente a op��o
void cadastrar_cliente(); //Cadastro um cliente pedindo apenas o nome
void cadastrar_veiculo(); //Cadastra um veiculo com nome e pre�o
void listar_veiculo(); //Mostra todos os veiculos cadastrados e as informa��es de aluguel
void listar_cliente(); //Exibe todos os clientes cadastrados
void pesquisar_veiculo(); //Pesquisa um veiculo e exibe suas informa��es
void pesquisar_cliente(); //Pesquisa um cliente e exibe suas informa��es
void alugar_veiculo(); //Aluga um veiculo e atualiza o arquivo
void entregar_veiculo(); //Recebe um veiculo de um cliente e atualiza as informa��es no arquivo
void excluir_veiculo(); //Exclui um veiculo do arquivo
void excluir_cliente();//Exclui um cliente do arquivo
void excluir ();//faz um submenu para exclus�es
// ************************* Prot�tipos das fun��es auxiliares ********************

t_veiculo *obter_veiculo(FILE *arq_veiculo, int id_veiculo); /*Procura um veiculo pelo id do veiculo
Par�metros:
arq_veiculo: ponteiro para um arquivo aberto
id_veiculo: ID do veiculo que ser� buscado
retorno: um ponteiro para o veiculo encontrado ou NULL caso o ID n�o exista
*/

t_cliente *obter_cliente(FILE *arq_cliente, int id_cliente); /*Procura um cliente pelo seu id
Par�metros:
arq_cliente: ponteiro para um arquivo aberto
id_cliente: ID do cliente que ser� buscado
retorno: um ponteiro para o cliente encontrado ou NULL caso o ID n�o exista
*/

int existe_veiculo(FILE *arq_veiculo, int id_veiculo); /*Procura um veiculo pelo seu id e informa se ele foi encontrado
Par�metros:
arq_veiculo: ponteiro para um arquivo aberto
id_veiculo: ID do veiculo que ser� buscado
retorno: 1 para veiculo encontrado ou 0 caso o ID n�o exista
*/

int existe_cliente(FILE *arq_cliente, int id_cliente); /*Procura um cliente pelo seu id e informa se ele foi encontrado
Par�metros:
arq_cliente: ponteiro para um arquivo aberto
id_cliente: ID do cliente que ser� buscado
retorno: 1 se o cliente existe ou 0 caso o ID n�o exista
*/

void atualizar_veiculo(FILE *arq_veiculo, t_veiculo *veiculo_alugado); /*Atualiza as informa��es do veiculo no arquivo
Par�metros:
arq_veiculo: ponteiro para um arquivo aberto
veiculo_alugado: ponteiro para o veiculo que ser� atualizado
*/

int str_somente_numeros(char str[]); /*Informa se a string � um n�mero
Par�metros:
str: ponteiro para uma cadeia de caracteres
retorno: 1 se a string s� conter n�meros ou 0 caso contr�rio
*/

#endif // LOCAR_H_INCLUDED
