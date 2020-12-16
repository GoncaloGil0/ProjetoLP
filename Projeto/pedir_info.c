#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "pedir_info.h"
#include "menus.h"
//#include "processar_info.h"


//FUNÇOES


//SABER PARTES DA DATA 

int define_data(int pedido) {

    struct tm *data;
    time_t tempo;

    time(&tempo);
    data = localtime(&tempo);

    switch (pedido) {
        case 1:
            return (data->tm_mday); //retorna o dia caso receba o numero 1
        case 2:
            return (data->tm_mon + 1); // retorna o mes caso receba o numero 2
        case 3:
            return (data->tm_year + 1900); // retorn o ano caso receba o numero 3
    }
}

//SABER A DATA COMPLETA

char *data_completa() {

    struct tm *data;
    time_t tempo;

    time(&tempo);
    data = localtime(&tempo);

    return (ctime(&tempo));
}

//CLEAN BUFFER

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

//OBTER NUMEROS

int obterInt(int min, int max, char *texto) {
    int valor;
    printf(texto);
    while (scanf("%d", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}

//OBTER STRINGS

void obterString(char *string, unsigned int tamanho, char *texto) {
    printf(texto);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

//OBTER DOUBLES

double obterNum(double min, double max, char *texto) {
    double valor;
    printf(texto);
    while (scanf("%lf", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}

//INPUTS DO FUNCIONARIO

int addFuncionario(Funcionarios *funcionarios, int codigo) {


    //VARIAVEIS LOCAIS
    int est_civil, cargo;
    char saida;


    //ASSOCIAR CODIGO
    funcionarios->funcionario_array[funcionarios->contador].codigo = codigo;


    //OBTER NOME
    obterString(funcionarios->funcionario_array[funcionarios->contador].nome, MAX_NOME, OBTER_NOME);


    //OBTER NUMERO TELEMOVEL
    double numero_tlm = obterNum(MIN_NUM_TELE, MAX_NUM_TELE, OBTER_NUM_TELE);
    funcionarios->funcionario_array[funcionarios->contador].numero_tlm = numero_tlm;


    //OBTER ESTADO CIVIL
    do {
        puts(OBTER_EST_CIVIL);
        scanf("%d", &est_civil);
    } while (est_civil > 3 || est_civil < 0);
    funcionarios->funcionario_array[funcionarios->contador].est_civil = est_civil;
    cleanInputBuffer();



    //OBTER NUMERO FILHOS
    puts(OBTER_NUM_FILHOS);
    scanf("%d", &funcionarios->funcionario_array[funcionarios->contador].numero_filhos);
    cleanInputBuffer();



    //OBTER CARGO NA EMPRESA
    do {
        puts(OBTER_CARGO);
        scanf("%d", &cargo);
    } while (cargo > 2 || cargo < 0);
    funcionarios->funcionario_array[funcionarios->contador].cargo = cargo;
    cleanInputBuffer();



    //OBTER SALARIO
    puts(OBTER_SALARIO);
    scanf("%f", &funcionarios->funcionario_array[funcionarios->contador].valor_hora);
    cleanInputBuffer();



    //OBTER SUBSIDIO ALIMENTACAO
    puts(OBTER_SUB_ALI);
    scanf("%f", &funcionarios->funcionario_array[funcionarios->contador].valor_sub_ali);
    cleanInputBuffer();



    //OBTER DATA NASCIMENTO
    puts(OBTER_DATA_NASC);
    funcionarios->funcionario_array[funcionarios->contador].nascimento.ano = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);
    funcionarios->funcionario_array[funcionarios->contador].nascimento.mes = obterInt(MIN_MES, MAX_MES, OBTER_MES);
    funcionarios->funcionario_array[funcionarios->contador].nascimento.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);



    //OBTER DATA ENTRADA
    puts(OBTER_DATA_ENT);
    funcionarios->funcionario_array[funcionarios->contador].entrada_emp.ano = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);
    funcionarios->funcionario_array[funcionarios->contador].entrada_emp.mes = obterInt(MIN_MES, MAX_MES, OBTER_MES);
    funcionarios->funcionario_array[funcionarios->contador].entrada_emp.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);



    //VERIFICAR SE CONTINUA NA EMPRESA
    do {
        printf("\nContinua na empresa (s/n)?: ");
        scanf(" %c", &saida);
    } while (saida != 'n' && saida != 's');
    cleanInputBuffer();



    //OBTER DATA SAIDA
    if (saida == 'n') {
        puts(OBTER_DATA_SAIDA);
        funcionarios->funcionario_array[funcionarios->contador].saida_emp.ano = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);
        funcionarios->funcionario_array[funcionarios->contador].saida_emp.mes = obterInt(MIN_MES, MAX_MES, OBTER_MES);
        funcionarios->funcionario_array[funcionarios->contador].saida_emp.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);

    } else {
        // temos de atribuir um valor a data quando ele ainda esta na empresa para podermos fazer os calculos dps
        // podemos dar o valor 0 e programa-lo para quando encontrar um 0 na data ir á funcao define_data() buscar 
        // o ano atual
    }


    //TORNAR FUNCIONARIO ATIVO
    //funcionarios->funcionario_array[funcionarios->contador].ativo = 1;


    //INCREMENTAR CONTADOR
    funcionarios->contador++;
}


//PROCURAR FUNCIONARIO

int procurarFuncionario(Funcionarios funcionarios, int codigo) {
    int i;
    for (i = 0; i < funcionarios.contador; i++) {
        if (funcionarios.funcionario_array[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

//VERIFICAR SE PODE ADICIONAR FUNCIONARIO OU SEJA SE JA EXISTE 

int verificarFuncionario(Funcionarios funcionarios, int codigo) {
    if (procurarFuncionario(funcionarios, codigo) != -1) {
        return -1;
    } else {
        addFuncionario(&funcionarios, codigo);
    }
}

//VERIFICAR SE LISTA DE FUNCIONARIOS ESTA CHEIA

int verificacao_addFuncionarios(Funcionarios funcionarios) {
    if (funcionarios.contador < MAX_FUNCIONARIOS) {
        if (verificarFuncionario(funcionarios, obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO)) == -1) {
            puts(FUNC_EXISTENTE);
            return 1;
        }
    } else {
        puts(LISTA_CHEIA);
        return -1;
    }
}

// FAZER A ALTER�AO DOS DADOS DO FUNCIONARIO 

void editarFuncionario(Funcionarios *funcionarios, int posicao, int opcao) {

    int est_civil, cargo;

    switch (opcao) {

        case 1:
            //ALTERAR TELEMOVEL
            double numero_tlm = obterNum(MIN_NUM_TELE, MAX_NUM_TELE, OBTER_NUM_TELE);
            funcionarios->funcionario_array[posicao].numero_tlm = numero_tlm;
            break;
        case 2:
            //ALTERAR ESTADO CIVIL
            do {
                puts(OBTER_EST_CIVIL);
                scanf("%d", &est_civil);
            } while (est_civil > 3 || est_civil < 0);
            funcionarios->funcionario_array[posicao].est_civil = est_civil;
            cleanInputBuffer();
            break;
        case 3:
            // ALTERAR NUMERO DE FILHOS
            puts(OBTER_NUM_FILHOS);
            scanf("%d", &funcionarios->funcionario_array[posicao].numero_filhos);
            cleanInputBuffer();
            break;
        case 4:
            // ALTERAR CARGO
            do {
                puts(OBTER_CARGO);
                scanf("%d", &cargo);
            } while (cargo > 2 || cargo < 0);
            funcionarios->funcionario_array[posicao].cargo = cargo;
            cleanInputBuffer();
            break;
        case 5:
            // ALTERAR VALOR HORA
            puts(OBTER_SALARIO);
            scanf("%f", &funcionarios->funcionario_array[posicao].valor_hora);
            cleanInputBuffer();
            break;
        case 6:
            // ALTERAR VALOR HORA ALIMENTACAO
            puts(OBTER_SUB_ALI);
            scanf("%f", &funcionarios->funcionario_array[posicao].valor_sub_ali);
            cleanInputBuffer();
            break;
        case 7:
            // ALTERAR DATA DE SAIDA DA EMPRESA
            puts(OBTER_DATA_SAIDA);
            funcionarios->funcionario_array[posicao].saida_emp.ano = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);
            funcionarios->funcionario_array[posicao].saida_emp.mes = obterInt(MIN_MES, MAX_MES, OBTER_MES);
            funcionarios->funcionario_array[posicao].saida_emp.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);
            // se pedirmos o ano primeiro podemos fazer uma condicional e saber se bissexto, caso seja incrementamos 1 dia
            // ao MAX_DIA caso n seja, nao faz nada
            break;
        case 0:
            // VOLTAR MENU DO FUNCIONARIO
            menu_gestao_funcionarios();
            break;
    }
}

// MOSTRAR OS DADOS DO FUNCIONARIO 

int infoFuncionario(Funcionarios funcionarios, int posicao) {

    int opcao;

    printf("%s%d\n", OBTER_CODIGO, funcionarios.funcionario_array[posicao].codigo);
    printf("%s%s\n", OBTER_NOME, funcionarios.funcionario_array[posicao].nome);
    printf("%s%d\n", OBTER_NUM_TELE, funcionarios.funcionario_array[posicao].numero_tlm);
    printf("%s%d\n", EST_CIVIL, funcionarios.funcionario_array[posicao].est_civil);
    printf("%s%d\n", OBTER_NUM_FILHOS, funcionarios.funcionario_array[posicao].numero_filhos);
    printf("%s%d\n", CARGO, funcionarios.funcionario_array[posicao].cargo);
    printf("%s%f\n", OBTER_SALARIO, funcionarios.funcionario_array[posicao].valor_hora);
    printf("%s%f\n", OBTER_SUB_ALI, funcionarios.funcionario_array[posicao].valor_sub_ali);
    printf("%s%d-%d-%d\n", OBTER_DATA_NASC, funcionarios.funcionario_array[posicao].nascimento.dia, funcionarios.funcionario_array[posicao].nascimento.mes, funcionarios.funcionario_array[posicao].nascimento.ano);
    printf("%s%d-%d-%d\n", OBTER_DATA_ENT, funcionarios.funcionario_array[posicao].entrada_emp.dia, funcionarios.funcionario_array[posicao].entrada_emp.mes, funcionarios.funcionario_array[posicao].entrada_emp.ano);
    printf("%s%d-%d-%d\n", OBTER_DATA_SAIDA, funcionarios.funcionario_array[posicao].saida_emp.dia, funcionarios.funcionario_array[posicao].saida_emp.mes, funcionarios.funcionario_array[posicao].saida_emp.ano); //melhorar para aqueles que cont na empresa

    do {
        puts("Escolha o parametro que deseja alterar: \n\n");
        puts("1) Numero de telemovel \n");
        puts("2) Estado Civil \n");
        puts("3) Numero de filhos \n");
        puts("4) Cargo \n");
        puts("5) Valor hora \n");
        puts("6) Valor hora subsidio de alimentação \n");
        puts("7) Data de saida da empresa \n");
        puts("0) Voltar \n");
        puts("Op��o: ");
        scanf("%d", &opcao);

    } while (opcao < 0 || opcao > 7);

    editarFuncionario(funcionarios, posicao, opcao);

    return (opcao);

}

//VERIFICAR SE PODE EDITAR FUNCIONARIO

void verificacao_editarFuncionarios(Funcionarios *funcionarios) {
    char resposta;
    int codigo = obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO);
    int posicao = procurarFuncionario(*funcionarios, codigo);
    if (posicao != -1) {
        infoFuncionario(funcionarios, posicao);
    } else {
        puts(FUNC_INEXISTENTE);
        do {
            printf("\nDeseja adicionar o funcion�rio [s/n]?");
            scanf(" %c", &resposta);
        } while (reposta != 's' || resposta != 'n');
        if (resposta == 's') {
            addFuncionario(&funcionarios, codigo);
        }
    }
}

//REMOVER FUNCIONARIOS

void removerFuncionario(Funcionarios * funcionarios) {
    int i, numero = procurarFuncionario(*funcionarios, obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO));
    if (numero != -1) {
        i = numero;
        //funcionarios->funcionario_array[i].ativo = 0;
        puts(SUCESSO);
    } else {
        puts(FUNC_INEXISTENTE);
    }
}

//OBTER NUMERO DE DIAS NO MES

int obterNumDias(char *texto) {
    int valor;
    printf(texto);
    scanf("%d", &valor);
    return valor;
    cleanInputBuffer();
}

//VERIFICAR SOMA DOS DIAS

int verificacaoDias(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, Mes * mes) {
    int soma = dias_compl + dias_meios + dias_fds + dias_faltas;
    if (soma > *(mes--)) { //para assinalar pela contagem do array da enum, pois ninguem vais escrever 0 para janeiro por exemplo
        puts(DIAS_MAIOR_MES);
        return -1;
    }
    return 0;
}

//CALCULAR SALARIOS

void calcSalarial(Funcionarios * funcionarios) {

    do {
        funcionarios->funcionario_array[funcionarios->contador].mes = obterNumDias(OBTER_NUM_MES); //se o mes mudar, o resto nao muda pois nao?
        funcionarios->funcionario_array[funcionarios->contador].dias_compl = obterNumDias(OBTER_DIAS_COMPL);
        funcionarios->funcionario_array[funcionarios->contador].dias_meios = obterNumDias(OBTER_DIAS_MEIOS);
        funcionarios->funcionario_array[funcionarios->contador].dias_fds = obterNumDias(OBTER_DIAS_FDS);
        funcionarios->funcionario_array[funcionarios->contador].dias_faltas = obterNumDias(OBTER_DIAS_FALTAS);
    } while (verificacaoDias(funcionarios->funcionario_array[funcionarios->contador].dias_compl,
            funcionarios->funcionario_array[funcionarios->contador].dias_meios,
            funcionarios->funcionario_array[funcionarios->contador].dias_fds,
            funcionarios->funcionario_array[funcionarios->contador].dias_faltas,
            &funcionarios->funcionario_array[funcionarios->contador].mes)
            == -1);
}
