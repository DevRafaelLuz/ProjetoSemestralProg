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

void cadastrarCliente() {
    Cliente cliente;
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

    fprintf(arquivo, "%d %s %s %s %d\n", cliente.id, cliente.nome, cliente.telefone, cliente.cpf, cliente.ativo);
    fclose(arquivo);
}

void listarClientes() {
    Cliente cliente;
    int opcao;

    do {
        FILE *arquivo = fopen("clientes.txt", "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+-----------------------------------------+\n");
        printf("|            Lista de Clientes            |\n");
        printf("+-----------------------------------------+\n");
        while (fscanf(arquivo, "%d %s %s %s %d\n", &cliente.id, cliente.nome, cliente.telefone, cliente.cpf, &cliente.ativo) != EOF) {
            if (cliente.ativo) {
                printf(" ID: %d\n", cliente.id);
                printf(" Nome: %s\n", cliente.nome);
                printf(" Telefone: %s\n", cliente.telefone);
                printf(" CPF: %s\n", cliente.cpf);
                printf(" Ativo: %d\n", cliente.ativo);
                printf("+-----------------------------------------+\n");
            }
        }
        printf("+-----------------------------------------+\n");
        printf("| 1. Voltar                               |\n ");
        printf("+-----------------------------------------+\n");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 1);
}

void consultarCliente() {
    int id, opcao = 1;
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
                printf("ID do Cliente: ");
                scanf("%d", &id);

                printf("+-----------------------------------------+\n");
                while (fscanf(arquivo, "%d %s %s %s %d\n", &cliente.id, cliente.nome, cliente.telefone, cliente.cpf, &cliente.ativo) != EOF) {
                    if (cliente.id == id && cliente.ativo) {
                        printf(" ID: %d\n", cliente.id);
                        printf(" Nome: %s\n", cliente.nome);
                        printf(" Telefone: %s\n", cliente.telefone);
                        printf(" CPF: %s\n", cliente.cpf);
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
            case 2:
                break;
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
                        fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
                        fprintf(arquivo, "%d %s %s %s %d\n", cliente.id, cliente.nome, cliente.telefone, cliente.cpf, cliente.ativo);
                        return;
                    }
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
                printf("| 1. Desativar outro Cliente              |\n");
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
    Prato prato;
    FILE *arquivo = fopen("pratos.txt", "a");
    if (arquivo == NULL) {
        return;
    }

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
    fclose(arquivo);
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

void consultarDisponibilidadePratos() {
    int opcao;
    Prato prato;
    do {
        FILE *arquivo = fopen("pratos.txt", "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+-----------------------------------------+\n");
        printf("|            Pratos Disponiveis           |\n");
        printf("+-----------------------------------------+\n");
        while (fscanf(arquivo, "%d %s %f %d\n", &prato.id, prato.nome, &prato.preco, &prato.disponibilidade) != EOF) {
            if (prato.disponibilidade) {
                printf(" ID: %d\n", prato.id);
                printf(" Nome: %s\n", prato.nome);
                printf(" Preco: %.2f\n", prato.preco);
            }
            printf("+-----------------------------------------+\n");
        }
        printf("Digite 0 para voltar ");
        scanf("%d", &opcao);
        fclose(arquivo);
    } while (opcao != 0);
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

void relatorioEstoque() {
    int opcao;
    Prato prato;

    do {
        FILE *arquivo = fopen("pratos.txt", "r");
        if (arquivo == NULL) {
            return;
        }

        system("cls");
        printf("+----------------------------------------+\n");
        printf("|          Relatorio de Estoque          |\n");
        printf("+----------------------------------------+\n");
        while (fscanf(arquivo, "%d %s %f %d\n", &prato.id, prato.nome, &prato.preco, &prato.disponibilidade) != EOF) {
            printf(" ID: %d\n", prato.id);
            printf(" Nome: %s\n", prato.nome);
            printf(" Preco: %.2f\n", prato.preco);
            printf(" Disponibilidade: %d\n", prato.disponibilidade);
            printf("+----------------------------------------+\n");
        }
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
            case 2: relatorioEstoque(); break;
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
                        case 2: listarClientes(); break;
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
                        case 2: consultarDisponibilidadePratos(); break;
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