//
// Created by Alexandru Trofim on 04.11.2023.
//

#include "Enemy.h"
#include "lab_m1/lab3/transform2D.h"
#include "core/gpu/shader.h"
#include "Tema1.h"

/*Setters*/
float Enemy::setScale(float new_scale) {
    scale = new_scale;
    translateToCurr();
}
glm::vec3 Enemy::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}

Enemy::Enemy(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 25;
    this->position = position;
    this->color = color;

    mesh1 = new Mesh(name);
    mesh1->SetDrawMode(GL_TRIANGLES);
    mesh2 = new Mesh(name);
    mesh2->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(2.55f, 4.39f, 0), color),
                    VertexFormat(glm::vec3(1.24f, 2.73f, 0), color),
                    VertexFormat(glm::vec3(2.05f, 0.76f, 0), color),
                    VertexFormat(glm::vec3(4.12f, 0.5f, 0), color),
                    VertexFormat(glm::vec3(5.42f, 2.14f, 0), color),
                    VertexFormat(glm::vec3(4.63f, 4.08f, 0), color),
            };
    std::vector<unsigned int> indices = {
            0, 1, 2,
            3, 4, 5,
            2, 3, 5,
            2, 5, 0,
    };

    mesh1->InitFromData(vertices, indices);
    mesh2->InitFromData(vertices, indices);

    /*Compute the center of the mesh*/
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    for (const VertexFormat& vertex : vertices) {
        center += vertex.position;
    }
    center /= static_cast<float>(vertices.size());

    this->translateToCurr();
}
void Enemy::translateToCurr() {
    modelMatrix = glm::mat3(1);
    //scale
    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
}

void Enemy::render(Shader* shader) {
    glm::mat3 modelForSmallerHexa = glm::mat3(1);
    modelMatrix *= transform2D::Translate(center.x +  position.x ,center.y + position.y);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x - position.x,  - center.y - position.y);
//    tema1->RenderMesh2D(mesh1, shader, modelMatrix);
//    tema1->RenderMesh2D(mesh2, shader, modelMatrix);
}
