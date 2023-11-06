//
// Created by Alexandru Trofim on 06.11.2023.
//

#ifndef GFXFRAMEWORK_HEART_H
#define GFXFRAMEWORK_HEART_H

#include "glm/fwd.hpp"
#include "glm/detail/type_vec3.hpp"
#include "core/gpu/mesh.h"

class Heart {

public:

    Heart(std::string name, glm::vec3 position, glm::vec3 color);
    Mesh* mesh;
    glm::mat3 modelMatrix;
    glm::vec3 setPosition(glm::vec3 new_position);
    Mesh *getMesh();
    void translateToCurr();


    glm::mat3 getModelMatrix();
    float setScale(float new_scale);

private:
    glm::vec3 center;
    glm::vec3 color;
    glm::vec3 position;
    float scale;
};


#endif //GFXFRAMEWORK_HEART_H
