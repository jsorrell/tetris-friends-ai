#include <string.h>
#include <stack>
#include <queue>
#include "windows.h"

#define HEIGHT_MUL -3.78
#define HOLE -2.31
#define BLOCKADE -0.59
#define CLEAR 1.6
#define SHARED_EDGE 3.97
#define WALL_EDGE 6.52
#define FLOOR_EDGE 0.65

#define WIDTH 10
#define HEIGHT 23
#define SEEABLE 20
#define SIZE WIDTH*HEIGHT
#define LIM WIDTH*(HEIGHT-1)

#define PIECE_COUNT 6

using namespace std;

struct gameState {
    queue<int, queue<int> > moveList;
    char* tetrisBoard;
    int evaluation;
};

inline int GetIndex(int x, int y){  //assume lower-left corner is zero index
    return WIDTH*y + x;
}

int is_floor_edge(char *board, int x, int y){
    return !y;
}

int is_wall_edge(char *board, int x, int y){
    return !x | (x == WIDTH - 1);
}

int num_shared_edge(char *board, int x, int y){
    int count = 0;

    if(x != WIDTH-1 && board[GetIndex(x+1,y)]){
        count++;
    }

    if(y != HEIGHT-1 && board[GetIndex(x,y+1)]){
        count++;
    }

    return count;
}

int count_blockade(char *board, int x, int y){  //if is a hole returns number of blocks above hole
    int count = 0;
    for(int i=0; i<HEIGHT-y; i++){
        if(board[GetIndex(x,y+i)])
            count++;
    }      
    
    return count;
}

int evaluate(char *board){
    if (!board)
        return 0;

    int total = 0;

    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(!board[i,j])
                total += (count_blockade(board, j, i) * BLOCKADE + HOLE);
            
            total += is_floor_edge(board, j, i)*FLOOR_EDGE;
            total += is_wall_edge(board, j, i)*WALL_EDGE;
            total += num_shared_edge(board, j, i)*SHARED_EDGE;
        }
    }

    return total;
}

void removeClears(char* board){
    int i = 0;
    char needsClear;
    int j;
    // all the way to 23?
    while (i < 20){
        j = 0;
        needsClear = 1;
        while (needsClear & (j < WIDTH))
            needsClear &= board[WIDTH*i + j++];
        if (needsClear){
            char* pushdown = new char[SIZE];
            for (int k = 0; k < WIDTH*i; k++)
                pushdown[k] = board[k];
            for (int k = WIDTH*i; k < LIM; k++)
                pushdown[k] = board[k + 10];
            for (int k = LIM; k < SIZE; k++)
                pushdown[k] = 0;
            board = pushdown;
        }
        i += !needsClear;
    }
}

/*
0: square
1: I-piece
2: S
3: Z
4: T
5: L
6: other L

0: <-
1: ->
2: rotate clockwise
*/

queue<int, queue<int> > rev (queue<int, queue<int> > Q){
    stack<int, queue<int> > S;
    while(!Q.empty()){
        S.push(Q.front());
        Q.pop();
    }
    while(!S.empty()){
        Q.push(S.top());
        S.pop();
    }
    return Q
} 

int h(char* b, int j){
    int h = 20;
    while (h && !(b[10 * (h-- - 1) + j]));
    return h;
}

char* movePiece (char* board, int j, int rotate, int piece){
    char* newBoard = new char[SIZE];
    for (int l = 0; l < SIZE; l++)
        newBoard[l] = board[l];

    int height = SEEABLE;
    while (height && !(newBoard[WIDTH * (height-- - 1) + j]));

    int pos;

    switch (piece){
        case (0):
        // square
            if (j == WIDTH - 1)
                return NULL;
            int rheight = SEEABLE;
            while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
            height = rheight > height ? rheight : height;
            
            pos = WIDTH*height + j;
            newBoard[pos] = 1;
            newBoard[pos + 1] = 1;
            newBoard[pos + WIDTH] = 1;
            newBoard[pos + WIDTH + 1] = 1;
            break;
        case (1):
        // I
            switch(rotate % 2){ 
                case (1):
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + 2 * WIDTH] = 1;
                    newBoard[pos + 3 * WIDTH] = 1;
                    break;
                default:
                    if (!j | j > WIDTH - 3)
                        return NULL;
                    int rheight = SEEABLE;
                    int midheight = SEEABLE;
                    int lheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 2]));
                    while (midheight && !(newBoard[WIDTH * (midheight-- - 1) + j + 1]));
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));

                    height = rheight > height ? rheight : height;
                    height = midheight > height ? midheight : height;
                    height = lheight > height ? lheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + 2] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos - 1] = 1;
            }
            break;
        case (2):
        // S
            switch(rotate % 2){
                case (1):
                    if (!j)
                        return NULL;
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = lheight - 1 > height? lheight - 1 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH - 1] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + 2*WIDTH - 1] = 1;

                    break;
                default:
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;
                    int lheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    height = rheight - 1 > height ? rheight - 1 : height;
                    height = lheight > height ? lheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + WIDTH + 1] = 1;        
            }
            break;
        case (3):
        // Z
            switch(rotate % 2){
                case (1):
                    if (!j)
                        return NULL;
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = lheight + 1 > height ? lheight + 1: height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos - WIDTH - 1] = 1;
                    newBoard[pos + WIDTH] = 1;

                    break;
                default:
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;
                    int lheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    height = rheight > height ? rheight : height;
                    height = lheight - 1 > height ? lheight - 1 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + WIDTH - 1] = 1;        
            }
            break;    
        case (4):
        // T
            switch(rotate){
                case (1):
                    if (!j)
                        return NULL;
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = lheight - 1 > height ? lheight - 1: height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + WIDTH - 1] = 1;
                    newBoard[pos + 2*WIDTH] = 1;

                    break;
                case (2):
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;                    
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    
                    height = lheight - 1 > height ? lheight - 1 : height;
                    height = rheight - 1 > height ? rheight - 1 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + WIDTH - 1] = 1;
                    newBoard[pos + WIDTH + 1] = 1;

                    break;
                case (3):
                    if (j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
        
                    height = rheight - 1 > height ? rheight - 1 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + WIDTH + 1] = 1;
                    newBoard[pos + 2*WIDTH] = 1;

                    break;
                default:
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;
                    int lheight = SEEABLE; 
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = rheight > height ? rheight : height;
                    height = lheight > height ? lheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos - 1] = 1;        
            }
            break;   
        case (5):
        // L
            switch(rotate){
                case (1):
                    if (!j)
                        return NULL;
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = lheight - 2 > height ? lheight - 2 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + 2*WIDTH] = 1;
                    newBoard[pos + 2*WIDTH - 1] = 1;

                    break;
                case (2):
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;                    
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    
                    height = lheight + 1 > height ? lheight + 1 : height;
                    height = rheight > height ? rheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos - WIDTH - 1] = 1;

                    break;
                case (3):
                    if (j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
        
                    height = rheight - 1 > height ? rheight - 1 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + WIDTH] = 1;
                    newBoard[pos + WIDTH + 1] = 1;
                    newBoard[pos + 2*WIDTH] = 1;

                    break;
                default:
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int rheight = SEEABLE;
                    int lheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    height = rheight > height ? rheight : height;
                    height = lheight > height ? lheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos + WIDTH+1] = 1;        
            }
            break; 
        case (6):
        // other L
            switch(rotate){
                case (1):
                    if (!j)
                        return NULL;
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = lheight > height ? lheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos + 2*WIDTH] = 1;
                    newBoard[pos + WIDTH] = 1;

                    break;
                case (2):
                    if (!j | j == WIDTH - 1)
                        return NULL;
                    int lheight = SEEABLE;
                    int rheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j - 1]));
                    
                    height = lheight > height ? lheight : height;
                    height = rheight + 1 > height ? rheight + 1 : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos - WIDTH + 1] = 1;

                    break;
                case (3):
                    if (j == WIDTH - 1)
                        return NULL;
                    int lheight = SEEABLE;
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    
                    height = lheight - 2 > height ? lheight - 2: height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + 2*WIDTH] = 1;
                    newBoard[pos + 2*WIDTH + 1] = 1;
                    newBoard[pos + WIDTH] = 1;

                    break;
                default:
                    if (!j | j == WIDTH-1)
                        return NULL;
                    int rheight = SEEABLE;
                    int lheight = SEEABLE;
                    while (rheight && !(newBoard[WIDTH * (rheight-- - 1) + j + 1]));
                    while (lheight && !(newBoard[WIDTH * (lheight-- - 1) + j - 1]));
                    height = rheight > height ? rheight : height;
                    height = lheight > height ? lheight : height;
            
                    pos = WIDTH*height + j;
                    newBoard[pos] = 1;
                    newBoard[pos + 1] = 1;
                    newBoard[pos - 1] = 1;
                    newBoard[pos + WIDTH-1] = 1; 
            }       
            break;
    }    

    return newBoard;
}

gameState* findBest (char* board, char* pieces, int c){
    if (!c){
        gameState* california = new gameState;
        california->tetrisBoard = board;
        queue<int, queue<int> > emp;
        california->moveList = emp;
        california->evaluation = evaluate(board);
        return california;
    }
    gameState* toReturn = new gameState;
    toReturn->evaluation = 0;

    gameState* nextBestState;
    int current;
    int currentPiece = pieces[0];
    int numSpins = ((currentPiece > 3) + 1) << 1;

    for (int j = 0; j < WIDTH; j ++){
        for (int k = 0; k < numSpins; k++){
            queue<int, queue<int> > moves;
            queue<int> pieceJiggle;
            for (int rot = 0; rot < k; rot++)
                pieceJiggle.push(2);
            //should make macro: 4 as MIDPOINT
            for (int lTrans = 0; lTrans < 4 - j; lTrans++)
                pieceJiggle.push(0);
            for (int rTrans = 4; rTrans < j; rTrans++)
                pieceJiggle.push(1);
            nextBestState = findBest(movePiece(board, j, k, currentPiece), pieces + 1, c-1);
            current = nextBestState->evaluation;         

            if (current > toReturn->evaluation){
                toReturn->movesList = (nextBestState->movesList).push(pieceJiggle);
                toReturn->tetrisBoard = nextBestState->tetrisBoard;
                toReturn->evaluation = current;
            }
        }
    }

    delete nextBestState;
    return toReturn;
}

void executeMoves (char* board, char* pieces){
    gameState* toDo = findBest(board, pieces, PIECE_COUNT);
    toDo->movesList = rev(toDo->movesList);

    queue<int> moves;
    int move;

    for(int i = 0; i < PIECE_COUNT; i++){
        moves = toDo->movesList.front();
        toDo->movesList.pop();
        while(!moves.empty()){
            move = moves.front();
            moves.pop();
            switch (move){
                case (0): /* <- */
                    break;
                case (1): /* -> */
                    break;
                case(2): /* rotate counterclockwise */
                    break;
            }
        }
        /* spacebar */
    }

    delete toDo;
}

int main(int argc, string* argv){
    char* board = new char[WIDTH * HEIGHT];
    for (int i = 0; i < HEIGHT * WIDTH; i++){
        board[i] = 0;
    }
    char* pieces;

    /* insert DP on board evaluations here */

    while(/* */){
        pieces = /* */;
        executeMoves(board, pieces);
        removeClears(board);
    }
}

