#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    //window dimensions
    const int windowWidth{800};
    const int windowHeight{450};
    // initialize the window
    InitWindow(windowWidth, windowHeight, "Raylib Runner Game");

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1'000};

    //nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebData{ 
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, 
        {windowWidth, windowHeight - nebula.height/8}, 
        0,  
        1.0/12.0, 
        0
    };

    AnimData neb2Data{ 
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, 
        {windowWidth + 300, windowHeight - nebula.height/8}, 
        0,  
        1.0/16.0, 
        0
    };

    //nebula x velocity (pixels/sec)
    int nebVel{-200};

    //scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.x = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    bool isInAir{false};
    const int jumpVel{-600};

    int velocity{0};


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        const float dT{GetFrameTime()};

        scarfyData.runningTime += dT;
        nebData.runningTime += dT;

        if (!isInAir)
        {

            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame ++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }

        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame ++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        //start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //update nebula position
        nebData.pos.x += nebVel * dT;

        neb2Data.pos.x += nebVel * dT;

        //update scarfy position
        scarfyData.rec.y += velocity * dT;

        //perform ground check
        if (scarfyData.rec.y >= windowHeight - scarfyData.rec.height)
        {
            //rectangle is one the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is int the air
            velocity += gravity * dT;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        //draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        //draw 2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        //draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}