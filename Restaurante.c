#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char nome[50];
    char telefone[15];
    char cpf[12];
    int ativo;
} Cliente;

typedef struct {
    int id;
    char nome[50];
    float preco;
    int disponibilidade;
} Prato;

typedef struct {
    int id;
    int clienteId;
    int pratoId;
    int quantidade;
    float total;
} Pedido;

int validarCPF(Cliente *cliente) { 
    int i, j, soma, resto, digito1, digito2;
    char *cpf = cliente->cpf; 
    
    if (strlen(cpf) != 11 || !isdigit(cpf[0])) return 0; 
    
    for (i = 1; i < 11; i++) { 
        if (cpf[i] != cpf[0]) break; 
        if (i == 10) return 0; 
    } 
    
    soma = 0; 
    for (i = 0, j = 10; i < 9; i++, j--) { 
        soma += (cpf[i] - '0') * j; 
    } 
    resto = soma % 11; 
    digito1 = (resto < 2) ? 0 : 11 - resto; 

    soma = 0; 
    for (i = 0, j = 11; i < 10; i++, j--) { 
        soma += (cpf[i] - '0') * j; 
    } 
    resto = soma % 11; 
    digito2 = (resto < 2) ? 0 : 11 - resto; 
    
    return (digito1 == (cpf[9] - '0') && digito2 == (cpf[10] - '0')); 
}

void cadastrarCliente() {
    int opcao;
    Cliente cliente;

    do {
        FILE *arquivo = fopen("clientes.txt", "a");
        if (arquivo == NULL) {
            return;
        }

        printf("ID do Cliente: ");
        scanf("%d", &cliente.id);
        printf("Nome do Cliente: ");
        scanf("%s", cliente.nome);
        printf("Telefone do Cliente: ");
        scanf("%s", cliente.telefone);
        printf("CPF do cliente: ");
        scanf("%s", cliente.cpf);
        cliente.ativo = 1;

        if (validarCPF(&cliente)) {
            fprintf(arquivo, "%d %s %s %s %d\n", cliente.id, cliente.nome, cliente.telefone, cliente.cpf, cliente.ativo);
            system("cls");
            printf("+-----------------------------------------+\n");
            printf("|     Cliente Cadastrado com Sucesso!     |\n");
            printf("+-----------------------------------------+\n");
            printf("| 1. Cadastrar Novo Cliente               |\n");
            printf("| 2. Voltar                               |\n");
            printf("+-----------------------------------------+\n");
        } else {
            system("cls");
            printf("+-----------------------------------------+\n");
            printf("|  Nao foi possivel cadastrar o Cliente!  |\n");
            printf("+-----------------------------------------+\n");
            printf("| 1. Cadastrar Novamente                  |\n");
            printf("| 2. Voltar                               |\n");
            printf("+-----------------------------------------+\n");
        }
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 2);
}

void listarClientes(const char* filename) {
    int opcao;

    do {
        FILE *arquivo = fopen(filename, "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+-----------------------------------------+\n");
        printf("|            Lista de Clientes            |\n");
        printf("+-----------------------------------------+\n");

        Cliente *clientes = NULL;
        size_t tamanho = 0;
        size_t capacidade = 1;
        clientes = malloc(capacidade * sizeof(Cliente));
        if (clientes == NULL) {
            fclose(arquivo);
        }

        while (fscanf(arquivo, "%d %s %s %s %d\n", &clientes[tamanho].id, clientes[tamanho].nome, clientes[tamanho].telefone, clientes[tamanho].cpf, &clientes[tamanho].ativo) != EOF) {
            tamanho++;
            if (tamanho == capacidade) {
                capacidade *= 2;
                Cliente *temp = realloc(clientes, capacidade * sizeof(Cliente));
                if (temp == NULL) {
                    free(clientes);
                    fclose(arquivo);
                }
                clientes = temp;
            }
        }

        for (size_t i = 0; i < tamanho - 1; i++) { 
            for (size_t j = 0; j < tamanho - i - 1; j++) { 
                if (strcmp(clientes[j].nome, clientes[j+1].nome) > 0) { 
                    Cliente temp = clientes[j]; clientes[j] = clientes[j+1]; clientes[j+1] = temp; 
                } 
            } 
        }

        for (size_t i = 0; i < tamanho; i++) { 
            printf(" ID: %d\n", clientes[i].id);
            printf(" Nome: %s\n", clientes[i].nome);
            printf(" Telefone: %s\n", clientes[i].telefone);
            printf(" CPF: %s\n", clientes[i].cpf);
            printf(" Ativo: %d\n", clientes[i].ativo);
            printf("+-----------------------------------------+\n");
        } 
        
        free(clientes);

        printf("| 1. Voltar                               |\n");
        printf("+-----------------------------------------+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 1);
}

void consultarCliente() {
    int opcao = 1;
    char cpf[11];
    Cliente cliente;
    do {
        FILE *arquivo = fopen("clientes.txt", "r");

        if (arquivo == NULL) {
            return;
        }

        switch (opcao) {
            case 1:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("|            Consultar Cliente            |\n");
                printf("+-----------------------------------------+\n");
                printf("CPF do Cliente: ");
                scanf("%s", cpf);

                printf("+-----------------------------------------+\n");
                while (fscanf(arquivo, "%d %s %s %s %d\n", &cliente.id, cliente.nome, cliente.telefone, cliente.cpf, &cliente.ativo) != EOF) {
                    if (strcmp(cliente.cpf, cpf) == 0 && cliente.ativo) {
                        printf(" ID: %d\n", cliente.id);
                        printf(" Nome: %s\n", cliente.nome);
                        printf(" Telefone: %s\n", cliente.telefone);
                        printf(" CPF: %s\n", cliente.cpf);
                        printf(" Ativo: %d\n", cliente.ativo);
                        break;
                    }
                }
                printf("+-----------------------------------------+\n");
                printf("| 1. Consultar outro Cliente              |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
            case 2: break;
            default:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("| 1. Consultar outro Cliente              |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
        }

        fclose(arquivo);
    } while (opcao != 2);
}

void desativarCliente() {
    int id, opcao = 1;
    Cliente cliente;

    do {
        FILE *arquivo = fopen("clientes.txt", "r+");
        FILE *temp = fopen("temp.txt", "w");

        if (arquivo == NULL) {
            return;
        }

        switch (opcao) {
            case 1:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("|            Desativar Cliente            |\n");
                printf("+-----------------------------------------+\n");
                printf("ID do Cliente: ");
                scanf("%d", &id);

                while (fscanf(arquivo, "%d %s %s %s %d\n", &cliente.id, cliente.nome, cliente.telefone, cliente.cpf, &cliente.ativo) != EOF) {
                    if (cliente.id == id) {
                        cliente.ativo = 0;
                    }
                    fprintf(temp, "%d %s %s %s %d\n", cliente.id, cliente.nome, cliente.telefone, cliente.cpf, cliente.ativo);
                }
                printf("+-----------------------------------------+\n");
                printf("| 1. Desativar outro Cliente              |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
            case 2:
                break;
            default:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("| 1. Desativar outro Cliente              |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
        }
        
        fclose(arquivo);
        fclose(temp);
        remove("clientes.txt");
        rename("temp.txt", "clientes.txt");
    } while (opcao != 2);
}

void excluirCliente() {
    int id, opcao = 1;
    Cliente cliente;

    do {
        FILE *arquivo = fopen("clientes.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        if (arquivo == NULL || temp == NULL) {
            return;
        }

        switch (opcao) {
            case 1:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("|             Excluir Cliente             |\n");
                printf("+-----------------------------------------+\n");
                printf("ID do Cliente: ");
                scanf("%d", &id);

                while (fscanf(arquivo, "%d %s %s %s %d\n", &cliente.id, cliente.nome, cliente.telefone, cliente.cpf, &cliente.ativo) != EOF) {
                    if (cliente.id != id) {
                        fprintf(temp, "%d %s %s %s %d\n", cliente.id, cliente.nome, cliente.telefone, cliente.cpf, cliente.ativo);
                    }
                }
                printf("+-----------------------------------------+\n");
                printf("| 1. Excluir outro Cliente                |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
            case 2:
                break;
            default:
                printf("+-----------------------------------------+\n");
                printf("| 1. Desativar outro Cliente              |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
        }
        
        fclose(arquivo);
        fclose(temp);
        remove("clientes.txt");
        rename("temp.txt", "clientes.txt");
    } while (opcao != 2);
}

void cadastrarPrato() {
    int opcao = 1;
    Prato prato;

    do {
        FILE *arquivo = fopen("pratos.txt", "a");
        if (arquivo == NULL) {
            return;
        }

        switch (opcao) {
            case 1:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("|          Cadastrar Novo Prato           |\n");
                printf("+-----------------------------------------+\n");
                printf(" ID do Prato: ");
                scanf("%d", &prato.id);
                printf(" Nome do Prato: ");
                scanf("%s", prato.nome);
                printf(" Preco do Prato: ");
                scanf("%f", &prato.preco);
                prato.disponibilidade = 1;
                fprintf(arquivo, "%d %s %.2f %d\n", prato.id, prato.nome, prato.preco, prato.disponibilidade);

                system("cls");
                printf("+-----------------------------------------+\n");
                printf("|      Prato Cadastrado com Sucesso!      |\n");
                printf("+-----------------------------------------+\n");
                printf("| 1. Cadastrar Novo Prato                 |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
            case 2: break;
            default:
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("| 1. Cadastrar Novo Prato                 |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);    
                break;           
        }
        fclose(arquivo);
    } while (opcao != 2);
}

void registrarPedido() {
    int opcao = 1;
    Pedido pedido;
    Prato prato;
    do {
        FILE *arquivo = fopen("pedidos.txt", "a");
        FILE *pratos = fopen("pratos.txt", "r");

        if (arquivo == NULL) {
            return;
        }

        switch (opcao) {
            case 1:
                system("cls");
                printf("+----------------------------------------+\n");
                printf("|          Registrar Novo Pedido         |\n");
                printf("+----------------------------------------+\n");
                printf(" ID do Pedido: ");
                scanf("%d", &pedido.id);
                printf(" ID do Cliente: ");
                scanf("%d", &pedido.clienteId);
                printf(" ID do Prato: ");
                scanf("%d", &pedido.pratoId);
                printf(" Quantidade: ");
                scanf("%d", &pedido.quantidade);
                
                while (fscanf(pratos, "%d %s %f %d", &prato.id, prato.nome, &prato.preco, &prato.disponibilidade) != EOF) {
                    if (pedido.pratoId == prato.id) {
                        pedido.total = pedido.quantidade * prato.preco;
                    } else {
                        pedido.total = 0.00;
                    }
                }

                fprintf(arquivo, "%d %d %d %d %.2f\n", pedido.id, pedido.clienteId, pedido.pratoId, pedido.quantidade, pedido.total);
                system("cls");
                printf("+-----------------------------------------+\n");
                printf("|     Pedido Registrado com Sucesso!      |\n");                        
                printf("+-----------------------------------------+\n");
                printf("Valor Total: %.2f Reais.\n", pedido.total);                
                printf("+-----------------------------------------+\n");
                printf("| 1. Registrar Novo Pedido                |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
            case 2: break;
            default:
                printf("+-----------------------------------------+\n");
                printf("| 1. Registrar Novo Pedido                |\n");
                printf("| 2. Voltar                               |\n");
                printf("+-----------------------------------------+\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                break;
        }
        
        fclose(arquivo);
        fclose(pratos);
    } while (opcao != 2);
}

void consultarDisponibilidadePratos(const char* filename) {
    int opcao;

    do {
        FILE *arquivo = fopen(filename, "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+----------------------------------------+\n");
        printf("|           Pratos Disponiveis           |\n");
        printf("+----------------------------------------+\n");

        Prato *pratos = NULL;
        size_t tamanho = 0;
        size_t capacidade = 1;
        pratos = malloc(capacidade * sizeof(Prato));
        if (pratos == NULL) {
            fclose(arquivo);
        }

        while (fscanf(arquivo, "%d %s %f %d\n", &pratos[tamanho].id, pratos[tamanho].nome, &pratos[tamanho].preco, &pratos[tamanho].disponibilidade) != EOF) {
            tamanho++;
            if (tamanho == capacidade) {
                capacidade *= 2;
                Prato *temp = realloc(pratos, capacidade * sizeof(Prato));
                if (temp == NULL) {
                    free(pratos);
                    fclose(arquivo);
                }
                pratos = temp;
            }
        }

        for (size_t i = 0; i < tamanho - 1; i++) { 
            for (size_t j = 0; j < tamanho - i - 1; j++) { 
                if (strcmp(pratos[j].nome, pratos[j+1].nome) > 0) { 
                    Prato temp = pratos[j]; pratos[j] = pratos[j+1]; pratos[j+1] = temp; 
                } 
            } 
        }

        for (size_t i = 0; i < tamanho; i++) {
            printf(" ID: %d\n", pratos[i].id);
            printf(" Nome: %s\n", pratos[i].nome);
            printf(" Preco: %.2f\n", pratos[i].preco);
            printf(" Disponibilidade: %d\n", pratos[i].disponibilidade);
            printf("+----------------------------------------+\n");
        }

        free(pratos);

        printf("| 1. Voltar                               |\n");
        printf("+-----------------------------------------+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 1);
}

void relatorioVendas() {
    int opcao;
    Pedido pedido;

    do {
        FILE *arquivo = fopen("pedidos.txt", "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+----------------------------------------+\n");
        printf("|           Relatorio de Vendas          |\n");
        printf("+----------------------------------------+\n");
        while (fscanf(arquivo, "%d %d %d %d %f\n", &pedido.id, &pedido.clienteId, &pedido.pratoId, &pedido.quantidade, &pedido.total) != EOF) {
            printf(" ID do Pedido: %d\n", pedido.id);
            printf(" ID do Cliente: %d\n", pedido.clienteId);
            printf(" ID do Prato: %d\n", pedido.pratoId);
            printf(" Quantidade: %d\n", pedido.quantidade);
            printf(" Total: %.2f\n", pedido.total);
            printf("+----------------------------------------+\n");
        }
        printf("| 1. Voltar                              |\n");
        printf("+----------------------------------------+\n");
        printf("Escolha um opcao: ");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 1);
}

void relatorioEstoque(const char* filename) {
    int opcao;

    do {
        FILE *arquivo = fopen(filename, "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+----------------------------------------+\n");
        printf("|          Relatorio de Estoque          |\n");
        printf("+----------------------------------------+\n");

        Prato *pratos = NULL;
        size_t tamanho = 0;
        size_t capacidade = 1;
        pratos = malloc(capacidade * sizeof(Prato));
        if (pratos == NULL) {
            fclose(arquivo);
        }

        while (fscanf(arquivo, "%d %s %f %d\n", &pratos[tamanho].id, pratos[tamanho].nome, &pratos[tamanho].preco, &pratos[tamanho].disponibilidade) != EOF) {
            tamanho++;
            if (tamanho == capacidade) {
                capacidade *= 2;
                Prato *temp = realloc(pratos, capacidade * sizeof(Prato));
                if (temp == NULL) {
                    free(pratos);
                    fclose(arquivo);
                }
                pratos = temp;
            }
        }

        for (size_t i = 0; i < tamanho - 1; i++) { 
            for (size_t j = 0; j < tamanho - i - 1; j++) { 
                if (strcmp(pratos[j].nome, pratos[j+1].nome) > 0) { 
                    Prato temp = pratos[j]; pratos[j] = pratos[j+1]; pratos[j+1] = temp; 
                } 
            } 
        }

        for (size_t i = 0; i < tamanho; i++) {
            printf(" ID: %d\n", pratos[i].id);
            printf(" Nome: %s\n", pratos[i].nome);
            printf(" Preco: %.2f\n", pratos[i].preco);
            printf(" Disponibilidade: %d\n", pratos[i].disponibilidade);
            printf("+----------------------------------------+\n");
        }

        free(pratos);

        printf("| 1. Voltar                              |\n");
        printf("+----------------------------------------+\n");
        printf("Escolha um opcao: ");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 1);
}

void relatorios() {
    int opcao;
    do {
        system("cls");
        printf("+------------------------------------------+\n");
        printf("|                Relatorios                |\n");
        printf("+------------------------------------------+\n");   
        printf("| 1. Relatorio de Vendas                   |\n");
        printf("| 2. Relatorio de Estoque                  |\n");
        printf("| 3. Voltar                                |\n");
        printf("+------------------------------------------+\n"); 
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: relatorioVendas(); break;
            case 2: relatorioEstoque("pratos.txt"); break;
            case 3: break;
            default: 
                printf("+------------------------------------------+\n");   
                printf("| 1. Relatorio de Vendas                   |\n");
                printf("| 2. Relatorio de Estoque                  |\n");
                printf("| 3. Voltar                                |\n");
                printf("+------------------------------------------+\n"); 
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
        }
    } while(opcao != 3);
}

int main() {
    int opcao;
    do {
        system("cls");
        printf("+------------------------------------------+\n");
        printf("|     Sistema de Gestao de Restaurante     |\n");
        printf("+------------------------------------------+\n");
        printf("| 1. Gerenciamento de Clientes             |\n");
        printf("| 2. Gerenciamento de Pratos               |\n");
        printf("| 3. Registrar Pedido                      |\n");
        printf("| 4. Relatorios de Vendas e Estoque        |\n");        
        printf("| 5. Sair                                  |\n");
        printf("+------------------------------------------+\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                do {
                    system("cls");
                    printf("+-----------------------------------------+\n");
                    printf("|        Gerenciamento de Clientes        |\n");
                    printf("+-----------------------------------------+\n");
                    printf("| 1. Cadastrar Cliente                    |\n");
                    printf("| 2. Listar Clientes                      |\n");
                    printf("| 3. Consultar Cliente                    |\n");
                    printf("| 4. Desativar Cliente                    |\n");
                    printf("| 5. Excluir Cliente                      |\n");
                    printf("| 6. Voltar                               |\n");
                    printf("+-----------------------------------------+\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao);
                    switch (opcao) {
                        case 1: cadastrarCliente(); break;
                        case 2: listarClientes("clientes.txt"); break;
                        case 3: consultarCliente(); break;
                        case 4: desativarCliente(); break;
                        case 5: excluirCliente(); break;
                        default: break;                        
                    }
                } while (opcao != 6);
                break;
            case 2:
                do {
                    system("cls");
                    printf("+-----------------------------------------+\n");
                    printf("|         Gerenciamento de Pratos         |\n");
                    printf("+-----------------------------------------+\n");
                    printf("| 1. Cadastrar Prato                      |\n");
                    printf("| 2. Consultar Disponibilidade de Pratos  |\n");
                    printf("| 3. Voltar                               |\n");
                    printf("+-----------------------------------------+\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao);
                    switch (opcao) {
                        case 1: cadastrarPrato(); break;
                        case 2: consultarDisponibilidadePratos("pratos.txt"); break;
                        default: break;                        
                    }
                } while (opcao != 3);
                break;
            case 3: registrarPedido(); break;
            case 4: 
                relatorios();
                break;
            case 5: 
                system("cls");
                printf("Saindo...\n"); 
                break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 5);

    return 0;
}