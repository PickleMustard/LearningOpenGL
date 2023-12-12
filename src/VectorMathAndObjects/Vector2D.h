#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <vector>

namespace VectorSpace2D {
    struct Point2D{
        int x {};
        int y {};
        int z {0};
    };

    struct Pointf2D{
        float x {};
        float y {};
        float z = {0.0f};
    };

    struct Triangle2D{
        Pointf2D t_points[3];
    };

    struct Polygon2D{
        int num_of_points {};
        std::vector<Triangle2D> triangles {};
        Pointf2D* p_points {};
    };

    float area2(const Pointf2D& a, const Pointf2D& b, const Pointf2D& c);
    bool insideTriangle(const Pointf2D& a, const Pointf2D& b, const Pointf2D& c, const Pointf2D& p);
    float angle(const Pointf2D& a, const Pointf2D& b, const Pointf2D& c);
    bool flippingDesirable(int iP, int iQ, int iR, int iS, const Pointf2D vertices[]);
    bool anyFlipping(const std::vector<Triangle2D>& tris);
    std::vector<Triangle2D> triangularizePolygon(const Polygon2D& pol);
    std::vector<float> createTriangleArray(const std::vector<Triangle2D>& tris);
}

#endif
