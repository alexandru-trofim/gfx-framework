//
// Created by Alexandru Trofim on 04.11.2023.
//

#include "Enemy.h"
#include "lab_m1/lab3/transform2D.h"
#include "core/gpu/shader.h"
#include "Tema1.h"

/*Setters*/
void Enemy::setScale(float new_scale) {
    scale = new_scale;
    translateToCurr();
}
void Enemy::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}

Enemy::Enemy(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 25;
    this->position = position;
    this->color = color;
    glm::vec3 secondaryColor = glm::vec3(1, 0, 1);

    mesh1 = new Mesh(name);
    mesh1->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices1 =
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

    mesh1->InitFromData(vertices1, indices);

    /*Compute the center of the mesh*/
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    for (const VertexFormat& vertex : vertices1) {
        center += vertex.position;
    }
    center /= static_cast<float>(vertices1.size());

    this->translateToCurr();
}

Enemy::Enemy(std::string name, glm::vec3 position,int type) {
    scale = 25;
    this->position = position;
    this->type = type;
    setColorFromType();

    mesh1 = new Mesh(name);
    mesh1->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices1 =
            {
                    VertexFormat(glm::vec3(2.55f, 4.39f, 1), color),
                    VertexFormat(glm::vec3(1.24f, 2.73f, 1), color),
                    VertexFormat(glm::vec3(2.05f, 0.76f, 1), color),
                    VertexFormat(glm::vec3(4.12f, 0.5f, 1), color),
                    VertexFormat(glm::vec3(5.42f, 2.14f, 1), color),
                    VertexFormat(glm::vec3(4.63f, 4.08f, 1), color),
            };
    std::vector<unsigned int> indices = {
            0, 1, 2,
            3, 4, 5,
            2, 3, 5,
            2, 5, 0,
    };

    /*Create the second mesh*/
    glm::vec3 secondColor = glm::vec3 (color);
    secondColor.x -= 0.3f;
    secondColor.y -= 0.3f;
    secondColor.z -= 0.3f;

    mesh2 = new Mesh(name);
    mesh2->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices2 =
            {
                    VertexFormat(glm::vec3(2.55f, 4.39f, 1), secondColor),
                    VertexFormat(glm::vec3(1.24f, 2.73f, 1), secondColor),
                    VertexFormat(glm::vec3(2.05f, 0.76f, 1), secondColor),
                    VertexFormat(glm::vec3(4.12f, 0.5f, 1), secondColor),
                    VertexFormat(glm::vec3(5.42f, 2.14f, 1), secondColor),
                    VertexFormat(glm::vec3(4.63f, 4.08f, 1), secondColor),
            };

    mesh1->InitFromData(vertices1, indices);
    mesh2->InitFromData(vertices2, indices);

    /*Compute the center of the mesh*/
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    for (const VertexFormat& vertex : vertices1) {
        center += vertex.position;
    }
    center /= static_cast<float>(vertices1.size());

    this->translateToCurr();
}
void Enemy::translateToCurr() {
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


void Enemy::setColorFromType() {
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
