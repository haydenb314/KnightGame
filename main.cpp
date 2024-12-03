#include <iostream>
#include "raylib.h"

void playAnimation() {

}

int main() {

    InitWindow(1600, 900, "Knight Game");
    SetTargetFPS(60);

    Texture2D knightSheet = LoadTexture("CMakeFiles/knight_sheet.png");

    //dimensions of a singular frame
    const float frameWidth = static_cast<float>(knightSheet.width) / 12;
    float frameHeight = static_cast<float>(knightSheet.height) / 30;

    //flips knight animation when moving backwards
    float currentFrameWidth = frameWidth;
    float flippedFrameWidth = -frameWidth;

    //timer
    float timer = 0.f;

    //frames
    int frame = 0;
    int currentMaxFrames;

    //structure to hold animation max frames + rectangle
    struct AnimationStruct {
        float animationHeight;
        int maxFrames;
    };

    AnimationStruct attackAnimation;
    attackAnimation.animationHeight = 0;
    attackAnimation.maxFrames = 4;

    AnimationStruct attack2Animation;
    attack2Animation.animationHeight = knightSheet.height - (frameHeight * 28);
    attack2Animation.maxFrames = 6;

    AnimationStruct idleAnimation;
    idleAnimation.animationHeight = knightSheet.height - (frameHeight * 14);
    idleAnimation.maxFrames = 10;

    AnimationStruct runAnimation;
    runAnimation.animationHeight = knightSheet.height - (frameHeight * 10);
    runAnimation.maxFrames = 10;

    //source rectangle height
    float currentAnimationHeight;

    //position
    float currentX = 0;
    float currentY = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(PURPLE);

        timer += GetFrameTime();

        if (timer >= 0.2f) {
            timer = 0.0f;
            frame += 1;
        }

        frame = frame % currentMaxFrames;


        if (IsKeyDown(KEY_D)) {
            currentFrameWidth = frameWidth;
            currentAnimationHeight = runAnimation.animationHeight;
            currentMaxFrames = runAnimation.maxFrames;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                currentX += 10;
            } else {
                currentX += 5;
            }
        } else if (IsKeyDown(KEY_A)) {
            currentFrameWidth = flippedFrameWidth;
            currentAnimationHeight = runAnimation.animationHeight;
            currentMaxFrames = runAnimation.maxFrames;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                currentX -= 10;
            } else {
                currentX -= 5;
            }
        } else if (IsKeyDown(KEY_G)) {
            currentAnimationHeight = attack2Animation.animationHeight;
            currentMaxFrames = attack2Animation.maxFrames;
        } else if (IsKeyDown(KEY_H)) {
            currentAnimationHeight = attackAnimation.animationHeight;
            currentMaxFrames = attackAnimation.maxFrames;
        } else {
            currentAnimationHeight = idleAnimation.animationHeight;
            currentMaxFrames = idleAnimation.maxFrames;
        }

        DrawTexturePro(
            knightSheet,
            Rectangle{ frameWidth * frame, currentAnimationHeight, currentFrameWidth, frameHeight },
            Rectangle{ currentX, currentY, frameWidth * 5, frameHeight * 5},
            Vector2{frameWidth / 2, frameHeight / 2},
            0.f,
            WHITE);

        EndDrawing();

    }

    UnloadTexture(knightSheet);

}