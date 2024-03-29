#include "GameEngine.hpp"
#include <iostream>
#include <sstream>
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
        if (x == 0)
        {
            x += 1;
        }
        else if (x == map.width - 1)
        {
            x -= 1;
        }

        if (y == 0)
        {
            y += 1;
        }
        else if (y == map.height - 1)
        {
            y -= 1;
        }

        if (currentGameState == GameStateEnum::PLAY && x == map.end.x && y == map.end.y)
        {
            currentGameState = GameStateEnum::WIN;
            isStateChanged = true;
        }
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
            std::stringstream ss;
            for (int height = 0; height < map.height; ++height)
            {
                for (int width = 0; width < map.width; ++width)
                {
                    if (height == 0 || height == map.height - 1 || width == 0 || width == map.width - 1)
                    {
                        ss << "#";
                    }
                    else if (height == y && width == x)
                    {
                        ss << "@";
                    }
                    else if (height == map.end.y && width == map.end.x)
                    {
                        ss << "x";
                    }
                    else
                    {
                        ss << " ";
                    }
                }
                ss << std::endl;
            }
            std::cout << ss.str();
        }

        else if (currentGameState == GameStateEnum::START)
        {
            system("cls");
            std::cout << "Press SPACE to play." << std::endl;
        }
        else if (currentGameState == GameStateEnum::WIN)
        {
            system("cls");
            std::cout << "Nyertel MO!" << std::endl;
        }
        isStateChanged = false;
    }

    int GameEngine::finish()
    {
        return 0;
    }

}
