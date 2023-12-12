#define _USE_MATH_DEFINES
#include "Vector2D.h"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <ranges>
#include <iostream>

float VectorSpace2D::area2(const Pointf2D& a, const Pointf2D& b, const Pointf2D& c){
    return (a.x - c.x) * (b.y-c.y) - (a.y-c.y) * (b.x-c.x);
}

bool VectorSpace2D::insideTriangle(const Pointf2D &a, const Pointf2D &b, const Pointf2D &c, const Pointf2D &p){
    return VectorSpace2D::area2(a,b, p) >= 0 &&
        VectorSpace2D::area2(b, c, p) >= 0 &&
        VectorSpace2D::area2(c, a, p) >= 0;
}

float VectorSpace2D::angle(const Pointf2D &a, const Pointf2D &b, const Pointf2D &c){
    float xBA = a.x - b.x, yBA = a.y - b.y,
          xBC = c.x - b.x, yBC = c.y - b.y,
          dotproduct = xBA * xBC + yBA * yBC,
          lenBA = sqrtf(xBA * xBA + yBA * yBA),
          lenBC = sqrtf(xBC * xBC + yBC * yBC),
          cosB = dotproduct / (lenBA * lenBC);
    return acosf(cosB);
}

bool VectorSpace2D::flippingDesirable(int iP, int iQ, int iR, int iS, const Pointf2D vertices[]){
    VectorSpace2D::Pointf2D vP = vertices[iP], vQ = vertices[iQ], vR = vertices[iR], vS = vertices[iS];
    return VectorSpace2D::angle(vP, vQ, vR) + VectorSpace2D::angle(vR, vS, vP) > M_PI;
}

/*bool anyFlipping(const std::vector<VectorSpace2D::Triangle2D>& tris){
    if(tris.size() < 2)
        return false;
    for(VectorSpace2D::Triangle2D t: tris) {

    }

}*/


std::vector<VectorSpace2D::Triangle2D> VectorSpace2D::triangularizePolygon(const Polygon2D &pol){
    printf("Num of points: %i\n", pol.num_of_points);
    std::vector<VectorSpace2D::Triangle2D> tr {};
    printf("tr size: %lu\n", tr.size());
    int next[pol.num_of_points];
    for(int i = 0; i < pol.num_of_points; i++) {
        next[i] = (i + 1) % pol.num_of_points;
    }

    for (int k = 0; k < pol.num_of_points - 2; k++){
        VectorSpace2D::Pointf2D a, b, c;
        bool triangleFound = false;
        int iA = 0, iB = 0, iC = 0, count = 0, nA = 0, nB = 0, nC = 0, j = 0, nj = 0;
        while(!triangleFound && ++count < pol.num_of_points){
            iB = next[iA], iC = next[iB];
            nA = abs(iA);
            nB = abs(iB);
            nC = abs(iC);
            a = pol.p_points[nA];
            b = pol.p_points[nB];
            c = pol.p_points[nC];
            //printf("Area2 for a, b, c: %f\n", VectorSpace2D::area2(a, b, c));
            if(VectorSpace2D::area2(a, b, c) >= 0) {
                //Edges AB and BC; diagonal AC
                //Test to see if no other polygon vertex
                //lies within ABC;
                j = next[iC];
                nj = abs(j);
                while (j != iA &&
                        (nj == nA || nj == nB || nj == nC) ||
                        !insideTriangle(a, b, c, pol.p_points[nj])) {
                    //printf("Inside Triangle: %i\n", insideTriangle(a, b, c, pol.p_points[nj]));
                    j = next[j];
                    nj = abs(j);
                }
                if(j == iA) {
                    printf("Pushing back triangle: %f, %f, %f\n", a.x, a.y, a.z);
                    printf("Pushing back triangle: %f, %f, %f\n", b.x, b.y, b.z);
                    printf("Pushing back triangle: %f, %f, %f\n", c.x, c.y, c.z);
                    tr.push_back(Triangle2D{a, b, c});
                    next[iA] = iC;
                    triangleFound = true;
                }
            }
            iA = next[iA];
        }

        if(count == pol.num_of_points){
            printf("ERROR: Not a simple polygon or vertex sequence not counter-clockwise");
            return std::vector<VectorSpace2D::Triangle2D>();
        }
    }

    //while (anyFlipping(tr));

    return tr;
}
std::vector<float> VectorSpace2D::createTriangleArray(const std::vector<Triangle2D>& tris){
    std::vector<float> triangle_point_list{};
    printf("Triangle Input Array Size: %lu\n", tris.size());
    for(Triangle2D t : tris){
        for(int i = 2; i >= 0; i--) {
            printf("Pushing back: %f, %f, %f\n", t.t_points[i].x, t.t_points[i].y, t.t_points[i].z);
            triangle_point_list.push_back(t.t_points[i].x);
            triangle_point_list.push_back(t.t_points[i].y);
            triangle_point_list.push_back(t.t_points[i].z);
        }
    }

    return triangle_point_list;
}

