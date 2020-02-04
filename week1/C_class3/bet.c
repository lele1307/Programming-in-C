#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int start(void);

int main(void)
{
    /*variables*/
    int betmode;
    int straightbet, cashbet, choose;
    int number;
    int balance;
    
    /*title*/

    /*Game instruction*/
    printf("There are two types of bet you can make.\n");
    printf("① Straight bet - Please choose a single number from 0 to 35.(35 to 1)\n");
    printf("② Odd or Even bet - Pleas choose odd or even.(2 to 1)\n");


    balance = 10;
    while (balance > 0) {
        /*Select which mode you want to try*/
        printf("\nPlease select a game type you want to join:");
        scanf("%d",&betmode);
        switch (betmode)
        {
        case 1:
            printf("\nWhich number do you want to choose?");
            scanf("%d",&straightbet);
            printf("\nHow much money do you want to input? £");
            scanf("%d",&cashbet);
            printf("You will bet £%d on number %d.\n",cashbet,straightbet);
            start();
                if(number == straightbet){
                    balance += cashbet*35;
                    printf("You win!! And your balance is £%d.",balance);
                }else{
                    balance -= cashbet*35;
                    cashbet *=35;
                    printf("Sorry. You've lost £%d. Your new balance is £%d.", cashbet, balance);
                }
            break;
            
        case 2:
            printf("\nPlease enter 1 for odd or 2 for even. ");
            scanf("%d", &choose);
            if (choose == 1||choose == 2)
            {
                printf("\nHow much money are you willing to risk? £");
            scanf("%d", &cashbet);
                if (choose == 1)
                    printf("\nYou have bet £%d on odds.", cashbet);
                else
                    printf("\nYou have bet £%d on evens.", cashbet);
            start();
                if (choose == 1){
                    if (number%2 == 1){
                        balance += cashbet;
                        printf("Win! You have £%d in your pocket!", balance);
                    }else{
                        balance -= cashbet;
                        printf("Sorry. You've lost £%d. Your new balance is £%d.",cashbet, balance);
                    }
                }else{
                    if (number%2 == 0){
                        balance += cashbet;
                        printf("Win! You have £%d in your pocket!", balance);
                    }else{
                        balance -= cashbet;
                        printf("You've lost £%d. Your new balance is £%d.",cashbet, balance);
                    }
                }
            }else{
               printf("You choose wrong type number!!"); 
            }
            break;

        default:
            printf("Error! Option is not correct!");
        }
    }
    return 0;
}

int start(void){
    int number;
    srand((unsigned)time(NULL));
    number = rand()%36;
    printf("\nThe random number is %d.\n",number);
    return number;
}