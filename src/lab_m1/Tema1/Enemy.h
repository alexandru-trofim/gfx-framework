//
// Created by Alexandru Trofim on 04.11.2023.
//

#ifndef GFXFRAMEWORK_ENEMY_H
#define GFXFRAMEWORK_ENEMY_H


#include "glm/vec3.hpp"
#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
class Enemy {
public:

    Enemy();

    Enemy(std::string name, glm::vec3 position, glm::vec3 color);

    ~Enemy();




    Mesh* mesh1;
    Mesh* mesh2;
    glm::mat3 modelMatrix;
    glm::vec3 center;
    glm::vec3 color;
    glm::vec3 position;
    float scale;

    void translateToCurr();

    float setScale(float new_scale);

    glm::vec3 setPosition(glm::vec3 new_position);

    void render(Shader *shader);

};


#endif //GFXFRAMEWORK_ENEMY_H
