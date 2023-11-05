//
// Created by Alexandru Trofim on 03.11.2023.
//

#ifndef GFXFRAMEWORK_ATTACKER_H
#define GFXFRAMEWORK_ATTACKER_H

#include "core/gpu/mesh.h"

class Attacker {

public:
    Attacker();
    Attacker(std::string name, glm::vec3 position, glm::vec3 color);
    ~Attacker();

    void translateToCurr();

    Mesh *getMesh();
    glm::vec3 getCenter();
    glm::vec3 getPosition();
    float getScale();

    glm::vec3 setPosition(glm::vec3 position);
    float setScale(float scale);
    glm::mat3 getModelMatrix();

private:
    Mesh* mesh;
    glm::mat3 modelMatrix;
    glm::vec3 center;
    glm::vec3 position;
    float scale;

protected:
    int price;
    glm::vec3 color;

};

#endif //GFXFRAMEWORK_ATTACKER_H
