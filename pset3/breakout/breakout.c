//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// brick size
#define BRICK_PADDING 5

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//height and width of paddle
#define PADDLE_WIDTH 75
#define PADDLE_HEIGHT 25

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(int argc, string argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;       
    
    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    double dX = drand48()*5;
    double dY = 2.0;
    while (lives > 0 && bricks > 0)
    {   
        //move ball     
        move(ball, dX, dY);
        //if ball is at side of window bounce
        if(getX(ball) + RADIUS >= WIDTH || getX(ball) <= 0)
        {
            dX = -dX;
        }
        //if ball at top of window bounce
        if(getY(ball) <= 0){
            dY = -dY;
        }
        //if ball at bottom of window lose life and start again
        if(getY(ball) + RADIUS >= HEIGHT){
            lives--;            
            removeGWindow(window,ball);
            ball = initBall(window);
            waitForClick();
        }
        //check for god mode 
        if(argc > 1){
            if(strcmp(argv[1],"GOD") == 0){
                if(getX(ball) < PADDLE_WIDTH/2)
                    setLocation(paddle,0,getY(paddle));
                else if(getX(ball) > WIDTH - PADDLE_WIDTH/2)
                    setLocation(paddle,WIDTH-PADDLE_WIDTH,getY(paddle));
                else
                    setLocation(paddle,getX(ball)-PADDLE_WIDTH/2,getY(paddle));
            }
        }
        else{
            //paddle movement       
            GEvent event = getNextEvent(MOUSE_EVENT);
            if(event != NULL){
                if(getEventType(event) == MOUSE_MOVED){
                    double x = getX(event) - PADDLE_WIDTH/2;
                    if(x < 0)
                        setLocation(paddle,0,getY(paddle));
                    else if (x > WIDTH-PADDLE_WIDTH)
                        setLocation(paddle,WIDTH-PADDLE_WIDTH,getY(paddle));
                    else
                        setLocation(paddle,x,getY(paddle));
                }
            }
        }
        
        //check if the ball hit something
        GObject object = detectCollision(window, ball);
        if(object != NULL){
            //if ball hits paddle bounce
            if(object == paddle){
                dY = -dY;    
            }
            //if ball hits brick, remove brick and add to score
            else if(strcmp(getType(object), "GRect") == 0){
                removeGWindow(window, object);
                bricks--;
                points += 5;
                dY = -dY;
                updateScoreboard(window, label, points);
                repaint(window);                    
            }    
        }
        //pause before continuing        
        pause(10);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{    
    double brickWidth = getWidth(window)/COLS - BRICK_PADDING;
    double brickHeight = brickWidth / 3;
    for(int j = 0; j < ROWS; j++){
        double brickY = (brickHeight + BRICK_PADDING)*j;
        for(int i = 0; i < COLS; i++){
            double brickX = (brickWidth + BRICK_PADDING)*i;            
            GRect brick = newGRect(brickX,brickY,brickWidth,brickHeight);
            setColor(brick, "GREEN");
            setFilled(brick, true);
            add(window,brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2, HEIGHT/2, RADIUS, RADIUS);    
    setFilled(ball, true);
    setColor(ball, "BLUE");
    add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double padding = 20;
    double paddleX = WIDTH/2 - PADDLE_WIDTH/2;
    double paddleY = HEIGHT - PADDLE_HEIGHT - padding;
    GRect paddle = newGRect(paddleX,paddleY,PADDLE_WIDTH,PADDLE_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "GRAY"); 
    add(window,paddle); 
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{     
    // put label at bottom left of screen
    GLabel label = newGLabel("Score"); 
    double x = 5;
    double y = HEIGHT-5;
    setLocation(label, x, y);
    add(window,label);
    return label;   
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);    
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
