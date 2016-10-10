/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// position struct
struct position
{
    int x;
    int y;
};

struct position emptyPosition;
struct position tilePosition;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
void swap(int * a, int * b);
bool won(void);
bool findTile(int n);
bool isEmptyNeighbor(void);
void updateEmptyPosition(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    
    bool even;
    // check if number of tiles is odd or even
    if ((d * d) % 2 == 0)
    {
        even = true;
    }
    else
    {
        even = false;
    }
    
    // init board in reverse
    int count = 0;
    // set indices for empty tile
    emptyPosition.x = d - 1, emptyPosition.y = d - 1;
   
   // initialize board
    for (int i = d - 1; i >= 0 ; i--)
    {
        for (int j = d - 1; j >= 0; j--)
        {
            board[i][j] = count;
            count++;
        }
    }
    
    // if even number of tiles, swap last two tiles
    if (even)
    {
        swap(&board[d - 1][d - 2], &board[d - 1][d - 3]);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // print underscore for 0
            if (board[i][j] == 0)
            {
                printf("%5s","_");
            }
            else
            {
                printf("%5d", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // find tile and swap if it borders empty spot
    if (findTile(tile))
    {
        if (isEmptyNeighbor())
        {
            swap(&board[tilePosition.x][tilePosition.y],
                 &board[emptyPosition.x][emptyPosition.y]);
            
            updateEmptyPosition();
            return true;
        }
        // still have to update position empty tile
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    if (board[d - 1][d - 1] != 0)
    {
        return false;
    }
    
    int check = 1;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i * j == (d - 1) * (d - 1))
            {
                break;
            }
            else if (board[i][j] != check)
            {
                return false;
            }
            check++;
        }
    }
    return true;
}

/**
 * Function takes two pointers and swaps the values 
 * of these variables
 */
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Function searches for tile and returns true if found;
 * else false is returned
 */
bool findTile(int n)
{
    // exit function when n exceeds max value of tiles
    if (n > d * d - 1)
    {
        return false;
    }
    
    // search for tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == n)
            {
                tilePosition.x = i, tilePosition.y = j;
                return true;
            }
        }
    }
    
    return false;
}

/**
 * function checks if tile borders an empty spot;
 * if so function returns true, else false
 */
bool isEmptyNeighbor(void)
{
    // define 4 neighbors
    const int neighbor[4][2] = {
                                    {-1, 0 },
                                    { 1, 0 },
                                    { 0, -1},
                                    { 0, 1 }
        
                                };
    // check neighbors around tile
    // return true if bordering empty tile
    for (int i = 0; i < 4; i++)
    {
        if ((tilePosition.x + neighbor[i][0] == emptyPosition.x) && (tilePosition.y + neighbor[i][1] == emptyPosition.y))
        {
            return true;
        }
    }
    
    return false;
}

/**
 * Function updates the position of the empty spot
 * (function should only be called if move is valid)
 */
void updateEmptyPosition(void)
{
    emptyPosition.x = tilePosition.x;
    emptyPosition.y = tilePosition.y;
}