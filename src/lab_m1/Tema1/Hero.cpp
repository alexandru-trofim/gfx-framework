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

/*Setters*/
float Hero::setScale(float new_scale) {
    scale = new_scale * scale;
    translateToCurr();
}
glm::vec3 Hero::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}


Hero::Hero(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 65;
    this->position = position;
    this->color = color;

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
    //scale
    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
}

