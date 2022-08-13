/*
    Elaine Dias Pires - 2020101903 
    Filipe Gomes Arante de Souza - 2020100625 
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define TAM1 10  // Maximo tamanho de caracetres separados para comorbidades 
#define TAM2 20  // FicouInternado (Sim, Nao, Nao Informado, Ignorado)
#define TAM3 50  // Maximo de caracteres de um municipio
#define TAM4 100 // Maximo tamanho de caracteres de meses e dias da idade na data de notificaçao que serao ignorados
#define QTDPACIENTES 202362 // O arquivo possui 202363, mas desconsideramos uma linha por ser o cabeçalho, entao temos 202362 pacientes variando de 0 a 202361
#define QTDMUNICIPIOS 78 // Quatidade de municipios do Espirito Santo

// Definindo estrutura tipo data
typedef struct{
    int dia;
    int mes;
    int ano;
}tData;

// Definindo estrutura tipo paciente
typedef struct{
    tData DataCadastro;
    tData DataObito;   
    char Classificacao[TAM2];
    char Municipio[TAM3];
    int IdadeNaDataNotificacao;
    char ComorbidadePulmao[TAM1];
    char ComorbidadeCardio[TAM1];
    char ComorbidadeRenal[TAM1];
    char ComorbidadeDiabetes[TAM1];
    char ComorbidadeTabagismo[TAM1];
    char ComorbidadeObesidade[TAM1];
    char FicouInternado[TAM2];
}tPaciente;

tPaciente p[QTDPACIENTES]; // Criamos um vetor global para poder armazenar todo o arquivo, pois criando na main a capacidade de armazenamento eh menor

// Funçoes TOPICO 1
tPaciente lePaciente(FILE *f);

// Funçoes TOPICO 2
int filtroDeDatas(tData d1, tData d2, tData d3);

// Funçoes TOPICO 3
void incrementaVetorDeCasos(tPaciente p[],char municipio[QTDMUNICIPIOS][TAM3],int casos[], int j);
void imprimeCidadesComMaisDeNCasos(int N, char municipio[QTDMUNICIPIOS][TAM3], int casos[], char pasta[]);
void criaVetorMunicipios(tPaciente p[], char municipio[QTDMUNICIPIOS][TAM3]);
int stringMaior(char string1[], char string2[]);
void OrdemAlfabeticaMunicipios(char municipio[QTDMUNICIPIOS][TAM3]);

// Funçoes TOPICO 4
int QTDCasosD1AteD2(tPaciente p[], tData d1, tData d2);
void imprimeQTDCasosD1AteD2(int qtdCasosD1D2, char pasta[]);

// Funçoes TOPICO 5
void ordenaTopNcidades(int topN, char topMunicipios[topN][TAM3], int topCasos[], char municipio[QTDMUNICIPIOS][TAM3], int casos[]);
void imprimeTopNcidades(int topN, char topMunicipios[topN][TAM3], int topCasos[],char pasta[]);

// Funçoes TOPICO 6
int ehMinuscula(char c);
void converteStringMaiuscula(char string[]);
float percentPessoasInternadasComCovid(tPaciente p[], char cidadeAnalisada[]);
float percentPessoasMorreramComCovid(tPaciente p[], char cidadeAnalisada[]);
float percentPessoasInternadasQueMorreramComCovid(tPaciente p[], char cidadeAnalisada[]);
void imprimePorcentagens(float porcentagem1, float porcentagem2, float porcentagem3, char cidadeAnalisada[],char pasta[]);

// Funçoes TOPICO 7
float calculaMedia(tPaciente p[], tData d1, tData d2);
float calculaDesvioPadrao(tPaciente p[], tData d1, tData d2);
int TemComorbidade(tPaciente p);
float percentMortesSemComorbidade(tPaciente p[], tData d1, tData d2);
void imprimeMediaDesvioPercentSemComorb(float media, float desvio, float percentSemComorb,char pasta[]);

// Outras (Utilizadas em dois ou mais topicos)
int calculaTAM(char string[]);
int stringIgual(char string1[], char string2[]);
void copiaString(char string1[], char string2[]); //achamos que eh do topico 5, mas vamos usar no 3 amanha
int pacienteFaleceu(tPaciente p);
void concatenaString(char string1[], char string2[]);

int main(){
    // Variaveis TOPICO 1
    int i = 0; // Contador do laço while
    
    // Variaveis TOPICO 2
    tData d1, d2, d1a, d2a, d1b, d2b;

    // Variaveis TOPICO 3
    int N, casos[QTDMUNICIPIOS];
    char municipio[QTDMUNICIPIOS][TAM3];

    // Variaveis TOPICO 4
    int qtdCasosD1D2;
    
    // Variaveis TOPICO 5
    int topN, maior, posMaior;
    
    // Variaveis TOPICO 6
    float porcentagem1, porcentagem2, porcentagem3;
    char cidadeAnalisada[TAM3];

    // Variaveis TOPICO 7
    float media, desvioPadrao, percentMortesSemComorb;
 
    // TOPICO 1 DO TRABALHO (Leitura do arquivo CSV)
    FILE *f  = fopen("covid19ES.csv", "r");
    if(f == NULL){
        printf("Erro na abertura do arquivo.");
        exit(1);
    }
    fscanf(f, "%*s\n");  // Ignora o cabeçalho
    while(!feof(f)){
        p[i] = lePaciente(f);
        
        if(feof(f)){
            break;
        }
        
        i++;
    }

    char pasta[TAM3];

    // Leitura do arquivo de entrada
    scanf("%s\n", pasta); 
    scanf("%d", &N); //Leitura do topico 3
    scanf("%d-%d-%d %d-%d-%d", &d1.ano, &d1.mes, &d1.dia, &d2.ano, &d2.mes, &d2.dia);  //Leitura do topico 4
    scanf("%d %d-%d-%d %d-%d-%d\n", &topN, &d1a.ano, &d1a.mes, &d1a.dia, &d2a.ano, &d2a.mes, &d2a.dia); //Leitura do topico 5
    scanf("%[^\n]\n", cidadeAnalisada); //Leitura do topico 6
    scanf("%d-%d-%d %d-%d-%d", &d1b.ano, &d1b.mes, &d1b.dia, &d2b.ano, &d2b.mes, &d2b.dia); //Leitura do topico 7

    //mkdir(pasta, 0777); // Criaçao da pasta de saida do trabalho 
    mkdir(pasta);
    // Variaveis do TOPICO 5 que tiveram que ser declaradas apenas agora, pois precisa de ler "topN" antes para os vetores terem tamanhos definidos
    int topCasos[topN];
    char topMunicipios[topN][TAM3];
    
    // TOPICO 3 DO TRABALHO 
    // Inicializando vetor de contagem de casos
    for(int k = 0; k < QTDMUNICIPIOS; k++){
        casos[k] = 0;
    }

    criaVetorMunicipios(p, municipio);
    OrdemAlfabeticaMunicipios(municipio);

    for(int j = 0; j < QTDPACIENTES; j++){ // Percorre o vetor de pacientes
        incrementaVetorDeCasos(p, municipio, casos, j);
    }

    imprimeCidadesComMaisDeNCasos(N, municipio, casos, pasta);

    // TOPICO 4 DO TRABALHO
    qtdCasosD1D2 = QTDCasosD1AteD2(p, d1, d2);
    imprimeQTDCasosD1AteD2(qtdCasosD1D2, pasta);
    
    // TOPICO 5 DO TRABALHO
    for(int i = 0; i < QTDMUNICIPIOS; i++){ // Reinicializando vetor de casos para reutiliza-lo no topico 5
        casos[i] = 0;
    }
    
    for(int j = 0; j < QTDPACIENTES; j++){
        if(filtroDeDatas(d1a, d2a, p[j].DataCadastro)){
            incrementaVetorDeCasos(p, municipio, casos, j);
        }
    }
    
    ordenaTopNcidades(topN, topMunicipios, topCasos, municipio, casos);
    imprimeTopNcidades(topN,topMunicipios,topCasos, pasta);
    
    // TOPICO 6 DO TRABALHO
    converteStringMaiuscula(cidadeAnalisada);
    
    porcentagem1 = percentPessoasInternadasComCovid(p, cidadeAnalisada);
    porcentagem2 = percentPessoasMorreramComCovid(p, cidadeAnalisada);
    porcentagem3 = percentPessoasInternadasQueMorreramComCovid(p, cidadeAnalisada);

    imprimePorcentagens(porcentagem1, porcentagem2, porcentagem3, cidadeAnalisada, pasta);
    
    // TOPICO 7 DO TRABALHO
    media = calculaMedia(p, d1b, d2b);
    desvioPadrao = calculaDesvioPadrao(p, d1b , d2b);
    percentMortesSemComorb = percentMortesSemComorbidade(p, d1b, d2b);
    
    imprimeMediaDesvioPercentSemComorb(media, desvioPadrao, percentMortesSemComorb, pasta);
    
    fclose(f);
    return 0;
}

// Funçao que executa a leitura de um paciente
tPaciente lePaciente(FILE *f){
    tPaciente p;
    char ignora[TAM4]; // Vetor para apenas "consumir" o trecho "Y anos, Z dias" em p.IdadeNaDataNotificacao

    fscanf(f,"%d-%d-%d,", &p.DataCadastro.ano, &p.DataCadastro.mes, &p.DataCadastro.dia);
    fscanf(f,"%d-%d-%d,", &p.DataObito.ano ,&p.DataObito.mes, &p.DataObito.mes);
    fscanf(f,"%[^,],", p.Classificacao);
    fscanf(f,"%[^,],\"",p.Municipio);
    fscanf(f,"%d", &p.IdadeNaDataNotificacao);
    fscanf(f,"%[^\"]\",", ignora);
    fscanf(f,"%[^,],", p.ComorbidadePulmao);
    fscanf(f,"%[^,],", p.ComorbidadeCardio);
    fscanf(f,"%[^,],", p.ComorbidadeRenal);
    fscanf(f,"%[^,],", p.ComorbidadeDiabetes);
    fscanf(f,"%[^,],", p.ComorbidadeTabagismo);
    fscanf(f,"%[^,],", p.ComorbidadeObesidade);
    fscanf(f,"%[^\n]\n", p.FicouInternado);

    return p;
}

// TOPICO 2 DO TRABALHO (Verifica se a data d3 esta entre d1 e d2)
int filtroDeDatas(tData d1, tData d2, tData d3){  
    if(d1.mes == d2.mes && d3.mes == d1.mes){
        if(d3.dia >= d1.dia && d3.dia <= d2.dia){
            return 1;
        } else{
            return 0;
        } 
    } else{
        if((d3.mes == d1.mes && d3.dia >= d1.dia) || 
           (d3.mes == d2.mes && d3.dia <= d2.dia) ||
           (d3.mes  > d1.mes && d3.mes < d2.mes)) {
            return 1;
        
        } else{
            return 0;
        }
    }

    return 0;
}

// Calcula o tamanho de uma string
int calculaTAM(char string[]){
    int tam = 0;
    for(int i = 0; string[i] != '\0'; i++){
        tam++;
    }

    return tam;
} 

// Verifica se duas strings sao iguais
int stringIgual(char string1[], char string2[]){
    int tam1, tam2;
    tam1 = calculaTAM(string1);
    tam2 = calculaTAM(string2);

    if(tam1 != tam2){
        return 0;
    }

    for(int i = 0; i < tam1; i++){
        if(string1[i] != string2[i]){
            return 0;
        }
    }

    return 1;
}

// Funçao que verifica se a pessoa esta com covid e incremento o numero de casos do municipio onde a pessoa mora 
void incrementaVetorDeCasos(tPaciente p[], char municipio[QTDMUNICIPIOS][TAM3], int casos[], int j){
    int k;
    if(stringIgual(p[j].Classificacao, "Confirmados")){ // Verifica se o paciente esta com covid
        for(k = 0; k < QTDMUNICIPIOS; k++){  // Percorre todos os municipios do ES
            if(stringIgual(p[j].Municipio, municipio[k])){ // Verifica se o municipio do paciente eh igual a um municipio da string
                casos[k]++; // Se for igual incrementa o numero de casos desse municipio
                break;
            }
        }
    }
}

// Verifica se o numero de casos de um municipio eh maior que um valor N da entrada (TOPICO 3)
void imprimeCidadesComMaisDeNCasos(int N, char municipio[QTDMUNICIPIOS][TAM3], int casos[], char pasta[]){
    int i;
    char pastaAux[TAM3];
    copiaString(pasta, pastaAux);
    
    concatenaString(pasta, "item3.txt");
    FILE *item3 = fopen(pasta, "w");

    if(item3 == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    for(i = 0; i < QTDMUNICIPIOS; i++){
        if(casos[i] > N){
            fprintf(item3, "- %s: %d casos\n", municipio[i], casos[i]);
        }
    }

    fclose(item3);
    copiaString(pastaAux, pasta); // Resetando string pasta para uso na proxima funçao de imprimir
}

// Funçao que conta quantos casos de covid tiveram de d1 ate d2
int QTDCasosD1AteD2(tPaciente p[], tData d1, tData d2){ 
    int m = 0, contCasos = 0;
    for(m=0; m < QTDPACIENTES; m++){
        if(filtroDeDatas (d1, d2, p[m].DataCadastro) == 1){ 
            if(stringIgual(p[m].Classificacao, "Confirmados")){
                contCasos++;
            }
        }  
    } 
    
    return contCasos;
}

// Copia uma string num outro vetor. Nesse caso, string1 sera copiada em string2
void copiaString(char string1[], char string2[]){
    int i;
    for(i=0; string1[i] != '\0'; i++){
        string2[i] = string1[i];
    }  
    string2[i] = '\0';
}

void ordenaTopNcidades(int topN, char topMunicipios[topN][TAM3], int topCasos[], char municipio[QTDMUNICIPIOS][TAM3], int casos[]){
    int i, j, maior, posMaior;
    
    for(i = 0; i < topN; i++){ // Identifica as N cidades com mais casos de covid
        for(j = 0; j < QTDMUNICIPIOS; j++){ // Percorre todos os municipios em busca da cidade com mais casos de covid
            if(j == 0){
                maior = casos[j];
                posMaior = j;
            
            } else if(casos[j] > maior){
                maior = casos[j];
                posMaior = j;
            }
        }

        topCasos[i] = maior;
        casos[posMaior] = -1; // Descarta a cidade com o maior numero de casos, para no proximo loop pegar a proxima cidade com mais casos de covid  
        copiaString(municipio[posMaior], topMunicipios[i]);      
    }
}

// Imprime as top N cidades com mais casos de covid (TOPICO 5)

void imprimeTopNcidades(int topN, char topMunicipios[topN][TAM3], int topCasos[], char pasta[]){
    int i;
    char pastaAux[TAM3];
    copiaString(pasta, pastaAux);
    concatenaString(pasta,"item5.txt");
    FILE *item5 = fopen(pasta, "w");
    if(item5 == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);  
    }

    if(topCasos[0] = 0){
        fprintf(item5, "");
    
    } else{
        for(i = 0; i < topN; i++ ){
            fprintf(item5, "- %s: %d casos\n",topMunicipios[i],topCasos[i]);   
        }
    }

    fclose(item5);
    copiaString(pastaAux, pasta); // Resetando string pasta para uso na proxima funçao de imprimir
}

// Verifica se um dado caractere eh letra minuscula
int ehMinuscula(char c){
    if(c >= 'a' && c <= 'z'){
        return 1;
    }

    return 0;
}

// Converte uma string para letras maiusculas
void converteStringMaiuscula(char string[]){
    for(int i = 0; string[i] != '\0'; i++){
        if(ehMinuscula(string[i])){
            string[i]-= 'a' - 'A';
        }
    }
}

// Verifica se paciente faleceu ou nao
int pacienteFaleceu(tPaciente p){
    if(p.DataObito.ano != 0 && p.DataObito.mes != 0 && p.DataObito.dia != 0){
        return 1;
    }

    return 0;
}

// Porcentagem de pessoas internadas com covid em relaçao ao total de pessoas com covid
float percentPessoasInternadasComCovid(tPaciente p[], char cidadeAnalisada[]){
    int i;
    float internadosCovid = 0, covid = 0;
    for(i=0; i< QTDPACIENTES; i++){
        if(stringIgual(p[i].Classificacao, "Confirmados") == 1){
            if(stringIgual(p[i].Municipio, cidadeAnalisada) == 1 || stringIgual(cidadeAnalisada, "TODAS") == 1){
                covid++;
                if(stringIgual(p[i].FicouInternado, "Sim") == 1){
                    internadosCovid++;
                }
            }
        }
    }
    
    return 100.0 * internadosCovid /covid;
}

// Porcentagem de pessoas que morreram por covid em relaçao ao total de pessoas com covid
float percentPessoasMorreramComCovid(tPaciente p[], char cidadeAnalisada[]){
    int i;
    float mortesCovid = 0, covid = 0;
    for(i=0; i< QTDPACIENTES; i++){
        if(stringIgual(p[i].Classificacao, "Confirmados") == 1){
            if(stringIgual(p[i].Municipio, cidadeAnalisada) == 1 || stringIgual(cidadeAnalisada, "TODAS") == 1){
                covid++;
                if(pacienteFaleceu(p[i]) == 1){
                    mortesCovid++;
                }
            }
        }
    }
    return 100.0 * mortesCovid / covid;
} 

//Porcentagem de pessoas que estavam internadas  com covid que morreram em relaçao ao numero de pessoas que morreram por covid
float percentPessoasInternadasQueMorreramComCovid(tPaciente p[], char cidadeAnalisada[]){
    int i;
    float mortesInternadosCovid = 0, mortesCovid = 0;
    for(i = 0; i< QTDPACIENTES; i++){
        if(stringIgual(p[i].Classificacao, "Confirmados") == 1){
            if(stringIgual(p[i].Municipio, cidadeAnalisada) == 1 || stringIgual(cidadeAnalisada, "TODAS") == 1){
                if(pacienteFaleceu(p[i]) == 1){
                    mortesCovid++;
                    if(stringIgual(p[i].FicouInternado, "Sim") == 1){
                        mortesInternadosCovid++;
                    }
                }
            }
        }
    }
    return 100.0 * mortesInternadosCovid / mortesCovid;
}

// Funçao para calculo da media da idade das pessoas que morreram por covid
float calculaMedia(tPaciente p[], tData d1, tData d2){
    float mortesCovid = 0, somaIdades = 0;;
    for(int i = 0; i < QTDPACIENTES; i++){
        if(filtroDeDatas(d1, d2, p[i].DataCadastro) == 1){
            if(stringIgual(p[i].Classificacao, "Confirmados") == 1){
                if(pacienteFaleceu(p[i]) == 1){
                    somaIdades += p[i].IdadeNaDataNotificacao;
                    mortesCovid++;
                }
            }
        }
    }

    if(mortesCovid == 0){
        return 0;
    }

    return somaIdades / mortesCovid;
}

// Funçao para calculo do desvio padrao da idade das pessoas que morreram por covid
float calculaDesvioPadrao(tPaciente p[], tData d1, tData d2){
    int i; 
    float soma = 0, desvio;
    float k = 0; //k eh contador para pessoas com covid que morreram e que estavam entre d1 e d2
    for(i = 0; i<QTDPACIENTES; i++){
        if(pacienteFaleceu(p[i]) == 1 ){
            if(stringIgual(p[i].Classificacao, "Confirmados") == 1){
                if(filtroDeDatas(d1, d2, p[i].DataCadastro) == 1){
                    k++;
                    soma += (p[i].IdadeNaDataNotificacao - calculaMedia(p, d1, d2)) * (p[i].IdadeNaDataNotificacao - calculaMedia(p, d1, d2));
                }
            }          
        }
    }

    if(k == 0){
        return 0;
    }

    soma = soma/(k-1); 
    desvio = sqrt(soma);  
    return desvio; 
}

// Funçao que verifica se o paciente tem ou nao alguma comorbidade
int TemComorbidade(tPaciente p){
    if(stringIgual(p.ComorbidadePulmao,    "Sim")==1) { return 1; }
    if(stringIgual(p.ComorbidadeCardio,    "Sim")==1) { return 1; }
    if(stringIgual(p.ComorbidadeRenal,     "Sim")==1) { return 1; }
    if(stringIgual(p.ComorbidadeDiabetes,  "Sim")==1) { return 1; }
    if(stringIgual(p.ComorbidadeTabagismo, "Sim")==1) { return 1; }
    if(stringIgual(p.ComorbidadeObesidade, "Sim")==1) { return 1; }
    
    return 0; // Nao tem nenhuma comorbidade
}

// Funçao para calculo da porcentagem de mortes por covid sem comorbidade em relaçao as mortes por covid
float percentMortesSemComorbidade(tPaciente p[], tData d1, tData d2){
    int i;
    float cont=0, mortesCovid = 0; //cont eh para contar mortes com covid sem comorbidade
    for(i=0; i < QTDPACIENTES; i++){
        if(filtroDeDatas(d1, d2, p[i].DataCadastro)){
            if(stringIgual(p[i].Classificacao, "Confirmados")){
                if(pacienteFaleceu(p[i])==1){
                    mortesCovid++;
                    if(TemComorbidade(p[i])==0){
                        cont++;                    
                    }
                }
            }
        }
    }

    if(mortesCovid == 0){
        return 0;
    }

    return 100.0 * cont / mortesCovid;
}

// Imprime TOPICO 4
void imprimeQTDCasosD1AteD2(int qtdCasosD1D2, char pasta[]){
    char pastaAux[TAM3];
    copiaString(pasta, pastaAux);
    concatenaString(pasta, "item4.txt"); 
    FILE *item4 = fopen(pasta, "w");
    if(item4 == NULL){ 
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    
    fprintf(item4,"- Total de pessoas: %d",  qtdCasosD1D2);
    fclose(item4);
    copiaString(pastaAux, pasta); // Resetando string pasta para uso na proxima funçao de imprimir
}

// Imprime TOPICO 6
void imprimePorcentagens(float porcentagem1, float porcentagem2, float porcentagem3, char cidadeAnalisada[], char pasta[]){
    char pastaAux[TAM3];
    copiaString(pasta, pastaAux);
    concatenaString(pasta, "item6.txt"); 
    FILE *item6 = fopen(pasta, "w");
    if(item6 == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }  
    
    fprintf(item6, "- Resultados para %s:\n", cidadeAnalisada);
    fprintf(item6, "- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n", porcentagem1);
    fprintf(item6, "- A %% de pessoas com Covid-19 que morreram: %.3f%%\n", porcentagem2);
    fprintf(item6, "- A %% de pessoas que ficaram internadas e morreram: %.3f%%", porcentagem3);

    fclose(item6);
    copiaString(pastaAux, pasta); // Resetando string pasta para uso na proxima funçao de imprimir
}

// Imprime TOPICO 7
void imprimeMediaDesvioPercentSemComorb(float media, float desvio, float percentSemComorb, char pasta[]){
    char pastaAux[TAM3];
    copiaString(pasta, pastaAux);
    concatenaString(pasta,"item7.txt");
    FILE *item7 = fopen(pasta, "w");
    if(item7 == NULL){
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    fprintf(item7, "A media e desvio padrao da idade: %.3f -- %.3f\n", media, desvio);
    fprintf(item7, "A %% de pessoas que morreram sem comorbidade: %.3f%%", percentSemComorb);
    
    fclose(item7);
    copiaString(pastaAux, pasta); // Resetando string pasta para uso na proxima funçao de imprimir
}

// Funçao que cria um vetor com todos os municipios do Espirito Santo
void criaVetorMunicipios(tPaciente p[], char municipio[QTDMUNICIPIOS][TAM3]){
    int QTDcidades = 0, aux, j;
    for(int i = 0; i < QTDPACIENTES; i++){
        aux=0;
    
        for(j = 0; j < QTDcidades; j++){ // Percorre o vetor de municipios
            if(stringIgual(p[i].Municipio, municipio[j])){
                aux = 1;
                break;
            }
        }

        if(aux == 0){
            copiaString(p[i].Municipio, municipio[QTDcidades]);
            QTDcidades++;
        }   
    
        if(QTDcidades == QTDMUNICIPIOS){
            break;
        }
    }
}

// Funçao que verifica se a string1 eh maior que a string2 (alfabeticamente falando)
int stringMaior(char string1[], char string2[]){
    for(int i = 0; string1[i] != '\0' && string2[i] != '\0'; i++){
        if(string1[i] == string2[i]){
            continue;
        
        } else if(string1[i] > string2[i]){
            return 1;
        
        } else{
            return 0;
        }
    }

    return 0;
}

// Funçao que ordena os municipios em ordem alfabetica
void OrdemAlfabeticaMunicipios(char municipio[QTDMUNICIPIOS][TAM3]){
    char aux[TAM3];
    for(int i = 0; i < QTDMUNICIPIOS; i++){
        for(int k = (i+1); k < QTDMUNICIPIOS; k++){
            if(stringMaior(municipio[i], municipio[k]) == 1){
                copiaString(municipio[i], aux);
                copiaString(municipio[k], municipio[i]);
                copiaString(aux, municipio[k]);   
            }
        }
    }
}

// Funçao que concatena duas strings na string1
void concatenaString(char string1[], char string2[]){
    int tam1, tam2;
    tam1 = calculaTAM(string1); 
    tam2 = calculaTAM(string2);           //   ./teste1/        item3.txt
    
    for(int i=0, m = tam1; i < tam2; i++,m++){     
        string1[m] = string2[i];
    } 

    string1[tam1 + tam2] = '\0';
}  