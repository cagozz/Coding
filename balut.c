#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LF 10

int rollDice(void);
int playComputer(int);
int playUser(int);
void scoreSheet(int, int, int);

int main()
{
    srand(time(NULL));

    int roundNum,currentRound=1;
    int turnDiceComp, turnDicePlayer;
    int pScore = 0, cScore = 0;

    printf("Welcome to the Balut game.\nLets get started!\n");

    printf("\nHow many rounds would you like to play? ");
    scanf("%d", &roundNum);

    turnDiceComp = rollDice();
    turnDicePlayer = rollDice();

    printf("\nI have rolled the dice and got %d\n", turnDiceComp);
    printf("I have rolled the dice for you and you got %d\n", turnDicePlayer);

    while(turnDiceComp == turnDicePlayer)//It runs until decide who will start if dices come same
    {
        printf("\nDices are same!\nRe-rolling!\n");
        turnDiceComp = rollDice();
        turnDicePlayer = rollDice();

        printf("I have rolled the dice and got %d\n", turnDiceComp);
        printf("I have rolled the dice for you and you got %d\n", turnDicePlayer);
    }

    if(turnDiceComp>turnDicePlayer)//if dice of computer is bigger than player's one, computer starts game firstly
    {
        while(currentRound<=roundNum)
        {
            cScore += playComputer(currentRound);//playComputer function returns score of computer, so it runs and after that this return value is added to cScore for each round
            pScore += playUser(currentRound);//playUser function returns score of player, so it runs and after that this return value is added to pScore for each round

            scoreSheet(pScore,cScore,currentRound);//scoreSheet function takes score data and show these data as output

            currentRound++;//currentRound variable stores number of Nth round
        }
    }
    else//all things are same with if statement
    {
        while(currentRound<=roundNum)
        {
            pScore += playUser(currentRound);
            cScore += playComputer(currentRound);

            scoreSheet(pScore,cScore,currentRound);

            currentRound++;
        }
    }

    //According to last scores, winner is shown by this if-else chain
    if(cScore>pScore)
    {
        printf("\nI AM THE WINNER!\n");
    }
    else if(pScore > cScore)
    {
        printf("\nYOU ARE THE WINNER!\n");
    }
    else
    {
        printf("\nWE ARE EVEN!\n");
    }

    return 0;
}

int rollDice(void)
{
    return 1+rand()%6;//it gives random number between 1-6
}

int playComputer(int round)
{
    int score = 0;//it stores score of computer for each round
    int firstDice, secondDice, thirdDice, fourthDice, fifthDice;//these variables represent each dice

    printf("\nRound %d -- My Turn:\n", round);
    printf("=========================================================================\n");

    //dices are rolled
    firstDice = rollDice();
    secondDice = rollDice();
    thirdDice = rollDice();
    fourthDice = rollDice();
    fifthDice = rollDice();

    printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

    if(firstDice == secondDice &&
       firstDice == thirdDice &&
       firstDice == fourthDice &&
       firstDice == fifthDice)
    {
        score = firstDice*5+20;//if all dices are same, this means that it is balut
    }
    else if(firstDice == 1 &&
             secondDice == 2 &&
             thirdDice == 3 &&
             fourthDice == 4 &&
             fifthDice == 5)
    {
        score += 15;//if dices are 1 2 3 4 5 with order, it is small straigth
    }
    else if(firstDice == 2 &&
             secondDice == 3 &&
             thirdDice == 4 &&
             fourthDice == 5 &&
             fifthDice == 6)
    {
        score += 20;//if dices are 2 3 4 5 6 with order, it is large straigth
    }
    //after this part, program controls each dice. If it is close to one of the straights, it rolls one of dices again
    else if(firstDice != 2 &&
             secondDice == 3 &&
             thirdDice == 4 &&
             fourthDice == 5 &&
             fifthDice == 6)
    {
        firstDice = rollDice();

        printf("Rolled Dice 1...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(firstDice == 2)
        {
            printf("Lucky me!\n");
            score += 20;
        }
        else
        {
            if(firstDice == 5 || firstDice == 6)
            {
                score += firstDice + 11;
            }
            else
            {
                score += 11;
            }
        }
    }
    else if(firstDice == 2 &&
             secondDice != 3 &&
             thirdDice == 4 &&
             fourthDice == 5 &&
             fifthDice == 6)
    {
        secondDice = rollDice();

        printf("Rolled Dice 2...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(secondDice == 3)
        {
            printf("Lucky me!\n");
            score += 20;
        }
        else
        {
            if(secondDice == 5 || secondDice == 6)
            {
                score += secondDice + 11;
            }
            else
            {
                score += 11;
            }
        }
    }
    else if(firstDice == 2 &&
             secondDice == 3 &&
             thirdDice != 4 &&
             fourthDice == 5 &&
             fifthDice == 6)
    {
        thirdDice = rollDice();

        printf("Rolled Dice 3...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(thirdDice == 4)
        {
            printf("Lucky me!\n");
            score += 20;
        }
        else
        {
            if(thirdDice == 5 || thirdDice == 6)
            {
                score += thirdDice + 11;
            }
            else
            {
                score += 11;
            }
        }
    }
    else if(firstDice == 2 &&
             secondDice == 3 &&
             thirdDice == 4 &&
             fourthDice != 5 &&
             fifthDice == 6)
    {
        fourthDice = rollDice();

        printf("Rolled Dice 4...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(fourthDice == 5)
        {
            printf("Lucky me!\n");
            score += 20;
        }
        else
        {
            if(fourthDice == 6)
            {
                score += 12;
            }
            else
            {
                score += 6;
            }
        }
    }
    else if(firstDice == 2 &&
             secondDice == 3 &&
             thirdDice == 4 &&
             fourthDice == 5 &&
             fifthDice != 6)
    {
        fifthDice = rollDice();

        printf("Rolled Dice 5...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(fifthDice == 6)
        {
            printf("Lucky me!\n");
            score += 20;
        }
        else
        {
            if(fifthDice == 5)
            {
                score += 10;
            }
            else
            {
                score += 5;
            }
        }
    }
    else if(firstDice != 1 &&
             secondDice == 2 &&
             thirdDice == 3 &&
             fourthDice == 4 &&
             fifthDice == 5)
    {
        firstDice = rollDice();

        printf("Rolled Dice 1...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(firstDice == 1)
        {
            printf("Lucky me!\n");
            score += 15;
        }
        else
        {
            if(firstDice == 5 || firstDice == 6)
            {
                score += firstDice + 5;
            }
            else
            {
                score += 5;
            }
        }
    }
    else if(firstDice == 1 &&
             secondDice != 2 &&
             thirdDice == 3 &&
             fourthDice == 4 &&
             fifthDice == 5)
    {
        secondDice = rollDice();

        printf("Rolled Dice 2...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(secondDice == 2)
        {
            printf("Lucky me!\n");
            score += 15;
        }
        else
        {
            if(secondDice == 5 || secondDice == 6)
            {
                score += secondDice + 5;
            }
            else
            {
                score += 5;
            }
        }
    }
    else if(firstDice == 1 &&
             secondDice == 2 &&
             thirdDice != 3 &&
             fourthDice == 4 &&
             fifthDice == 5)
    {
        thirdDice = rollDice();

        printf("Rolled Dice 3...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(thirdDice == 3)
        {
            printf("Lucky me!\n");
            score += 15;
        }
        else
        {
            if(thirdDice == 5 || thirdDice == 6)
            {
                score += thirdDice + 5;
            }
            else
            {
                score += 5;
            }
        }
    }
    else if(firstDice == 1 &&
             secondDice == 2 &&
             thirdDice == 3 &&
             fourthDice != 4 &&
             fifthDice == 5)
    {
        fourthDice = rollDice();

        printf("Rolled Dice 4...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(fourthDice == 4)
        {
            printf("Lucky me!\n");
            score += 15;
        }
        else
        {
            if(fourthDice == 5 || fourthDice == 6)
            {
                score += fourthDice + 5;
            }
            else
            {
                score += 5;
            }
        }
    }
    else if(firstDice == 1 &&
             secondDice == 2 &&
             thirdDice == 3 &&
             fourthDice == 4 &&
             fifthDice != 5)
    {
        fifthDice = rollDice();


        printf("Rolled Dice 5...\n");
        printf("I got -> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d\n", firstDice, secondDice, thirdDice, fourthDice, fifthDice);

        if(fifthDice == 5)
        {
            printf("Lucky me!\n");
            score += 15;
        }
        else
        {
            if(fifthDice == 6)
            {
                score += 6;
            }
            else
            {
                score += 0;
            }
        }
    }
    else
    {
        //if any special case is not satisfy, fives and sixes are counted
        if(firstDice == 5 || firstDice == 6)
        {
            score += firstDice;
        }
        if(secondDice == 5 || secondDice == 6)
        {
            score += secondDice;
        }
        if(thirdDice == 5 || thirdDice == 6)
        {
            score += thirdDice;
        }
        if(fourthDice == 5 || fourthDice == 6)
        {
            score += fourthDice;
        }
        if(fifthDice == 5 || fifthDice == 6)
        {
            score += fifthDice;
        }
    }

    printf("My score: %d\n", score);

    return score;
}

int playUser(int round)
{

    char control;//to take input
    int count = 1;//to take input
    int score = 0;//stores last score for each round
    int isRepeat = 0;//if player press enter without writing any value to take some dices, dices will be rolled again. To check that, this variable is created
    int rollCount = 0;//to control most three times roll
    int firstDice, secondDice, thirdDice, fourthDice, fifthDice;//to store values of dices
    int firstStore = 0,secondStore = 0,thirdStore = 0,fourthStore = 0,fifthStore = 0;//to take input
    int isFirstSelected = 0, isSecondSelected = 0, isThirdSelected = 0, isFourthSelected = 0, isFiftthSelected = 0;//if some dices are selected by player, these variables store 1

    printf("\nRound %d -- Your Turn:\n", round);
    printf("=========================================================================\n");
    printf("Are you ready to play!\n");

    while(rollCount<3)//to control round number
    {
        if(firstStore == 0 &&
           secondStore == 0 &&
           thirdStore == 0 &&
           fourthStore == 0 &&
           fifthStore == 0)
        {
            printf("I rolled them for you and you got\n-> ");
        }

        if(!rollCount || isRepeat)//If dices are rolled first time OR after dices are rolled first time but nothing is selected, all dices are rolled again
        {
            firstDice = rollDice();
            secondDice = rollDice();
            thirdDice = rollDice();
            fourthDice = rollDice();
            fifthDice = rollDice();
            rollCount++;//counting total rolling
            isRepeat = 0;
            printf("[Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d", firstDice, secondDice, thirdDice, fourthDice, fifthDice);
        }

        printf("\nWhich ones you want to keep? ");

        fflush(stdin);
        control = 0;
        while(control != LF)//to take input with spaces
        {
            scanf("%c", &control);

            if(count == 1 && control != LF)
                firstStore = control;
            else if(count == 3 && control != LF)
                secondStore = control;
            else if(count == 5 && control != LF)
                thirdStore = control;
            else if(count == 7 && control != LF)
                fourthStore = control;
            else if(count == 9 && control != LF)
                fifthStore = control;
            count++;
        }
        count = 1;

        if(firstStore!=0&&secondStore!=0&&thirdStore!=0&&fourthStore!=0&&fifthStore!=0)//If all dices are selected, dices are controlled to provide any special situation or not
        {
            if(firstDice == secondDice &&
               firstDice == thirdDice &&
               firstDice == fourthDice &&
               firstDice == fifthDice)
            {
                score = firstDice*5+20;
            }
            else if(firstDice == 1 &&
                     secondDice == 2 &&
                     thirdDice == 3 &&
                     fourthDice == 4 &&
                     fifthDice == 5)
            {
                score += 15;
            }
            else if(firstDice == 2 &&
                     secondDice == 3 &&
                     thirdDice == 4 &&
                     fourthDice == 5 &&
                     fifthDice == 6)
            {
                score += 20;
            }
            else//If there is not any special situation, all dices are controlled in terms of fives and sixes
            {
                if(firstDice == 5 || firstDice == 6)
                {
                    score += firstDice;
                }
                if(secondDice == 5 || secondDice == 6)
                {
                    score += secondDice;
                }
                if(thirdDice == 5 || thirdDice == 6)
                {
                    score += thirdDice;
                }
                if(fourthDice == 5 || fourthDice == 6)
                {
                    score += fourthDice;
                }
                if(fifthDice == 5 || fifthDice == 6)
                {
                    score += fifthDice;
                }
            }
            break;
        }
        if(firstStore==0&&secondStore==0&&thirdStore==0&&fourthStore==0&&fifthStore==0)//If no dice is selected, dices are rolled again
        {
            if(rollCount == 1)
            {
                isRepeat = 1;
                continue;
            }
        }

        //If any input value is 1 and firstDice is not selected before, it is checked. For all input values, they are checked with this if statemnts
        if((firstStore == '1' ||
           secondStore == '1' ||
           thirdStore == '1' ||
           fourthStore == '1') &&
           !isFirstSelected)
        {
            if((firstDice == 5 || firstDice == 6))
            {
                score += firstDice;
            }
            isFirstSelected = 1;
        }

        if(!isFirstSelected)//If firstDice is not selected, dice 1 is written to screen again. All dices are controlled with this type of IFs
        {
            firstDice = rollDice();
            printf("I rolled the remaining and you got\n-> ");
            printf("[Dice 1]: %d ", firstDice);
        }

        if((firstStore == '2' ||
           secondStore == '2' ||
           thirdStore == '2' ||
           fourthStore == '2') &&
           !isSecondSelected)
        {
            if(secondDice == 5 || secondDice == 6)
            {
                score += secondDice;
            }
            isSecondSelected = 1;
        }

        if(!isSecondSelected)
        {
            secondDice = rollDice();
            if(isFirstSelected)
                printf("I rolled the remaining and you got\n-> ");
            printf("[Dice 2]: %d ", secondDice);
        }

        if((firstStore == '3' ||
           secondStore == '3' ||
           thirdStore == '3' ||
           fourthStore == '3') &&
           !isThirdSelected)
        {
            if(thirdDice == 5 || thirdDice == 6)
            {
                score += thirdDice;
            }
            isThirdSelected = 1;
        }

        if(!isThirdSelected)
        {
            thirdDice = rollDice();
            if(isFirstSelected && isSecondSelected)
                printf("I rolled the remaining and you got\n-> ");
            printf("[Dice 3]: %d ", thirdDice);
        }

        if((firstStore == '4' ||
           secondStore == '4' ||
           thirdStore == '4' ||
           fourthStore == '4') &&
           !isFourthSelected)
        {
            if(fourthDice == 5 || fourthDice == 6)
            {
                score += fourthDice;
            }
            isFourthSelected = 1;
        }

        if(!isFourthSelected)
        {
            fourthDice = rollDice();
            if(isFirstSelected && isSecondSelected && isThirdSelected)
                printf("I rolled the remaining and you got\n-> ");
            printf("[Dice 4]: %d ", fourthDice);
        }

        if((firstStore == '5' ||
           secondStore == '5' ||
           thirdStore == '5' ||
           fourthStore == '5') &&
           !isFiftthSelected)
        {
            if(fifthDice == 5 || fifthDice == 6)
            {
                score += fifthDice;
            }
            isFiftthSelected = 1;
        }

        if(!isFiftthSelected)
        {
            fifthDice = rollDice();
            if(isFirstSelected && isSecondSelected && isThirdSelected && isFourthSelected)
                printf("I rolled the remaining and you got\n-> ");
            printf("[Dice 5]: %d ", fifthDice);
        }

        rollCount++;

        if(rollCount == 3)
        {
            if(!isFirstSelected)
            {
                if(firstDice == 5 || firstDice == 6)
                {
                    score += firstDice;
                }
            }

            if(!isSecondSelected)
            {
                if(secondDice == 5 || secondDice == 6)
                {
                    score += secondDice;
                }
            }

            if(!isThirdSelected)
            {
                if(thirdDice == 5 || thirdDice == 6)
                {
                    score += thirdDice;
                }
            }

            if(!isFourthSelected)
            {
                if(fourthDice == 5 || fourthDice == 6)
                {
                    score += fourthDice;
                }
            }

            if(!isFiftthSelected)
            {
                if(fifthDice == 5 || fifthDice == 6)
                {
                    score += fifthDice;
                }
            }
        }
    }
    printf("\nYour Score: %d\n", score);
    return score;
}

void scoreSheet(int playerScore, int computerScore, int round)
{
    printf("\nOur scoreSheet after round %d\n", round);
    printf("=============================\n\n");
    printf("My score\tYour score\n");
    printf("%d\t\t%d\n", computerScore, playerScore);
}
