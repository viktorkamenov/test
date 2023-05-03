// DOCUMENTATION
// Program for solving maze
// How the program "MAZE SOLVER" works:
// Step 1: Enter the maze.
// Step 2: Validation.
// Step 2.1: Check if entered number of elements in the maze is equal to the predefined number of elements in the maze.
// Step 2.2: Check if the maze has only 1 start and 1 end. Find the coordinates of the start and the end.
//           Set current position on the start.
// (*optional) Step 2.3: Show on the screen all the information about the maze.
// Step 3: Try solve the maze
// Step 3.1: Check if the current position in the maze is on start then if it is possible to move from there.
//           If it's not possible then show on the screen that the maze can't be solved.
// Step 3.2: Check if current position is 1 step from the end in any direction. If it's true show on the screen the map of the maze.
// Step 3.3: If there isn't free positions in all directions, set current as visited and go back with 1 step.
// Step 3.4: Repeat Step 3.1 only once.
// Step 4: Go back to Step 3 and continue from there again.

/* Including standard libraries such as stdio.h, ctype.h, stdlib.h,
and windows.h. The pound sign (#) at the beginning of the line is a preprocessor directive
that is used to include header files in the program. */
#include <stdio.h>


/* Defining constants and macros for a maze-solving program. It defines constants for
different types of cells in the maze (START, END, FREE, WALL, PATH, VISITED, NOTVISITED, and
MOVINGOBJECT) and the number of columns and rows in the maze (MAZE_COLUMNS and MAZE_ROWS). These
constants are likely used in the implementation of the maze-solving algorithm. */
#define START -1
#define END -2
#define FREE -3
#define WALL -4
#define PATH -5
#define VISITED -6
#define NOTVISITED -7
#define OBJECT -8
#define MAZE_COLUMNS 15
#define MAZE_ROWS 17
/* Global declaration of variables and constants for a maze solver. It defines the
symbols used in the maze such as the start symbol, end symbol, free symbol, wall symbol, path
symbol, visited symbol, not visited symbol, and moving object symbol. It also initializes variables for
keeping track of the number of start and end symbols found, their respective row and column indices,
the current position of the moving object, the number of steps taken, and the number of elements and rows
in the maze. Additionally, it sets flags for whether the moving object can move in certain directions. */
char start_symbol = 'S', end_symbol = 'E', free_symbol = ' ', wall_symbol = '#', path_symbol = '.', visited_symbol = 'V', notvisited_symbol = 'X', object_symbol = '@';
int found_starts = 0, start_row_index = 0, start_column_index = 0;
int found_ends = 0, end_row_index = 0, end_column_index = 0;
int current_position_row_index = 0;
int current_position_column_index = 0;
int steps = 0;
int found_elements_in_the_row = 0, found_rows_in_the_maze = 0;
int can_not_move_right, can_not_move_left, can_not_move_up, can_not_move_down;
int main()
{
/* Defining a 2D array called "maze" which represents a maze. The maze is made up of
cells, each of which can be either a wall, a free space, the start point, or the end point. The maze
is defined using constants for the different types of cells (START, END, WALL, and FREE) and the
dimensions of the maze (MAZE_ROWS and MAZE_COLUMNS). */
    int maze[MAZE_ROWS][MAZE_COLUMNS] = 
    {
        {START,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE},
        {WALL,FREE,WALL,FREE,WALL,FREE,WALL,WALL,WALL,FREE,WALL,FREE,WALL,FREE,WALL},
        {FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE},
        {WALL,FREE,WALL,FREE,WALL,WALL,WALL,FREE,WALL,FREE,WALL,WALL,WALL,FREE,WALL},
        {FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE},
        {WALL,WALL,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL},
        {FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE},
        {WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL},
        {FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE},
        {WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL},
        {FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE},
        {WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,FREE,WALL,WALL,WALL},
        {FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE},
        {WALL,FREE,WALL,WALL,WALL,FREE,WALL,FREE,WALL,WALL,WALL,FREE,WALL,FREE,WALL},
        {FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE},
        {WALL,FREE,WALL,FREE,WALL,FREE,WALL,WALL,WALL,FREE,WALL,FREE,WALL,FREE,WALL},
        {FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,FREE,WALL,FREE,FREE,FREE,END}
    };
/**
 * This function refreshes the console screen by printing the maze with different symbols for different
 * elements.
 */
void refresh()
{
   system("cls");
   for (int scanned_row_index = 0; scanned_row_index < MAZE_ROWS; scanned_row_index++)
    {
        for (int scanned_column_index = 0; scanned_column_index < MAZE_COLUMNS; scanned_column_index++)
        {
            switch(maze[scanned_row_index][scanned_column_index])
            {
            case OBJECT:
                printf("[%c]", object_symbol);
                break;
            case 0:
                printf("[%c]", start_symbol);
                break;
            case END:
                printf("[%c]", end_symbol);
                break;
            case FREE:
                printf("[%c]", free_symbol);
                break;
            case WALL:
                printf("[%c]", wall_symbol);
                break;
            case VISITED:
                printf("[%c]", visited_symbol);
                break;
            case NOTVISITED:
                printf("[%c]", notvisited_symbol);
                break;
            default:
                printf("[%c]", path_symbol);
                break;
            }
        }
        printf("\n");
    }
   Sleep(2000);
}    
    /* Checking if the maze array has the correct number of rows and columns. It scan
    each element in the maze array and checks if it is a valid element (START, END, WALL, or
    FREE). If the number of valid elements in a row is less than the number of columns in the maze, it
    prints an error message indicating the row number and the number of missing columns. If the number
    of valid rows in the maze is less than the number of rows specified in the constant MAZE_ROWS, it
    prints an error message indicating the number of missing rows. */
    for (int scanned_row_index = 0; scanned_row_index < MAZE_ROWS; scanned_row_index++)
    {
        for (int scanned_column_index = 0; scanned_column_index < MAZE_COLUMNS; scanned_column_index++)
        {
            if 
            (
                (maze[scanned_row_index][scanned_column_index] == START) ||
                (maze[scanned_row_index][scanned_column_index] == END) ||
                (maze[scanned_row_index][scanned_column_index] == WALL) ||
                (maze[scanned_row_index][scanned_column_index] == FREE)
            )
            {
                found_elements_in_the_row++;
            }
        }
        if(found_elements_in_the_row < MAZE_COLUMNS)
        {
            printf("error: number of columns on row %d is %d, please add %d", scanned_row_index, found_elements_in_the_row, (MAZE_COLUMNS-found_elements_in_the_row));
            return 0;
        }
        found_rows_in_the_maze++;
        found_elements_in_the_row = 0;
    }
    if(found_rows_in_the_maze < MAZE_ROWS)
        {
            printf("error: number of rows is %d, please add %d more", found_rows_in_the_maze, (MAZE_ROWS-found_rows_in_the_maze));
            return 0;
        }

    // Check if the maze has only 1 start 1 end 
    for (int scanned_row_index = 0; scanned_row_index < MAZE_ROWS; scanned_row_index++)
    {
        for (int scanned_column_index = 0; scanned_column_index < MAZE_COLUMNS; scanned_column_index++)
        {
            if (maze[scanned_row_index][scanned_column_index] == START)
            {
                found_starts++;
                start_row_index = scanned_row_index;
                start_column_index = scanned_column_index;
                current_position_row_index = start_row_index;
                current_position_column_index = start_column_index;
            }
            if (maze[scanned_row_index][scanned_column_index] == END)
            {
                found_ends++;
                end_row_index = scanned_row_index;
                end_column_index = scanned_column_index;
            }
        }
    }
    if((found_starts == 0) && (found_ends == 0))
    {
        printf("error: start and end not found\n");
        return 0;
    }
    if((found_starts == 0) && (found_ends == 1))
    {
        printf("error: start not found");
        return 0;
    }
    if((found_starts == 1) && (found_ends == 0))
    {
        printf("error: end not found");
        return 0;
    }
    if((found_starts > 1) && (found_ends > 1))
    {
        printf("error: more than 1 start and 1 end");
        return 0;
    } 
    if(found_starts > 1)
    {
        printf("error: more than 1 start");
        return 0;
    }
    if(found_ends > 1)
    {
        printf("error: more than 1 end");
        return 0;
    }
    /* Printing out statistics and the maze in a formatted way. It prints out the coordinates of the start and end points and then prints out the maze
    with symbols representing the different types of cells (start, end, free, and wall). The code also
    includes a Sleep function call, which pauses the program for 4 seconds before continuing. */
    printf("Stats: \n");
    printf("Start coordinates [%d][%d]\n", start_row_index, start_column_index);
    printf("End coordinated [%d][%d]\n", end_row_index, end_column_index);
    printf("\n");
    printf("Maze:\n");
    for (int scanned_row_index = 0; scanned_row_index < MAZE_ROWS; scanned_row_index++)
    {
        for (int scanned_column_index = 0; scanned_column_index < MAZE_COLUMNS; scanned_column_index++)
        {
            switch(maze[scanned_row_index][scanned_column_index])
            {
            case START:
                printf("[%c]", start_symbol);
                break;
            case END:
                printf("[%c]", end_symbol);
                break;
            case FREE:
                printf("[%c]", free_symbol);
                break;
            case WALL:
                printf("[%c]", wall_symbol);
                break;
            default:
                printf("error: stats switch case");
                break;
            }
        }
        printf("\n");
    }
    Sleep(4000);
    // Set start to 0, because it is 0 positions from the start
    maze[start_row_index][start_column_index] = steps;
    refresh();
    while(1)
    { 
        /* Checking if the current position in a maze is the starting position and
        then checking if the position can be moved in any direction (right, left, up, or down)
        without hitting a wall or a previously visited position. If the position cannot be moved in
        any direction, the code prints a message indicating that the maze cannot be solved. If the
        position can be moved in at least one direction, the code resets the direction flags and
        continues with the maze-solving algorithm. */
        if
        (
        ((current_position_row_index == start_row_index) && (current_position_column_index == start_column_index))
        )
        {  
            // CHECK IF CAN'T MOVE RIGHT
            if((current_position_column_index + 1) == MAZE_COLUMNS)
            {
                can_not_move_right = 1; 
            }
            else if
            (
            ((maze[current_position_row_index][current_position_column_index + 1]) == WALL) ||
            ((maze[current_position_row_index][current_position_column_index + 1]) == VISITED)
            )
            {
                can_not_move_right = 1;
            }
            // CHECK IF CAN'T MOVE LEFT
            if((current_position_column_index - 1) < 0)
            {
                can_not_move_left = 1;
            }
            else if
            (
            ((maze[current_position_row_index][current_position_column_index - 1]) == WALL) ||
            ((maze[current_position_row_index][current_position_column_index - 1]) == VISITED)
            )
            {
                can_not_move_left = 1;
            }
            // CHECK IF CAN'T MOVE UP
            if((current_position_row_index - 1) < 0)
            {
                can_not_move_up = 1;
            }
            else if
            (
            ((maze[current_position_row_index - 1][current_position_column_index]) == WALL) ||
            ((maze[current_position_row_index - 1][current_position_column_index]) == VISITED)
            )
            {
                can_not_move_up = 1;
            }
            // CHECK IF CAN'T MOVE DOWN
            if((current_position_row_index + 1) == MAZE_ROWS)
            {
                can_not_move_down = 1;
            } 
            else if
            (
            ((maze[current_position_row_index+1][current_position_column_index]) == WALL) ||
            ((maze[current_position_row_index+1][current_position_column_index]) == VISITED)
            )
            {                   
                can_not_move_down = 1;
            }
            // CHECK IF CAN'T MOVE IN ALL DIRECTIONS
            if((can_not_move_right == 1) && (can_not_move_left == 1) && (can_not_move_up == 1) && (can_not_move_down == 1))
            {
                printf("The maze can not be solved.");
                break;
            }
            else
            {   
                // RESET THE DIRECTIONS
                can_not_move_right = 0;
                can_not_move_left = 0;
                can_not_move_up = 0;
                can_not_move_down = 0;
            }
        }
        /* Check if the current position in a maze is near to the end position. If
        it is, it prints out the map of the maze with symbols representing the path taken, start
        position, end position, walls, and visited positions. */
        if
        (
        (((current_position_row_index + 1) == end_row_index) && (current_position_column_index == end_column_index)) ||
        (((current_position_row_index - 1) == end_row_index) && (current_position_column_index == end_column_index)) ||
        (((current_position_row_index) == end_row_index) && ((current_position_column_index + 1) == end_column_index)) ||
        (((current_position_row_index) == end_row_index) && ((current_position_column_index - 1) == end_column_index))
        )
        {
            // PRINT THE MAP OF THE MAZE
            printf("Map ot the maze:\n");
            for (int scanned_row_index = 0; scanned_row_index < MAZE_ROWS; scanned_row_index++)
            {
                for (int scanned_column_index = 0; scanned_column_index < MAZE_COLUMNS; scanned_column_index++)
                {   
                    if(maze[scanned_row_index][scanned_column_index] > 0)
                    {
                        printf("[%c]", path_symbol);
                    }
                    else
                    {
                        switch(maze[scanned_row_index][scanned_column_index])
                        {
                        case OBJECT:
                            printf("[%c]", path_symbol);
                            break;
                        case 0:
                            printf("[%c]", start_symbol);
                            break;
                        case END:
                            printf("[%c]", end_symbol);
                            break;
                        case FREE:
                            printf("[%c]", notvisited_symbol);
                            break;
                        case WALL:
                            printf("[%c]", wall_symbol);
                            break;
                        case VISITED:
                            printf("[%c]", visited_symbol);
                            break;
                        default:
                            printf("error: map of the maze switch case");
                            break;
                        }
                    }
                }
                printf("\n");
            }
            break;
        }
        /* Check if the object can move down, left, up, or right in a maze. If the object
        can move in any of these directions, the code updates the object's position in the maze and
        increments the number of steps taken. The code also refreshes the display of the maze after each
        move. */
        // Check if can move down
        if(((current_position_row_index + 1) != MAZE_ROWS) && ((maze[current_position_row_index + 1][current_position_column_index]) == FREE))
        {
            (maze[current_position_row_index][current_position_column_index]) = steps;
            ++current_position_row_index;
            ++steps;
            (maze[current_position_row_index][current_position_column_index]) = OBJECT;
            refresh();
            continue;
        }
        // Check if can move left
        else if(((current_position_column_index - 1) >= 0) && ((maze[current_position_row_index][current_position_column_index - 1]) == FREE))
        {
            (maze[current_position_row_index][current_position_column_index]) = steps;
            --current_position_column_index;
            ++steps;
            (maze[current_position_row_index][current_position_column_index]) = OBJECT;
            refresh();
            continue;
        }
        // Check if can move up
        else if(((current_position_row_index - 1) >= 0) && ((maze[current_position_row_index - 1][current_position_column_index]) == FREE))
        {
            (maze[current_position_row_index][current_position_column_index]) = steps;
            --current_position_row_index;
            ++steps;
            (maze[current_position_row_index][current_position_column_index]) = OBJECT;
            refresh();
            continue;
        }
        // Check if can move right
        else if(((current_position_column_index + 1) != MAZE_COLUMNS) && ((maze[current_position_row_index][current_position_column_index + 1]) == FREE))
        {
            (maze[current_position_row_index][current_position_column_index]) = steps;
            ++current_position_column_index;
            ++steps;
            (maze[current_position_row_index][current_position_column_index]) = OBJECT;
            refresh();
            continue;
        }
        /* Check from the current position in
        the maze if can move in any direction (right, left, up, down) and if can't move in any
        direction, it sets the current position as visited and goes back one position.*/
        // Check if can't move right
        if((current_position_column_index + 1) == MAZE_COLUMNS)
        {
           can_not_move_right = 1; 
        }
        else if
        (
        ((maze[current_position_row_index][current_position_column_index + 1]) == WALL) ||
        ((maze[current_position_row_index][current_position_column_index + 1]) == VISITED) ||
        ((maze[current_position_row_index][current_position_column_index + 1]) == (steps-1))
        )
        {          
            can_not_move_right = 1;
        }
        // CHECK IF CAN'T MOVE LEFT
        if((current_position_column_index - 1) < 0)
        {
            can_not_move_left = 1;
        }
        else if
        (
        ((maze[current_position_row_index][current_position_column_index - 1]) == WALL) ||
        ((maze[current_position_row_index][current_position_column_index - 1]) == VISITED) ||
        ((maze[current_position_row_index][current_position_column_index - 1]) == (steps-1))
        )
        {
            can_not_move_left = 1;
        }
        // Check if can't move up
        if((current_position_row_index - 1) < 0)
        {
            can_not_move_up = 1;
        }
        else if
        (
        ((maze[current_position_row_index - 1][current_position_column_index]) == WALL) ||
        ((maze[current_position_row_index - 1][current_position_column_index]) == VISITED) ||
        ((maze[current_position_row_index - 1][current_position_column_index]) == (steps-1))
        )
        {
            can_not_move_up = 1;
        }
        // Check if can't move down
        if((current_position_row_index + 1) == MAZE_ROWS)
        {
            can_not_move_down = 1;
        } 
        else if
        (
        ((maze[current_position_row_index+1][current_position_column_index]) == WALL) ||
        ((maze[current_position_row_index+1][current_position_column_index]) == VISITED) ||
        ((maze[current_position_row_index+1][current_position_column_index]) == (steps-1))
        )
        {                   
            can_not_move_down = 1;
        }
        
        if((can_not_move_right == 1) && (can_not_move_left == 1) && (can_not_move_up == 1) && (can_not_move_down == 1))
        {
            
            maze[current_position_row_index][current_position_column_index] = VISITED;
            refresh();
            --steps;
            for (int scanned_row_index = 0; scanned_row_index < MAZE_ROWS; scanned_row_index++)
            {
                for (int scanned_column_index = 0; scanned_column_index < MAZE_COLUMNS; scanned_column_index++)
                {
                    if (maze[scanned_row_index][scanned_column_index] == steps)
                    {
                        current_position_row_index = scanned_row_index;
                        current_position_column_index = scanned_column_index;
                        (maze[current_position_row_index][current_position_column_index]) = OBJECT;
                    }
                }
            }
            /* Checking if the current position in a maze is the starting position
            and then checking from it if can move in any direction (right, left, up, down)
            without hitting a wall or a previously visited position. If the position cannot be moved
            in any direction, it prints a message that the maze cannot be solved. If the position
            can be moved in at least one direction, it resets the direction flags and continues with
            the maze solving algorithm. */
            if
            (
            ((current_position_row_index == start_row_index) && (current_position_column_index == start_column_index))
            )
            {  
                // Check if can't move right
                if((current_position_column_index + 1) == MAZE_COLUMNS)
                {
                    can_not_move_right = 1; 
                }
                else if
                (
                ((maze[current_position_row_index][current_position_column_index + 1]) == WALL) ||
                ((maze[current_position_row_index][current_position_column_index + 1]) == VISITED)
                )
                {
                    can_not_move_right = 1;
                }
                // Check if can't move left
                if((current_position_column_index - 1) < 0)
                {
                    can_not_move_left = 1;
                }
                else if
                (
                ((maze[current_position_row_index][current_position_column_index - 1]) == WALL) ||
                ((maze[current_position_row_index][current_position_column_index - 1]) == VISITED)
                )
                {
                    can_not_move_left = 1;
                }
                // CHECK IF CAN'T MOVE UP
                if((current_position_row_index - 1) < 0)
                {
                    can_not_move_up = 1;
                }
                else if
                (
                ((maze[current_position_row_index - 1][current_position_column_index]) == WALL) ||
                ((maze[current_position_row_index - 1][current_position_column_index]) == VISITED)
                )
                {
                    can_not_move_up = 1;
                }
                // Check if can't move down
                if((current_position_row_index + 1) == MAZE_ROWS)
                {
                    can_not_move_down = 1;
                } 
                else if
                (
                ((maze[current_position_row_index+1][current_position_column_index]) == WALL) ||
                ((maze[current_position_row_index+1][current_position_column_index]) == VISITED)
                )
                {                   
                    can_not_move_down = 1;
                }
                // Check if can't move in all directions
                if((can_not_move_right == 1) && (can_not_move_left == 1) && (can_not_move_up == 1) && (can_not_move_down == 1))
                {
                    printf("The maze can not be solved.");
                    break;
                }
                else
                {   
                    // Reset the direction flags
                    can_not_move_right = 0;
                    can_not_move_left = 0;
                    can_not_move_up = 0;
                    can_not_move_down = 0;
                }
            }
        }
        else
        {   
            // Reset the direction flags
            can_not_move_right = 0;
            can_not_move_left = 0;
            can_not_move_up = 0;
            can_not_move_down = 0;
        }
    }
    return 0;
}
