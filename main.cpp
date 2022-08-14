#include <Windows.h>

#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <random>
#include <time.h>

using namespace std;


static int WINDOW_WIDTH = 640;
static int WINDOW_HEIGHT = 480;

static unsigned int player_score = 0;
static unsigned int cpu_score = 0;
static unsigned int stage = 1;

static unsigned int speed = 5;

float r, g, b = 0.0;

bool gameOver = false;
bool pause = false;

int counter = 0;

struct Point {
    float x;
    float y;
};

static bool _left = true;
static bool _down = true;

// Player's rectangle bar
Point r1 = { 0.0, 5.0 };
Point r2 = { 100.0, 15.0 };

// The bouncing square, outside boundry
Point s1 = { 600.0, 400.0 };
Point s2 = { 620.0, 420.0 };

void init(); // Initialize
void display(); // displays the entire screen with orthographic view
std::string score(std::string s, unsigned int score); // returns the string with score concatenated
void passiveMotion(int x, int y); // This function is activated when mouse moves without any button held.
void moveSquare(); // moves the ball every frame 
void specialKeys(int key, int x, int y); // handling special keys for restart
void pauseKey(unsigned char key, int x, int y); // handles normal keys
void Restart();
void ChangeToRandomColor(); // changes color value r g b which handles background color



int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the mode to draw in.
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set the window size in screen pixels.
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
        (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2); // Set the window position in screen pixels.
    glutCreateWindow("Pong_CS4300"); 

    // Initialize
    r = 0.0;
    g = 0.0;
    b = 0.0;
    gameOver = false;
    init();
    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion); // handling mouse input
    glutIdleFunc(moveSquare); // moves the ball every frame
    glutKeyboardFunc(pauseKey);
    glutSpecialFunc(specialKeys); //handles key event 
    glutMainLoop(); // main event loop
    return 0;
}

void pauseKey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Escape key
        pause = !pause;
        break;
    }
}

void Restart() {
    speed = 5;
    stage = 1;
    player_score = 0;
    r = 0;
    g = 0;
    b = 0;
    gameOver = false;
}
 //handles keyboard interaction
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:    // F1: Restart
        if (gameOver)
            Restart();
        break;
    }
}




std::string score(std::string s, unsigned int score) {
    std::stringstream ss;
    ss << s << score;
    std::string str = ss.str();
    return str;
}

// returns rgb value between 0 and 1
void ChangeToRandomColor() {
    srand((unsigned)time(NULL));
    r = (float) rand() / RAND_MAX;
    g = (float) rand() / RAND_MAX;
    b = (float) rand() / RAND_MAX;
}

// background
void init() {
    //cout << "r " << r << " g " << g << " b " << b << endl;
    glClearColor((float)r, (float)g, (float)b, 1.0); // Set clear color to black
    glMatrixMode(GL_PROJECTION); // Projection matrix, applies subsequent matrix operations 
    glLoadIdentity(); // Set current matrix to identity matrix
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0); // orthographic mode
    glMatrixMode(GL_MODELVIEW); // Model view matrix
    glLoadIdentity(); // Set current matrix to identity matrix
}

void draw_ball() 
{
    glColor3ub(255, 255, 255); // Set color state to white
    glRectf(s1.x, s1.y, s2.x, s2.y);
}

// basic setup
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear buffer to clear color (black)

    glPushMatrix(); // Remember where you are
    glColor3ub(128, 128, 255); // Set color state to white
    glRectf(r1.x, r1.y, r2.x, r2.y);
    glPopMatrix();

    //TODO: draw the small square
    glPushMatrix(); // Remember where you are
    draw_ball();
    glPopMatrix();

    // Draw scoreboard
    // Human's score
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(10, 460);
    std::string human = score("Human's Score: ", player_score);
    for (unsigned int i = 0; i < human.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, human[i]);
    }

    // stage number
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(240, 460);
    std::string stages = score("Stage: ", stage);
    for (unsigned int i = 0; i < stages.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, stages[i]);
    }

    // necessary for displaying texts on screen
    glutSwapBuffers();
}


void passiveMotion(int x, int y) {
    // Change axis
    int cursor_x = x;
    if (cursor_x >= 50 && cursor_x <= 590) {
        r1.x = cursor_x - 50;
        r2.x = cursor_x + 50;
    }
}


// calculates the bounce
void moveSquare() {
    init();
    Sleep((int)(1000 / 60));
    if (gameOver)
    {
        // stops the screen 
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT/2);
        std::string gameOverMsg = "Game Over! You Scored "+ to_string(player_score)+". Press F1 to restart. ";
        for (unsigned int i = 0; i < gameOverMsg.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, gameOverMsg[i]);
        }
        glutSwapBuffers();
        return;
    }
    if (pause) {
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
        std::string pauseMSG = "Game Paused!";
        for (unsigned int i = 0; i < pauseMSG.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, pauseMSG[i]);
        }
        glutSwapBuffers();
        return;
    }
    if (_left) {
        s1.x -= speed;
        s2.x -= speed;
    }
    else {
        s1.x += speed;
        s2.x += speed;
    }
    // handles down movement
    if (_down) {
        if (abs(s1.y - r2.y) <= 5.0 && ((s1.x + s2.x) / 2) < r2.x + 20 && ((s1.x + s2.x) / 2) > r1.x - 20) {
            player_score++;
            stage += 1;
            speed += 1;
            ChangeToRandomColor();
            init();
            _down = false;
        }
        else {
            s1.y -= speed;
            s2.y -= speed;
        }
    }
    else {
        s1.y += speed;
        s2.y += speed;
    }

    
    if (_left && s1.x <= 0) {
        _left = false;
    }
    else if (!_left && s2.x >= 640) {
        _left = true;
    }
    // when the ball hits the ground
    if (_down && s1.y <= 0) {
        _down = false;
        cpu_score++;
        gameOver = true;
    }
    else if (!_down && s2.y >= 480) {
        _down = true;
    }

    
    glutPostRedisplay(); // Call display
}