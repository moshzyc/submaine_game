#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE_BOARD 25
#define MAX_SIZE_BOARD 50
#define RED "\033[0;41m"
#define GREEN "\033[0;42m"
#define YELLOW "\033[0;43m"
#define RESET "\033[0m"


void game();
void clear_screen();
void welcome_message();
void draw_board(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int size);
void draw_board_placing(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int size);
void draw_cells(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int size);
void draw_cells_placing(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int size);
void numbers(int lenght);
void place_submarines(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD] ,int siboard_sizeze, int player);
void place_instructions();
void target_submarine(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size, int *points_counter);
void game_rounds(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD],
                 char a2[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size);

int play_again();
int choose_board_size();
int Checking_the_place(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD],
                       int row, int col, int direcion, int size, int board_size);

int main()
{
    welcome_message();
    game();

	return 0;
}

void game()
{
    do {
    char board_pleyer1[MAX_SIZE_BOARD][MAX_SIZE_BOARD] = { 0 };
    char board_pleyer2[MAX_SIZE_BOARD][MAX_SIZE_BOARD] = { 0 };
    int board_size;
    board_size = choose_board_size();
    place_submarines(board_pleyer1, board_size, 1);
    place_submarines(board_pleyer2, board_size, 2);
    game_rounds(board_pleyer1, board_pleyer2, board_size);
    } while (play_again());
}

void clear_screen()
{
    printf("%47s", "Press Enter to continue...\n");
    getchar();
 #ifdef _WIN32
	system("cls");

 #else
	system("clear");
 #endif
}
void welcome_message()
{
    printf("--------------------------------------------------------------------------\n");
    printf("%47s", "Welcome to 'SUBMARINE GAME' \n");
    printf("this is a game for 2 pleyers to drawn the other player submarines!\n");
    printf("%52s", "the winner is the first one that drawn all the other player submarines \n");
    printf("--------------------------------------------------------------------------\n");
    printf("\n");
    clear_screen();
}
void draw_cells(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int size)
{
    int i;
    printf("%2d", row + 1);
    for (i = 0; i < size; i++)
    {
        if (a[row][i] == -1)
        {
            printf("|");
            printf(RED"XX"RESET);
        }
        else if (a[row][i] == -2)
        {
            printf("|");
            printf(YELLOW"00"RESET);
        }
        else
        printf("|  ");
    }
    printf("|");
    printf("\n");
}
void numbers(int lenght)
{
    int i;
    printf("  |");
    for (i = 0; i < lenght; i++)
        printf("%2d|",i+1);

    printf("\n");
}
void draw_board(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int size)
{
    int i;
    numbers(size);
    for (i=0;i<size;i++)
    {
        draw_cells(a, i, size);
    }
}
void draw_cells_placing(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int size)
{
    int i;
    printf("%2d", row+1);
    for (i = 0; i < size; i++)
    {
        if (a[row][i] == 1)
        {
            printf("|");
            printf(GREEN"**"RESET);
        }
        else
            printf("|  ");
    }
    printf("|");
    printf("\n");
}
void draw_board_placing(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int size)
{
    int i;
    numbers(size);
    for (i = 0; i < size; i++)
    {
        draw_cells_placing(a, i, size);
    }
}
int choose_board_size()
{
    int size;
    do
    {
        printf("pleas enter the size of the board (min %d, max %d):\n", MIN_SIZE_BOARD, MAX_SIZE_BOARD);
        scanf("%d", &size);
        if (size<MIN_SIZE_BOARD || size > MAX_SIZE_BOARD)
            printf("invalid value, pleas enter agein\n");
    } while (size<MIN_SIZE_BOARD || size > MAX_SIZE_BOARD);
    getchar();
    clear_screen(); 
    return size;
}
void place_instructions()
{
    printf("entering submarine in this formar: x x (like 28 4)\n");
    printf("when the firs number is the row and the scond is the square in the row\n");
    printf("the location is the submarine head, if you place it horizontally it will place to the right\n");
    printf("if you place it vertically it will place towards down\n");
    printf("\n");
}
int Checking_the_place(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD],
    int row, int col, int direction, int size, int board_size)
{
    int i, j, newRow, newCol, right = 1, down = 1;

    
    if (direction == 2) { 
        if (col + size - 1 >= board_size)
            return 1; 
        right = size;
    }
    else { 
        if (row + size - 1 >= board_size)
            return 1;
        down = size;
    }

    for (i = -1; i <= down; i++) {
        for (j = -1; j <= right; j++) {
            newRow = row + i;
            newCol = col + j;

            if (newRow >= 0 && newRow < board_size && newCol >= 0 && newCol < board_size) {
                if (a[newRow][newCol])
                    return 1;
            }
        }
    }

    return 0;
}
void place_submarines(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size, int player)
{
    printf("Player %d pleas place your submarinse", player);

    int i, j, row, col, direcion=1, size, see;
    for (size = 1; size <= 5; size++)
    {
        place_instructions();
        see = 0;
        do {

            printf("if you want to see the board enter 1, else enter 2:\n");
            scanf("%d", &see);
        } while (see != 1 && see != 2);
        if (see == 1)
            draw_board_placing(a, board_size);

        for (i = 0; i <=5-size; i++)
        {
            do
            {
            printf("pleas place %d square submarine number %d (you have more %d to place):\n", size, i + 1, 6 - size - i);
                scanf("%d%d", &row, &col);
                if (size > 1)
                {
                    direcion = 0;
                    do
                    {
                        printf("pleas choose the submarine direcion, if down enter '1' if right '2':\n");
                        scanf("%d", &direcion);

                    } while (direcion != 1 && direcion != 2);
                }
                if (row > board_size || col > board_size || row < 1 || col < 1 ||
                    Checking_the_place(a, row - 1, col - 1,
                        direcion, size, board_size))
                {
                    printf("invalid place, pleas enter agein\n");
                }
            } while (row > board_size || col > board_size || row < 1 || col < 1 ||
                Checking_the_place(a, row - 1, col - 1,
                    direcion, size, board_size));
            if (direcion == 2)
                for (j = 0; j < size; j++)
                    a[row - 1][col + j - 1] = 1;
            else
                for (j = 0; j < size; j++)
                    a[row + j - 1][col - 1] = 1;
        }
        getchar();
        clear_screen();
    }
}
void target_submarine(char a[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size, int* points_counter)
{
    int see;
    do {

        printf("if you want to see the impact board enter 1, else enter 2:\n");
        scanf("%d", &see);
    } while (see != 1 && see != 2);
    if (see == 1)
        draw_board(a, board_size);
    int row, col;

    do {
        printf("pleas choose where to where to hit: row&square in x x formt (like 4 7)\n");
        scanf("%d%d", &row, &col);
    } while (row - 1 < 0 || row - 1 > board_size || col - 1 < 0 || col - 1 > board_size ||
            a[row - 1][col - 1] == -1 || a[row - 1][col - 1] == -2);

    if (a[row - 1][col - 1] == 1)
    {
        a[row - 1][col - 1] = -1;
        (*points_counter)++;
        printf("you hit a submarine\n");
    }
    else
    {
        a[row - 1][col - 1] = -2;
        printf("you miss\n");
    }
    if (row - 1 < 0 || row - 1 > board_size || col - 1 < 0 || col - 1 > board_size)
        printf("invalid place, pleas enter agein\n");


    draw_board(a, board_size);
    getchar();
    clear_screen();
}
void game_rounds(char a1[MAX_SIZE_BOARD][MAX_SIZE_BOARD],
                 char a2[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size)
{
    int player1_score = 0, player2_score = 0;
    do
    {
        printf("player 1 turn:\n");
        target_submarine(a2, board_size, &player1_score);

        if (player1_score < 35)
        {
            printf("player 2 turn:\n");
            target_submarine(a1, board_size, &player2_score);
        }
    } while (player1_score < 35 && player2_score < 35);
    if (player1_score == 35)
        printf("player 1 won!!!\n");
    else
        printf("player 2 won!!!\n");
}
int play_again()
{
    int restart;
    printf("to end enter 0 to new game enter other namber:\n");
    scanf("%d", &restart);
    if (restart)
        clear_screen();
    return restart;
}