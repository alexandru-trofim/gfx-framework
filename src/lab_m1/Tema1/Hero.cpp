//
// Created by Alexandru Trofim on 03.11.2023.
//

#include "Hero.h"
#include "lab_m1/lab3/transform2D.h"

Hero::Hero() {
}
Hero::~Hero() {
}

/*Getters*/
Mesh* Hero::getMesh() {
   return mesh;
}
glm::vec3 Hero::getPosition() {
    return position;
}
glm::vec3 Hero::getCenter() {
    return center;
}
glm::mat3 Hero::getModelMatrix() {
    return modelMatrix;
}
float Hero::getScale() {
    return scale;
}
int Hero::getType() {
    return type;
}

/*Setters*/
float Hero::setScale(float new_scale) {
    scale = new_scale * scale;
    radius = new_scale * radius;
    translateToCurr();
}
glm::vec3 Hero::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}


Hero::Hero(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 65;
    projectileSpawnTime = 3;
    killedState = 0;
    this->position = position;
    this->color = color;

    mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(1.5f, 2.5f, 1), color),
                    VertexFormat(glm::vec3(1, 1.5f, 1), color),
                    VertexFormat(glm::vec3(1.5f, 0.5f, 1), color),
                    VertexFormat(glm::vec3(1.9f, 1.3f, 1), color),
                    VertexFormat(glm::vec3(2.8f, 1.3f, 1), color),
                    VertexFormat(glm::vec3(2.8f, 1.7f, 1), color),
                    VertexFormat(glm::vec3(1.9f, 1.7f, 1), color)
            };
    std::vector<unsigned int> indices = {
            1, 6, 0,
            1, 3, 6,
            1, 2, 3,
            3, 4, 5,
            3, 5, 6
    };

    mesh->InitFromData(vertices, indices);

    /*Compute the center of the mesh*/
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    for (const VertexFormat& vertex : vertices) {
        center += vertex.position;
    }
    center /= static_cast<float>(vertices.size());

    radius = glm::distance(center,glm::vec3(2.8f, 1.7f, 1) * scale);

    this->translateToCurr();
}

Hero::Hero(std::string name, glm::vec3 position, int type, int row) {
    scale = 65;
    projectileSpawnTime = 3;
    killedState = 0;
    this->row = row;
    this->position = position;
    this->type = type;
    /*Here is the difference from the previous constructor*/
    setColorFromType();

    mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(1.5f, 2.5f, 0.1f), color),
                    VertexFormat(glm::vec3(1, 1.5f, 0.1f), color),
                    VertexFormat(glm::vec3(1.5f, 0.5f, 0.1f), color),
                    VertexFormat(glm::vec3(1.9f, 1.3f, 0.1f), color),
                    VertexFormat(glm::vec3(2.8f, 1.3f, 0.1f), color),
                    VertexFormat(glm::vec3(2.8f, 1.7f, 0.1f), color),
                    VertexFormat(glm::vec3(1.9f, 1.7f, 0.1f), color)
            };
    std::vector<unsigned int> indices = {
            1, 6, 0,
            1, 3, 6,
            1, 2, 3,
            3, 4, 5,
            3, 5, 6
    };

    mesh->InitFromData(vertices, indices);

    /*Compute the center of the mesh*/
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    for (const VertexFormat& vertex : vertices) {
    center += vertex.position;
    }
    center /= static_cast<float>(vertices.size());

    this->translateToCurr();
}

void Hero::translateToCurr() {
    modelMatrix = glm::mat3(1);
//    //scale
//    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
//    modelMatrix *= transform2D::Scale(scale, scale);
//    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
//    //translate
//    modelMatrix *= transform2D::Translate(position.x,   position.y);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
    //scale
    modelMatrix *= transform2D::Translate(center.x  ,center.y );
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x ,  - center.y );
}

void Hero::setColorFromType() {
    switch (type) {
        case 0:
            color = glm::vec3(0.259f, 0.839f, 0.643f);
            break;
        case 1:
            color = glm::vec3(0.973f, 0.953f, 0.553f);
            break;
        case 2:
            color = glm::vec3(1, 0.706f, 0.502f);
            break;
        case 3:
            color = glm::vec3(0.78f, 0.502f, 0.91f);
            break;
        default:
            break;
    }
}
