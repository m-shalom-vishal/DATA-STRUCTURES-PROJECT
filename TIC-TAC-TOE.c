#include <stdio.h>

#define SIZE 3

// Define a structure to represent the game state
typedef struct {
    char board[SIZE][SIZE];
    char current_player;
    int moves;
} Game;

// Function to initialize the game state
void init_game(Game *game) {
    // Initialize the board with numbers 1 to 9
    char num = '1';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            game->board[i][j] = num++;
        }
    }
    game->current_player = 'X'; // Player X starts
    game->moves = 0;
}

// Function to print the board
void print_board(Game *game) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", game->board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

// Function to check if the current player wins
int check_winner(Game *game) {
    for (int i = 0; i < SIZE; i++) {
        // Check rows and columns
        if ((game->board[i][0] == game->board[i][1] && game->board[i][1] == game->board[i][2]) ||
            (game->board[0][i] == game->board[1][i] && game->board[1][i] == game->board[2][i])) {
            return 1;
        }
    }
    // Check diagonals
    if ((game->board[0][0] == game->board[1][1] && game->board[1][1] == game->board[2][2]) ||
        (game->board[0][2] == game->board[1][1] && game->board[1][1] == game->board[2][0])) {
        return 1;
    }
    return 0;
}

// Function to check if the board is full (draw)
int is_draw(Game *game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->board[i][j] >= '1' && game->board[i][j] <= '9') {
                return 0; // Still empty spots
            }
        }
    }
    return 1; // No empty spots, it's a draw
}

// Function to process a move
int make_move(Game *game, int position) {
    int row = (position - 1) / SIZE;
    int col = (position - 1) % SIZE;

    if (position < 1 || position > 9 || game->board[row][col] == 'X' || game->board[row][col] == 'O') {
        return 0; // Invalid move
    }
    
    game->board[row][col] = game->current_player;
    return 1; // Valid move
}

// Main game loop
int main() {
    Game game;
    int position;

    // Initialize the game
    init_game(&game);

    printf("Tic Tac Toe Game\n");
    print_board(&game);

    while (1) {
        printf("Player %c, enter your move (1-9): ", game.current_player);
        scanf("%d", &position);

        if (!make_move(&game, position)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        print_board(&game);
        game.moves++;

        if (check_winner(&game)) {
            printf("Player %c wins!\n", game.current_player);
            break;
        }

        if (is_draw(&game)) {
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        game.current_player = (game.current_player == 'X') ? 'O' : 'X';
    }

    return 0;
}
