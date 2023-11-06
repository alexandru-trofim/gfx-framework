//
// Created by Alexandru Trofim on 06.11.2023.
//
#include "Heart.h"
#include "lab_m1/lab3/transform2D.h"

float Heart::setScale(float new_scale) {
    scale = new_scale * scale;
    translateToCurr();
}
glm::vec3 Heart::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}

Heart::Heart(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 10;
    this->position = position;
    this->color = color;

    mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(1.97f, 2.4f, 0), color),
                    VertexFormat(glm::vec3(1.72, 2.68f, 0), color),
                    VertexFormat(glm::vec3(1.32f, 2.68f, 0), color),
                    VertexFormat(glm::vec3(1.03f, 2.36f, 0), color),
                    VertexFormat(glm::vec3(1.03f, 1.85f, 0), color),
                    VertexFormat(glm::vec3(2, 1, 0), color),
                    VertexFormat(glm::vec3(2.87f, 1.87f, 0), color),
                    VertexFormat(glm::vec3(2.87f, 2.4f, 0), color),
                    VertexFormat(glm::vec3(2.6f, 2.69f, 0), color),
                    VertexFormat(glm::vec3(2.21f, 2.69f, 0), color),
            };
    std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 5,
            0, 5, 6,
            0, 6, 7,
            0, 7, 8,
            0, 8 ,9

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
void Heart::translateToCurr() {
    modelMatrix = glm::mat3(1);
    //scale
    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
}

Mesh* Heart::getMesh() {
    return mesh;
}
glm::mat3 Heart::getModelMatrix() {
    return modelMatrix;
}
