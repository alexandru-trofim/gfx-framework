#include "lab_m1/lab3/lab3.h"
#include "Tema1.h"
#include "Hero.h"
#include "Enemy.h"
#include "Heart.h"
#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    /* Camera Initialization*/
    nrOfLives = 5;
    nrOfStars = 8;
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


//    enemy1->scale = enemy->scale * 0.7;
//    enemy1->translateToCurr();
//    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    renderScene();
//
//    RenderMesh2D(attacker->getMesh(), shaders["VertexColor"], attacker->getModelMatrix());
//    RenderMesh2D(star->mesh, shaders["VertexColor"], star->modelMatrix);
//
//    glm::vec3 newPos = glm::vec3(enemy->position);
//    newPos.x += 100 * deltaTimeSeconds;
//    enemy->setPosition(newPos);
//    renderEnemy(enemy);

    /*Draw the hearts*/
    Heart* heart = new Heart("heart", glm::vec3(500, 500, 0), glm::vec3(1, 0, 0));
    heart->setScale(4.8f);
    heart->translateToCurr();
    for (int i = 0; i < nrOfLives; ++i) {
        glm::vec3 pos = glm::vec3(660 + i * 100, 670, 0);
        heart->setPosition(pos);
        RenderMesh2D(heart->getMesh(), shaders["VertexColor"], heart->getModelMatrix());
    }

    /*Draw the stars*/
    Star* star= new Star("star", glm::vec3(500, 500, 0), glm::vec3(0.61f, 0.61f, 0.61f));
    star->setScale(1.4f);
    star->translateToCurr();
    for (int i = 0; i < nrOfStars; ++i) {
        glm::vec3 pos = glm::vec3(640 + i * 50, 580, 0);
        star->setPosition(pos);
        RenderMesh2D(star->getMesh(), shaders["VertexColor"], star->getModelMatrix());
    }

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

/*Renders the enemy itself, with a smaller enemy inside of it*/
void Tema1::renderEnemy(Enemy* enemy1) {
    Enemy* secondaryEnemy = new Enemy("Ceburek1232",  enemy1->position, glm::vec3(1,0.5,1));
    secondaryEnemy->scale = enemy1->scale * 0.7;
    secondaryEnemy->translateToCurr();

    RenderMesh2D(secondaryEnemy->mesh1, shaders["VertexColor"], secondaryEnemy->modelMatrix);
    RenderMesh2D(enemy1->mesh1, shaders["VertexColor"], enemy1->modelMatrix);
}

void Tema1::renderScene() {
    //Create square
    float paddingBottom = 40;
    float length = 120;

    /*Draw the 9 squares*/
    Mesh* square = object2D::CreateSquare("square_for_scene",
                                          glm::vec3(0, 0, 0),
                                          length,
                                          glm::vec3(0.031f, 0.792f, 0.82f),
                                          true
                                          );

    translateX = 70;
    translateY = paddingBottom;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(translateX, translateY);
            RenderMesh2D(square, shaders["VertexColor"], modelMatrix);
            translateX += 150;
        }
        translateX = 70;
        translateY += 150;
    }

    /*Draw the finish line*/
    translateX = 20;
    translateY = paddingBottom;
    length = 25;
    square = object2D::CreateSquare("square_for_scene",
                                          glm::vec3(0, 0, 0),
                                          length,
                                          glm::vec3(1, 0.412f, 0.38f),
                                          true
    );
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(15, paddingBottom);
    modelMatrix *= transform2D::Scale(1.5f , 16.8f);
    RenderMesh2D(square, shaders["VertexColor"], modelMatrix);

    /*Draw top menu bar*/
    length = 120;
    square = object2D::CreateSquare("square_for_scene",
                                          glm::vec3(0, 0, 0),
                                          length,
                                          glm::vec3(0.62f, 0.62f, 0.62f),
                                          false
    );

    translateX = 30;
    translateY = 570;
    Star* star = new Star("attacker1", glm::vec3(30, 570, 0.2), glm::vec3(0.61f, 0.61f, 0.61f));
    star->setScale(0.8f);
    vector<Hero*> heroes;
    Hero* hero = new Hero("attacker1", glm::vec3(30, 570, 0.2), glm::vec3(0.259f, 0.839f, 0.643f));
    heroes.push_back(hero);
    hero = new Hero("attacker2", glm::vec3(30, 570, 0.2), glm::vec3(0.973f, 0.953f, 0.553f));
    heroes.push_back(hero);
    hero = new Hero("attacker3", glm::vec3(30, 570, 0.2), glm::vec3(1, 0.706f, 0.502f));
    heroes.push_back(hero);
    hero = new Hero("attacker4", glm::vec3(30, 570, 0.2), glm::vec3(0.78f, 0.502f, 0.91f));
    heroes.push_back(hero);

    for(int i = 0; i < 4; ++i) {
        //Add square
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        RenderMesh2D(square, shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX + length / 2, translateY + length / 2);
        glm::vec3 newPos = glm::vec3(translateX + length / 2, translateY + length / 2, 0);
        heroes[i]->setPosition(newPos);
        heroes[i]->setScale(0.8f);
        heroes[i]->translateToCurr();
        RenderMesh2D(heroes[i]->getMesh(), shaders["VertexColor"], heroes[i]->getModelMatrix());


        /*price of each hero*/
        float posX = 38 + i * 150;
        float posY = 550;
        for (int j = 0; j < i + 1; j++) {
            glm::vec3 pos = glm::vec3(posX + j * 30, posY, 0);
            star->setPosition(pos);
            RenderMesh2D(star->getMesh(), shaders["VertexColor"], star->getModelMatrix());
        }
        translateX += 150;
    }

}
