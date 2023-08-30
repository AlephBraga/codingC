#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#define nRooms 2
#define nSessions 2
#define nRows 7
#define nSeats 12

/* Define uma sessão (sala com (nRows * nSeats) assentos disponíveis ---------*/
typedef struct{/* Validado */
	char name[100];
	int ageToWatch;
	int availableTickets;
	char price[50];
	bool seat[nRows][nSeats];
	char time[50];
}Session;

/* Define uma sala com (nSession) sessões (originalmente 2, tarde e noite) ---*/
typedef struct{/* Validado */
	Session session[nSessions];
}Room;

/* Imprime linha de tamanho 80 (tamanho padrão de console Windows/Linux/IBM) -*/
void LineBreak(void){/* Validado */
	for(int i = 0; i < 80; i++)
		printf("%c", (char)196);
	printf("\n");
	return;
}

/* Converte letra da fileira em posição dentro de uma matriz ----------------*/
int RowToPos(char row){/* Validado */
	return ((int) toupper(row)) - 65;
}

/* Converte posição dentro de uma matrix em uma letra da fileira -------------*/
char PosToRow(int seat){/* Validado */
	return (char) (seat + 65);
}

/* Converte o numero do assento em posição dentro da matriz ------------------*/
int IntToPos(int rowNumber){/* Validado */
	return rowNumber - 1;
}

/* Converte posição dentro da matriz em um numero de assento -----------------*/
int PosToInt(int rowNumber){/* Validado */
	return rowNumber + 1;
}

int PointToInt(Room * r, int nR, int nS){
	return r[nR].session[nS].ageToWatch;
}

/* Imprime nome do filme, classificação, e se bool TRUE, os assentos da sala -*/
void PrintSession(Room * r, int nR, int nS, bool printRoom){/* Validado */
	printf("Sala: %d // ", PosToInt(nR));
	printf("sess%co das %s: ",(char)198, r[nR].session[nS].time);
	printf("%s\n", r[nR].session[nS].name);
	
	printf("Classifica%c%co indicativa: ", (char)135, (char)198);
	if(r[nR].session[nS].ageToWatch != 0){
		printf("%d anos\n", PointToInt(r, nR, nS));
	}
	else{
		printf("Todas as idades\n");
	}
	
	printf("Ingresso: R$ %s - ", r[nR].session[nS].price);
		
	printf("Ingressos dispon%cveis: %d\n", (char)161, r[nR].session[nS].availableTickets);
	LineBreak();
	
	if(printRoom){
		
		printf("%c", (char)201);
		for(int i = 1; i < (nSeats * 4); i++){
			printf("%c", (char)205);
		}
		printf("%c", (char)187);
		printf("\n");
		
		printf("%c", (char)186);
		for(int i = 1; i < (nSeats * 4); i++){
			printf(" ");
		}
		printf("%c", (char)186);
		printf("\n");
		
		printf("%c", (char)186);
		for(int i = 1; i < (nSeats * 4); i++){
			printf(" ");
		}
		printf("%c", (char)186);
		printf("\n");
		
		printf("%c", (char)186);
		for(int i = 1; i < (nSeats * 4); i++){
			printf(" ");
		}
		printf("%c", (char)186);
		printf("\n");
		
		printf("%c", (char)200);
		for(int i = 1; i < (nSeats * 4); i++){
			printf("%c", (char)205);
		}
		printf("%c", (char)188);
		printf("\n\n");
		
		printf("%c", (char)218);
		for(int i = 1; i < (nSeats * 4); i++){
			if(i % 4 != 0)
				printf("%c", (char)196);
			else
				printf("%c", (char)194);
		}
		printf("%c", (char)191);
		printf("\n");
		for(int i = 0; i < nRows; i++){
			printf("%c", (char)179);
			for(int j = 0; j < nSeats; j++){
				if(r[nR].session[nS].seat[i][j]){
					printf("%c%c%c", (char)177, (char)177, (char)177);
				}else{
					if(j < 9)
						printf("%c0%d", PosToRow(i), j + 1);
					else
						printf("%c%d", PosToRow(i), j + 1);
				}
				printf("%c", (char)179);
			}
			if(i < (nRows - 1)){
				printf("\n");
				printf("%c", (char)195);
				for(int i = 1; i < (nSeats * 4); i++){
					if(i % 4 != 0)
						printf("%c", (char)196);
					else
						printf("%c", (char)197);
				}
				printf("%c", (char)180);
			}
			printf("\n");
		}
		printf("%c", (char)192);
		for(int i = 1; i < (nSeats * 4); i++){
			if(i % 4 != 0)
				printf("%c", (char)196);
			else
				printf("%c", (char)193);
		}
		printf("%c", (char)217);
		printf("\n");	
	}
	return;
}

/* Libera todos os assentos da sala para compra ------------------------------*/
/* E se roomOnly for FALSE, muda o nome do filme e classificação indicativa - */
 void ResetSession(Room * r, int nR,int nS, bool roomOnly, bool init){/* Validado */
 	int confirmR = 2;
	
  	if(!roomOnly){
  		if(!init){
  			do{
  				system("cls");
  				PrintSession(r,nR, nS, false); 
  				printf("Deseja resetar a sess%co das %s ", (char)198, r[nR].session[nS].time);
  				printf("da sala %d?\n", PosToInt(nR));
  				printf("[1]Sim [0]N%co\n", (char)198);
  				fflush(stdin);
  				scanf("%d", &confirmR);
			}while(confirmR != 1 && confirmR != 0);
		}else{
			confirmR = 1;
		}
		
		if(confirmR == 1){
			system("cls");
  			printf("Digite o nome do filme das %s ", r[nR].session[nS].time);
			printf("da sala %d:\n", PosToInt(nR));
			fflush(stdin);
			scanf("%[^\n]", r[nR].session[nS].name);
			
			printf("\nDigite o hor%crio do filme:\n", (char)160 /* á */);
			fflush(stdin);
			scanf("%[^\n]", r[nR].session[nS].time);
			
			printf("\nQual o pre%co do ingresso?\n", (char)135);
			printf("R$: ");
			fflush(stdin);
			scanf("%[^\n]", r[nR].session[nS].price);
			
			printf("\nQual a classifica%c%co indicativa do filme?\n", (char)135, (char)198);
			printf("Digite a idade m%cnima para assistir o filme\n", (char)161);
			printf("Ou digite 0 para todas as idades:\n");
			fflush(stdin);
			scanf("%d", &r[nR].session[nS].ageToWatch);
			
			system("cls");
			LineBreak();
			printf("\nSess%co resetada com sucesso\n", (char)198);
		}
	}  	
  	
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nSeats; j++){
			r[nR].session[nS].seat[i][j] = false;
		}
	}
	
	r[nR].session[nS].availableTickets = nRows * nSeats;
	return;
}

/*Cancela compra de um ingresso CASO já tenha sido comprado ------------------*/
void CancelPurchase(Room * r){
	int choiceRS = 1, ticketRoom ,nR, nS, seat;
	int changeSeat = 1, confirmCancel = 2;
	char row;
	system("cls");
	
	for(int i = 0; i < nRooms; i++){
		for(int j = 0; j < nSessions; j++){
			printf("[%d] - ", choiceRS++);
			PrintSession(r, i, j, false);
		}
	}
	
	do{
		printf("Digite o n%cmero da sess%co para cancelar o ingresso:\n", (char)163, (char)198);
		fflush(stdin);
		scanf("%d", &ticketRoom);
	}while((ticketRoom < 1) || (ticketRoom > (nRooms * nSessions)));
	
	choiceRS = 1;
	for (int i = 0; i < nRooms; i++){
		for(int j = 0; j < nSessions; j++){
			if(choiceRS == ticketRoom){
				nR = i;
				nS = j;
			}
			choiceRS++;
		}
	}
	
	do{
		system("cls");
		PrintSession(r, nR, nS, true);
		do{
			do{
				printf("Qual poltrona deseja cancelar? Exemplo: a 1\n");
				fflush(stdin);
				scanf("%c %d", &row, &seat);
			}while(RowToPos(row) < 0 || RowToPos(row) > nRows);
		}while(IntToPos(seat) < 0 || IntToPos(seat) > nSeats);
			
		if(r[nR].session[nS].seat[RowToPos(row)][IntToPos(seat)]){
			system("cls");
			LineBreak();
			
			do{
				LineBreak();
				printf("Cancelar compra?\n");
				printf("[1]Sim [0]N%co\n", (char)198);
				fflush(stdin);
				scanf("%d", &confirmCancel);
			}while(confirmCancel < 0 || confirmCancel > 1);
			
			if(confirmCancel == 1){
				printf("\nCancelamento da compra do ingresso ");
				printf("foi realizada com sucesso\n");
				r[nR].session[nS].seat[RowToPos(row)][IntToPos(seat)] = false;
				r[nR].session[nS].availableTickets += 1;
			}else{
				system("cls");
				LineBreak();
				printf("\nA compra do ingresso n%co foi cancelada\n", (char)198);
			}
			changeSeat = 2;
		}else{
			do{
				printf("O ingresso da poltrona %c-%d ", row, seat);
				printf("ainda n%co foi comprado, gostaria de cancelar ", (char)198);
				printf("a compra de outra poltrona?\n");
				printf("[1]Sim [0]N%co\n", (char)198);
				fflush(stdin);
				scanf("%d", &changeSeat);
			}while(changeSeat < 0 || changeSeat > 1);
			if( changeSeat == 0){
				system("cls");
				LineBreak();
				printf("\nA compra do ingresso n%co foi cancelada\n", (char)198);
			}
		}
	}while(changeSeat == 1);
	return;
}

/* Permite comprar ingresso CASO o cliente tenha idade o suficiente --------- */
void BuyTicket(Room * r){
	int choiceRS = 1, ticketRoom ,nR, nS, seat;
	int clientAge, newSeat = 1, confirmPurchase = 2;
	char row;
	bool age = false;
	
	system("cls");
	LineBreak();
	for(int i = 0; i < nRooms; i++){
		for(int j = 0; j < nSessions; j++){
			printf("[%d] - ", choiceRS++);
			PrintSession(r, i, j, false);
		}
	}
	
	do{
		printf("Digite o n%cmero da sess%co desejada:", (char)163, (char)198);
		fflush(stdin);
		scanf("%d", &ticketRoom);
	}while((ticketRoom < 1 || (ticketRoom > (nRooms * nSessions)));
	
	choiceRS = 1;
	for (int i = 0; i < nRooms; i++){
		for(int j = 0; j < nSessions; j++){
			if(choiceRS == ticketRoom){
				nR = i;
				nS = j;
			}
			choiceRS++;
		}
	}
	
	system("cls");
	PrintSession(r, nR, nS, false);
	
	int hasAge = PointToInt(r, nR, nS);
	if(hasAge != 0){
		do{
			system("cls");
			PrintSession(r, nR, nS, false);
			printf("O cliente tem idade para ver o filme?\n");
			printf("[1]Sim [0]N%co\n", (char)198);
			fflush(stdin);
			scanf("%d", &clientAge);
		}while(clientAge < 0 || clientAge > 1 );
		if(clientAge == 1){
			age = true;
		}else{
			age = false;	
		}
	}else{
		age = true;
	}	
	
	while(newSeat == 1){
		if(age == true){
			system("cls");
			PrintSession(r, nR, nS, true);
			
			do{
				do{
					printf("Qual poltrona deseja comprar? (Exemplo: a 1)\n");
					fflush(stdin);
					scanf("%c %d", &row, &seat);
				}while(RowToPos(row) < 0 || RowToPos(row) > nRows);
			}while(IntToPos(seat) < 0 || IntToPos(seat) > nSeats);
			
			if(!r[nR].session[nS].seat[RowToPos(row)][IntToPos(seat)]){
				do{
					LineBreak();
					printf("Confirmar compra?\n");
					printf("[1]Sim [0]N%co\n", (char)198);
					fflush(stdin);
					scanf("%d", &confirmPurchase);
				}while(confirmPurchase < 0 || confirmPurchase > 1);
				if(confirmPurchase == 1){
					system("cls");
					LineBreak();
					printf("\nCompra do ingresso foi realizado com sucesso\n");
					r[nR].session[nS].seat[RowToPos(row)][IntToPos(seat)] = true;
					r[nR].session[nS].availableTickets -= 1;
				}else{
					system("cls");
					LineBreak();
					printf("\nA compra do ingresso foi cancelada\n");
				}
				newSeat = 0;
			}else{
				do{
					printf("O ingresso da poltrona %c-%d ", row, seat);
					printf("j%c foi comprado, gostaria de ", (char)160);
					printf("escolher outra poltrona?\n");
					printf("[1]Sim [0]N%co\n", (char)198);
					fflush(stdin);
					scanf("%d", &newSeat);
				}while(newSeat < 0 || newSeat > 1);
			}
		}else{
			system("cls");
			LineBreak();
			printf("\nN%co foi poss%cvel concluir a compra do ingresso ", (char)198, (char)161);
			printf("dada a classifica%c%co indicativa\n", (char)135, (char)198);
			newSeat = 0;
		}
	}
	return;
}

/* Inicializa as salas de cinema e as classificações indicativas, DEPOIS -----*/
/* Permite executar compra, cancelamento e liberação das salas ---------------*/
int main (void){
	bool keepRunning = true;
	int nR, nS, nRS, choiceRS, option;
	
	Room r[nRooms];
	
	setlocale(LC_ALL,"C.UTF-8");
	
	for(int i = 0; i < nRooms; i++){
		for(int j = 0; j < nSessions; j++){
			ResetSession(r, i, j, false, true);
		}
	}
	
	system("cls");
	do{
		printf("\n");
		LineBreak();
		printf("%c", (char)201);
		for(int i = 0; i < 19; i++)
			printf("%c", (char)205);
		printf("%c\n", (char)187);
		printf("%c[1]Comprar ingresso%c\n", (char)186, (char)186);
		printf("%c[2]Cancelar compra %c\n", (char)186, (char)186);
		printf("%c[3]Resetar sala    %c\n", (char)186, (char)186);
		printf("%c[0]Sair            %c\n", (char)186, (char)186);
		printf("%c", (char)200);
		for(int i = 0; i < 19; i++)
			printf("%c", (char)205);
		printf("%c\nOp%c%co:", (char)188, (char)135, (char)198);
		fflush(stdin);
		scanf("%d", &option);
		
		switch(option){
			case 1:
				LineBreak();
				BuyTicket(r);
				break;
			case 2:
				CancelPurchase(r);
				break;
			case 3:
				system("cls");
				choiceRS = 1;
				for(int i = 0; i < nRooms; i++){
					for(int j = 0; j < nSessions; j++){
						printf("[%d] - ", choiceRS++);
						PrintSession(r, i, j, false);
					}
				}
				
				do{
					printf("Digite o n%cmero da sess%co a ser resetada:\n", (char)163, (char)198);
					fflush(stdin);
					scanf("%d", &nRS);
				}while((nRS < 1) || (nRS > (nRooms * nSessions)));
				
				choiceRS = 1;
				for (nR = 0; (nR < nRooms) && (choiceRS < nRS); nR++){
					for(nS = 0; (nS < nSessions) && (choiceRS < nRS); nS++){
						choiceRS++;
					}
				}
				
				system("cls");
				PrintSession(r, nR, nS, false);
				printf("[1]Liberar todos os assentos para compra\n");
				printf("[2]Trocar filme e classifica%c%co indicativa\n", (char)135, (char)198);
				printf("[0]Abortar cancelamento\n");
				fflush(stdin);
				scanf("%d", &option);
				
				if(option == 1){
					ResetSession(r, nR, nS, true, false);
					system("cls");
					LineBreak();
					printf("Assentos liberados para compra\n");
				}else if(option == 2){
					ResetSession(r, nR, nS, false, false);
				}else if(option == 0){
					system("cls");
					LineBreak();
					printf("Cancelamento abortado com sucesso\n");
				}
				break;
			case 0:
				keepRunning = false;
				system("cls");
				printf("%c", (char)201);
				for(int i = 0; i < 15; i++)
					printf("%c", (char)205);
				printf("%c\n", (char)187);
				printf("%cFim do programa%c\n", (char)186, (char)186);
				printf("%c", (char)200);
				for(int i = 0; i < 15; i++)
					printf("%c", (char)205);
				printf("%c", (char)188);
				break;
			default:
				system("cls");
				printf("%c", (char)201);
				for(int i = 0; i < 14; i++)
					printf("%c", (char)205);
				printf("%c\n", (char)187);
				printf("%c", (char)186);
				printf("Op%c%co inv%clida", (char)135, (char)198, (char)160);
				printf("%c\n", (char)186);
				printf("%c", (char)200);
				for(int i = 0; i < 14; i++)
					printf("%c", (char)205);
				printf("%c", (char)188);
				break;
		}
	}while(keepRunning);
	
	return 0;
}
