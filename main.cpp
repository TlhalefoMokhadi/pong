#include <raylib.h>

#include "header/Ball.h"
#include "header/Paddle.h"

// Definitions not in raylib
//--------------------------------------------------------------------------------------

#define EMERALD        \
    (Color)            \
    {                  \
        1, 96, 75, 255 \
    }
bool collisonDetection(const Ball &ball, const Paddle &paddle);
//--------------------------------------------------------------------------------------

int main()
{
    // Window Initialisation
    //----------------------------------------------------------------------------------
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 800;

    Image icon = LoadImage("resource/icon.png");
    SetWindowIcon(icon);

    InitWindow((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, "Pong-Ping");
    InitAudioDevice(); // Will be used to play our sounds
    if (!IsAudioDeviceReady())
        InitAudioDevice();
    SetTargetFPS(60);
   
    //----------------------------------------------------------------------------------

    // Game Object Initialisation
    //-----------------------------------------------------------------------------------
    Ball ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0, 15.0f, WHITE);                  // ping pong ball
    Paddle paddle1((Vector2){25.f, WINDOW_HEIGHT / 2.0f - (100 / 2.0f)});                // player one
    Paddle paddle2((Vector2){WINDOW_WIDTH - 25.f, WINDOW_HEIGHT / 2.0f - (100 / 2.0f)}); // player two

    Font font = LoadFontEx("resource/font/pixelplay.ttf", 64, 0, 250);
    int player1Score = 0, player2Score = 0;

    Sound fxWallHit = LoadSound("resource/sound/wallHit.wav");
    Sound fxPaddelHit = LoadSound("resource/sound/paddleHit.wav");

    bool isPause=false;
    int frameCount=0;
    //----------------------------------------------------------------------------------

    // Main Game Loop
    while (!WindowShouldClose())
    {
      //Creating an instance of pausing the game 
      if(IsKeyPressed(KEY_P))
        isPause=!isPause;

      frameCount++; 
      BeginDrawing();
      ClearBackground(BLACK);
      DrawFPS(10, 10);

        // Draw the net at the half-way mark of the game
        for (int y = 0; y < WINDOW_HEIGHT; y++)
            if (y % 5)
                DrawPixel(WINDOW_WIDTH / 2, y, WHITE);

        // Drawing the game paddles
        DrawRectangleV((Vector2){paddle1.getRect().x, paddle1.getRect().y},
                       (Vector2){paddle1.getRect().width, paddle1.getRect().height},
                       RED);
        DrawRectangleV((Vector2){paddle2.getRect().x, paddle2.getRect().y},
                       (Vector2){paddle2.getRect().width, paddle2.getRect().height},
                       BLUE);

        // Drawing the score-board
        DrawTextEx(font, TextFormat("%i", player1Score), (Vector2){WINDOW_WIDTH / 4.0f, 20.0f}, (float)font.baseSize, 2, LIME);
        DrawTextEx(font, TextFormat("%i", player2Score), (Vector2){3 * WINDOW_WIDTH / 4.0f, 20.0f}, (float)font.baseSize, 2, LIME); // player2
        
      DrawCircle(ball.getX(),ball.getY(),ball.getRad(),ball.getColor());    

      if(isPause==false)
    {
        // Starts to move the balls
        if (IsKeyPressed(KEY_SPACE))
        {
            ball.setSpeedX(10);
            ball.setSpeedY(10);
        }

        ball.incrementSpeedX();
        ball.incrementSpeedY();

        // Collision detection
        //----------------------------------------------------------------------------------

        if (ball.getX() + ball.getRad() >= WINDOW_WIDTH)
        {
            // resseting the ball and ball speed
            ball.reset(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            PlaySound(fxWallHit);

            player1Score++;
        }

        else if (ball.getX() - ball.getRad() <= 0)
        {
            // resseting the ball and ball speed
            ball.reset(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            PlaySound(fxWallHit);

            player2Score++;
        }

        if (ball.getY() + ball.getRad() >= WINDOW_HEIGHT || ball.getY() - ball.getRad() <= 0)
            ball.reverseSpeedY();

        if (collisonDetection(ball, paddle1) || collisonDetection(ball, paddle2))
        {
            ball.reverseSpeed();
            PlaySound(fxPaddelHit);
        }

        //----------------------------------------------------------------------------------

        // Controls for paddle movements
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_W))
            paddle1.moveUP();

        if (IsKeyDown(KEY_S))
            paddle1.moveDown(WINDOW_HEIGHT);

        if (IsKeyDown(KEY_UP))
            paddle2.moveUP();

        if (IsKeyDown(KEY_DOWN))
            paddle2.moveDown(WINDOW_HEIGHT);
        
    }

    //This happens on pause to show some text about the pause text
    if(isPause && (frameCount/30)%2)
      DrawText("GAME PAUSED", (WINDOW_WIDTH/2)-100, WINDOW_HEIGHT/2, 30,GREEN);

    DrawFPS(10,10);
    EndDrawing();
  }
  

   // Deinitialisation
    //----------------------------------------------------------------------------------
    UnloadFont(font);
    UnloadSound(fxWallHit);
    UnloadSound(fxPaddelHit);
    CloseWindow();

    CloseAudioDevice();
    //----------------------------------------------------------------------------------

    return 0;
}

// Function definitions
//--------------------------------------------------------------------------------------
bool collisonDetection(const Ball &ball, const Paddle &paddle)
{
    // ball vertices
    float ballTop = static_cast<float>(ball.getY() - ball.getRad());
    float ballBottom = static_cast<float>(ball.getY() + ball.getRad());
    float ballLeft = static_cast<float>(ball.getX() - ball.getRad());
    float ballRight = static_cast<float>(ball.getX() + ball.getRad());

    // paddle vertices
    float paddleTop = static_cast<float>(paddle.getRect().y);
    float paddleBottom = static_cast<float>(paddle.getRect().y + paddle.getRect().height);
    float paddleRight = static_cast<float>(paddle.getRect().x + paddle.getRect().width);
    float paddleLeft = static_cast<float>(paddle.getRect().x);

    if (ballLeft >= paddleRight)
    {
        return false;
    }

    if (ballRight <= paddleLeft)
    {
        return false;
    }

    if (ballTop >= paddleBottom)
    {
        return false;
    }

    if (ballBottom <= paddleTop)
    {
        return false;
    }
    return true;
}
