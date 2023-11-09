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

    Star(std::string name, glm::vec3 position, int type);

    ~Star();

    Mesh* mesh;
    glm::mat3 modelMatrix;
    int type;
    glm::vec3 setPosition(glm::vec3 new_position);
    Mesh *getMesh();
    void translateToCurr();


    glm::mat3 getModelMatrix();
    float setScale(float new_scale);

    glm::vec3 getCenter();

    float getRadius();

    glm::vec3 getPosition();

private:
    glm::vec3 center;
    glm::vec3 color;
    glm::vec3 position;
    float radius;
    float scale;
    int type;


    void setColorFromType();
};


#endif //GFXFRAMEWORK_STAR_H
