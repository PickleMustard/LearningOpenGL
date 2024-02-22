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


bool VectorSpace3D::flippingDesirable(int iP, int iQ, int iR, int iS, const std::vector<VectorSpace3D::Point3D> vertices){
    int vP = iP, vQ = iQ, vR = iR, vS = iS;
    float angle1 = VectorSpace3D::angle(vertices[vP], vertices[vQ], vertices[vR]), angle2 = VectorSpace3D::angle(vertices[vR], vertices[vS], vertices[vP]);
    printf("First Angle: %.8f | Second Angle: %.8f | Addition: %.8f | PI: %.8f\n", angle1, angle2, angle1 + angle2, M_PI);
    return ((angle1 + angle2 - .00001) > M_PI) && (!(angle1 == angle2));
}

//Flips around the vertices stored in triangles i and j
void VectorSpace3D::flipTriangles(std::vector<VectorSpace3D::Triangle3D> tris, int iP, int iQ, int iR, int iS, int i, int j) {
    tris[i] = VectorSpace3D::Triangle3D{iP, iQ, iS};
    tris[j] = VectorSpace3D::Triangle3D{iS, iQ, iR};
}


bool VectorSpace3D::anyFlipping(std::vector<Triangle3D>* tris, const std::vector<VectorSpace3D::Point3D> vertices){
    if((*tris).size() < 2) {
        return false;
    }
    for(int i = 0; i < (*tris).size(); i++) {
        int t[] {(*tris)[i].vertices[0], (*tris)[i].vertices[1], (*tris)[i].vertices[2]};
        for(int j = i+1; j < (*tris).size(); j++) {
            int u[] {(*tris)[j].vertices[0], (*tris)[j].vertices[1], (*tris)[j].vertices[2]};
            //Look for a common edge of triangles t and u
            for (int h = 0; h < 3; h++) {
                for (int k = 0; k < 3; k++) {
                    if((vertices[t[h]].x == vertices[u[k]].x && vertices[t[h]].y == vertices[u[k]].y && vertices[t[h]].z == vertices[u[k]].z) &&
                            (vertices[t[(h+1)%3]].x == vertices[u[(k+2)%3]].x && vertices[t[(h+1)%3]].y == vertices[u[(k+2)%3]].y && vertices[t[(h+1)%3]].z == vertices[u[(k+2)%3]].z)) {
                        int iP = t[(h+1)%3], iQ = t[(h+2)%3],
                                                iR = t[h], iS = u[(k+1)%3];
                        if(flippingDesirable(iP, iQ, iR, iS, vertices)){
                            printf("Flipping\n");
                            printf("Edges: %i and %ii\n", h, k);
                            printf("Triangle i: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    vertices[(*tris)[i].vertices[0]].x, vertices[(*tris)[i].vertices[0]].y, vertices[(*tris)[i].vertices[0]].z,
                                    vertices[(*tris)[i].vertices[1]].x, vertices[(*tris)[i].vertices[1]].y, vertices[(*tris)[i].vertices[1]].z,
                                    vertices[(*tris)[i].vertices[2]].x, vertices[(*tris)[i].vertices[2]].y, vertices[(*tris)[i].vertices[2]].z);
                            printf("Triangle j: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    vertices[(*tris)[j].vertices[0]].x, vertices[(*tris)[j].vertices[0]].y, vertices[(*tris)[j].vertices[0]].z,
                                    vertices[(*tris)[j].vertices[1]].x, vertices[(*tris)[j].vertices[1]].y, vertices[(*tris)[j].vertices[1]].z,
                                    vertices[(*tris)[j].vertices[2]].x, vertices[(*tris)[j].vertices[2]].y, vertices[(*tris)[j].vertices[2]].z);
                            //VectorSpace3D::flipTriangles(tris,iP, iQ, iR, iS, i, j);
                            (*tris)[i] = VectorSpace3D::Triangle3D{iP, iQ, iS};
                            (*tris)[j] = VectorSpace3D::Triangle3D{iS, iQ, iR};

                            printf("Triangle i: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    vertices[(*tris)[i].vertices[0]].x, vertices[(*tris)[i].vertices[0]].y, vertices[(*tris)[i].vertices[0]].z,
                                    vertices[(*tris)[i].vertices[1]].x, vertices[(*tris)[i].vertices[1]].y, vertices[(*tris)[i].vertices[1]].z,
                                    vertices[(*tris)[i].vertices[2]].x, vertices[(*tris)[i].vertices[2]].y, vertices[(*tris)[i].vertices[2]].z);
                            printf("Triangle j: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
                                    vertices[(*tris)[j].vertices[0]].x, vertices[(*tris)[j].vertices[0]].y, vertices[(*tris)[j].vertices[0]].z,
                                    vertices[(*tris)[j].vertices[1]].x, vertices[(*tris)[j].vertices[1]].y, vertices[(*tris)[j].vertices[1]].z,
                                    vertices[(*tris)[j].vertices[2]].x, vertices[(*tris)[j].vertices[2]].y, vertices[(*tris)[j].vertices[2]].z);


                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

//Get the non-normalized magnitude of the vector between two points in world space
float vectorMagnitude(VectorSpace3D::Point3D v1, VectorSpace3D::Point3D v2) {
    return sqrtf(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y,2) + powf(v1.z - v2.z, 2));
}


//Get the size of the object by comparing each vertex with each other
//The greatest distance between verticies is used as the size of the object in world space
//Keeps the indicies of the vertexes that are furthest from each other
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

//The constructor will take the following:
//An x, y, and z coordinate defining the central point of the object in world space
//A vector list of the vertexes that construct the object
//A vector list of arrays of integers defining the indices of the vertexes that construct each face
//The viewpoint of the camera within world space
VectorSpace3D::World_Object::World_Object(float x, float y, float z, const std::vector<VectorSpace3D::Point3D> vertex_list,
        const std::vector<std::vector<int>> shape_faces, const VectorSpace3D::Point3D& viewpoint){
    object_origin = {x, y, z};
    input_faces = shape_faces;
    vertices = vertex_list;
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
        " with " << input_faces.size() << " number of faces." << std::endl;
}

void VectorSpace3D::World_Object::printEyeSpace() const {
    std::cout << "Number of points: " << eye_point_vertices.size() << std::endl;
}

int VectorSpace3D::World_Object::getNumTriangles() const {
    int num_of_triangles = 0;
    for(int i = 0; i < triangularized_faces.size(); i++){
        num_of_triangles += triangularized_faces[i].triangles.size();
    }
    return num_of_triangles;
}

void VectorSpace3D::World_Object::convertToEyeCoord(){
    //Need to multiply the value of every vertex within the faces by the transformation matrix
    //The transformation matrix is composed of a translation of the origin from O to view point E
    //Rotation about the z-axis to make x-axis perpendicular to plane OE
    //Rotation about the x-axis to make the z-axis collinear with the line OE
    float rho = sqrtf((viewpoint_E.x * viewpoint_E.x) + (viewpoint_E.y * viewpoint_E.y) +
                    (viewpoint_E.z * viewpoint_E.z));
    float theta = atan2f(viewpoint_E.y, viewpoint_E.x);
    float phi = acos(viewpoint_E.z / rho);
    for(VectorSpace3D::Point3D fc : vertices) {
        float x_prime = (fc.x * -sinf(theta)) + (fc.y * cosf(theta));
        float y_prime = (fc.x * -cosf(phi) * cosf(theta)) + (fc.y * -cosf(phi) * sinf(theta)) +
            (fc.z * sinf(phi));
        float z_prime = (fc.x * sinf(phi) * cosf(theta)) + (fc.y * sinf(phi) * sinf(theta)) +
            (fc.z * cosf(phi)) + (fc.w * -rho);
        float w_prime = fc.w;
        eye_point_vertices.push_back(VectorSpace3D::Point3D{x_prime, y_prime, z_prime, w_prime});
    }
}

void VectorSpace3D::World_Object::convertToScreenCoord(float screenMinMax) {
    //Choose the plane Q such that the plane perpendicular to -z includes Q
    //For each vertex in each face that has been converted to an eye coord,
    //Calculate the screen coordinates through dividing the x&y by z and multiplying by -Z of camera location
    float rho = sqrtf((viewpoint_E.x * viewpoint_E.x) + (viewpoint_E.y * viewpoint_E.y) +
            (viewpoint_E.z * viewpoint_E.z));
    float d = rho * screenMinMax / obj_size;
    //Go through each vertex and convert it to the screen coordinates
    for(VectorSpace3D::Point3D vertex : eye_point_vertices) {
        float x_coord = (vertex.x / vertex.z) * -d;
        float y_coord = (vertex.y / vertex.z) * -d;
        screen_point_vertices.push_back(VectorSpace3D::Point3D{x_coord, y_coord, vertex.z, vertex.w});
    }
}


//Convert a world object into a vector of 3D triangles
//
void VectorSpace3D::World_Object::triangularizeObject(){
    //Go through each of the faces in screen coordinates
    for(int l = 0; l < input_faces.size(); ++l) {
        std::vector<VectorSpace3D::Triangle3D> tr {};
        //Construct an array of indices corresponding to the next vertex index in screen coordinates
        int next[input_faces[l].size()];
        for(int i = 0; i < input_faces[l].size(); i++) {
            next[i] = (i + 1) % input_faces[l].size();
        }
        for (int k = 0; k < input_faces[l].size() - 2; k++){
            int a, b, c;
            bool triangleFound = false;
            int iA = 0, iB = 0, iC = 0, count = 0, nA = 0, nB = 0, nC = 0, j = 0, nj = 0;
            while(!triangleFound && ++count < input_faces[l].size()){
                printf("Triangling\n");
                iB = next[iA], iC = next[iB];
                nA = abs(iA);
                nB = abs(iB);
                nC = abs(iC);
                a = input_faces[l][nA];
                b = input_faces[l][nB];
                c = input_faces[l][nC];
                if(VectorSpace3D::area2(vertices[a], vertices[b], vertices[c]) >= 0) {
                    //Edges AB and BC; diagonal AC
                    //Test to see if no other polygon vertex
                    //lies within ABC;
                    j = next[iC];
                    nj = abs(j);
                    while (j != iA &&
                            (nj == nA || nj == nB || nj == nC) ||
                            !insideTriangle(vertices[a], vertices[b], vertices[c], vertices[input_faces[l][nj]])) {
                        printf("Inside Triangle ((%f, %f, %f), (%f,%f,%f), (%f,%f,%f))  & (%f,%f,%f): %i\n",
                                vertices[a].x, vertices[a].y, vertices[a].z, vertices[b].x, vertices[b].y, vertices[b].z, vertices[c].x, vertices[c].y, vertices[c].z,
                                vertices[input_faces[l][nj]].x,
                                vertices[input_faces[l][nj]].y,
                                vertices[input_faces[l][nj]].z,
                                insideTriangle(vertices[a], vertices[b], vertices[c], vertices[input_faces[l][nj]]));
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

            if(count == input_faces[l].size()){
                printf("ERROR: Not a simple polygon or vertex sequence not counter-clockwise\n");
            }
        }
        printf("Flipping\n");
        while (anyFlipping(&tr, vertices));
        printf("Finished\n");
        triangularized_faces.push_back(VectorSpace3D::Face3D {tr});
        printf("Fac Triangles Size after swap: %lu\n", input_faces[l].size());
    }
    printf("Faces Triangles after loop: %i\n", getNumTriangles());
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

std::vector<GLuint> VectorSpace3D::World_Object::createIndexArray() {
    std::vector<GLuint> index_array{};
    for(Face3D fac: triangularized_faces) {
        for(Triangle3D t: fac.triangles) {
            index_array.push_back(t.vertices[0]);
            index_array.push_back(t.vertices[1]);
            index_array.push_back(t.vertices[2]);
        }
    }
    return index_array;
}

std::vector<GLfloat> VectorSpace3D::World_Object::createTriangleArray(){
    std::vector<GLfloat> triangle_point_list{};
    printf("Number of faces: %lu\n", triangularized_faces.size());
    printf("Number of triangles on face 1: %lu\n", triangularized_faces[0].triangles.size());
    for(Face3D fac: triangularized_faces){
        printf("Triangle Input Array Size: %lu\n", fac.triangles.size());
        for(Triangle3D t : fac.triangles){
            Point3D p[] = {vertices[t.vertices[0]], vertices[t.vertices[1]], vertices[t.vertices[2]]};
            if(!clockwise(p, 3)) {
                for(int i = 2; i >= 0; i--) {
                    printf("Clockwise\n");
                    triangle_point_list.push_back(vertices[t.vertices[i]].x);
                    triangle_point_list.push_back(vertices[t.vertices[i]].y);
                    triangle_point_list.push_back(vertices[t.vertices[i]].z);
                    triangle_point_list.push_back(0.8f);
                    triangle_point_list.push_back(0.3f);
                    triangle_point_list.push_back(0.02f);
                }
            } else {
                for(int i = 0; i < 3; i++) {
                    printf("Not Clockwise\n");
                    triangle_point_list.push_back(vertices[t.vertices[i]].x);
                    triangle_point_list.push_back(vertices[t.vertices[i]].y);
                    triangle_point_list.push_back(vertices[t.vertices[i]].z);
                    triangle_point_list.push_back(0.8f);
                    triangle_point_list.push_back(0.3f);
                    triangle_point_list.push_back(0.02f);
                }
            }
        }
    }
    printf("Triangle Point List Size b4 return: %lu\n", triangle_point_list.size());
    return triangle_point_list;
}


std::vector<GLfloat> VectorSpace3D::World_Object::createNormalArray(const std::vector<float> point_list) {
    std::vector<float> normal_point_list{};
    float normX = 0, normY = 0, normZ = 0;
    for(int i = 0; i < point_list.size(); i+=9) {
        normX = (point_list[4] - point_list[1]) * (point_list[8] - point_list[5]) - (point_list[5]-point_list[2]) * (point_list[7] - point_list[4]);
        normY = (point_list[5] - point_list[2]) * (point_list[6] - point_list[3]) - (point_list[3]-point_list[0]) * (point_list[8] - point_list[5]);
        normZ = (point_list[3] - point_list[0]) * (point_list[7] - point_list[4]) - (point_list[4]-point_list[1]) * (point_list[6] - point_list[3]);
        normal_point_list.push_back(normX);
        normal_point_list.push_back(normY);
        normal_point_list.push_back(normZ);
    }

    return normal_point_list;

}

std::vector<GLfloat> VectorSpace3D::World_Object::createColorArray(const std::vector<float> point_list) {
    std::vector<float> color_point_list{};
    float r_value = 0, g_value = 0, b_value = 0;
    for(int i = 0; i < point_list.size(); i+=9){
        r_value = i;
        g_value = i;
        b_value = i;
        color_point_list.push_back(r_value);
        color_point_list.push_back(g_value);
        color_point_list.push_back(b_value);
    }
    return color_point_list;
}
