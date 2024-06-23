/*
###########Members List###################
#                                        #
#    Name                      ID        #
# 1. Birtukan Adis          UGR/5759/13  #
# 2. Newal Yimam            UGR/9108/14  #
# 3. Yigerem Bisrat         UGR/5026/14  #
# 4. Yodahe Gosa            UGR/9595/14  #
# 5. Yohannes Belay         UGR/4223/14  #
##########################################
*/


#include <GL/glut.h>
#include <iostream>
#include <math.h>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
bool playerTurn = true; // true for player 'X', false for player 'O'

void drawBoard() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the grid
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(200.0f, 0.0f);
    glVertex2f(200.0f, 600.0f);
    glVertex2f(400.0f, 0.0f);
    glVertex2f(400.0f, 600.0f);
    glVertex2f(0.0f, 200.0f);
    glVertex2f(600.0f, 200.0f);
    glVertex2f(0.0f, 400.0f);
    glVertex2f(600.0f, 400.0f);
    glEnd();

    // Draw the pieces
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 'X') {
                glBegin(GL_LINES);
                glVertex2f(j * 200 + 20, i * 200 + 20);
                glVertex2f((j + 1) * 200 - 20, (i + 1) * 200 - 20);
                glVertex2f((j + 1) * 200 - 20, i * 200 + 20);
                glVertex2f(j * 200 + 20, (i + 1) * 200 - 20);
                glEnd();
            } else if (board[i][j] == 'O') {
                glBegin(GL_LINE_LOOP);
                for (int k = 0; k < 360; ++k) {
                    float angle = k * 3.14159f / 180;
                    glVertex2f((j * 200 + 100) + cos(angle) * 80, (i * 200 + 100) + sin(angle) * 80);
                }
                glEnd();
            }
        }
    }

    glutSwapBuffers();
}

bool checkWin(char player) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

void checkGameState() {
    if (checkWin('X')) {
        std::cout << "Player X wins!" << std::endl;
        exit(0);
    } else if (checkWin('O')) {
        std::cout << "Player O wins!" << std::endl;
        exit(0);
    } else {
        bool draw = true;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    draw = false;
                }
            }
        }
        if (draw) {
            std::cout << "The game is a draw!" << std::endl;
            exit(0);
        }
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int row = y / 200;
        int col = x / 200;
        if (board[row][col] == ' ') {
            board[row][col] = playerTurn ? 'X' : 'O';
            playerTurn = !playerTurn;
            checkGameState();
            glutPostRedisplay();
        }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 600.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Tic-Tac-Toe");
    init();
    glutDisplayFunc(drawBoard);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}

