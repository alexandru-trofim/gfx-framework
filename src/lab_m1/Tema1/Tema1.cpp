#include "lab_m1/lab3/lab3.h"
#include "Tema1.h"
#include "Attacker.h"
#include "Enemy.h"
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
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


     attacker =  new Attacker("Ceburek", glm::vec3(300, 300, 0), glm::vec3(0,1,1));
     star=  new Star("Ceburek1",  glm::vec3(100, 100, 0), glm::vec3(1,0,1));
    enemy =  new Enemy("Ceburek2",  glm::vec3(300, 200, 0), glm::vec3(0.3,0.5,1));
    enemy1 =  new Enemy("Ceburek3",  glm::vec3(300, 200, 0.1), glm::vec3(1,0.5,1));
    enemy1->scale = enemy->scale * 0.7;
    enemy1->translateToCurr();
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
    RenderMesh2D(attacker->getMesh(), shaders["VertexColor"], attacker->getModelMatrix());
    RenderMesh2D(star->mesh, shaders["VertexColor"], star->modelMatrix);

    glm::vec3 newPos = glm::vec3(enemy1->position);
    newPos.x += 320 * deltaTimeSeconds;
    enemy1->setPosition(newPos);
    enemy->setPosition(newPos);
    glm::mat3 modelForSmallerHexa = glm::mat3(1);
    modelMatrix *= transform2D::Translate(enemy1->center.x + enemy1->position.x ,enemy1->center.y + enemy1->position.y);
    modelMatrix *= transform2D::Scale(enemy1->scale * 0.8f,enemy1->scale * 0.8f);
    modelMatrix *= transform2D::Translate( -enemy1->center.x - enemy1->position.x ,-enemy1->center.y - enemy1->position.y);
    RenderMesh2D(enemy1->mesh1, shaders["VertexColor"], enemy1->modelMatrix);
    RenderMesh2D(enemy->mesh2, shaders["VertexColor"], enemy->modelMatrix);

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
