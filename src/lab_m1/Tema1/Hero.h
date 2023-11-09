//
// Created by Alexandru Trofim on 03.11.2023.
//

#ifndef GFXFRAMEWORK_HERO_H
#define GFXFRAMEWORK_HERO_H

#include "core/gpu/mesh.h"

class Hero {

public:
    Hero();
    Hero(std::string name, glm::vec3 position, glm::vec3 color);
    Hero(std::string name, glm::vec3 position, int type, int row);
    ~Hero();

    void translateToCurr();

    Mesh *getMesh();
    glm::vec3 getCenter();
    glm::vec3 getPosition();
    float getScale();

    glm::vec3 setPosition(glm::vec3 position);
    float setScale(float scale);
    glm::mat3 getModelMatrix();

    int getType();

    float projectileSpawnTime;
    int row;

    float radius;
    int killedState;
    float scale;
private:
    Mesh* mesh;
    glm::mat3 modelMatrix;
    glm::vec3 center;
    glm::vec3 position;
    int type;

protected:
    int price;
    glm::vec3 color;

    void setColorFromType();

};

#endif //GFXFRAMEWORK_HERO_H
