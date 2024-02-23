#include "matrix.h"
#include "vector.h"

namespace LML {
    LML::mat4x4::mat4x4() {
        columns[0] = vector_4f(1, 0, 0, 0);
        columns[1] = vector_4f(0, 1, 0, 0);
        columns[2] = vector_4f(0, 0, 1, 0);
        columns[3] = vector_4f(0, 0, 0, 1);
    }

    LML::mat4x4::mat4x4(vector_4f a, vector_4f b, vector_4f c, vector_4f d) {
        columns[0] = a;
        columns[1] = b;
        columns[2] = c;
        columns[3] = d;
    }

    LML::vector_4f operator*(const mat4x4& M, const vector_4f& V) {
        return vector_4f(
                M[0][0] * V[0] + M[1][0] * V[1] + M[2][0] * V[2] + M[3][0] * V[3],
                M[0][1] * V[0] + M[1][1] * V[1] + M[2][1] * V[2] + M[3][1] * V[3],
                M[0][2] * V[0] + M[1][2] * V[1] + M[2][2] * V[2] + M[3][2] * V[3],
                M[0][3] * V[0] + M[1][3] * V[1] + M[2][3] * V[2] + M[3][3] * V[3]);
    }

    LML::mat4x4 operator*(const mat4x4& M, const mat4x4& M2){
        vector_4f x = M * M2[0];
        vector_4f y = M * M2[1];
        vector_4f z = M * M2[2];
        vector_4f w = M * M2[3];

        return mat4x4(x, y, z, w);
    }
}
