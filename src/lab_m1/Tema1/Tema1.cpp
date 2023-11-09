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
    MinStarSpawnTime = 5;
    MaxStarSpawnTime = 10;
    MinEnemySpawnTime = 5;
    MaxEnemySpawnTime = 10;
    nrOfLives = 5;
    nrOfStars = 8;
    buingNow = 0;
    newHero = nullptr;
//    testStar = nullptr;
    /* Initialize all elements to nullptr */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            heroesMatrix[i][j] = nullptr;
        }
    }

    /* Camera Initialization*/
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    /* Seed for random */
    srand (static_cast <unsigned> (time(0)));

    /* Get spawn time for Star and Enemy*/
    starSpawnTime = getRandomFloatInRange(MinStarSpawnTime, MaxStarSpawnTime);
    enemySpawnTime = getRandomFloatInRange(MinEnemySpawnTime, MaxEnemySpawnTime);

    /*Create square for tiles*/
    squareForScene = object2D::CreateSquare("square_for_scene",
                                          glm::vec3(0, 0, 0),
                                          120,
                                          glm::vec3(0.031f, 0.792f, 0.82f),
                                          true
    );
    squareForFinish = object2D::CreateSquare("square_for_scene",
                                    glm::vec3(0, 0, 0),
                                    25,
                                    glm::vec3(1, 0.412f, 0.38f),
                                    true
    );

    squareForMenuBar = object2D::CreateSquare("square_for_scene",
                                    glm::vec3(0, 0, 0),
                                    120,
                                    glm::vec3(0.62f, 0.62f, 0.62f),
                                    false
    );

    heroesForMenuBar.push_back(new Hero("attacker1", glm::vec3(30, 570, 0.2), glm::vec3(0.259f, 0.839f, 0.643f)));
    heroesForMenuBar.push_back(new Hero("attacker2", glm::vec3(30, 570, 0.2), glm::vec3(0.973f, 0.953f, 0.553f)));
    heroesForMenuBar.push_back(new Hero("attacker3", glm::vec3(30, 570, 0.2), glm::vec3(1, 0.706f, 0.502f)));
    heroesForMenuBar.push_back(new Hero("attacker4", glm::vec3(30, 570, 0.2), glm::vec3(0.78f, 0.502f, 0.91f)));

    starForPrice = new Star("attacker1", glm::vec3(30, 570, 0.2), glm::vec3(0.61f, 0.61f, 0.61f));

     star= new Star("star", glm::vec3(500, 500, 0), glm::vec3(0.61f, 0.61f, 0.61f));
     star->setScale(1.4f);
     star->translateToCurr();

     heart = new Heart("heart", glm::vec3(500, 500, 0), glm::vec3(1, 0, 0));
    heart->setScale(4.8f);
    heart->translateToCurr();

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
//    renderScene();

    /*Draw the hearts*/
    for (int i = 0; i < nrOfLives; ++i) {
        glm::vec3 pos = glm::vec3(660 + i * 100, 670, 0);
        heart->setPosition(pos);
        RenderMesh2D(heart->getMesh(), shaders["VertexColor"], heart->getModelMatrix());
    }

    /*Draw the stars*/
    for (int i = 0; i < nrOfStars; ++i) {
        glm::vec3 pos = glm::vec3(640 + i * 50, 580, 0);
        star->setPosition(pos);
        RenderMesh2D(star->getMesh(), shaders["VertexColor"], star->getModelMatrix());
    }

    /* Print the newHero which is created but not placed yet */
    if (newHero != nullptr) {
        newHero->setPosition(glm::vec3(my_mouseX, my_mouseY, 0));
        newHero->translateToCurr();
        RenderMesh2D(newHero->getMesh(), shaders["VertexColor"], newHero->getModelMatrix());
    }

    /* Draw all the heroes from the table */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (heroesMatrix[i][j] != nullptr) {
                if (heroesMatrix[i][j]->killedState == 1) {
                    if (heroesMatrix[i][j]->scale - 35 * deltaTimeSeconds  > 35 * deltaTimeSeconds) {
                        heroesMatrix[i][j]->scale -= 35 * deltaTimeSeconds;
                    } else {
                        delete heroesMatrix[i][j];
                        heroesMatrix[i][j] = nullptr;
                        continue;
                    }
                    heroesMatrix[i][j]->translateToCurr();
                }
                RenderMesh2D(heroesMatrix[i][j]->getMesh(), shaders["VertexColor"], heroesMatrix[i][j]->getModelMatrix());
            }
        }
    }

    /* Draw all the spawned stars */
    for (int i = 0; i < spawnedStars.size(); i++) {
        RenderMesh2D(spawnedStars[i]->getMesh(), shaders["VertexColor"], spawnedStars[i]->getModelMatrix());
    }

    /*Draw all enemies*/
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < spawnedEnemies[i].size(); j++) {
           Enemy* enemy = spawnedEnemies[i][j];
           glm::vec3 pos = glm::vec3(enemy->position);
           pos.x -= 45 * deltaTimeSeconds;
           if (spawnedEnemies[i][j]->killedState == 1) {
                if (spawnedEnemies[i][j]->scale - 35 * deltaTimeSeconds  > 35 * deltaTimeSeconds) {
                    spawnedEnemies[i][j]->scale -= 35 * deltaTimeSeconds;
                } else {
                    delete spawnedEnemies[i][j];
                    spawnedEnemies[i].erase(spawnedEnemies[i].begin() + j);
                    j--;
                    continue;
                }
                spawnedEnemies[i][j]->translateToCurr();
           }
           enemy->setPosition(pos);
           renderEnemy(enemy);

        }
    }

    /* Spawn new stars at a random interval of time */
    starSpawnTime -= deltaTimeSeconds;
    if(starSpawnTime <= 0)
    {
        /*Create new random coordinates*/
        float newX = getRandomFloatInRange(500, 1250);
        float newY = getRandomFloatInRange(0, 570);
        /* Create a star with random coordinates and add it to the stars vector */
        Star* newStar = new Star("new_star", glm::vec3(newX, newY, 0), glm::vec3(0.616f, 0.58f, 1));
        newStar->setScale(2);
        newStar->translateToCurr();

        spawnedStars.push_back(newStar);
        /*Reset the new star Spawn time*/
        starSpawnTime = getRandomFloatInRange(MinStarSpawnTime, MaxStarSpawnTime);
    }

    /* Spawn new enemies at a random interval of time */
    enemySpawnTime -= deltaTimeSeconds;
    if(enemySpawnTime <= 0)
    {
        /*Create new random coordinates*/
        int row = getRandomIntInRange(0, 2);
        cout << "row" << row << endl;
        int type = getRandomIntInRange(0,3);
        float x = 1200;
        float y = 100.0f + row * 150.0f;
        /* Create a star with random coordinates and add it to the stars vector */
        Enemy* newEnemy = new Enemy("enemy", glm::vec3(x, y, 0), type);

        spawnedEnemies[row].push_back(newEnemy);
        /*Reset the new star Spawn time*/
        enemySpawnTime= getRandomFloatInRange(MinEnemySpawnTime, MaxEnemySpawnTime);
    }

    /*Iterate through all to check what projectiles to launch*/
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (heroesMatrix[i][j] != nullptr) {
                int isHeroShooting = false;
                /*Check if the hero is Shooting*/
                for(int k = 0; k < spawnedEnemies[i].size(); k++) {
                    if (heroesMatrix[i][j]->getType() == spawnedEnemies[i][k]->type) {
                        isHeroShooting = true;
                        break;
                    }
                }
                if (isHeroShooting) {
                    heroesMatrix[i][j]->projectileSpawnTime -= deltaTimeSeconds;
                    if (heroesMatrix[i][j]->projectileSpawnTime <= 0) {
                        //Create new projectile
                        glm::vec3 projectilePos = glm::vec3(heroesMatrix[i][j]->getPosition());
                        projectilePos.x += 45;
                        Star* newProjectile = new Star("projectile", projectilePos, heroesMatrix[i][j]->getType());
                        newProjectile->setScale(1.5f);
                        projectiles.push_back(newProjectile);
                        heroesMatrix[i][j]->projectileSpawnTime = 5;
                    }

                }
            }
        }
    }

    /*Move all launched projectiles*/
    for (int i = 0; i < projectiles.size(); i++) {
        glm::vec3 newPos = glm::vec3(projectiles[i]->getPosition());
        newPos.x += 170 * deltaTimeSeconds;
        projectiles[i]->setPosition(newPos);
        //add rotation here
        projectiles[i]->setRotation(-RADIANS(1000) * deltaTimeSeconds);
        RenderMesh2D(projectiles[i]->getMesh(), shaders["VertexColor"], projectiles[i]->getModelMatrix());
    }

    /* Detect collisions betweeen stars and enemies*/
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < spawnedEnemies[i].size(); j++) {
            for (int k = 0; k < projectiles.size(); k++) {
                float distance = glm::distance(projectiles[k]->getPosition(), spawnedEnemies[i][j]->position);
                if (distance < projectiles[k]->getRadius() + spawnedEnemies[i][j]->radius &&
                    projectiles[k]->type == spawnedEnemies[i][j]->type) {
                    spawnedEnemies[i][j]->lives--;
                    if (spawnedEnemies[i][j]->lives == 0) {
                        spawnedEnemies[i][j]->killedState = 1;
                    }
                    /*Delete the star*/
                    delete projectiles[k];
                    projectiles.erase(projectiles.begin() + k);
                    //???
                    k--;
                }
            }
        }
    }

    /* Detect collisions between enemies and heroes */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (heroesMatrix[i][j] != nullptr) {
                for (int k = 0; k < 3; k++) {
                    for (int v = 0; v < spawnedEnemies[k].size(); v++) {
                        float distance = glm::distance(heroesMatrix[i][j]->getPosition(), spawnedEnemies[k][v]->position);
                        if (distance < heroesMatrix[i][j]->radius + spawnedEnemies[k][v]->radius + 80) {
                            heroesMatrix[i][j]->killedState = 1;
                        }
                    }

                }
            }

        }
    }
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < spawnedEnemies[i].size(); j++) {
            if (spawnedEnemies[i][j]->position.x < 30) {
                nrOfLives--;
                delete spawnedEnemies[i][j];
                spawnedEnemies[i].erase(spawnedEnemies[i].begin() + j);
            }
        }
    }




    /*Moved it here because the stars were rendering behind the squares*/
    renderScene();

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
    if (key == GLFW_KEY_V) {
        cout << "random number in range: " << getRandomFloatInRange(1, 3) << endl;
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    my_mouseX= mouseX;
    my_mouseY=  720 - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    my_mouseX = mouseX;
    my_mouseY =  720 - mouseY;

    /* Detect if we want to buy a new hero */
    if (buingNow == 0 && button == 1) {
        int x = 30, y = 570;
        for (int i = 0; i < 4; ++i) {
            int square_x = x + 150 * i;
            //check if mouse click is in the range of the i-th square and we have enough stars
            if (my_mouseX >= square_x && my_mouseX <= square_x + 120 &&
                     my_mouseY >= y && my_mouseY <= y + 120 &&
                     getNrOfStars() >= i + 1) {
                cout << "new hero should be of type " << i << endl;
                newHero = new Hero("new_hero", glm::vec3(my_mouseX, my_mouseY, 0), i, 0);
                buingNow = 1;
            }

        }
    }
    /*Detect if we want to collect a star*/
    if (button == 1) {

        for (int i = 0; i < spawnedStars.size(); i++) {
            Star* star = spawnedStars[i];
            glm::vec3 starCenter = star->getCenter();
            glm::vec3 starPos = star->getPosition();
            if (i == 0) {
                cout <<"radius: " << star->getRadius() << endl;
                cout <<"distance: " << glm::distance(glm::vec3(my_mouseX,my_mouseY,0),starPos) << endl;
            }
            if (glm::distance(glm::vec3(my_mouseX + 2 ,my_mouseY + 2,0),starPos) < star->getRadius()) {
//                cout << "clicked on the star " << i << endl;
                nrOfStars++;
                spawnedStars.erase(spawnedStars.begin() + i);
            }
        }
    }
    if (button == 2) {
        int x = 70, y = 40;
        for(int i = 0; i < 3; i++) {
            x = 70;
            for (int j = 0; j < 3; j++) {
                //Check if our mouse is within the range o a square
                if (mouseX >= x && mouseX <= x + 120 && (720 - mouseY) >= y && (720 - mouseY) <= y + 120) {
                    //check if our square is free
                    if (heroesMatrix[i][j] != nullptr) {
                       heroesMatrix[i][j]->killedState = 1;
                    }
                }
                x += 150;
            }
            y += 150;
        }
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 1 && buingNow == 1) {
        int heroPlaced = 0;
        //check if the new hero is situated on a square
        int x = 70, y = 40;
        for(int i = 0; i < 3; i++) {
            x = 70;
            for (int j = 0; j < 3; j++) {
                //Check if our mouse is within the range o a square
                if (mouseX >= x && mouseX <= x + 120 && (720 - mouseY) >= y && (720 - mouseY) <= y + 120) {
                    //check if our square is free
                    if (heroesMatrix[i][j] == nullptr) {
                        //place hero on a square
                        heroesMatrix[i][j] = newHero;
                        //set the position of the hero in the middle of the selected square
                        newHero->setPosition(glm::vec3(x + 120 / 2, y + 120 / 2, 0));
                        newHero->translateToCurr();
                        //Set the row of the newHero
                        newHero->row = i;
                        //toggle hero placed to not delete the newHero
                        heroPlaced = 1;
                        //Spend the amount of stars needed
                        setNrOfStars(getNrOfStars() - (newHero->getType() + 1));
                    }
              }
               x += 150;
            }
            y += 150;
        }
        //if the hero is not placed on a square we will delete it;
        if (!heroPlaced) {
            delete newHero;
        }
        newHero = nullptr;
        buingNow = 0;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::setNrOfStars(int nrOfStars) {
    this->nrOfStars = nrOfStars;
}
int Tema1::getNrOfStars() {
    return this->nrOfStars;
}

/*Renders the enemy itself, with a smaller enemy inside of it*/
void Tema1::renderEnemy(Enemy* enemy1) {
//    glm::vec3 color = enemy1->color;
//    color.x -= 0.3f;
//    color.y -= 0.3f;
//    color.z -= 0.3f;
//    Enemy* secondaryEnemy = new Enemy("Ceburek1232",  enemy1->position, color);
//    secondaryEnemy->scale = enemy1->scale * 0.7;
//    secondaryEnemy->translateToCurr();
//
//    RenderMesh2D(secondaryEnemy->mesh1, shaders["VertexColor"], secondaryEnemy->modelMatrix);
//    RenderMesh2D(enemy1->mesh1, shaders["VertexColor"], enemy1->modelMatrix);
    glm::vec3 secondPos = glm::vec3(enemy1->position);
    //translate
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(enemy1->position.x,   enemy1->position.y);
    //scale
    modelMatrix *= transform2D::Translate(enemy1->center.x  , enemy1->center.y );
    modelMatrix *= transform2D::Scale(enemy1->scale * 0.8f, enemy1->scale * 0.8f);
    modelMatrix *= transform2D::Translate(- enemy1->center.x ,  -enemy1->center.y );
    RenderMesh2D(enemy1->mesh2, shaders["VertexColor"], modelMatrix);
    RenderMesh2D(enemy1->mesh1, shaders["VertexColor"], enemy1->modelMatrix);
}

float Tema1::getRandomFloatInRange(float min, float max) {

    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max - min)));
}
int Tema1::getRandomIntInRange(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

void Tema1::renderScene() {
    //Create square
    float paddingBottom = 40;
    float length = 120;

    /*Draw the 9 squares*/
    translateX = 70;
    translateY = paddingBottom;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(translateX, translateY);
            RenderMesh2D(squareForScene, shaders["VertexColor"], modelMatrix);
            translateX += 150;
        }
        translateX = 70;
        translateY += 150;
    }

    /*Draw the finish line*/
    translateX = 20;
    translateY = paddingBottom;
    length = 25;
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(15, paddingBottom);
    modelMatrix *= transform2D::Scale(1.5f , 16.8f);
    RenderMesh2D(squareForFinish, shaders["VertexColor"], modelMatrix);

    /*Draw top menu bar*/
    length = 120;

    /*Draw buy section*/
    translateX = 30;
    translateY = 570;

    for(int i = 0; i < 4; ++i) {
        //Add square
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        RenderMesh2D(squareForMenuBar, shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX + length / 2, translateY + length / 2);

        /*Draw heroes*/
        glm::vec3 newPos = glm::vec3(translateX + length / 2, translateY + length / 2, 0);
        heroesForMenuBar[i]->setPosition(newPos);
        heroesForMenuBar[i]->translateToCurr();
        RenderMesh2D(heroesForMenuBar[i]->getMesh(), shaders["VertexColor"], heroesForMenuBar[i]->getModelMatrix());

        /*Draw price of each hero*/
        float posX = 38 + i * 150;
        float posY = 550;
        for (int j = 0; j < i + 1; j++) {
            glm::vec3 pos = glm::vec3(posX + j * 30, posY, 0);
            starForPrice->setPosition(pos);
            RenderMesh2D(starForPrice->getMesh(), shaders["VertexColor"], starForPrice->getModelMatrix());
        }
        translateX += 150;
    }

}
