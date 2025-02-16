#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#define MAX_VELOCITY 1000
#define MIN_VELOCITY -1000

struct Square {
    float x, y;
    float vx, vy;
    float size;
    bool isJumping;
};

void handleInput(Square &square, float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) {
        square.vx -= 200 * deltaTime;
        if (square.vx < MIN_VELOCITY){
            square.vx = MIN_VELOCITY;
        }
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        square.vx += 200 * deltaTime;
        if (square.vx > MAX_VELOCITY){
            square.vx = MAX_VELOCITY;
        }
    }
    if (state[SDL_SCANCODE_UP] && !square.isJumping) {
        square.vy = -300; 
        square.isJumping = true;
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Gravity Square", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Square square = { 400, 300, 0, 0, 50, 0 };
    const float gravity = 500.0f;
    Uint32 lastTime = SDL_GetTicks();

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        handleInput(square, deltaTime);

        square.vy += gravity * deltaTime;

        square.x += square.vx * deltaTime;
        square.y += square.vy * deltaTime;

        if (square.y + square.size > 600) {
            square.y = 600 - square.size;
            square.vy = 0;
            square.isJumping = false;
        }

        if (square.x < 0) {
            square.x = 0;
            square.vx = 0;
        }
        if (square.x + square.size > 800) {
            square.x = 800 - square.size;
            square.vx = 0;
        }
        if (square.y < 0) {
            square.y = 0;
            square.vy = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_Rect rect = { static_cast<int>(square.x), static_cast<int>(square.y), static_cast<int>(square.size), static_cast<int>(square.size) };
        SDL_Point center = { static_cast<int>(square.size / 2), static_cast<int>(square.size / 2) };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
