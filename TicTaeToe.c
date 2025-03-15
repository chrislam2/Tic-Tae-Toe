#include <stdio.h>

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

/* Initialize the game board by setting all nine squares to EMPTY */
void initGameBoard(int gameBoard[3][3]) {

    // TODO: Complete this part
    int i,j,k;
    for (i=0;i<=2;i++) {
     if (i != 2) {
       k = 3 * (2-i);
     } else {
       k = 0;
     }
     for (j=0;j<=2;j++) {
       k++;
       gameBoard[i][j] = k;
     }
   }
}



/* Display the game board on the screen */
void printGameBoard(int gameBoard[3][3]) {
  int i,j;
  printf("=========\n");
  for (i=0;i<=2;i++) {
     for (j=0;j<=2;j++) {
       if (gameBoard[i][j] == 1001) {
         printf("|O|");
       } else if (gameBoard[i][j] == 1002) {
         printf("|X|");
       } else if (gameBoard[i][j] == 1010) {
         printf("|\\|"); // this is supposed to be used for removing a square, it is unused for now, since I find this feature boring.
       } else {
         printf("|%d|",gameBoard[i][j]);
       }
       if (j==2) {
         printf("\n");
       }
     }
   }
   printf("=========\n");
}


/* Ask the human player to place the mark. Assume that the user input must be valid (i.e, an empty space between 1 and 9). */
void placeMarkByHumanPlayer(int gameBoard[3][3], int mark, int overwrite, int *P) {

    // TODO: Complete this part
    int i,j,place,tmp,counter;
    if (mark == 1) {
      counter = 1002;
    } else if (mark == 2) {
      counter = 1001;
    }
    scanf("%d",&place);
    //check invalid input
    if ((place < 1)||(place > 9)) {
      printf("Invalid input, please enter your mark in [1-9]!\n");
      printf("Player %d, please place your mark [1-9]:\n",mark);
      if ((overwrite == 1)&&(P == 0)) {
        printf("(You can activate \"Over write opponent's mark\".\n");
      }
      placeMarkByHumanPlayer(gameBoard, mark, overwrite, P);
      return;
    }
    tmp = place;
    j = place - 1;
    i = 2;
    while (j > 2) {
      i--;
      j = j-3;
    }
    if ((gameBoard[i][j] == counter)&&(overwrite==1)&&(*P==0)) {
      *P = 1;
    } else if ((gameBoard[i][j]) > 1000) {
      printf("Invalid input, square \"%d\" has been placed a mark already!\n",tmp);
      printf("Player %d, please place your mark [1-9]:\n",mark);
      if ((overwrite == 1)&&(P == 0)) {
        printf("(You can activate \"Over write opponent's mark\".\n");
      }
      placeMarkByHumanPlayer(gameBoard, mark, overwrite, P);
      return;
    }
    if (mark == 1) {
      gameBoard[i][j] = 1001;
    } else if (mark == 2) {
      gameBoard[i][j] = 1002;
    }
}


/* Return 1 if there is a winner in the game, otherwise return 0 */
/* Note: the winner is the current player indicated in main() */
int hasWinner(int gameBoard[3][3]) {

    // TODO: Complete this part
    int i,j,a,b,c,d,e,f,g,h;
    // check vertical or horizontal
    for (i=0;i<=2;i++) {
      a = 0;
      b = 0;
      c = 0;
      d = 0;
      for (j=0;j<=2;j++) {
        if (gameBoard[i][j] == 1001) {
          a++;
        }
        if (gameBoard[i][j] == 1002) {
          b++;
        }
        if (gameBoard[j][i] == 1001) {
          c++;
        }
        if (gameBoard[j][i] == 1002) {
          d++;
        }
      }
      if ((a==3)||(b==3)||(c==3)||(d==3)){
        break;
      }
    }
    // check diagonal
    e = 0;
    f = 0;
    for (i=0,j=0;(i<=2)&&(j<=2);i++,j++){
      if (gameBoard[i][j] == 1001) {
        e++;
      }
      if (gameBoard[i][j] == 1002) {
        f++;
      }
    }
    g = 0;
    h = 0;
    for (i=0,j=2;(i<=2)&&(j>=0);i++,j--){
      if (gameBoard[i][j] == 1001) {
        g++;
      }
      if (gameBoard[i][j] == 1002) {
        h++;
      }
    }
    //check win or not
    if ((a==3)||(b==3)||(c==3)||(d==3)||(e==3)||(f==3)||(g==3)||(h==3)){
      return 1;
    } else {
      return 0;
    }
}



/* Return 1 if the game board is full, otherwise return 0 */
int isFull(int gameBoard[3][3]) {
  int i,j,k=0;
    for (i=0;i<=2;i++) {
      for (j=0;j<=2;j++) {
        if (gameBoard[i][j] >= 1001) {
          k++;
        }
      }
    }
  if (k==9) {
    return 1;
  } else {
    return 0;
  }
}


/* Determine the next move of the computer player. */

// TODO: Complete the placeMarkByComputerPlayer(...) function here
void placeMarkByComputerPlayer(int gameBoard[3][3], int mark, int difficulty) {

    // TODO: Complete this part
    int a,b,c,d,i,j,k,m,n,q,w;

    // Pick Place
    int place = 1;
    int stop = 0; // used for stop scanning after placed a mark
    int self = 1002;
    int counter = 1001;
    if (mark == CIRCLE) {
      self = 1001;
      counter = 1002;
    }

    if (difficulty != 1) {
      // Counter
      // check if any possible for players to win (of course, it helps nothing when player can win with "two lines".)
      // check vertical or horizontal first as these winning situations are more than that of diagonal.
      // Note that impossible computer will always take winning as the first priority.
      if (stop == 0) {
        if (difficulty == 3) {
          for (i=0;i<=2;i++) {
            c = 0;
            d = 0;
            // q and w are used for if all three square of vertical line has been placed a mark already, the computer will ignore this line.
            q = 0;
            w = 0;
            for (j=0;j<=2;j++) {
              if (gameBoard[i][j] == self) {
                c++;
                m = i;
              }
              if (gameBoard[i][j] > 1000) {
                q++;
              }
              if (q==3) {
                c = 1000;
              }
              if (gameBoard[j][i] == self) {
                d++;
                n = i;
              }
              if (gameBoard[j][i] > 1000) {
                w++;
              }
              if (w==3) {
                d = 1000;
              }
            }
            if ((c==2)||(d==2)){
              break;
            }
          }
          if ((c==2)&&(stop==0)) {
            for (i=0;i<=2;i++) {
              if (gameBoard[m][i] <= 1000) {
                place = gameBoard[m][i];
                stop++;
                break;
              }
            }
          }
          if ((d==2)&&(stop==0)) {
            for (j=0;j<=2;j++) {
              if (gameBoard[j][n] <= 1000) {
                place = gameBoard[j][n];
                stop++;
                break;
              }
            }
          }
          c = 0;
          for (i=0,j=0;(i<=2)&&(j<=2)&&(stop==0);i++,j++){
            if (gameBoard[i][j] == self) {
              c++;
            }
          }
          d = 0;
          for (i=0,j=2;(i<=2)&&(j>=0)&&(stop==0);i++,j--){
            if (gameBoard[i][j] == self) {
              d++;
            }
          }
          if (c >= 2) {
            for (i=0,j=0;(i<=2)&&(j<=2)&&(stop==0);i++,j++) {
              if (gameBoard[i][j] <= 1000) {
                place = gameBoard[i][j];
                stop++;
                break;
              }
            }
          }
          if (d >= 2) {
            for (i=0,j=2;(i<=2)&&(j>=0)&&(stop==0);i++,j--) {
              if (gameBoard[i][j] <= 1000) {
              place = gameBoard[i][j];
              stop++;
              break;
              }
            }
          }
        }

        for (i=0;(i<=2)&&(stop==0);i++) {
          a = 0;
          b = 0;
          // q and w are used for if all three square of vertical line has been placed a mark already, the computer will ignore this line.
          q = 0;
          w = 0;
          for (j=0;j<=2;j++) {
            if (gameBoard[i][j] == counter) {
              a++;
              m = i;
            }
            if (gameBoard[i][j] > 1000) {
              q++;
            }
            if (q==3) {
              a = 1000;
            }
            if (gameBoard[j][i] == counter) {
              b++;
              n = i;
            }
            if (gameBoard[j][i] > 1000) {
              w++;
            }
            if (w==3) {
              b = 1000;
            }
          }
          if ((a==2)||(b==2)){
            break;
          }
        }
        if ((a==2)&&(stop==0)) {
          for (i=0;i<=2;i++) {
            if (gameBoard[m][i] <= 1000) {
              place = gameBoard[m][i];
              stop++;
              break;
            }
          }
        }
        if ((b==2)&&(stop==0)) {
          for (j=0;j<=2;j++) {
            if (gameBoard[j][n] <= 1000) {
              place = gameBoard[j][n];
              stop++;
              break;
            }
          }
        }
      }

      // check diagonal
      if (stop==0) {
        c = 0;
        for (i=0,j=0;(i<=2)&&(j<=2);i++,j++){
          if (gameBoard[i][j] == counter) {
            c++;
          }
        }
        d = 0;
        for (i=0,j=2;(i<=2)&&(j>=0);i++,j--){
          if (gameBoard[i][j] == counter) {
            d++;
          }
        }
        if (c >= 2) {
          for (i=0,j=0;(i<=2)&&(j<=2);i++,j++) {
            if (gameBoard[i][j] <= 1000) {
              place = gameBoard[i][j];
              stop++;
              break;
            }
          }
        }
        if (d >= 2) {
          for (i=0,j=2;(i<=2)&&(j>=0);i++,j--) {
            if (gameBoard[i][j] <= 1000) {
            place = gameBoard[i][j];
            stop++;
            break;
            }
          }
        }
      }
      // Counter End

      // Computer strategy
      if (stop==0) {
        if (gameBoard[1][1] <= 1000) {
          place = 5;
          stop++;
        }
      }
      // Attempt to counter player
      if (stop==0) {
        if (difficulty == 3) {
          if (gameBoard[1][1] == self) {
            q = 0;
            w = 0;
            for (i=0;i<=2;i++) {
              if (gameBoard[i][1] == counter) {
                q++;
              }
            }
            for (i=0;i<=2;i++) {
              if (gameBoard[1][i] == counter) {
                w++;
              }
            }
            for (i=0;i<=2;i++) {
              if ((gameBoard[1][i] <= 1000)&&(stop==0)&&(q==0)&&(w==0)) {
                place = gameBoard[1][i];
                stop++;
                break;
              }
            }
            for (i=0;i<=2;i++) {
              if ((gameBoard[i][1] <= 1000)&&(stop==0)&&(q==0)&&(w==0)) {
                place = gameBoard[i][1];
                stop++;
                break;
              }
            }
          }
        } else {
          for (i=0;i<=2;i=i+2) {
            for (j=0;j<=2;j=j+2) {
              if ((gameBoard[i][j] <= 1000)&&(gameBoard[2-i][2-j] !=   counter)) {
                place = gameBoard[i][j];
                stop++;
                break;
              }
            }
          }
        }
      }
      if ((stop==0)&&(difficulty==3)) {
        for (i=0;i<=2;i=i+2) {
            for (j=0;j<=2;j=j+2) {
                q = 0;
                w = 0;
                if (gameBoard[i][1] == counter) {
                    q++;
                }
                if (gameBoard[1][i] == counter) {
                    w++;
                }
                if ((q==1)&&(stop==0)) {
                    if (gameBoard[i][j] <= 1000) {
                        place = gameBoard[i][j];
                        stop++;
                        break;
                    }
                }
                if ((w==1)&&(stop==0)) {
                    if (gameBoard[j][i] <= 1000) {
                        place = gameBoard[j][i];
                        stop++;
                        break;
                    }
                }
            }
        }
      }

      if (stop==0) {
        for (i=0;i<=2;i=i+2) {
          for (j=0;j<=2;j=j+2) {
            if (gameBoard[i][j] <= 1000) {
              place = gameBoard[i][j];
              stop++;
              break;
            }
          }
        }
      }
    }

    //scanning for all empty square from 1 to 9.
    if (stop==0) {
      for (i=0;i<=2;i++) {
      if (i != 2) {
       k = 3 * (2-i);
      } else {
       k = 0;
      }
      for (j=0;j<=2;j++) {
        k++;
        if (gameBoard[i][j] == k) {
          place = gameBoard[i][j];
          stop++;
          break;
        }
       }
      }
    }
    // Pick Place End

    // Put the mark
    j = place-1;
    i = 2;
    while (j > 2) {
      i--;
      j = j-3;
    }
    if (mark == 1) {
      gameBoard[i][j] = 1001;
    } else if (mark == 2) {
      gameBoard[i][j] = 1002;
    }
}

/* Custom function */
// turn around the situation
void turnaroundthesituation(int gameBoard[3][3]) {
  int i,j;
  for (i=0;i<=2;i++) {
    for (j=0;j<=2;j++) {
      if (gameBoard[i][j] == 1001) {
        gameBoard[i][j] = 1002;
      } else if (gameBoard[i][j] == 1002) {
        gameBoard[i][j] = 1001;
      }
    }
  }
}

// Compare string
int comparestring(char str1[],char str2[],int size) {
  int i,k=0;
  size++;
  for (i=0;i<=size;i++) {
    if (str1[i] == str2[i]) {
      k++;
    }
  }
  if (k==size) {
    return 1;
  } else {
    return 0;
  }
}

/* The main function */
int main() {
    /* Local variables */
    int gameBoard[3][3];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1 (Human)   2: Player 2 (Human) or Computer Player
    int gameEnds;           // 0: The game continues   1: The game ends
    int numOfHumanPlayers = 0;  // 1 or 2
    int mark;
    int winner;
    char str[20];
    int skipA = 0; // used for skip player 1's turn
    int skipB = 0; // used for skip player 2's turn
    int i,j; // used for loop

    /* Initialize the local variables by invoking a function, using assignment statements, and reading the user input */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameEnds = 0;
    while ((numOfHumanPlayers != 1) && (numOfHumanPlayers != 2)) {
      printf("How many human players [1-2]?\n");
      scanf("%d", &numOfHumanPlayers);    // In Part 1, you can assume that the user input must be valid
      if ((numOfHumanPlayers != 1) && (numOfHumanPlayers != 2)) {
        printf("Invalid input, number of human players must be either 1 or 2!\n");
      }
    }

    if (numOfHumanPlayers == 1) {
      printf("Since you are the only player, you are going to play with computer.\n");
    }

    // Initialize some special local variables
    int first = 0;
    int tmpfirst = 0;
    int difficulty = 0;
    int turnaround = 0;
    int overwrite = 0;
    int games[3] = {0};
    int win[3] = {0};
    int lose[3] = {0};
    int tie[3] = {0};
    int load = 0;
    // Since we need to set the setting in every games, hence we can load last setting for convenience.
    FILE *fptr;
    fptr = fopen("data.txt","r");
    fscanf(fptr,"%d%d%d%d",&first,&difficulty,&turnaround,&overwrite);
    tmpfirst = first;
    for (i=0;i<=2;i++) {
      fscanf(fptr,"%d%d%d%d",&win[i],&lose[i],&tie[i],&games[i]);
    }
    if (fptr != NULL) {
      if (numOfHumanPlayers == 1) {
        if ((games[0]>0)||(games[1]>0)||(games[2]>0)) {
          printf("Player vs Computer statistic are shown below:\n");
        }
        for (i=0;i<=2;i++) {
            if (games[i] > 0) {
              if (i==0) {
                printf("***Beginner Computer***\n");
              } else if (i==1) {
                printf("***Normal Computer***\n");
              } else if (i==2) {
                printf("***Impossible Computer***\n");
              }
              printf("Total number of games: %d\n", games[i]);
              printf("Win: %d Lose: %d Tie: %d\n",win[i],lose[i],tie[i]);
              printf("Winning Percentage: %.2f%%\n",(double) win[i] / games[i] *100.0);
            }
        }
      }
      printf("Last game setting datum are shown below:\n");
      if (numOfHumanPlayers == 1) {
        if (difficulty == 1) {
          printf("Computer difficulty: Beginner\n");
        } else if (difficulty == 2) {
          printf("Computer difficulty: Normal\n");
        } else if (difficulty == 3) {
          printf("Computer difficulty: Impossible\n");
        }
        if (first == 1) {
          printf("\"First turn\": Player\n");
        } else if (first == 2) {
          printf("\"First turn\": Computer\n");
        }
      }
      if (turnaround == 1) {
        printf("\"Turn around the situation\": yes\n");
      } else if (turnaround == 2) {
        printf("\"Turn around the situation\": no\n");
      }
      if (overwrite == 1) {
        printf("\"Overwrite opponent's mark\": yes\n");
      } else if (overwrite == 2) {
        printf("\"Overwrite opponent's mark\": no\n");
      }
      while ((load != 1)&&(load != 2)) {
        printf("Load last game setting datum? (Type \"yes\" or \"no\".)\n");
        scanf("%s",str);
        if (comparestring(str,"yes",3) == 1) {
          load = 1;
        } else if (comparestring(str,"No",2) == 1) {
          load = 2;
        } else {
          printf("Invalid input, please enter \"yes\" or \"no\".\n");
        }
      }
      if (load==1) {
        printf("Last game setting datum loaded.\n");
      } else if (load==2) {
        printf("Last game setting datum were not loaded.\n");
        if (numOfHumanPlayers == 1) {
          first = 0;
          difficulty = 0;
        }
        turnaround = 0;
        overwrite = 0;
      }
    } else {
      load = 2;
      first = 0;
      difficulty = 0;
      turnaround = 0;
      overwrite = 0;
    }
    fclose(fptr);

    // Enter Who take first turn and computer difficulty
    if (numOfHumanPlayers == 1) {
      // difficulty
      if (difficulty==0) {
        while ((difficulty < 1) || (difficulty > 3)) {
          printf("Computer intelligence:\n\"1\": Beginner (Very easy to beat it!)\n\"2\": Normal (You can beat the \"normal\" computer but don't belittle it!)\n\"3\": Impossible (Believe me, unless you enable \"Overwrite opponent's mark\", you will never beat the \"impossilbe\" computer!)\nPlease choose computer intelligence [1-3]:\n");
          scanf("%d",&difficulty);
          if ((difficulty < 1) || (difficulty > 3)) {
          printf("Invalid input, please enter a integer in [1-3].\n");
          }
        }
      }
      // first turn
      if (first==0) {
        while ((first != 1)&&(first != 2)) {
          printf("Who take the first turn? You or computer?\nType \"1\" if you want you to be the first.\nType \"2\" if you want computer to be the first.\n");
          scanf("%d",&first);
          tmpfirst = first;
          if ((first != 1)&&(first != 2)) {
          printf("Invalid input, please enter \"1\" (player) or \"2\" (computer).\n");
          }
        }
      }
    }

    // Enable turn around the situation or not?
    int turnaroundP1 = 0, turnaroundP2 = 0;
    if (turnaround==0) {
      while ((turnaround != 1)&&(turnaround != 2)) {
        printf("\"Turn around the situations\" allow both two players (or computer) can turn opponent's mark to be your mark and vice versa. You will skip placing mark when you use it.\nEnable \"Turn around the situations\"?\nType \"yes\" or \"no\" to indicate your preference.\n");
        scanf("%s",str);
        if (comparestring(str,"yes",3) == 1) {
          turnaround = 1;
        } else if (comparestring(str,"No",2) == 1) {
          turnaround = 2;
        } else {
          printf("Invalid input, please enter \"yes\" or \"no\".\n");
        }
      }
    }

    // Enable overwrite a mark?
    int overwriteP1 = 0, overwriteP2 = 0, *P1 = &overwriteP1, *P2 = &overwriteP2;
    if (overwrite==0) {
      while ((overwrite != 1)&&(overwrite != 2)) {
        printf("Enable overwrite opponent's mark? (It can only be activated one time in the game.)\nType \"yes\" or \"no\" to indicate your preference.\n");
        scanf("%s",str);
        if (comparestring(str,"yes",3) == 1) {
          overwrite = 1;
        } else if (comparestring(str,"No",2) == 1) {
          overwrite = 2;
        } else {
          printf("Invalid input, please enter \"yes\" or \"no\".\n");
        }
      }
    }

    /* Uncomment the following statements to test whether the printGameBoard() and the placeMarkByHumanPlayer() functions
       are implemented correctly
       You can add more if you wish
       After testing, you can delete them or move them elsewhere */
    //printGameBoard(gameBoard);
    //printf("Player 1, please place your mark [1-9]:\n");
    //placeMarkByHumanPlayer(gameBoard, CIRCLE);
    //printf("Player 2, please place your mark [1-9]:\n");

    /* Game start
       If there are two human players, they are Player 1 and Player 2
       If there is only one human player, he/she is Player 1 and another player is the computer player
       For both cases, Player 1 moves first and places the CIRCLE mark; while Player 2 (or the computer player) places the CROSS mark
       */

    printGameBoard(gameBoard);
    while (gameEnds == 0) {
    currentPlayer = 1;
    if ((first != 2)||(numOfHumanPlayers == 2)) {
      if ((turnaround == 1)&&(turnaroundP1 != 1)) {
        while ((turnaroundP1 != 1)&&(turnaroundP1 != 2)) {
          printf("Player 1, do you want to activate \"Turn around the situation\"?\nType \"yes\" or \"no\" to indicate your preference.\n");
          scanf("%s",str);
          if (comparestring(str,"yes",3) == 1) {
          turnaroundP1 = 1;
          skipA++;
          turnaroundthesituation(gameBoard);
          printGameBoard(gameBoard);
          } else if (comparestring(str,"No",2) == 1) {
            turnaroundP1 = 2;
          } else {
            printf("Invalid input, please enter \"yes\" or \"no\".\n");
          }
        }
      }
      if (turnaroundP1 == 2) {
          turnaroundP1 = 0;
      }
      if (skipA == 0) {
        printf("Player 1, please place your mark [1-9]:\n");
        if ((overwrite == 1)&&(overwriteP1 == 0)) {
          printf("(You can activate \"Over write opponent's mark\".)\n");
        }
        placeMarkByHumanPlayer(gameBoard, CIRCLE, overwrite, P1);
        printGameBoard(gameBoard);
      } else {
        skipA = 0;
      }
    } else {
      first = 0;
    }

    gameEnds = isFull(gameBoard);
    winner = hasWinner(gameBoard);
    if ((gameEnds != 0)||(winner == 1)) {
      break;
    }

    currentPlayer = 2;
    if (numOfHumanPlayers == 2) {
      if ((turnaround == 1)&&(turnaroundP2 != 1)) {
        while ((turnaroundP2 != 1)&&(turnaroundP2 != 2)) {
          printf("Player 2, do you want to activate \"Turn around the situation\"?\nType \"yes\" or \"no\" to indicate your preference.\n");
          scanf("%s",str);
          if (comparestring(str,"yes",3) == 1) {
          turnaroundP2 = 1;
          skipB++;
          turnaroundthesituation(gameBoard);
          printGameBoard(gameBoard);
          } else if (comparestring(str,"No",2) == 1) {
            turnaroundP2 = 2;
          } else {
            printf("Invalid input, please enter \"yes\" or \"no\".\n");
          }
        }
      }
      if (turnaroundP2 == 2) {
          turnaroundP2 = 0;
      }
      if (skipB == 0) {
        printf("Player 2, please place your mark [1-9]:\n");
        if ((overwrite == 1)&&(overwriteP2 == 0)) {
          printf("(You can activate \"Over write opponent's mark\".)\n");
        }
        placeMarkByHumanPlayer(gameBoard, CROSS, overwrite, P2);
        printGameBoard(gameBoard);
      } else {
        skipB = 0;
      }
    } else {
        if ((turnaround == 1)&&(turnaroundP1 == 1)&&(turnaroundP2 != 1)&&(difficulty == 3)) {
            printf("Computer activated \"Turn around the situation\"!\n");
            turnaroundP2 = 1;
            skipB++;
            turnaroundthesituation(gameBoard);
            printGameBoard(gameBoard);
        }
        if ((overwrite==1)&&(overwriteP2 != 1)&&(difficulty==3)) {
            int a,b;
            for (i=0;(i<=2)&&(skipB==0);i++) {
                a = 0;
                b = 0;
                for (j=0;(j<=2)&&(skipB==0);j++) {
                    if (gameBoard[i][j] == 1001) {
                        a++;
                    }
                    if (gameBoard[j][i] == 1001) {
                        b++;
                    }
                    if (a>=2) {
                      if (gameBoard[i][j] == 1001) {
                        printf("Computer activated \"Over write opponent's mark\"!\n");
                        gameBoard[i][j] = 1002;
                        printGameBoard(gameBoard);
                        overwriteP2 = 1;
                        skipB++;
                      }
                    }
                    if (b>=2) {
                      if (gameBoard[j][i] == 1001) {
                        printf("Computer activated \"Over write opponent's mark\"!\n");
                        gameBoard[j][i] = 1002;
                        printGameBoard(gameBoard);
                        overwriteP2 = 1;
                        skipB++;
                      }
                    }
                }
            }
            a = 0;
            for (i=0,j=0;(i<=2)&&(j<=2)&&(skipB==0);i++,j++) {
                if (gameBoard[i][j] == 1001) {
                    a++;
                }
                if (a>=2) {
                    if (gameBoard[i][j] == 1001) {
                        printf("Computer activated \"Over write opponent's mark\"!\n");
                        gameBoard[i][j] = 1002;
                        printGameBoard(gameBoard);
                        overwriteP2 = 1;
                        skipB++;
                    }
                }
            }
            a = 0;
            for (i=0,j=2;(i<=2)&&(j>=0)&&(skipB==0);i++,j--) {
                if (gameBoard[i][j] == 1001) {
                    a++;
                }
                if (a>=2) {
                    if (gameBoard[i][j] == 1001) {
                        printf("Computer activated \"Over write opponent's mark\"!\n");
                        gameBoard[i][j] = 1002;
                        printGameBoard(gameBoard);
                        overwriteP2 = 1;
                        skipB++;
                    }
                }
            }
        }
        if (skipB == 0) {
            printf("Computer places the mark:\n");
            placeMarkByComputerPlayer(gameBoard, CROSS, difficulty);
            printGameBoard(gameBoard);
        } else {
            skipB = 0;
        }
    }

    gameEnds = isFull(gameBoard);
    winner = hasWinner(gameBoard);
    if ((gameEnds != 0)||(winner == 1)) {
      break;
    }
    }

    if (winner == 1) {
      if (currentPlayer == 1) {
      printf("Player 1 win! Congratulations!\n");
      if (numOfHumanPlayers == 1) {
        win[difficulty-1]++;
      }
      } else if (currentPlayer == 2) {
        if (numOfHumanPlayers == 2) {
          printf("Player 2 win! Congratulations!\n");
        } else {
          printf("Computer wins!\n");
          lose[difficulty-1]++;
        }
      }
    } else {
      printf("Draw game!\n");
      if (numOfHumanPlayers == 1) {
        tie[difficulty-1]++;
      }
    }
    if (numOfHumanPlayers == 1) {
        games[difficulty-1]++;
    }

    fptr = fopen("data.txt","w");
    fprintf(fptr,"%d\n",tmpfirst);
    fprintf(fptr,"%d\n",difficulty);
    fprintf(fptr,"%d\n",turnaround);
    fprintf(fptr,"%d\n",overwrite);
    for (i=0;i<=2;i++) {
        fprintf(fptr,"%d\n",win[i]);
        fprintf(fptr,"%d\n",lose[i]);
        fprintf(fptr,"%d\n",tie[i]);
        fprintf(fptr,"%d\n",games[i]);
    }
    fclose(fptr);
    return 0;
}
