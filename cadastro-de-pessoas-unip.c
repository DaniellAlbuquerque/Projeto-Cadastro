#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <direct.h>
#include <assert.h>
int opcao;

FILE *arq_pacientes;
FILE *arq_pacientesc;
FILE *arq_todos;

int main()
{
     setlocale(LC_ALL, "Portuguese");


    char usuario[20], scanUsuario[20];
    char senha[20], scanSenha[20];

    strcpy(usuario,"admin");
    strcpy(senha,"123");

    bool usuariosIguais = false;
    bool senhasIguais = false;

    do{
        printInfoBase(0);

        printf("\n\nBEM VINDO!");
        printf("\nLOGIN:");
        scanf("%s",scanUsuario);

        printInfoBase(0);
        printf("\nSENHA:");
        scanf ("%s",scanSenha);

        usuariosIguais = strcmp(usuario,scanUsuario) == 0;
        senhasIguais = strcmp(senha, scanSenha) == 0;

        if (!usuariosIguais || !senhasIguais){
            printInfoBase(0);
            printf("\n\n\n\tUsuário e/ou senha incorretos.Por favor tente novamente!\n");
            getch();
        }

    } while(!usuariosIguais || !senhasIguais);

    printInfoBase(0);
    printf("\nLogin realizado com sucesso!\n");
    getch();

    do
	{
	    printf("\nTecle Enter para Continuar!");

	    char nome[50], email[50];
        char cpf[50], endereco_rua[50], endereco_numero[50], endereco_bairro[50], endereco_cep[50];
        char telefone[50], strIdade[4],dataDiagnostico[50],comorbidades[50];
        int idade, nitems,opcaoComorbidade;


	    printInfoBase(0);
        printf("\n** SISTEMA PARA CADASTRO DE PACIENTES COM  COVID-19 **\n");
        printf("\n** 1-Cadastrar novo paciente **\n");
        printf("\n** 2-Listar pacientes fora do grupo de risco **\n");
        printf("\n** 3-Listar pacientes considerados de risco **\n");
        printf("\n** 4-Listar todos os pacientes cadastrados **\n");
        printf("\n** 0-Sair **\n");
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao){
            case 0:;
                printInfoBase(0);
                printf("Muito obrigado pela prefer�ncia.");
                getch();
                break;
            case 1:;
                bool continuaValido = true;

                struct tm *data_hora_atual;
                time_t segundos;
                time(&segundos);
                data_hora_atual = localtime(&segundos);
                data_hora_atual = localtime(&segundos);
                int diaA = data_hora_atual->tm_mday;
                int mesA = data_hora_atual->tm_mon+1; //m�s
                int anoA = data_hora_atual->tm_year+1900; //ano Atual

                printInfoBase(1);

                printf("\nDigite o nome completo do paciente: ");
                scanf("%[^\n]s",&nome);

                if(ValidarSomenteTexto(nome)!=1){
                    printf("\nNome informado � inv�lido pois est� vazio ou contem n�meros.");
                    getch();
                    goto final_1;
                }

                if(VerificarCancelamento(nome)==0) goto cancelamento;


                printf("\nDigite o CPF do paciente (xxx.xxx.xxx-xx): ");
                scanf(" %[^\n]s",&cpf);

                if(VerificarCancelamento(cpf)==0) goto cancelamento;

                printf("\nDigite o endereco do paciente (Rua): ");
                scanf(" %[^\n]s",&endereco_rua);

                if(VerificarCancelamento(endereco_rua)==0) goto cancelamento;

                printf("\nDigite o endereco do paciente (Numero): ");
                scanf(" %[^\n]s",&endereco_numero);

                if(VerificarCancelamento(endereco_numero)==0) goto cancelamento;

                printf("\nDigite o endereco do paciente (Bairro): ");
                scanf(" %[^\n]s",&endereco_bairro);

                if(VerificarCancelamento(endereco_bairro)==0) goto cancelamento;

                printf("\nDigite o endereco do paciente (CEP): ");
                scanf(" %[^\n]d",&endereco_cep);

                if(ValidarSomenteDigitos(endereco_cep)!=1){
                    printf("\nCEP foi informado de forma inv�lida.");
                    getch();
                    goto final_1;
                }

                if(VerificarCancelamento(endereco_cep)==0) goto cancelamento;


                printf("\nDigite o telefone do paciente (xx-xxxxxxxx): ");
                scanf(" %[^\n]s",&telefone);

                if(VerificarCancelamento(telefone)==0) goto cancelamento;

                printf("\nDigite data de diagnostico na seguinte configuracao: dd/mm/aaaa\n");
                scanf(" %[^\n]s",&dataDiagnostico);

                if(VerificarCancelamento(dataDiagnostico)==0) goto cancelamento;

                printf("\nDigite o e-mail do paciente: ");
                scanf(" %[^\n]s",&email);

                if(VerificarCancelamento(email)==0) goto cancelamento;

                int diaN, mesN, anoN, idade;

                printf("\nInforme a sua data de nascimento na seguinte configuracao: dd/mm/aaaa\n");
                printf("\n(N�o digite 'exit' nessa informa��o.')\n");
                scanf("%d/%d/%d", &diaN, &mesN, &anoN);

                if ((mesN > mesA) || ((mesN = mesA) && (diaN > diaA))){
                   idade = anoA - anoN ;
                   printf("Paciente tem %d", idade);
                }
                else {
                    idade = anoA - anoN;
                    printf("Paciente tem %d", idade);
                }


                printf("\nVoc� tem algum comorbidade(Sim 1/Nao 2): ");
                scanf("%d",&opcaoComorbidade);

                if(opcaoComorbidade == 1) {
                    printf("\nInforme a Comorbidade: ");
                    scanf(" %[^\n]s",&comorbidades);}

                    if(VerificarCancelamento(comorbidades)==0) goto cancelamento;
                }

                if((opcaoComorbidade == 1)||(idade >= 65)){
                   arq_pacientesc=fopen("pacientescomorb.txt","a");
                   fprintf(arq_pacientesc,"\nNome: %s",nome);
                   fprintf(arq_pacientesc,"\nCEP: %s",endereco_cep);
                   fprintf(arq_pacientesc,"\nidade: %d",idade);
                   fprintf(arq_pacientesc,"\nComorbidade: %s \n\n",comorbidades);

                   arq_todos=fopen("todospacientes.txt","a");
                   fprintf(arq_todos,"\nNome: %s",nome);
                   fprintf(arq_todos,"\nCPF: %s",cpf);
                   fprintf(arq_todos,"\nE-mail: %s",email);
                   fprintf(arq_todos, "\nRua: %s",endereco_rua);
                   fprintf(arq_todos, "\nNumero: %s",endereco_numero);
                   fprintf(arq_todos, "\nBairro: %s",endereco_bairro);
                   fprintf(arq_todos, "\nCEP: %s",endereco_cep);
                   fprintf(arq_todos,"\nTelefone: %s",telefone);
                   fprintf(arq_todos,"\nData de diagnostico: %s",dataDiagnostico);


                    fclose(arq_pacientesc);
                    fclose(arq_todos);

                    printInfoBase(0);
                    printf("\nPaciente Cadastrado com Sucesso");
                    getch();
                    goto final_1;
                }
                else if ((opcaoComorbidade == 2)||(idade < 65)){
                   arq_pacientes=fopen("pacientes.txt","a");
                   fprintf(arq_pacientes,"\nNome: %s",nome);
                   fprintf(arq_pacientes,"\nCPF: %s",cpf);
                   fprintf(arq_pacientes,"\nCEP: %s",endereco_cep);
                   fprintf(arq_pacientes,"\nTelefone: %s",telefone);
                   fprintf(arq_pacientes,"\nIdade: %d\n",idade);
                   fclose(arq_pacientes);

                   arq_todos=fopen("todospacientes.txt","a");
                   fprintf(arq_todos,"\nNome: %s",nome);
                   fprintf(arq_todos,"\nCPF: %s",cpf);
                   fprintf(arq_todos,"\nE-mail: %s",email);
                   fprintf(arq_todos, "\nRua: %s",endereco_rua);
                   fprintf(arq_todos, "\nNumero: %s",endereco_numero);
                   fprintf(arq_todos, "\nBairro: %s",endereco_bairro);
                   fprintf(arq_todos, "\nCEP: %s",endereco_cep);
                   fprintf(arq_todos,"\nTelefone: %s",telefone);
                   fprintf(arq_todos,"\nData de diagnostico: %s",dataDiagnostico);
                   fclose(arq_todos);


                    printInfoBase(0);
                    printf("\nPaciente Cadastrado com Sucesso");
                    getch();
                    goto final_1;
                }else {
                    printInfoBase(0);
                    printf("\nHouve uma falha durante o cadastro.");
                    getch();
                    goto final_1;
                }

                cancelamento:
                    printf("\nVoltando ao Menu Principal.");
                    getch();

                final_1:
                break;

            case 2:;
                printInfoBase(0);

                char ch;
                arq_pacientes = fopen("pacientes.txt", "r");
                if(arq_pacientes == NULL)
                {   printInfoBase(0);
                    /* Unable to open file hence exit */
                    printf("N�o foi poss�vel abrir o arquivo.\n");
                    printf("Por favor verifique as permiss�es de acesso ou se os arquivos existem.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch = fgetc(arq_pacientes);
                    putchar(ch);


                } while(ch != EOF); /* Repeat this if last read character is not EOF */

                fclose(arq_pacientes);


                printf("\n\n\n************************************************************************************************");
                printf("\nFim da lista de pacientes.");
                getch();
                break;


              case 3:;
                printInfoBase(0);

                char ch1;
                arq_pacientesc = fopen("pacientescomorb.txt", "r");
                if(arq_pacientesc == NULL)
                {   printInfoBase(0);
                    /* Unable to open file hence exit */
                    printf("N�o foi poss�vel abrir o arquivo.\n");
                    printf("Por favor verifique as permiss�es de acesso ou se os arquivos existem.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch1 = fgetc(arq_pacientesc);
                    putchar(ch1);


                } while(ch1 != EOF); /* Repeat this if last read character is not EOF */

                fclose(arq_pacientesc);


                printf("\n\n\n************************************************************************************************");
                printf("\nFim da lista de pacientes de risco.");
                getch();
                break;

                  case 4:;
                printInfoBase(0);

                char ch2;
                arq_todos = fopen("todospacientes.txt", "r");
                if(arq_todos == NULL)
                {   printInfoBase(0);
                    /* Unable to open file hence exit */
                    printf("N�o foi poss�vel abrir o arquivo.\n");
                    printf("Por favor verifique as permiss�es de acesso ou se os arquivos existem.\n");
                    exit(EXIT_FAILURE);
                } else do {
                   ch2 = fgetc(arq_todos);
                    putchar(ch2);


                } while(ch2 != EOF); /* Repeat this if last read character is not EOF */

                fclose(arq_todos);


                printf("\n\n\n************************************************************************************************");
                printf("\nFim da lista de pacientes.");
                getch();
                break;



            default:;
                printInfoBase(0);
                printf("Op��o inv�lida\n");
                getch();
                break;
            }
    } while(opcao !=0);

    system('cls');
}

void printInfoBase(int informarOpcaoCancelar){


    system("cls");
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    printf("\nHora ........: %d:",data_hora_atual->tm_hour);//hora
    printf("%d:",data_hora_atual->tm_min);//minuto
    printf("%d\n",data_hora_atual->tm_sec);//segundo
    printf("\nData ........: %d/", data_hora_atual->tm_mday);
    printf("%d/",data_hora_atual->tm_mon+1); //m�s
    printf("%d\n\n",data_hora_atual->tm_year+1900); //ano

    printf("\n************************************************************");
    printf("\n****************GERENCIAMENTO PACIENTE COVID****************");
    printf("\n************************************************************\n\n");

    if(informarOpcaoCancelar==1)
        printf("\nEscreva 'exit' para retornar ao menu principal.\n\n");


    return segundos;
}

int VerificarCancelamento(char *entrada){

    if (strcmp(strlwr(entrada),"exit")==0){
        return 0;
    }
    return 1;
}


int ValidarSomenteTexto(char *entrada){

    if(strlen(entrada) == 0)
        return 0;
    for (int i = 0; entrada[i] != '\0'; i++)
    {
        char ch = entrada[i];
        if (isdigit(ch)){
            return 0;
        }
    }
    return 1;
}


int ValidarSomenteDigitos(char *entrada){

    if(strlen(entrada) == 0)
        return 0;
    for (int i = 0; entrada[i] != '\0'; i++)
    {
        char ch = entrada[i];
        if (!isdigit(ch)){
            return 0;
        }
    }
    return 1;
}


