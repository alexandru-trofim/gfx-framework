//
// Created by Alexandru Trofim on 03.11.2023.
//

#include "Attacker.h"
#include "lab_m1/lab3/transform2D.h"

Attacker::Attacker() {
}
Attacker::~Attacker() {
}

/*Getters*/
Mesh* Attacker::getMesh() {
   return mesh;
}
glm::vec3 Attacker::getPosition() {
    return position;
}
glm::vec3 Attacker::getCenter() {
    return center;
}
glm::mat3 Attacker::getModelMatrix() {
    return modelMatrix;
}
float Attacker::getScale() {
    return scale;
}

/*Setters*/
float Attacker::setScale(float new_scale) {
    scale = new_scale;
    translateToCurr();
}
glm::vec3 Attacker::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}


Attacker::Attacker(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 25;
    this->position = position;
    this->color = color;

    mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(1.5f, 2.5f, 0.1), color),
                    VertexFormat(glm::vec3(1, 1.5f, 0.1), color),
                    VertexFormat(glm::vec3(1.5f, 0.5f, 0.1), color),
                    VertexFormat(glm::vec3(1.9f, 1.3f, 0), color),
                    VertexFormat(glm::vec3(2.8f, 1.3f, 0), color),
                    VertexFormat(glm::vec3(2.8f, 1.7f, 0), color),
                    VertexFormat(glm::vec3(1.9f, 1.7f, 0), color)
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

void Attacker::translateToCurr() {
    modelMatrix = glm::mat3(1);
    //scale
    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
}

