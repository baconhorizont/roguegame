#include "GameEngine.hpp"
#include <iostream>
#include <windows.h>
#include "GameStateEnum.hpp"

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
        if (GetKeyState('W') & IS_PRESSED)
        {
            --y;
            isStateChanged = true;
        }
        else if (GetKeyState('S') & IS_PRESSED)
        {
            ++y;
            isStateChanged = true;
        }
        else if (GetKeyState('A') & IS_PRESSED)
        {
            --x;
            isStateChanged = true;
        }
        else if (GetKeyState('D') & IS_PRESSED)
        {
            ++x;
            isStateChanged = true;
        }
        else if (GetKeyState('Q') & IS_PRESSED)
        {
            quit = true;
        }
        else if (currentGameState == GameStateEnum::START && GetKeyState(VK_SPACE) & IS_PRESSED)
        {
            currentGameState = GameStateEnum::PLAY;
            isStateChanged = true;
        }
    }
    void GameEngine::update()
    {
    }
    void GameEngine::render()
    {
        if (!isStateChanged)
        {
            return;
        }

        if (currentGameState == GameStateEnum::PLAY)
        {
            system("cls");

            for (int height = 0; height < y - 1; ++height)
            {
                std::cout << std::endl;
            }
            for (int widht = 0; widht < x - 1; ++widht)
            {
                std::cout << " ";
            }
            std::cout << "@";
            std::cout << std::endl;
        }
        if (currentGameState == GameStateEnum::START)
        {
            system("cls");
            std::cout << "Press SPACE to play." << std::endl;
        }
        isStateChanged = false;
    }

    int GameEngine::finish()
    {
        return 0;
    }

}
