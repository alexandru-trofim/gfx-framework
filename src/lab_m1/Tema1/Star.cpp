//
// Created by Alexandru Trofim on 04.11.2023.
//

#include "Star.h"
#include "lab_m1/lab3/transform2D.h"


float Star::setScale(float new_scale) {
    scale = new_scale * scale;
    translateToCurr();
}
glm::vec3 Star::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}

Star::Star(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 10;
    this->position = position;
    this->color = color;

    mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(5, 4, 0), color),
                    VertexFormat(glm::vec3(4.475f, 2.903f, 0), color),
                    VertexFormat(glm::vec3(3.3f, 2.75f, 0), color),
                    VertexFormat(glm::vec3(4.15f, 1.91f, 0), color),
                    VertexFormat(glm::vec3(3.92f, 0.77f, 0), color),
                    VertexFormat(glm::vec3(4.96f, 1.27f, 0), color),
                    VertexFormat(glm::vec3(5.96f, 0.7f, 0), color),
                    VertexFormat(glm::vec3(5.8f, 1.86f, 0), color),
                    VertexFormat(glm::vec3(6.67f, 2.68f, 0), color),
                    VertexFormat(glm::vec3(5.51f, 2.85f, 0), color),
            };
    std::vector<unsigned int> indices = {
            0, 1, 9,
            1, 2, 3,
            3, 4, 5,
            5, 6, 7,
            7, 8, 9,
            1, 3, 9,
            9, 3, 5,
            9, 5, 7
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
void Star::translateToCurr() {
    modelMatrix = glm::mat3(1);
    //scale
    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
}

Mesh* Star::getMesh() {
    return mesh;
}
glm::mat3 Star::getModelMatrix() {
    return modelMatrix;
}
