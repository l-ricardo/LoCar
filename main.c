#include "locadora.h"

int main(){
	char opcao;

    // loop infinito do programa
	while(1){

		opcao = menu(); // obtém a escolha do usuário

		// testa o valor de "opcao"
		if(opcao == '1') cadastrar_veiculo();
		else if(opcao == '2') cadastrar_cliente();
		else if(opcao == '3') listar_veiculo();
		else if(opcao == '4') listar_cliente();
		else if(opcao == '5') pesquisar_veiculo();
		else if(opcao == '6') pesquisar_cliente();
		else if(opcao == '7') alugar_veiculo();
		else if(opcao == '8') entregar_veiculo();
		else if(opcao == '9') excluir();
		else if(opcao == '0') break; // sair do loop while
		else {
			printf("\nOpcao invalida! Pressione <Enter> para continuar...");
			scanf("%*c");
            // limpando o buffer do teclado
            fseek(stdin, 0, SEEK_END);
        }
		system("cls");
	}
	printf("\nObrigado por usar a LoCar \n");
	return 0;
}


// função que exibe o menu e retorna a opção escolhida pelo usuário
char menu(){
	char opcao;

    printf("--------------------------------------------------------------------------------");
    printf("\n                                    LoCar                                 \n\n");
    printf("--------------------------------------------------------------------------------");
	printf("\n1. Cadastrar um veiculo\n");
	printf("2. Cadastrar um cliente\n");
	printf("3. Listar todos os veiculos\n");
	printf("4. Listar todos os clientes\n");
	printf("5. Pesquisar por veiculo\n");
	printf("6. Pesquisar por cliente\n");
	printf("7. Alugar um veiculo\n");
	printf("8. Devolver um veiculo\n");
	printf("9. Remover\n");
	printf("0. Sair\n");
	printf("Digite o numero da opcao: ");
	scanf("%1s%*c", &opcao); // o *c pega o Enter e descarta

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	// se chegou aqui, é porque a opção é válida
	return opcao;
}


//*************************************FUNCOES AUXILIARES***********************************

// função que verifica se uma string contém somente números
int str_somente_numeros(char str[]){
	int i = 0;
	int len_str = strlen(str);

	for(i = 0; i < len_str; i++) {
		if(str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}


// função que verifica se um veiculo existe, retorna 0 se NÃO existe e 1 caso contrário
int existe_veiculo(FILE *arq_veiculo, int id_veiculo){
	// vai para o início do arquivo, pois não sabemos a posição do ponteiro no arquivo
	rewind(arq_veiculo);

	t_veiculo veiculo;
	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	while(1){

		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculo);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		// verifica se o ID é igual
		if(veiculo.id == id_veiculo)
			return 1;
	}

	// se chegou aqui é porque NÃO existe o veiculo, então retorna 0
	return 0;
}


// função que verifica se um cliente existe, retorna 0 se NÃO existe e 1 caso contrário
int existe_cliente(FILE *arq_cliente, int id_cliente){
	// vai para o início do arquivo
	rewind(arq_cliente);

	t_cliente cliente;
	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	while(1){
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_cliente);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		// verifica se o ID é igual
		if(cliente.id == id_cliente)
			return 1;
	}

	// se chegou aqui é porque NÃO existe o cliente, então retorna 0
	return 0;
}


// função que obtém um cliente pelo ID
t_cliente *obter_cliente(FILE *arq_clientes, int id_cliente){
	// vai para o início do arquivo
	rewind(arq_clientes);

	t_cliente *cliente;

	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	// aloca espaço mesmo sem saber se o cliente existe
	cliente = (t_cliente *)malloc(sizeof(t_cliente));
	while(1){

		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(cliente, sizeof(t_cliente), 1, arq_clientes);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0){
			free(cliente); // libera a mémoria, pois o cliente não foi encontrado
			return NULL;
		}
		// verifica se os ID's são iguais
		if(cliente->id == id_cliente) break;
	}
	return cliente;
}


// função que obtém um veiculo pelo ID
t_veiculo *obter_veiculo(FILE *arq_veiculo, int id_veiculo){
	// vai para o início do arquivo
	rewind(arq_veiculo);

	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	t_veiculo *veiculo;

	// aloca espaço mesmo sem saber se o veiculo existe
	veiculo = (t_veiculo *)malloc(sizeof(t_veiculo));
	while(1){

		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(veiculo, sizeof(t_veiculo), 1, arq_veiculo);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		// verifica se os ID's são iguais
		if(veiculo->id == id_veiculo) return veiculo;
	}
	free(veiculo); // libera recursos
	return NULL;
}


// função para atualizar um veiculo, recebe o ponteiro para o arquivo e o veiculo
void atualizar_veiculo(FILE *arq_veiculo, t_veiculo *veiculo_alugado){
	// vai para o início do arquivo
	rewind(arq_veiculo);

	t_veiculo veiculo;
	// loop para percorrer o arquivo
	while(1){
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculo);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		// verifica se os ID's são iguais
		if(veiculo.id == veiculo_alugado->id){
			// fseek posiciona o arquivo
			fseek(arq_veiculo, - sizeof(t_veiculo), SEEK_CUR);
			// atualiza o veiculo
			fwrite(veiculo_alugado, sizeof(t_veiculo), 1, arq_veiculo);
			break; // sai do loop
		}
	}
}


//*************************************FUNCOES SUBMENU***********************************

// função para cadastrar cliente
void cadastrar_cliente(){
	// abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_cliente;
	arq_cliente = fopen("clientes.bin", "a+b");

	// testa a abertura do arquivo
	if(arq_cliente == NULL){
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1);
	}
	/*NÃO é interessante que o usuário digite o ID do cliente, esse
    ID tem que ser gerado automático, então temos que pegar o
    ID do último usuário cadastrado */
	int cont_bytes = 0;

	// cont irá guardar o número total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_cliente, 0, SEEK_END);
	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_cliente);

	t_cliente cliente;

	if(cont_bytes == 0){
		// se for 0, então não existe cliente cadastrado
		// coloco o ID começando de 1
		cliente.id = 1;
	}
	else{
		t_cliente ultimo_cliente;

		// utilizo a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(t_cliente) serve para posicionar
		// para que possamos pegar o último cliente cadastrado
		fseek(arq_cliente, cont_bytes - sizeof(t_cliente), SEEK_SET);

		// ler o cliente
		fread(&ultimo_cliente, sizeof(t_cliente), 1, arq_cliente);

		// o ID do cliente é o ID do último cliente acrescido em 1
		cliente.id = ultimo_cliente.id + 1;
	}
	system("cls"); //limpa o menu da tela
    printf("Cadastrando um novo cliente...\n");
	// ^\n indica para pegar até a quebra de linha
	// %*c descarta o enter
	// %99 pega somente os 99 primeiros caracteres digitados
	printf("\nDigite o nome do cliente: ");
	scanf("%99[^\n]%*c", cliente.nome);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

    printf("Digite o cpf do cliente: ");
	scanf("%11[^\n]%*c", cliente.cpf);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

    printf("Digite o telefone do cliente: ");
	scanf("%8[^\n]%*c", cliente.telefone);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	printf("Digite a rua do cliente: ");
	scanf("%49[^\n]%*c", cliente.endereco.rua);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	printf("Digite o numero da casa do cliente: ");
	scanf("%4[^\n]%*c", &cliente.endereco.numero);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	printf("Digite o bairro do cliente: ");
	scanf("%49[^\n]%*c", cliente.endereco.bairro);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_cliente, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&cliente, sizeof(t_cliente), 1, arq_cliente);

	// fecha o arquivo
	fclose(arq_cliente);

	printf("\nCliente \"%s\" cadastrado com sucesso!\n", cliente.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função para cadastrar veiculos
void cadastrar_veiculo(){
	// abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_veiculo;
	arq_veiculo = fopen("veiculo.txt", "a+b");

	// testa a abertura do arquivo
	if(arq_veiculo == NULL){
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}

	t_veiculo veiculo;

	/*NÃO é interessante que o usuário digite o ID do veiculo, esse
    ID tem que ser gerado automático, então temos que pegar o
    ID do último veiculo cadastrado*/
	int cont_bytes = 0;

	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_veiculo, 0, SEEK_END);
	// cont irá guardar o número total de bytes
	cont_bytes = ftell(arq_veiculo);

	if(cont_bytes == 0){
		// se for 0, então não existe veiculo cadastrado
		// coloco o ID começando de 1
		veiculo.id = 1;
	}
	else{
		t_veiculo ultimo_veiculo;

		// utiliza a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(t_cliente) serve para posicionar
		// para que possamos pegar o último veiculo cadastrado
		fseek(arq_veiculo, cont_bytes - sizeof(t_veiculo), SEEK_SET);

		// ler o veiculo
		fread(&ultimo_veiculo, sizeof(t_veiculo), 1, arq_veiculo);

		// o ID do veiculo é o ID do último veiculo acrescido em 1
		veiculo.id = ultimo_veiculo.id + 1;
	}
	system("cls"); //limpa o menu da tela
    printf("Cadastrando um novo veiculo...\n");

	// obtém o modelo do veiculo
	// ^\n indica para pegar até a quebra de linha
	// %*c descarta o enter
	// %49 eh a quantidade de caracteres que serao pegos
	printf("\nDigite o modelo do veiculo: ");
	scanf("%49[^\n]%*c", veiculo.modelo);
	// limpando o buffer do  teclado
    fseek(stdin, 0, SEEK_END);

    printf("Digite a placa do veiculo: ");
	scanf("%19[^\n]%*c", veiculo.placa);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

    printf("Digite o ano do veiculo: ");
	scanf("%4[^\n]%*c", veiculo.ano);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	do{
		char str_preco[6];
		float float_preco;
		int somente_numeros = 1;

		// obtém o preço da diaria do veiculo
		printf("Digite o valor da diaria do veiculo: ");
		scanf("%5s%*c", str_preco);
        // limpando o buffer do teclado
        fseek(stdin, 0, SEEK_END);

		// verifica se o preço possui somente números
		somente_numeros = str_somente_numeros(str_preco);
		// verifica se o preço contém somente números
		if(somente_numeros == 1){
			// se chegou aqui, é porque tudo está validado
			// preenche a variável float_preco com o valor de str_preco
			int int_preco;
			// exemplo: 459,50 deve digitar 45950
			sscanf(str_preco, "%i", &int_preco);
			float_preco = int_preco / 100.0;
			veiculo.preco = float_preco;
			break;
		}
	}while(1);

	// inicializa o id_cliente com -1 indicando que o veiculo NÃO está alugado
	veiculo.id_cliente = -1;

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_veiculo, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&veiculo, sizeof(t_veiculo), 1, arq_veiculo);

	// fecha o arquivo
	fclose(arq_veiculo);

	printf("\nVeiculo \"%s\" cadastrado com sucesso!\n", veiculo.modelo);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função para listar todos os clientes
void listar_cliente(){
	// rb => abre arquivo binário para leitura apenas
	FILE *arq_cliente;
	arq_cliente = fopen("clientes.bin", "rb");

	// testa a abertura do arquivo
	if(arq_cliente == NULL){
		printf("\nFalha ao abrir arquivo ou nenhum cliente foi cadastrado ate o momento.");
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c"); // pega o Enter e descarta
        // limpando o buffer do teclado
        fseek(stdin, 0, SEEK_END);
		return;
	}

	// variável que indica se encontrou pelo menos 1 cliente
	int encontrou_cliente = 0;
	t_cliente cliente;

	system("cls"); //limpa o menu da tela
	printf("Listando todos os clientes...\n");
	// loop para percorrer o arquivo
	while(1){
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_cliente);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		// atualiza a variável indicando que encontrou
		// pelo menos um cliente
		encontrou_cliente = 1;

		// mostra os dados do cliente
		printf("\nID do cliente: %i\n", cliente.id);
		printf("Nome do cliente: %s\n", cliente.nome);
        printf("CPF do cliente: %s\n", cliente.cpf);
        printf("Telefone do cliente: %s\n", cliente.telefone);
		printf("Rua %s, %s. Bairro %s\n", cliente.endereco.rua, cliente.endereco.numero, cliente.endereco.bairro);
    }

	if(encontrou_cliente == 0)
		printf("\nNenhum cliente cadastrado.\n");

	fclose(arq_cliente);

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função para listar todos os veiculos
void listar_veiculo(){
	// lista de todos os veiculo

	// rb => abre para leitura somente, ponteiro para o início do arquivo
	FILE *arq_veiculo;
	arq_veiculo = fopen("veiculo.txt", "rb");
	FILE *arq_cliente;
	arq_cliente = fopen("clientes.bin", "rb");

	// se o arquivo de veiculo não existe
	if(arq_veiculo == NULL){
		printf("\nFalha ao abrir arquivo ou nenhum veiculo foi cadastrado ate o momento");
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c"); // pega o Enter e descarta
        // limpando o buffer do teclado
        fseek(stdin, 0, SEEK_END);
		return;
	}

	// variável que indica se encontrou pelo menos 1 veiculo
	int encontrou_veiculo = 0;

	system("cls"); //limpa o menu da tela
	printf("Listando todos os veiculos...\n");
	// loop para percorrer o arquivo
	t_veiculo veiculo;

	while(1){
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculo);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		// atualiza a variável indicando que encontrou
		// pelo menos um veiculo
		encontrou_veiculo = 1;

		// mostra os dados do veiculo
		printf("\nID do veiculo: %i\n", veiculo.id);
		printf("Modelo do veiculo: %s\n", veiculo.modelo);
		printf("Placa do veiculo: %s\n", veiculo.placa);
		printf("Ano do veiculo: %s\n", veiculo.ano);
		printf("Valor da diaria: %.2f\n", veiculo.preco);


		// se id_cliente for diferente de -1, então o veiculo está alugado, pois
		// possui algum id válido do cliente que alugou o veiculo.
		// se id_cliente for igual a -1, indica que o veiculo não está alugado,
		// pois o id -1 NÃO é um id válido
		if(veiculo.id_cliente != -1){
			// se o arquivo de clientes não existir, atenção esse teste
			// não pode ser realizado no início da função, pois pode acontecer de
			// todos os veiculos não estarem alugados
			if(arq_cliente == NULL){
				printf("\nFalha ao abrir arquivo!\n");
				fclose(arq_veiculo); // libera recursos
				exit(1); // aborta o programa
			}
			t_cliente *cliente = obter_cliente(arq_cliente, veiculo.id_cliente);
			printf("Alugado? Sim. Cliente: %s\n", cliente->nome);
			free(cliente); // evita vazamento de memória
		}
		else
			printf("Alugado? Nao\n");
	}

	// verifica se encontrou pelo menos um veiculo
	if(encontrou_veiculo == 0)
		printf("\nNenhum veiculo cadastrado.\n");

	// fecha os arquivos em ordem inversa que foram abertos
	if(arq_cliente != NULL)
		fclose(arq_cliente); // apenas se foi aberto
	fclose(arq_veiculo);

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função para pesquisar por algum veiculo
void pesquisar_veiculo(){
	char modelo[100];
	int encontrou_veiculo = 0;

	// rb => abre para leitura somente
	FILE *arq_veiculo;
	arq_veiculo = fopen("veiculo.txt", "rb");
	FILE *arq_cliente;
	arq_cliente = fopen("clientes.bin", "rb");

	// testa a abertura do arquivo
	if(arq_veiculo == NULL){
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}
    system("cls"); //limpa o menu da tela
    printf("Pesquisando veiculos...\n");
	printf("\nDigite o modelo do veiculo: ");
	scanf("%49[^\n]%*c", modelo);

	printf("\nVeiculos do modelo \"%s\":\n\n", modelo);
	// loop para percorrer o arquivo
	// busca linear, pois o campo modelo não possui índice
	t_veiculo veiculo;
	while(1){
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculo);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		char modelo_aux[100];
		// faz uma cópia para não alterar veiculo.modelo
		strcpy(modelo_aux, veiculo.modelo);

		// verifica se é igual
		if(strcmp(strupr(modelo_aux), strupr(modelo)) == 0){
			// mostra os dados do veiculo
            printf("\nID do veiculo: %i\n", veiculo.id);
            printf("Modelo do veiculo: %s\n", veiculo.modelo);
            printf("Placa do veiculo: %s\n", veiculo.placa);
            printf("Ano do veiculo: %s\n", veiculo.ano);
            printf("Valor da diaria: %.2f\n", veiculo.preco);

			if(veiculo.id_cliente != -1){
				// se o arquivo de clientes não existir
				if(arq_cliente == NULL){
					printf("\nFalha ao abrir arquivo!\n");
					fclose(arq_veiculo); // libera recursos
					exit(1); // aborta o programa
				}
				t_cliente *cliente = obter_cliente(arq_cliente, veiculo.id_cliente);
				printf("Alugado? Sim. Cliente: %s\n", cliente->nome);
				free(cliente); // evita vazamento de memória
			}
			else
				printf("Alugado? Nao\n");
			encontrou_veiculo = 1;
			printf("\n");
		}
	}

	if(encontrou_veiculo == 0)
		printf("Nenhum veiculo encontrado.\n\n");

	fclose(arq_veiculo);

	printf("Pressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função para pesquisar por algum cliente
void pesquisar_cliente(){
	char nome[100];
	int encontrou_cliente = 0;

	// rb+ => abre para leitura somente
	FILE *arq_cliente;
	arq_cliente = fopen("clientes.bin", "rb");

	// testa a abertura do arquivo
	if(arq_cliente == NULL){
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}
    system("cls"); //limpa o menu da tela
    printf("Pesquisando clientes...\n");

	printf("\nDigite o nome do cliente: ");
	scanf("%99[^\n]%*c", nome);

	printf("\nClientes com o nome \"%s\":\n\n", nome);
	// loop para percorrer o arquivo
	t_cliente cliente;
	while(1){
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_cliente);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0) break;

		char nome_aux[100];
		// faz uma cópia para não alterar cliente->nome
		strcpy(nome_aux, cliente.nome);

		// verifica se é igual
		if(strcmp(strupr(nome_aux), strupr(nome)) == 0){
			// mostra os dados do cliente
			printf("ID do cliente: %i\n", cliente.id);
            printf("Nome do cliente: %s\n", cliente.nome);
            printf("CPF do cliente: %s\n", cliente.cpf);
            printf("Telefone do cliente: %s\n", cliente.telefone);
            printf("Rua %s, %s. Bairro %s\n\n", cliente.endereco.rua, cliente.endereco.numero, cliente.endereco.bairro);
			encontrou_cliente = 1;
		}
	}

	if(encontrou_cliente == 0)
		printf("Nenhum cliente encontrado.\n\n");

	// fecha o arquivo
	fclose(arq_cliente);

	printf("Pressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função responsável pelo aluguel dos veiculos
void alugar_veiculo(){
	char str_id_cliente[10];
	int id_cliente;

	// rb+ abre para leitura/atualização
	FILE *arq_veiculo;
	arq_veiculo = fopen("veiculo.txt", "rb+");
	FILE *arq_cliente;
	arq_cliente = fopen("clientes.bin", "rb+");

	// se não conseguiu abrir, então cria o arquivo
	// wb+ abre para escrita/atualização (cria o arquivo se ele NÃO existir)
	if(arq_veiculo == NULL){
		arq_veiculo = fopen("veiculo.txt", "wb+");
		if(arq_veiculo == NULL)	{
			printf("\nFalha ao criar arquivo!\n");
			exit(1); // aborta o programa
		}
	}

	// se não conseguiu abrir, então cria o arquivo
	// wb+ abre para escrita/atualização (cria o arquivo se ele NÃO existir)
	if(arq_cliente == NULL){
		arq_cliente = fopen("clientes.bin", "wb+");
		if(arq_cliente == NULL){
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}

    system("cls"); //limpa o menu da tela
    printf("Alugando um veiculo...\n");

	// obtém o ID do cliente
	printf("\nDigite o ID do cliente: ");
	scanf("%10s%*c", str_id_cliente);
	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	if(str_somente_numeros(str_id_cliente) == 1){
		// se caiu aqui é porque o ID possui somente números, então
		// preenche a variável "id_cliente" com o valor de "str_id_cliente"
		sscanf(str_id_cliente, "%i", &id_cliente);

		// verifica se o ID do do cliente existe
		if(existe_cliente(arq_cliente, id_cliente)){
			char str_id_veiculo[10];
			int id_veiculo;

			printf("\nDigite o ID do veiculo: ");
			scanf("%10s%*c", str_id_veiculo);

            // limpando o buffer do teclado
            fseek(stdin, 0, SEEK_END);

			if(str_somente_numeros(str_id_veiculo) == 1){
				// se chegou aqui é porque o ID do veiculo é válido
				sscanf(str_id_veiculo, "%i", &id_veiculo);

				// obtém o veiculo pelo ID
				t_veiculo *veiculo = obter_veiculo(arq_veiculo, id_veiculo);

				// testa se o veiculo existe...
				if(veiculo != NULL){
					// se chegou aqui é porque o veiculo existe
					// testa se o veiculo já está alugado
					if(veiculo->id_cliente != -1)
						printf("\nO veiculo \"%s\" ja esta alugado!\n", veiculo->modelo);
					else {
						// se o veiculo NÃO está alugado, então seta o
						// id_cliente do veiculo para associar o cliente
						// ao aluguel do veiculo em questão
						veiculo->id_cliente = id_cliente;
						atualizar_veiculo(arq_veiculo, veiculo); // atualiza o veiculo no arquivo
						printf("\nVeiculo \"%s\" alugado com sucesso!\n", veiculo->modelo);
					}
					free(veiculo); // libera o veiculo alocado
				}
				else
					printf("\nNao existe veiculo com o ID \"%i\".\n", id_veiculo);
			}
			else
				printf("\nO ID so pode conter numeros!\n");
		}
		else
			printf("\nNao existe cliente com o ID \"%i\".\n", id_cliente);
	}
	else
		printf("\nO ID so pode conter numeros!\n");

	// fecha os arquivos
	fclose(arq_cliente);
	fclose(arq_veiculo);

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

    // limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}


// função responsável pela entrega dos veiculos
void entregar_veiculo(){
	char str_id_veiculo[10];
	int id_veiculo;

	// rb+ abre para leitura/atualização
	FILE *arq_veiculo;
	arq_veiculo = fopen("veiculo.txt", "rb+");

	// se não conseguiu abrir, então cria o arquivo
	// wb+ abre para escrita/atualização (cria o arquivo se ele NÃO existir)
	if(arq_veiculo == NULL){
		arq_veiculo = fopen("veiculo.txt", "wb+");
		if(arq_veiculo == NULL){
			printf("\nFalha ao criar arquivo(s)!\n");
			exit(1); // aborta o programa
		}
	}

    system("cls"); //limpa o menu da tela
    printf("Devolvendo um veiculo...\n");

	printf("\nDigite o ID do veiculo: ");
	scanf("%10s%*c", str_id_veiculo);

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	if(str_somente_numeros(str_id_veiculo) == 1){
		// se chegou aqui é porque o ID do veiculo é válido
		sscanf(str_id_veiculo, "%i", &id_veiculo);

		// obtém o veiculo pelo ID
		t_veiculo *veiculo = obter_veiculo(arq_veiculo, id_veiculo);

		// testa se o veiculo existe...
		if(veiculo != NULL){
			// se chegou aqui é porque o veiculo existe
			// testa se o veiculo já foi entregue
			if(veiculo->id_cliente == -1)
				printf("\nO veiculo \"%s\" ja esta disponivel!\n", veiculo->modelo);
			else{
				// se o veiculo NÃO foi entregue, então seta o
				// id_cliente para -1 para indicar que ele foi entregue
				veiculo->id_cliente = -1;
				atualizar_veiculo(arq_veiculo, veiculo); // atualiza o veiculo no arquivo
				printf("\nVeiculo \"%s\" entregue com sucesso!\n", veiculo->modelo);
			}
			free(veiculo); // libera memória
		}
		else
			printf("\nNao existe veiculo com o ID \"%i\".\n", id_veiculo);
	}
	else
		printf("\nO ID so pode conter numeros!\n");

	// fecha o arquivo
	fclose(arq_veiculo);

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}
//sub menu para exclusão de pessoas e veículos
void excluir(){
char opcaodel;
system("cls");
printf("O que voce deseja excluir:");
printf("\n1-Veiculos");
printf("\n2-Clientes\n");
printf("Digite uma opcao valida:");
scanf("%1s%*c", &opcaodel);
if(opcaodel == '1') excluir_veiculo();
else if(opcaodel == '2') excluir_cliente();
}
//função responsável por excluir clientes
void excluir_cliente(){
    	char str_id_cliente[10];
	int id_cliente;

    system("cls"); //limpa o menu da tela
    printf("Excluindo um cliente...\n");

	printf("\nDigite o ID do cliente: ");
	scanf("%10s%*c", str_id_cliente);

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	// verifica se str_id_cliente só contém números
	if(str_somente_numeros(str_id_cliente) == 1){
		// se chegou aqui é porque o ID do cliente é válido
		sscanf(str_id_cliente, "%i", &id_cliente);

		// rb abre para leitura (o arquivo deve existir)
		FILE *arq_cliente;
		arq_cliente = fopen("clientes.bin", "rb");

		if(arq_cliente == NULL){
			printf("\nFalha ao abrir arquivo(s)!\n");
			exit(1); // aborta o programa
		}

		// verifica se o veiculo existe
		if(existe_cliente(arq_cliente, id_cliente) == 1){
			char nome_cliente[100];
			// abre um novo arquivo temporário
			FILE *arq_temp = fopen("temp_cliente.bin", "a+b");
			if(arq_temp == NULL){
				printf("\nFalha ao criar arquivo temporario!\n");
				fclose(arq_cliente);
				exit(1); // aborta o programa
			}
			rewind(arq_cliente); // vai para o início do arquivo
			t_cliente cliente;

			// loop para percorrer o arquivo
			while(1){

				// fread retorna o número de elementos lidos com sucesso
				size_t result = fread(&cliente, sizeof(t_cliente), 1, arq_cliente);

				// se for 0, é porque não há mais elemento, então sai do loop
				if(result == 0) break;

				// só copia pro novo arquivo se for diferente
				if(cliente.id != id_cliente){
					// escreve no arquivo temporário
					fwrite(&cliente, sizeof(t_cliente), 1, arq_temp);
				}
				else
					strcpy(nome_cliente, cliente.nome);
			}

			// antes de fazer operações de remover arquivo e renomear,
			// é preciso fechar os dois arquivos
			fclose(arq_cliente);
			fclose(arq_temp);

			// depois de fechar o arquivo, então tentamos remover
			if(remove("clientes.bin") != 0)
				printf("\nErro ao deletar o arquivo \"clientes.bin\"\n");
			else {
				// renomeia o arquivo
				int r = rename("temp_cliente.bin", "clientes.bin");
				if(r != 0){
					printf("\nPermissao negada para renomear o arquivo!\n");
					printf("Feche esse programa bem como o arquivo \"temp_cliente.bin\" e renomeie manualmente para \"cliente.bin\"\n");
				}
				else
					printf("\nCliente \"%s\" removido com sucesso!\n", nome_cliente);
			}
		}
		else {
			fclose(arq_cliente);
			printf("\nNao existe cliente com o ID \"%i\".\n", id_cliente);
		}
	}
	else
		printf("\nO ID so pode conter numeros!\n");

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}

// função responsável por excluir veiculos
void excluir_veiculo(){
	char str_id_veiculo[10];
	int id_veiculo;

    system("cls"); //limpa o menu da tela
    printf("Excluindo um veiculo...\n");

	printf("\nDigite o ID do veiculo: ");
	scanf("%10s%*c", str_id_veiculo);

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);

	// verifica se str_id_veiculos só contém números
	if(str_somente_numeros(str_id_veiculo) == 1){
		// se chegou aqui é porque o ID do veiculo é válido
		sscanf(str_id_veiculo, "%i", &id_veiculo);

		// rb abre para leitura (o arquivo deve existir)
		FILE *arq_veiculo;
		arq_veiculo = fopen("veiculo.txt", "rb");

		if(arq_veiculo == NULL){
			printf("\nFalha ao abrir arquivo(s)!\n");
			exit(1); // aborta o programa
		}

		// verifica se o veiculo existe
		if(existe_veiculo(arq_veiculo, id_veiculo) == 1){
			char modelo_veiculo[100];
			// abre um novo arquivo temporário
			FILE *arq_temp = fopen("temp_veiculo.txt", "a+b");
			if(arq_temp == NULL){
				printf("\nFalha ao criar arquivo temporario!\n");
				fclose(arq_veiculo);
				exit(1); // aborta o programa
			}
			rewind(arq_veiculo); // vai para o início do arquivo
			t_veiculo veiculo;

			// loop para percorrer o arquivo
			while(1){

				// fread retorna o número de elementos lidos com sucesso
				size_t result = fread(&veiculo, sizeof(t_veiculo), 1, arq_veiculo);

				// se for 0, é porque não há mais elemento, então sai do loop
				if(result == 0) break;

				// só copia pro novo arquivo se for diferente
				if(veiculo.id != id_veiculo){
					// escreve no arquivo temporário
					fwrite(&veiculo, sizeof(t_veiculo), 1, arq_temp);
				}
				else
					strcpy(modelo_veiculo, veiculo.modelo);
			}

			// antes de fazer operações de remover arquivo e renomear,
			// é preciso fechar os dois arquivos
			fclose(arq_veiculo);
			fclose(arq_temp);

			// depois de fechar o arquivo, então tentamos remover
			if(remove("veiculo.txt") != 0)
				printf("\nErro ao deletar o arquivo \"veiculo.bin\"\n");
			else {
				// renomeia o arquivo
				int r = rename("temp_veiculo.txt", "veiculo.txt");
				if(r != 0){
					printf("\nPermissao negada para renomear o arquivo!\n");
					printf("Feche esse programa bem como o arquivo \"temp_veiculo.bin\" e renomeie manualmente para \"veiculo.bin\"\n");
				}
				else
					printf("\nVeiculo \"%s\" removido com sucesso!\n", modelo_veiculo);
			}
		}
		else {
			fclose(arq_veiculo);
			printf("\nNao existe veiculo com o ID \"%i\".\n", id_veiculo);
		}
	}
	else
		printf("\nO ID so pode conter numeros!\n");

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// limpando o buffer do teclado
    fseek(stdin, 0, SEEK_END);
}
