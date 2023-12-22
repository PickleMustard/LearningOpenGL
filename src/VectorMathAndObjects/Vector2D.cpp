#define _USE_MATH_DEFINES
#include "Vector2D.h"
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <cstdio>

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

bool VectorSpace2D::flippingDesirable(VectorSpace2D::Pointf2D iP, VectorSpace2D::Pointf2D iQ, VectorSpace2D::Pointf2D iR, VectorSpace2D::Pointf2D iS){
    VectorSpace2D::Pointf2D vP = iP, vQ = iQ, vR = iR, vS = iS;
    float angle1 = VectorSpace2D::angle(vP, vQ, vR), angle2 = VectorSpace2D::angle(vR, vS, vP);
    printf("First Angle: %.8f | Second Angle: %.8f | Addition: %.8f | PI: %.8f\n", angle1, angle2, angle1 + angle2, M_PI);
    return ((angle1 + angle2 - .00001) > M_PI) && (!(angle1 == angle2));
}

void VectorSpace2D::flipTriangles(std::vector<VectorSpace2D::Triangle2D> tris, VectorSpace2D::Pointf2D iP, VectorSpace2D::Pointf2D iQ, VectorSpace2D::Pointf2D iR, VectorSpace2D::Pointf2D iS, int i, int j) {
    tris[i] = VectorSpace2D::Triangle2D{iP, iQ, iS};
    tris[j] = VectorSpace2D::Triangle2D{iS, iQ, iR};
}


bool VectorSpace2D::anyFlipping(std::vector<Triangle2D>* tris){
    if((*tris).size() < 2) {
        return false;
    }
    for(int i = 0; i < (*tris).size(); i++) {
        VectorSpace2D::Pointf2D t[] {(*tris)[i].t_points[0], (*tris)[i].t_points[1], (*tris)[i].t_points[2]};
        for(int j = i+1; j < (*tris).size(); j++) {
            VectorSpace2D::Pointf2D u[] {(*tris)[j].t_points[0], (*tris)[j].t_points[1], (*tris)[j].t_points[2]};
            //Look for a common edge of triangles t and u
            for (int h = 0; h < 3; h++) {
                for (int k = 0; k < 3; k++) {
                    if((t[h].x == u[k].x && t[h].y == u[k].y && t[h].z == u[k].z) &&
                            (t[(h+1)%3].x == u[(k+2)%3].x && t[(h+1)%3].y == u[(k+2)%3].y && t[(h+1)%3].z == u[(k+2)%3].z)) {
                        VectorSpace2D::Pointf2D iP = t[(h+1)%3], iQ = t[(h+2)%3],
                                                iR = t[h], iS = u[(k+1)%3];
                        if(flippingDesirable(iP, iQ, iR, iS)){
                            printf("Flipping\n");
                            printf("Edges: %i and %ii\n", h, k);
                            printf("Triangle i: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[i].t_points[0].x, (*tris)[i].t_points[0].y, (*tris)[i].t_points[0].z,
                                    (*tris)[i].t_points[1].x, (*tris)[i].t_points[1].y, (*tris)[i].t_points[1].z,
                                    (*tris)[i].t_points[2].x, (*tris)[i].t_points[2].y, (*tris)[i].t_points[2].z);
                            printf("Triangle j: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[j].t_points[0].x, (*tris)[j].t_points[0].y, (*tris)[j].t_points[0].z,
                                    (*tris)[j].t_points[1].x, (*tris)[j].t_points[1].y, (*tris)[j].t_points[1].z,
                                    (*tris)[j].t_points[2].x, (*tris)[j].t_points[2].y, (*tris)[j].t_points[2].z);
                            //VectorSpace2D::flipTriangles(tris,iP, iQ, iR, iS, i, j);
                            (*tris)[i] = VectorSpace2D::Triangle2D{iP, iQ, iS};
                            (*tris)[j] = VectorSpace2D::Triangle2D{iS, iQ, iR};

                            printf("Triangle i: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[i].t_points[0].x, (*tris)[i].t_points[0].y, (*tris)[i].t_points[0].z,
                                    (*tris)[i].t_points[1].x, (*tris)[i].t_points[1].y, (*tris)[i].t_points[1].z,
                                    (*tris)[i].t_points[2].x, (*tris)[i].t_points[2].y, (*tris)[i].t_points[2].z);
                            printf("Triangle j: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[j].t_points[0].x, (*tris)[j].t_points[0].y, (*tris)[j].t_points[0].z,
                                    (*tris)[j].t_points[1].x, (*tris)[j].t_points[1].y, (*tris)[j].t_points[1].z,
                                    (*tris)[j].t_points[2].x, (*tris)[j].t_points[2].y, (*tris)[j].t_points[2].z);

                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void VectorSpace2D::rotateShape(float angle, float *points, int num_of_points){
    //Matrix multiplication
    float rad = (angle * M_PI) / 180.0f;
    float original_point_x, original_point_y;
    for(int i = 0; i < num_of_points; i+=3){
        original_point_x = points[i];
        original_point_y = points[i+1];
        points[i] = (original_point_x * cosf(rad)) + (original_point_y * (-sinf(rad)));
        points[i+1] = (original_point_x * sinf(rad)) + (original_point_y * cosf(rad));
    }
}

void VectorSpace2D::scaleShape(float x_scaling_factor, float y_scaling_factor, float *points, int num_of_points) {
    for(int i = 0; i < num_of_points; i+=3) {
        points[i] *= x_scaling_factor;
        points[i+1] *= y_scaling_factor;
    }
}

void VectorSpace2D::shearShape(float shearing_factor, bool shearing_axis, float *points, int num_of_points) {
    float x_shear = shearing_factor * shearing_axis, y_shear = shearing_factor * (!shearing_axis);
    float original_point_x, original_point_y;
    for(int i = 0; i < num_of_points; i+=3){
        original_point_x = points[i], original_point_y = points[i+1];
        points[i] = original_point_x + (original_point_y * y_shear);
        points[i+1] = original_point_y + (original_point_x * x_shear);
    }
}

void VectorSpace2D::translateShape(float x_translation_factor, float y_translation_factor, float *points, int num_of_points){
    for(int i = 0; i < num_of_points; i+=3){
        points[i] += x_translation_factor;
        points[i+1] += y_translation_factor;
    }
}
std::vector<VectorSpace2D::Triangle2D> VectorSpace2D::triangularizePolygon(const Polygon2D &pol){
    std::vector<VectorSpace2D::Triangle2D> tr {};
    //printf("tr size: %lu\n", tr.size());
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
            if(VectorSpace2D::area2(a, b, c) >= 0) {
                //Edges AB and BC; diagonal AC
                //Test to see if no other polygon vertex
                //lies within ABC;
                j = next[iC];
                nj = abs(j);
                while (j != iA &&
                        (nj == nA || nj == nB || nj == nC) ||
                        !insideTriangle(a, b, c, pol.p_points[nj])) {
                    j = next[j];
                    nj = abs(j);
                }
                if(j == iA) {
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

    while (anyFlipping(&tr));
    printf("Finished\n");
    return tr;
}

bool VectorSpace2D::clockwise(const Pointf2D p[], int length){
    int k = 0;
    for (int i = 1; i < length; i++) {
        if((p[i]).x <= p[k].x && (p[i].x < p[k].x || p[i].y < p[k].y)) {
            k = i;
        }
        int prev = k - 1, next = k + 1;
        if (prev == -1){
            prev = length - 1;
        }
        if (next == length) {
            next = 0;
        }
        return area2(p[prev], p[k], p[next]) > 0;
    }
    return false;
}

std::vector<float> VectorSpace2D::createTriangleArray(const std::vector<Triangle2D>& tris){
    std::vector<float> triangle_point_list{};
    printf("Triangle Input Array Size: %lu\n", tris.size());
    for(Triangle2D t : tris){
        if(!clockwise(t.t_points, 3)) {
            for(int i = 0; i < 3; i++) {
                printf("Clockwise\n");
                triangle_point_list.push_back(t.t_points[i].x);
                triangle_point_list.push_back(t.t_points[i].y);
                triangle_point_list.push_back(t.t_points[i].z);
            }
        } else {
            for(int i = 2; i >= 0; i--) {
                printf("Not Clockwise\n");
                triangle_point_list.push_back(t.t_points[i].x);
                triangle_point_list.push_back(t.t_points[i].y);
                triangle_point_list.push_back(t.t_points[i].z);
            }
        }
    }

    return triangle_point_list;
}

