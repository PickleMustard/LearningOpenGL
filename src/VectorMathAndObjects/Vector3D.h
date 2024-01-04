#pragma once
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>

namespace VectorSpace3D {
    struct Point3D {
        float x {};
        float y {};
        float z {};
        float w {}; //Create homogenous system
    };

    struct Triangle3D {
        Point3D points[3];
    };

    struct Face3D {
        std::vector<Point3D> points {};
        std::vector<Triangle3D> triangles {};
    };

    float area2(const Point3D& a, const Point3D& b, const Point3D& c);
    bool insideTriangle(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& p);
    float angle(const Point3D& a, const Point3D& b, const Point3D& c);
    bool flippingDesirable(Point3D iP, Point3D iQ, Point3D iR, Point3D iS);
    void flipTriangles(std::vector<Triangle3D> tris, Point3D iP, Point3D iQ, Point3D iR, Point3D iS, int i, int j);
    bool anyFlipping(std::vector<Triangle3D>* tris);
    bool clockwise(const Point3D p[], int length);

    class World_Object {
        private:
            Point3D object_origin;
            Point3D viewpoint_E;
            std::vector<Face3D> faces;
            std::vector<Face3D> eye_point_faces;
            std::vector<Face3D> screen_coordinates;
            std::vector<Point3D> vertices;
            float obj_size;
            int size_v1, size_v2;

            void setObjSize();


        public:
            World_Object(float x, float y, float z, const std::vector<Face3D>& shape_faces, const Point3D& camera_viewpoint);
            Point3D getLocation() const;
            Point3D getCameraViewpoint() const;
            void setCameraViewpoint(const Point3D& new_viewpoint);
            int getNumTriangles() const;
            void setEyePointFaces(const std::vector<Face3D>& epfs);
            void setScreenCoordinateFaces(const std::vector<Face3D>& scfs);
            void print() const;
            void printEyeSpace() const;
            std::vector<Face3D> convertToEyeCoord();
            std::vector<Face3D> convertToScreenCoord(float screenMinMax);
            void triangularizeObject();
            std::vector<float> createTriangleArray();

    };

}



#endif

