#include "GameEngine.hpp"
#include <iostream>

namespace game
{
    int GameEngine::run()
    {
        init();
        gameLoop();
        return finish();
    }

    void GameEngine::init()
    {
    }
    void GameEngine::gameLoop()
    {
        render();
    }
    void GameEngine::handleInput()
    {
    }
    void GameEngine::update()
    {
    }
    void GameEngine::render()
    {
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
    }

    int GameEngine::finish()
    {
        return 0;
    }

}
