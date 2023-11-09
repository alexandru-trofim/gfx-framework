#pragma once

#include "components/simple_scene.h"
#include "Hero.h"
#include "Star.h"
#include "Enemy.h"
#include "Heart.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float translateX, translateY;
        float my_mouseX = 0;
        float my_mouseY = 0;

        int nrOfLives;
        int nrOfStars;

        int buingNow;

        float starSpawnTime;
        float MinStarSpawnTime = 0;
        float MaxStarSpawnTime = 0;

        float enemySpawnTime;
        float MinEnemySpawnTime = 0;
        float MaxEnemySpawnTime = 0;

        Hero* heroesMatrix[3][3];
        Hero* newHero;
        std::vector<Star*> spawnedStars;
        std::vector<Enemy*> spawnedEnemies[3];
        Star* starForPrice;
        Mesh* squareForScene;
        Mesh* squareForFinish;
        Mesh* squareForMenuBar;
        Heart* heart;
        Star* star;
        std::vector<Hero*> heroesForMenuBar;


        // TODO(student): If you need any other class variables, define them here.

        void renderEnemy(Enemy *enemy1);
        void renderScene();
        void setNrOfStars(int nrOfStars);
        int getNrOfStars();

        float getRandomFloatInRange(float min, float max);

        int getRandomIntInRange(int min, int max);
    };
}   // namespace m1
