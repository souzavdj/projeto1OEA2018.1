#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @author Vinicius
 * @version 1.0
 */
#pragma pack(1)

/** Criação da assinatura da estrutura. */
typedef struct _Endereco Endereco;
struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

/**
 * Função principal do projeto que realiza a busca de um cep em um arquivo atraves do método de busca binária.
 * @param argc quantidade de parametros passados para a função principal
 * @param argv valores dos parametros passados para a função principal
 * @return retorno da função principal é do tipo inteiro e retorna 0 caso seja executada com sucesso e 1 para erro.
 */
int main(int argc, char**argv) {
    /** Inicialização de variáveis. */
    Endereco endereco;
    FILE *file;
    int c = 0;
    long meio=0, inicio=0, fim=0;

    /** Verificação de uso correto dos parametros passados para a função. */
    if(argc != 2) {
        fprintf(stderr, "USO: %s [CEP]\n", argv[0]);
        return 1;
    }
    /** Abertura do arquivo do arquivo cep_ordenado.dat. */
    file = fopen("cep_ordenado.dat","r");

    /** Atribuindo valor a variavel inicio e botando a cabeça de leitura no inicio do arquivo. */
    fseek(file,0,SEEK_SET);
    inicio = ftell(file);

    /** Atribuindo valor a variavel fim e botando a cabeça de leitura no fim do arquivo. */
    fseek(file,inicio*sizeof(Endereco),SEEK_END);
    fim = (ftell(file)/ sizeof(Endereco))-1;

    /** Atribuindo valor a variavel meio e botando a cabeça de leitura no meio do arquivo */
    meio = (inicio+fim)/2;
    fseek(file,meio*sizeof(Endereco),SEEK_SET);

    /** Lendo uma linha do arquivo cep_ordenado.dat e armazenando na estrutura endereco. */
    fread(&endereco,sizeof(Endereco),1,file);

    /** Implementação da busca binaria. */
    while(inicio <= fim) {
        c++;
        if (strncmp(argv[1],endereco.cep,8)>0) {
            inicio=meio+1;
        }else if (strncmp(argv[1],endereco.cep,8)<0) {
            fim = meio-1;
        }else {
            printf("\n%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n\n",endereco.logradouro,endereco.bairro,endereco.cidade,endereco.uf,endereco.sigla,endereco.cep);
            break;
        }
        meio = (inicio+fim)/2;
        fseek(file,meio*sizeof(Endereco),SEEK_SET);
        fread(&endereco,sizeof(Endereco),1,file);
    }
    /** Fechando o arquivo cep_ordenado.dat. */
    fclose(file);
    printf("A quantidade de vezes que passou no while: %d\n\n", c);
    return 0;
}