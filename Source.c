//um espeai necessita passar informaçao para o comando via  arquivo, mas este nao podera ser comprometido pelo inimigo
//entao apos digitar o texto ele devera ser criptografado pelo espiao e descriptografado pelo comando
//utilize um menu para realizar  as operações sobre o aqruivo
//1- criar arquivo - apenas o espiao pode criar // se identifica ususari oe senha
//struct senha.txt - nome, usuario, cpf, cargo , senha, data cadastro, informaco se ativo ou inativo
// cargo - 1-comandante, 2 espiao, 3 admin
//2 - criptografa msg - somente espiao criptografa
//3 - descriptogrfa msg - somente comando
//4 - atalizar senhas - somente adm atulizar ou criar senha

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

typedef struct UsuarioLogado {
	char nomeLogado[20], usuarioLogado[20], ativoInativoLogado;
	int cpfLogado, senhaLogado;
	enum TipoCargo tipoCargoLogado;
}UsuarioLogado;

void Arte();
void MotraMenu();
void AtualizaSenhas();
void CriarArquivo();
int VerificaUsuario();
void CadastraAdmin();

int main() {

	int opMenu = 1;
	FILE *arqSenhas;
	//arqSenhas = fopen("senha.txt", "at");
	//fclose(arqSenhas);
	CadastraAdmin();
	do {
		Arte();
		MotraMenu();
		scanf("%d", &opMenu);
		switch (opMenu)
		{
		case 1:
			CriarArquivo();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			AtualizaSenhas();
			break;
		case 5:
			break;
		default:
			printf("\nOpcao invalida, aperte uma tecla para continuar");
			_getch();
			system("cls");
			break;
		}
	} while (opMenu != 5);

}

void Arte(){
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
	printf("\n*2 - Criptografar Mensagem            *");
	printf("\n*3 - Ler Mensagem Criptografada       *");
	printf("\n*4 - Atualizar Cadastro               *");
	printf("\n*5 - Sair                             *");
	printf("\n***************************************");
}

void CriarArquivo() {
	char login[20];
	int senha;
	printf("\nUsuario: ");
	scanf("%s", login);
	setbuf(stdin, NULL);
	printf("\nSenha: ");
	scanf("%d", &senha);
	setbuf(stdin, NULL);
	
	UsuarioLogado usuarioLogado;
	FILE *arqSenhas;
	arqSenhas = fopen("senha.txt", "rt");
	fread(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);

	if (strcmp(usuarioLogado.usuarioLogado, login) == 0) {
		if (usuarioLogado.senhaLogado == senha) {
			printf("OK");
		}
	}

	fclose(arqSenhas);
}

void AtualizaSenhas() {
	
	UsuarioLogado usuarioLogado;
	FILE *arqSenhas;
	arqSenhas = fopen("senha.txt", "at");

	int tipoCargo = VerificaUsuario();

	if (tipoCargo != 3)
	{
		printf("\nUsuario invalido para operacao selecionada\nAperte qualquer tecla para continuar");
		_getch();
		system("cls");
		return;
	}

	fwrite(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);
	fclose(arqSenhas);
}

int VerificaUsuario() {
	UsuarioLogado usuarioLogado;
	FILE *arqSenhas;
	arqSenhas = fopen("senha.txt", "rt");

	char login[20];
	int senha;
	printf("\nUsuario: ");
	scanf("%s", login);
	setbuf(stdin, NULL);
	printf("\nSenha: ");
	scanf("%d", &senha);
	setbuf(stdin, NULL);

	fread(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);

	switch (usuarioLogado.tipoCargoLogado)
	{
	case 1:
		printf("\nBem vindo Comandante");
		break;
	case 2:
		printf("\nBem vindo Espiao");
		break;
	case 3:
		printf("\nBem vindo Administrador");
		break;
	default:
		break;
	}
}

void CadastraAdmin() {
	UsuarioLogado usuarioLogado;
	FILE *arqSenhas;
	arqSenhas = fopen("senha.txt", "at");

	strcpy(usuarioLogado.nomeLogado, "Admin");
	strcpy(usuarioLogado.usuarioLogado, "admin");
	usuarioLogado.ativoInativoLogado = 'S';
	usuarioLogado.cpfLogado = 191;
	usuarioLogado.senhaLogado = 123;
	usuarioLogado.tipoCargoLogado = 3;

	fwrite(&usuarioLogado, sizeof(UsuarioLogado), 1, arqSenhas);
	fclose(arqSenhas);
}