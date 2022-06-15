#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//some constant definitions to use throughout all code
#define ROUND_NUMBER 7
#define ROW 7
#define COLUMN 6

//all function prototypes
int rollDice();
void displayBoard(char[ROW][COLUMN],int,int);
void placeCompToken(char[ROW][COLUMN], int, int, int);
void placeUserToken(char[ROW][COLUMN], int, int, int);
void checkMatch(char [ROW][COLUMN], int, int, int, int []);
void winner(int [], int);

int main()
{
    srand(time(NULL));

    char option;//to ask user if one want to play again or not
    char board[ROW][COLUMN];//7x6 play board
    int score[2] = {0,0};//to store scores of user and computer
    int turnDicePlayer, turnDiceComp;//dices to select starter
    int roundCount;//after game started, it counts round number until 7
    int rowReset = 0, columnReset = 0;//to clear all coordinates after created board
    int rowFilledCount;//each row has 6 space so program needs to ask 3 times to user coordinate, this counts until 3

    printf("Welcome to the PopThree :)\n");
    printf("Let's get started!\n");
    printf("\n-----------------------------------------------\n");

    do
    {

        for(rowReset = 0; rowReset < ROW; rowReset++)//to initialize board clearly
        {
            for(columnReset = 0; columnReset < COLUMN; columnReset++)
            {
                board[rowReset][columnReset] = ' ';//each space of board is cleaning
            }
        }

        //dices are rolled
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

        printf("\nBoard:\n");
        displayBoard(board,ROW,COLUMN);//it shows empty board

        if(turnDiceComp > turnDicePlayer)//computer dice is bigger than user, so computer starts firstly
        {
            for(roundCount = 1; roundCount <= ROUND_NUMBER; roundCount++)//to count all rounds until 7 because board has 7 rows
            {
                printf("\n------------------Round %d----------------------\n", roundCount);

                for(rowFilledCount = 0; rowFilledCount < COLUMN/2; rowFilledCount++)//it runs until a row is filled
                {
                    placeCompToken(board,ROW,COLUMN,roundCount);//computer places token
                    placeUserToken(board,ROW,COLUMN,roundCount);//user places token
                    displayBoard(board,ROW,COLUMN);//to show board
                }
                checkMatch(board,ROW,COLUMN,roundCount,score);//after one round is finished, it checks scores
            }
            winner(score,roundCount);//to print who did win
        }
        else//same things with inside of 'if', a difference is that user starts firstly here
        {
            for(roundCount = 1; roundCount <= ROUND_NUMBER; roundCount++)
            {
                printf("\n------------------Round %d----------------------\n", roundCount);

                for(rowFilledCount = 0; rowFilledCount < COLUMN/2; rowFilledCount++)
                {
                    placeUserToken(board,ROW,COLUMN,roundCount);
                    placeCompToken(board,ROW,COLUMN,roundCount);
                    displayBoard(board,ROW,COLUMN);
                }
                checkMatch(board,ROW,COLUMN,roundCount,score);
            }
            winner(score,roundCount);
        }

        printf("\nWould you like to play again (Y/N)? ");
        fflush(stdin);
        scanf("%c", &option);
        score[0] = 0;score[1] = 0;//these resets scores for next playing

    }while(option == 'Y');

    return 0;
}

int rollDice()
{
    return 1+(int)rand()%6;//rolls dice
}

void displayBoard(char board[ROW][COLUMN], int row, int column)
{
    int rowCount = 0, columnCount = 0;

    printf("\n");
    for(rowCount = 0; rowCount <= row; rowCount++)//each row is displayed with this 'for'
    {
        for(columnCount = 0; columnCount <= column; columnCount++)//each column is displayed with this 'for'
        {
            if(rowCount == 0 && columnCount == 0)
                printf("  ");//the most left and top is a gap
            else if(rowCount == 0)
                printf("%d ", columnCount);//top numbers(1 2 3 4 5 6)
            else if(columnCount == 0)
                printf("\n%d ",rowCount);//left numbers(\n1\n2\n3\n4\n5\n6\n7)
            else
                printf("%c ", board[rowCount-1][columnCount-1]);//it is actual board on which game is played
                /*there are (-1)s because values of count variables starts from 1 and can reach 8, so it means outside of board.
                To prevent that, there are (-1)s.*/
        }

    }
    printf("\n\n");
}

void placeCompToken(char board[ROW][COLUMN], int row, int column, int roundNumber)
{
    int currenRow = -1*(roundNumber-7);/*each round, program needs to use only one row. For example, first round,
    program needs to use row 7(actually it is 6 in terms of arrays). this variable gives row program needs according to round number*/
    int currentColumn;//it is created to store empty place
    int count;

    for(count = 0; count < column; count++)//this 'for' scans row, and when it find, it stores this column value in currenColumn
    {
        if(board[currenRow][count] == ' ')
        {
            currentColumn = count;
            break;
        }
    }

    board[currenRow][currentColumn] = '*';//computer places token first empty place

    printf("My turn -> I placed token to location (%d,%d)\n", currenRow+1, currentColumn+1);

}

void placeUserToken(char board[ROW][COLUMN], int row, int column, int roundNumber)
{
    int currentRow = -1*(roundNumber-7)+1;/*this variable is like currentRow in placeCompToken function. There is +1 because
    users write their coordinates by starting 1 not 0*/
    int inpRow,inpColumn;//to take input from user
    int isValid;//if all needs are correct it stores 1

    do
    {
        printf("Your turn -> Enter location to place your token: ");
        fflush(stdin);
        scanf("(%d,%d)",&inpRow,&inpColumn);

        if((inpRow < 1 || inpRow > row) ||
           (inpColumn < 1 || inpColumn > column))//to check whether input is in board or not
        {
            printf("You cannot place a token outside the board!\n");
            isValid = 0;
        }
        else if(inpRow != currentRow)//to check whether input is in correct row or not
        {
            printf("At this turn you can only place token to row %d!\n", currentRow);
            isValid = 0;
        }
        else if(board[inpRow-1][inpColumn-1] != ' ')//to check whether selected coordinate is empty or not
        {
            printf("A token is already placed there!\n");
            isValid = 0;
        }
        else
        {
            isValid = 1;//if all things are correct, it can be placed
        }

    }while(!isValid);

    board[inpRow-1][inpColumn-1] = '+';
}

void checkMatch(char board[ROW][COLUMN], int row, int column, int roundNumber, int scores[])
{
    int currentRow = -1*(roundNumber-7);//it is like currentRow in placeCompToken function.
    int rowCount;

    for(rowCount = 0; rowCount < column-2; rowCount++)//this 'for' checks if there is valid token order or not
    {
        //if program checks current column and columns that are at right according to current column(two of them), it will be enough to add score
        if(board[currentRow][rowCount] == board[currentRow][rowCount+1] &&
           board[currentRow][rowCount] == board[currentRow][rowCount+2])
        {
            if(board[currentRow][rowCount] == '*')
                scores[0]++;
            else
                scores[1]++;
        }
    }

    printf("Scores [My Yours]: [%d %d]\n", scores[0],scores[1]);
}

void winner(int scores[], int round)//after all game finished, to write who did win
{
        if(scores[0] > scores[1])
            printf("\nI won!!!");
        else if(scores[0] < scores[1])
            printf("\nYou won!!!");
        else
            printf("\nEven!");

        printf("\n------------------End----------------------\n");
}
