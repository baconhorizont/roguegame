#include "GameEngine.hpp"
#include <iostream>
#include <windows.h>



namespace game
{
#define IS_PRESSED 0x8000

using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timeStep(50ms);

    int GameEngine::run()
    {
        init();
        gameLoop();
        return finish();
    }

    void GameEngine::init()
    {
        currentTime = std::chrono::high_resolution_clock::now();
    }
    void GameEngine::gameLoop()
    {
        std::chrono::nanoseconds lag(0ns);
        while (!quit)
        {
            auto deltaTime = std::chrono::high_resolution_clock::now() - currentTime;
            currentTime = std::chrono::high_resolution_clock::now();
            lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

            while (lag >= timeStep)
            {
                lag -= timeStep;
                handleInput();
                update();
                render();
            }
            
            
        }
    }
    void GameEngine::handleInput()
    {
        if(GetKeyState('W') & IS_PRESSED)
        {
            --y;
            isStateChanged = true;
        }
        else if(GetKeyState('S') & IS_PRESSED)
        {
            ++y;
            isStateChanged = true;
        }
        else if(GetKeyState('A') & IS_PRESSED)
        {
            --x;
            isStateChanged = true;
        }
        else if(GetKeyState('D') & IS_PRESSED)
        {
            ++x;
            isStateChanged = true;
        }
        else if(GetKeyState('Q') & IS_PRESSED)
        {
            quit = true;
        }
    }
    void GameEngine::update()
    {
    }
    void GameEngine::render()
    {
        if(!isStateChanged){
            return;
        }

        system("cls");

        for(int height = 0; height < y-1; ++height)
        {
            std::cout << std::endl;
        }
        for(int widht = 0; widht < x-1; ++widht)
        {
            std::cout << " ";
        }
        std::cout << "@";
        std::cout << std::endl;
        isStateChanged = false;
    }

    int GameEngine::finish()
    {
        return 0;
    }

}
