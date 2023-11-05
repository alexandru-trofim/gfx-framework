//
// Created by Alexandru Trofim on 04.11.2023.
//

#ifndef GFXFRAMEWORK_STAR_H
#define GFXFRAMEWORK_STAR_H


#include "glm/fwd.hpp"
#include "glm/detail/type_vec3.hpp"
#include "core/gpu/mesh.h"

class Star {

public:
    Star();

    Star(std::string name, glm::vec3 position, glm::vec3 color);

    ~Star();

    Mesh* mesh;
    glm::mat3 modelMatrix;
private:
    glm::vec3 center;
    glm::vec3 color;
    glm::vec3 position;
    float scale;

    void translateToCurr();

    glm::vec3 setPosition(glm::vec3 new_position);

    float setScale(float new_scale);
};


#endif //GFXFRAMEWORK_STAR_H
