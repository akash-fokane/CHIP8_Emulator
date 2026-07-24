#include <iostream>
#include <chrono>
#include "raylib.h"
#include "chip8.hpp"

int SCALE = 5;
int DELAY = 1;

int keymap[16] = {
    KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, 
    KEY_Q, KEY_W, KEY_E, KEY_R, 
    KEY_A, KEY_S, KEY_D, KEY_F, 
    KEY_Z, KEY_X, KEY_C, KEY_V};

int main(int argc, char* argv[])
{
    if(argc!=4)
    {
        std::cerr << "Usage:" << argv[0] << "<SCALE> <DELAY> <ROM>\n";
        std::exit(0);
    }

    SCALE = std::stoi(argv[1]);
    DELAY = std::stoi(argv[2]);
    char const *rom = argv[3];

    InitWindow(VIDEO_WIDTH * SCALE, VIDEO_HEIGHT * SCALE, "CHIP-8 EMULATOR");
    SetTargetFPS(60); 

    Chip8 chip8;
    chip8.loadROM(rom);

    auto LastTime = std::chrono::high_resolution_clock::now();
    //user input and update logic
    while(!WindowShouldClose())
    {
        for (auto i = 0; i < 16; i++)
        {
            chip8.keypad[i] = IsKeyDown(keymap[i]);
        }

        auto CurrentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::milli>(CurrentTime - LastTime).count();

        if(dt > DELAY)
        {
            LastTime = CurrentTime;

            chip8.Cycle();

            BeginDrawing();
		    ClearBackground(BLACK);

            // DrawText("Hello AKASH", 200,20,25,BEIGE);
            // draw some text using the default font
            
            for (int y = 0; y < 32; y++)
            {
                for (int x = 0; x < 64; x++)
                {
                    if (chip8.video[y * 64 + x])
                    {
                        DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, WHITE);
                    }
                }
            }
            EndDrawing();
        }
    }
    
    CloseWindow();
    return 0;
}