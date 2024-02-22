#pragma once
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
#include <GL/glew.h>

namespace VectorSpace3D {
    struct Point3D {
        float x {};
        float y {};
        float z {};
        float w {}; //Create homogenous system
    };

    struct Triangle3D {
       int vertices[3];
    };

    struct Face3D {
        std::vector<Triangle3D> triangles {};
    };

    float area2(const Point3D& a, const Point3D& b, const Point3D& c);
    bool insideTriangle(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& p);
    float angle(const Point3D& a, const Point3D& b, const Point3D& c);
    bool flippingDesirable(int iP, int iQ, int iR, int iS, std::vector<Point3D> vertices);
    void flipTriangles(std::vector<Triangle3D> tris, int iP, int iQ, int iR, int iS, int i, int j);
    bool anyFlipping(std::vector<Triangle3D>* tris, const std::vector<Point3D> vertices);
    bool clockwise(const Point3D p[], int length);

    class World_Object {
        private:
            Point3D object_origin;
            Point3D viewpoint_E;
            std::vector<std::vector<int>> input_faces;
            std::vector<Face3D> triangularized_faces;
            std::vector<Point3D> vertices;
            std::vector<Point3D> eye_point_vertices;
            std::vector<Point3D> screen_point_vertices;
            float obj_size;
            int size_v1, size_v2;

            void setObjSize();


        public:
            World_Object(float x, float y, float z, const std::vector<VectorSpace3D::Point3D> vertex_list,
            const std::vector<std::vector<int>> shape_faces, const VectorSpace3D::Point3D& viewpoint);
            Point3D getLocation() const;
            Point3D getCameraViewpoint() const;
            void setCameraViewpoint(const Point3D& new_viewpoint);
            int getNumTriangles() const;
            void setEyePointFaces(const std::vector<Face3D>& epfs);
            void setScreenCoordinateFaces(const std::vector<Face3D>& scfs);
            void print() const;
            void printEyeSpace() const;
            void convertToEyeCoord();
            void convertToScreenCoord(float screenMinMax);
            void triangularizeObject();
            std::vector<GLuint> createIndexArray();
            std::vector<GLfloat> createTriangleArray();
            std::vector<GLfloat> createNormalArray(const std::vector<GLfloat> point_array);
            std::vector<GLfloat> createColorArray(const std::vector<GLfloat> point_array);

    };

}



#endif

