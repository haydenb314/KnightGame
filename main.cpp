#include <iostream>
#include "raylib.h"

int main() {

    InitWindow(1600, 900, "Knight Game");
    SetTargetFPS(60);

    Texture2D knightSheet = LoadTexture("CMakeFiles/knight_sheet.png");

    //heights
    const float frameWidth = static_cast<float>(knightSheet.width) / 12;
    float frameHeight = static_cast<float>(knightSheet.height) / 30;

    float currentFrameWidth = frameWidth;
    float flippedFrameWidth = -frameWidth;

    float attackHeight = 0;
    float attack2Height = knightSheet.height - (frameHeight * 28);
    float idleHeight = knightSheet.height - (frameHeight * 14);
    float runHeight = knightSheet.height - (frameHeight * 10);

    float timer = 0.f;

    //frames
    int frameAttack = 0;
    int maxFramesAttack = 4;

    int frameAttack2 = 0;
    int maxFramesAttack2 = 6;

    int frameIdle = 0;
    int maxFramesIdle = 10;

    int frameRun = 0;
    int maxFramesRun = 10;

    float frameAnimation = frameIdle;
    float animationHeight = idleHeight;

    float currentX = 0;
    float currentY = 0;


    float originX = frameWidth / 2;
    float originY = frameHeight / 2;


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(PURPLE);

        timer += GetFrameTime();

        if (timer >= 0.2f) {
            timer = 0.0f;
            frameAttack += 1;
            frameAttack2 += 1;
            frameIdle += 1;
            frameRun += 1;
        }

        frameAttack = frameAttack % maxFramesAttack;
        frameAttack2 = frameAttack2 % maxFramesAttack2;
        frameIdle = frameIdle % maxFramesIdle;
        frameRun = frameRun % maxFramesRun;


        if (IsKeyDown(KEY_D)) {
            currentFrameWidth = frameWidth;
            frameAnimation = frameRun;
            animationHeight = runHeight;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                currentX += 10;
            } else {
                currentX += 5;
            }
        } else if (IsKeyDown(KEY_A)) {
            currentFrameWidth = flippedFrameWidth;
            frameAnimation = frameRun;
            animationHeight = runHeight;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                currentX -= 10;
            } else {
                currentX -= 5;
            }
        } else if (IsKeyPressed(KEY_G)) {
            frameAnimation = frameAttack2;
            animationHeight = attack2Height;
        } else if (IsKeyDown(KEY_H)) {
            frameAnimation = frameAttack;
            animationHeight = attackHeight;
        } else {
            frameAnimation = frameIdle;
            animationHeight = idleHeight;
        }

        DrawTexturePro(
            knightSheet,
            Rectangle{ frameWidth * frameAnimation, animationHeight, currentFrameWidth, frameHeight },
            Rectangle{ currentX, currentY, frameWidth * 5, frameHeight * 5},
            Vector2{originX, originY},
            0.f,
            WHITE);



        EndDrawing();

    }

    UnloadTexture(knightSheet);

}