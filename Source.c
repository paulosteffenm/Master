

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

enum TipoCargo {
	Comandante = 1,
	Espiao,
	Administrador
};

enum AtivoInativo {
	Ativo = 1,
	Inativo
};

typedef struct DateTime {
	int dia, mes, ano;
}DateTime;

typedef struct UsuarioLogado {
	char nomeLogado[20], usuarioLogado[20];
	int cpfLogado, senhaLogado;
	enum TipoCargo tipoCargoLogado;
	enum AtivoInativo ativoInativo;
	DateTime dateTime;
}UsuarioLogado;

void Arte();
void MotraMenu();
void AtualizaSenhas();
void CriarArquivo();
int VerificaUsuario();
void CadastraAdmin();
void LerArquivo();

int main() {

	int opMenu = 1;
	FILE* arqSenhas;
	//CadastraAdmin();
	do {	
		Arte();
		MotraMenu();
		setbuf(stdin, NULL);
		scanf("%d", &opMenu);
		switch (opMenu)
		{
		case 1:
			CriarArquivo();
			break;
		case 2:
			LerArquivo();
			break;
		case 3:
			system("cls");
			AtualizaSenhas();
			break;
		case 4:
			break;
		default:
			printf("\nOpcao invalida, aperte uma tecla para continuar");
			_getch();
			system("cls");
			break;
		}
	} while (opMenu != 4);

}

void Arte() {
	printf("\n");
	printf("**********   **********   **        **\n");
	printf("**********   **********    **      **\n");
	printf("***          **      **     **    ** \n");
	printf("***          **      **      **  **   \n");
	printf("**********   **********        **   \n");
	printf("**********   **********        ** \n");
	printf("       ***   ***               **  \n");
	printf("       ***   ***               **  \n");
	printf("**********   ***               ** \n");
	printf("**********   ***               ** \n");
	printf("\n                                  ");

}

void MotraMenu() {
	printf("\n***************************************");
	printf("\n*1 - Criar Mensagem                   *");
	printf("\n*2 - Ler Mensagem Criptografada       *");
	printf("\n*3 - Atualizar Cadastro               *");
	printf("\n*4 - Sair                             *");
	printf("\n***************************************");
	printf("\n");
}

void CriarArquivo() {
	system("cls");
	int tipoCargo = VerificaUsuario();

	if (tipoCargo != 2)
	{
		if (tipoCargo != 0) 
		{
			printf("\nUsuario invalido para operacao selecionada\nAperte qualquer tecla para continuar");
			_getch();
			system("cls");
		}
	}
	else
	{
		FILE* arqMensagem;
		arqMensagem = fopen("mensagem.txt", "wt");
		char mensagem[100];
		printf("\nEntre com a mensagem: ");
		gets(mensagem);
		for (int i = 0; i != strlen(mensagem); i++)
		{
			mensagem[i] = mensagem[i] + (i+1);
		}
		fprintf(arqMensagem, "%s", mensagem);
		//system("cls");
		printf("\nMensagem cadastrada\nAperte qualquer tecla para continuar");
		_getch();
		system("cls");
		fclose(arqMensagem);
	}
}

void AtualizaSenhas() {

	UsuarioLogado usuarioLogado;
	FILE* arqSenhas;
	arqSenhas = fopen("senha.txt", "at");

	int tipoCargo = VerificaUsuario();

	if (tipoCargo != 3)
	{
		if (tipoCargo != 0)
		{
			printf("\nUsuario invalido para operacao selecionada\nAperte qualquer tecla para continuar");
			_getch();
			system("cls");	
		}
	}
	else
	{

		printf("\nEntre com o seu NOME: ");
		scanf("%s", usuarioLogado.nomeLogado);
		setbuf(stdin, NULL);
		printf("\nEntre com o seu LOGIN: ");
		scanf("%s", usuarioLogado.usuarioLogado);
		setbuf(stdin, NULL);
		printf("\nEntre com o seu CPF: ");
		scanf("%d", &usuarioLogado.cpfLogado);
		setbuf(stdin, NULL);
		do
		{
			printf("\nEntre com o seu CARGO: ");
			scanf("%d", &usuarioLogado.tipoCargoLogado);
			setbuf(stdin, NULL);
			if (usuarioLogado.tipoCargoLogado != 1 && usuarioLogado.tipoCargoLogado != 2 && usuarioLogado.tipoCargoLogado != 3)
			{
				printf("\nCargo Invalido");
			}
		} while (usuarioLogado.tipoCargoLogado != 1 && usuarioLogado.tipoCargoLogado != 2 && usuarioLogado.tipoCargoLogado != 3);
		printf("\nEntre com o sua SENHA: ");
		scanf("%d", &usuarioLogado.senhaLogado);
		setbuf(stdin, NULL);
		printf("\nEntre com a DATA DE CADASTRO:(dia/mes/ano) ");
		scanf("%d", &usuarioLogado.dateTime.dia);
		setbuf(stdin, NULL);
		scanf("%d", &usuarioLogado.dateTime.mes);
		setbuf(stdin, NULL);
		scanf("%d", &usuarioLogado.dateTime.ano);
		setbuf(stdin, NULL);
		do {
			printf("\nAtivo ou Inativo(1/0) ");
			scanf("%d", &usuarioLogado.ativoInativo);
			setbuf(stdin, NULL);
			if (usuarioLogado.ativoInativo != 1 && usuarioLogado.ativoInativo != 0)
			{
				printf("Tipo invalido");
			}
		} while (usuarioLogado.ativoInativo != 1 && usuarioLogado.ativoInativo != 0);

		fwrite(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);
		fclose(arqSenhas);
	}
}

int VerificaUsuario() {
	UsuarioLogado usuarioLogado;
	FILE* arqSenhas;
	arqSenhas = fopen("senha.txt", "rt");

	char login[20];
	int senha;
	printf("\nUsuario: ");
	scanf("%s", login);
	setbuf(stdin, NULL);
	printf("\nSenha: ");
	scanf("%d", &senha);
	setbuf(stdin, NULL);

	while (!feof(arqSenhas)) {
		fread(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);
		if ((strcmp(usuarioLogado.usuarioLogado, login) == 0) && (usuarioLogado.senhaLogado == senha))
		{
			switch (usuarioLogado.tipoCargoLogado)
			{
			case 1:
				printf("\nBem vindo Comandante");
				fclose(arqSenhas);
				return 1;
			case 2:
				printf("\nBem vindo Espiao");
				fclose(arqSenhas);
				return 2;
			case 3:
				printf("\nBem vindo Administrador");
				fclose(arqSenhas);
				return 3;
			default:
				return 0;
			}
		}	
	}
	printf("\nUsuario/Senha invalido(s)\nAperte qualquer tecla para continuar");
	_getch();
	system("cls");
	fclose(arqSenhas);
	return 0;
}

void LerArquivo() {
	system("cls");
	int tipoCargo = VerificaUsuario();

	if (tipoCargo != 1)
	{
		if (tipoCargo != 0)
		{
			printf("\nUsuario invalido para operacao selecionada\nAperte qualquer tecla para continuar");
			_getch();
			system("cls");
		}
	}
	else
	{
		FILE* arqMensagem;
		arqMensagem = fopen("mensagem.txt", "rt");
		char c, formtado[100];
		int numeroCaracter = 0;
		printf("\nMensagem: ");
		for(int i = 0; !feof(arqMensagem); i++)
		{ 
			fscanf(arqMensagem, "%c", &c);
			formtado[i] = c - (i + 1);
			numeroCaracter++;
		}
		for (int i = 0; i != numeroCaracter - 1; i++)
		{
			printf("%c", formtado[i]);
		}
		printf("\nAperte qualquer tecla para continuar");
		_getch();
		system("cls");
		fclose(arqMensagem);
	}
}

void CadastraAdmin() {
	UsuarioLogado usuarioLogado;
	FILE* arqSenhas;
	arqSenhas = fopen("senha.txt", "at");

	strcpy(usuarioLogado.nomeLogado, "Admin");
	strcpy(usuarioLogado.usuarioLogado, "admin");
	usuarioLogado.ativoInativo = 1;
	usuarioLogado.cpfLogado = 191;
	usuarioLogado.senhaLogado = 123;
	usuarioLogado.tipoCargoLogado = 3;

	fwrite(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);
	fclose(arqSenhas);
}
