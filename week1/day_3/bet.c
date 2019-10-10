#include <stdio.h>
#include <stdlib.h>

int spin_roulette(void);

int main(void)
{
    //variables
    int betmode;
    int straightbet, cashbet, choose;
    int number;
    int balance;
    
    //title

    //Game instruction
    printf("There are two types of bet you can make.\n");
    printf("① Straight bet - Please choose a single number from 0 to 35.(35 to 1)\n");
    printf("② Odd or Even bet - Pleas choose odd or even.(2 to 1)\n");

    //Select which mode you want to try
    printf("\nPlease select a game type you want to join:");
    scanf("%d",&betmode);
    balance = 100;
    while (balance > 0) {
        if(betmode == 1){
            printf("Which number do you want to choose?");
            scanf("%d",&straightbet);
            printf("\nHow much money do you want to input?");
            scanf("%d",&cashbet);
            printf("You will bet %d on number %d.",cashbet,straightbet);
            start();
            if(number == straightbet){
                balance += cashbet*35;
                printf("You win!! And your balance is %d",balance);
            }else{
                balance -= cashbet*35;
                printf("Sorry. You've lost $%d. Your new balance is $%d", cashbet, balance);
            }
        }else if(betmode == 2){
            printf("Please enter 1 for odd or 2 for even. ");
            scanf("%d", &choose);
            printf("\nHow much money are you willing to risk? Payout is 1 to 1> ");
            scanf("%d", &cashbet);
                if (choose == 1)
                    printf("\nYou have bet $%d on odds", cashbet);
                else
                    printf("\nYou have bet $%d on evens", cashbet);
            start();
                if (choose == 1){
                    if (number%2==1){
                        balance += cashbet;
                        printf("Win! You have %d in your pocket", balance);
                    }else{
                        balance -= cashbet;
                        printf("Sorry. You've lost %d. Your new balance is %d",cashbet, balance);
                    }
                }else{
                    if (number%2==0){
                        balance += cashbet;
                        printf("Win! You have %d in your pocket", balance);
                    }else{
                        balance -= cashbet;
                        printf("You've lost %d. Your new balance is %d",cashbet, balance);
                    }
                }
        }
    }
    return 0;
}

int start(void){
    int number;
    srand((unsigned)time(NULL));
    number = random()%36;
    printf("The random number is %d\n.",number);
    return number;
}