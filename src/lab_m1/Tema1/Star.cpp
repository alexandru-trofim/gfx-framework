//
// Created by Alexandru Trofim on 04.11.2023.
//

#include "Star.h"
#include "lab_m1/lab3/transform2D.h"


float Star::setScale(float new_scale) {
    scale = new_scale * scale;
    radius = new_scale * radius;
    translateToCurr();
}
float Star::setRotation(float new_rotation) {
    rotation = rotation + new_rotation;
    translateToCurr();
}
glm::vec3 Star::setPosition(glm::vec3 new_position) {
    position = glm::vec3(new_position);
    translateToCurr();
}

Star::Star(std::string name, glm::vec3 position, glm::vec3 color) {
    scale = 10;
    rotation = 0;
    killedState = 0;
    this->position = position;
    this->color = color;

    mesh = new Mesh(name);
    mesh->SetDrawMode(GL_TRIANGLES);

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(glm::vec3(5, 4, 1.1f), color),
                VertexFormat(glm::vec3(4.475f, 2.903f, 1.1f), color),
                    VertexFormat(glm::vec3(3.3f, 2.75f, 1.1f), color),
                    VertexFormat(glm::vec3(4.15f, 1.91f, 1.1f), color),
                    VertexFormat(glm::vec3(3.92f, 0.77f, 1.1f), color),
                    VertexFormat(glm::vec3(4.96f, 1.27f, 1.1f), color),
                    VertexFormat(glm::vec3(5.96f, 0.7f, 1.1f), color),
                    VertexFormat(glm::vec3(5.8f, 1.86f, 1.1f), color),
                    VertexFormat(glm::vec3(6.67f, 2.68f, 1.1f), color),
                    VertexFormat(glm::vec3(5.51f, 2.85f, 1.1f), color),
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

    radius = glm::distance(center,glm::vec3(5, 4, 0)) * scale ;

    this->translateToCurr();
}

Star::Star(std::string name, glm::vec3 position, int type) {
    scale = 10;
    killedState = 0;
    rotation = 0;
    this->position = position;
    this->type = type;
    setColorFromType();



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

    radius = glm::distance(center,glm::vec3(5, 4, 0)) * scale ;

    this->translateToCurr();
}
void Star::translateToCurr() {
    modelMatrix = glm::mat3(1);
    //translate
    modelMatrix *= transform2D::Translate(position.x,   position.y);
    //scale
    modelMatrix *= transform2D::Translate(center.x  ,center.y );
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Translate(- center.x ,  - center.y );
    //rotate
    modelMatrix *= transform2D::Translate(center.x  ,center.y );
    modelMatrix *= transform2D::Rotate(rotation);
    modelMatrix *= transform2D::Translate(- center.x ,  - center.y );
}

Mesh* Star::getMesh() {
    return mesh;
}
glm::mat3 Star::getModelMatrix() {
    return modelMatrix;
}
float Star::getRadius() {
    return radius;
}
glm::vec3 Star::getCenter() {
    return center;
}
glm::vec3 Star::getPosition() {
    return position;
}
void Star::setColorFromType() {
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

Star::~Star() {

}
