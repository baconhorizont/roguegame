#pragma once
namespace game
{
    class GameEngine
    {
    public:
        int run();

    private:
        void init();

        void gameLoop();
        void handleInput();
        void update();
        void render();

        int finish();
    private:
        int x = 3;
        int y = 3;
    };
}
