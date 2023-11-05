#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float tX, float tY)
    {
        return glm::mat3(1, 0, 0,
                         0, 1, 0,
                         tX, tY, 1);

    }

    // Scale matrix
    inline glm::mat3 Scale(float sX, float sY)
    {
        return glm::transpose(
                glm::mat3(sX, 0, 0,
                          0, sY, 0,
                          0, 0, 1)
        );

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        float cos = glm::cos(radians);
        float sin = glm::sin(radians);

        return glm::transpose(
                glm::mat3(cos, -sin, 0,
                          sin, cos, 0,
                          0, 0, 1)
        );
    }
}   // namespace transform2D
