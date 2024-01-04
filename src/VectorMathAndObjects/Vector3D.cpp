#include "Vector3D.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <math.h>


float VectorSpace3D::area2 (const Point3D& a, const Point3D& b, const Point3D& c){
    return (a.x - c.x) * (b.y-c.y) - (a.y-c.y) * (b.x-c.x);
}

bool VectorSpace3D::insideTriangle(const Point3D &a, const Point3D &b, const Point3D &c, const Point3D &p){
    return VectorSpace3D::area2(a,b, p) >= 0 &&
        VectorSpace3D::area2(b, c, p) >= 0 &&
        VectorSpace3D::area2(c, a, p) >= 0;
}

float VectorSpace3D::angle(const Point3D &a, const Point3D &b, const Point3D &c){
    float xBA = a.x - b.x, yBA = a.y - b.y,
          xBC = c.x - b.x, yBC = c.y - b.y,
          dotproduct = xBA * xBC + yBA * yBC,
          lenBA = sqrtf(xBA * xBA + yBA * yBA),
          lenBC = sqrtf(xBC * xBC + yBC * yBC),
          cosB = dotproduct / (lenBA * lenBC);
    return acosf(cosB);
}


bool VectorSpace3D::flippingDesirable(VectorSpace3D::Point3D iP, VectorSpace3D::Point3D iQ, VectorSpace3D::Point3D iR, VectorSpace3D::Point3D iS){
    VectorSpace3D::Point3D vP = iP, vQ = iQ, vR = iR, vS = iS;
    float angle1 = VectorSpace3D::angle(vP, vQ, vR), angle2 = VectorSpace3D::angle(vR, vS, vP);
    printf("First Angle: %.8f | Second Angle: %.8f | Addition: %.8f | PI: %.8f\n", angle1, angle2, angle1 + angle2, M_PI);
    return ((angle1 + angle2 - .00001) > M_PI) && (!(angle1 == angle2));
}

void VectorSpace3D::flipTriangles(std::vector<VectorSpace3D::Triangle3D> tris, VectorSpace3D::Point3D iP, VectorSpace3D::Point3D iQ, VectorSpace3D::Point3D iR, VectorSpace3D::Point3D iS, int i, int j) {
    tris[i] = VectorSpace3D::Triangle3D{iP, iQ, iS};
    tris[j] = VectorSpace3D::Triangle3D{iS, iQ, iR};
}


bool VectorSpace3D::anyFlipping(std::vector<Triangle3D>* tris){
    if((*tris).size() < 2) {
        return false;
    }
    for(int i = 0; i < (*tris).size(); i++) {
        VectorSpace3D::Point3D t[] {(*tris)[i].points[0], (*tris)[i].points[1], (*tris)[i].points[2]};
        for(int j = i+1; j < (*tris).size(); j++) {
            VectorSpace3D::Point3D u[] {(*tris)[j].points[0], (*tris)[j].points[1], (*tris)[j].points[2]};
            //Look for a common edge of triangles t and u
            for (int h = 0; h < 3; h++) {
                for (int k = 0; k < 3; k++) {
                    if((t[h].x == u[k].x && t[h].y == u[k].y && t[h].z == u[k].z) &&
                            (t[(h+1)%3].x == u[(k+2)%3].x && t[(h+1)%3].y == u[(k+2)%3].y && t[(h+1)%3].z == u[(k+2)%3].z)) {
                        VectorSpace3D::Point3D iP = t[(h+1)%3], iQ = t[(h+2)%3],
                                                iR = t[h], iS = u[(k+1)%3];
                        if(flippingDesirable(iP, iQ, iR, iS)){
                            printf("Flipping\n");
                            printf("Edges: %i and %ii\n", h, k);
                            printf("Triangle i: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[i].points[0].x, (*tris)[i].points[0].y, (*tris)[i].points[0].z,
                                    (*tris)[i].points[1].x, (*tris)[i].points[1].y, (*tris)[i].points[1].z,
                                    (*tris)[i].points[2].x, (*tris)[i].points[2].y, (*tris)[i].points[2].z);
                            printf("Triangle j: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[j].points[0].x, (*tris)[j].points[0].y, (*tris)[j].points[0].z,
                                    (*tris)[j].points[1].x, (*tris)[j].points[1].y, (*tris)[j].points[1].z,
                                    (*tris)[j].points[2].x, (*tris)[j].points[2].y, (*tris)[j].points[2].z);
                            //VectorSpace3D::flipTriangles(tris,iP, iQ, iR, iS, i, j);
                            (*tris)[i] = VectorSpace3D::Triangle3D{iP, iQ, iS};
                            (*tris)[j] = VectorSpace3D::Triangle3D{iS, iQ, iR};

                            printf("Triangle i: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[i].points[0].x, (*tris)[i].points[0].y, (*tris)[i].points[0].z,
                                    (*tris)[i].points[1].x, (*tris)[i].points[1].y, (*tris)[i].points[1].z,
                                    (*tris)[i].points[2].x, (*tris)[i].points[2].y, (*tris)[i].points[2].z);
                            printf("Triangle j: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    (*tris)[j].points[0].x, (*tris)[j].points[0].y, (*tris)[j].points[0].z,
                                    (*tris)[j].points[1].x, (*tris)[j].points[1].y, (*tris)[j].points[1].z,
                                    (*tris)[j].points[2].x, (*tris)[j].points[2].y, (*tris)[j].points[2].z);

                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

float vectorMagnitude(VectorSpace3D::Point3D v1, VectorSpace3D::Point3D v2) {
    return sqrtf(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y,2) + powf(v1.z - v2.z, 2));
}

void VectorSpace3D::World_Object::setObjSize(){
    int vertex1, vertex2;
    float size = vectorMagnitude(vertices[0], vertices[1]);
    for(int i = 0; i < vertices.size(); i++){
        for(int j = 0; j < vertices.size(); j++) {
            float mag = vectorMagnitude(vertices[i], vertices[j]);
            if(mag > size) {
                    size = mag;
                    vertex1 = i;
                    vertex2 = j;
            }
        }
    }
    obj_size = size;
    size_v1 = vertex1;
    size_v2 = vertex2;
}

VectorSpace3D::World_Object::World_Object(float x, float y, float z, const std::vector<Face3D>& shape_faces, const VectorSpace3D::Point3D& viewpoint){
    object_origin = {x, y, z};
    faces = shape_faces;
    for(int i = 0; i < faces.size(); i++) {
        for(int j = 0; j < faces[i].points.size(); j++) {
            vertices.push_back(faces[i].points[j]);
        }
    }
    viewpoint_E = std::move(viewpoint);
    setObjSize();
}

void VectorSpace3D::World_Object::setCameraViewpoint(const VectorSpace3D::Point3D& new_viewpoint){
    viewpoint_E = std::move(new_viewpoint);
}

VectorSpace3D::Point3D VectorSpace3D::World_Object::getCameraViewpoint() const {
    return viewpoint_E;
}


void VectorSpace3D::World_Object::print() const {
    std::cout << "Location: (" << object_origin.x << ", " <<
        object_origin.y << ", " << object_origin.z << ") " <<
        " with " << faces.size() << " number of faces." << std::endl;
}

void VectorSpace3D::World_Object::printEyeSpace() const {
    std::cout << "Number of points: " << eye_point_faces[0].points.size() << " | Number of triangles: " <<
        eye_point_faces[0].triangles.size() << "." << std::endl;
}

void VectorSpace3D::World_Object::setEyePointFaces(const std::vector<VectorSpace3D::Face3D>& epfs) {
    eye_point_faces = std::move(epfs);
}

void VectorSpace3D::World_Object::setScreenCoordinateFaces(const std::vector<VectorSpace3D::Face3D>& scfs) {
    screen_coordinates = std::move(scfs);
}

int VectorSpace3D::World_Object::getNumTriangles() const {
    int num_of_triangles = 0;
    for(int i = 0; i < screen_coordinates.size(); i++){
        num_of_triangles += screen_coordinates[i].triangles.size();
    }
    return num_of_triangles;
}

std::vector<VectorSpace3D::Face3D> VectorSpace3D::World_Object::convertToEyeCoord(){
    //Need to multiply the value of every vertex within the faces by the transformation matrix
    //The transformation matrix is composed of a translation of the origin from O to view point E
    //Rotation about the z-axis to make x-axis perpendicular to plane OE
    //Rotation about the x-axis to make the z-axis collinear with the line OE
    std::vector<Point3D> moved_points;
    std::vector<Face3D> moved_faces;
    printf("Herery");
    float rho = sqrtf((viewpoint_E.x * viewpoint_E.x) + (viewpoint_E.y * viewpoint_E.y) +
                    (viewpoint_E.z * viewpoint_E.z));
    float theta = atan2f(viewpoint_E.y, viewpoint_E.x);
    float phi = acos(viewpoint_E.z / rho);
    for(VectorSpace3D::Face3D fc : faces) {
        moved_points.clear();
        for(VectorSpace3D::Point3D point : fc.points){
            float x_prime = (point.x * -sinf(theta)) + (point.y * cosf(theta));
            float y_prime = (point.x * -cosf(phi) * cosf(theta)) + (point.y * -cosf(phi) * sinf(theta)) +
                (point.z * sinf(phi));
            float z_prime = (point.x * sinf(phi) * cosf(theta)) + (point.y * sinf(phi) * sinf(theta)) +
                (point.z * cosf(phi)) + (point.w * -rho);
            float w_prime = point.w;
            moved_points.push_back(VectorSpace3D::Point3D{x_prime, y_prime, z_prime, w_prime});
        }
        moved_faces.push_back(VectorSpace3D::Face3D{moved_points});
    }

    return moved_faces;
}

std::vector<VectorSpace3D::Face3D> VectorSpace3D::World_Object::convertToScreenCoord(float screenMinMax) {
    //Choose the plane Q such that the plane perpendicular to -z includes Q
    //For each vertex in each face that has been converted to an eye coord,
    //Calculate the screen coordinates through dividing the x&y by z and multiplying by -Z of camera location
    float rho = sqrtf((viewpoint_E.x * viewpoint_E.x) + (viewpoint_E.y * viewpoint_E.y) +
            (viewpoint_E.z * viewpoint_E.z));
    float d = rho * screenMinMax / obj_size;
    std::vector<Point3D> calculated_points;
    std::vector<Face3D> screen_faces;
    printf("Here");
    for(VectorSpace3D::Face3D fc : eye_point_faces){
        calculated_points.clear();
        for(VectorSpace3D::Point3D point : fc.points) {
            float x_coord = (point.x / point.z) * -d;
            float y_coord = (point.y / point.z) * -d;
            calculated_points.push_back(VectorSpace3D::Point3D{x_coord, y_coord, point.z, point.w});
        }
        screen_faces.push_back((VectorSpace3D::Face3D{calculated_points}));
    }
    return screen_faces;
}



void VectorSpace3D::World_Object::triangularizeObject(){
    printf("Size of eye_point_faces: %lu\n", screen_coordinates.size());
    printf("Num of points eye_point_faces: %lu\n", screen_coordinates[0].points.size());
    for(int l = 0; l < screen_coordinates.size(); ++l){
        std::vector<VectorSpace3D::Triangle3D> tr {};
        int next[screen_coordinates[l].points.size()];
        for(int i = 0; i < screen_coordinates[l].points.size(); i++) {
            next[i] = (i + 1) % screen_coordinates[l].points.size();
        }
        for (int k = 0; k < screen_coordinates[l].points.size() - 2; k++){
            VectorSpace3D::Point3D a, b, c;
            bool triangleFound = false;
            int iA = 0, iB = 0, iC = 0, count = 0, nA = 0, nB = 0, nC = 0, j = 0, nj = 0;
            while(!triangleFound && ++count < screen_coordinates[l].points.size()){
                printf("Triagilng\n");
                iB = next[iA], iC = next[iB];
                nA = abs(iA);
                nB = abs(iB);
                nC = abs(iC);
                a = screen_coordinates[l].points[nA];
                b = screen_coordinates[l].points[nB];
                c = screen_coordinates[l].points[nC];
                if(VectorSpace3D::area2(a, b, c) >= 0) {
                    //Edges AB and BC; diagonal AC
                    //Test to see if no other polygon vertex
                    //lies within ABC;
                    j = next[iC];
                    nj = abs(j);
                    while (j != iA &&
                            (nj == nA || nj == nB || nj == nC) ||
                            !insideTriangle(a, b, c, screen_coordinates[l].points[nj])) {
                        printf("Inside Triangle ((%f, %f, %f), (%f,%f,%f), (%f,%f,%f))  & (%f,%f,%f): %i\n",
                                a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z,
                                screen_coordinates[l].points[nj].x,
                                screen_coordinates[l].points[nj].y,
                                screen_coordinates[l].points[nj].z,
                                insideTriangle(a,b,c,screen_coordinates[l].points[nj]));
                        printf("j: %i | iA: %i | nj: %i | nA: %i | nB: %i | nC: %i\n", j, iA, nj, nA, nB, nC);
                        j = next[j];
                        nj = abs(j);
                    }
                    if(j == iA) {
                        tr.push_back(Triangle3D{a, b, c});
                        next[iA] = iC;
                        triangleFound = true;
                    }
                }
                iA = next[iA];
            }

            if(count == screen_coordinates[l].points.size()){
                printf("ERROR: Not a simple polygon or vertex sequence not counter-clockwise\n");
            }
        }
        printf("Flipping\n");
        while (anyFlipping(&tr));
        printf("Finished\n");
        screen_coordinates[l].triangles.swap(tr);
        printf("Fac Triangles Size after swap: %lu\n", screen_coordinates[l].triangles.size());
    }
    printf("Faces Triangles after loop: %lu\n", screen_coordinates[0].triangles.size());
}


bool VectorSpace3D::clockwise(const Point3D p[], int length){
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

std::vector<float> VectorSpace3D::World_Object::createTriangleArray(){
    std::vector<float> triangle_point_list{};
    printf("Number of faces: %lu\n", screen_coordinates.size());
    printf("Number of vertices on face 1: %lu\n", screen_coordinates[0].points.size());
    printf("Number of triangles on face 1: %lu\n", screen_coordinates[0].triangles.size());
    for(Face3D fac: screen_coordinates){
        printf("Triangle Input Array Size: %lu\n", fac.triangles.size());
        for(Triangle3D t : fac.triangles){
            if(!clockwise(t.points, 3)) {
                for(int i = 2; i >= 0; i--) {
                    printf("Clockwise\n");
                    triangle_point_list.push_back(t.points[i].x);
                    triangle_point_list.push_back(t.points[i].y);
                    triangle_point_list.push_back(t.points[i].z);
                }
            } else {
                for(int i = 0; i < 3; i++) {
                    printf("Not Clockwise\n");
                    triangle_point_list.push_back(t.points[i].x);
                    triangle_point_list.push_back(t.points[i].y);
                    triangle_point_list.push_back(t.points[i].z);
                }
            }
        }
    }
    printf("Triangle Point List Size b4 return: %lu\n", triangle_point_list.size());
    return triangle_point_list;
}
