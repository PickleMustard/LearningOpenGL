#include <algorithm>
#include <eigen3/Eigen/Dense>
#include <GL/glew.h>
#include <cstdlib>
//#define GLFW_DLL
#define GL_LOG_FILE "gl.log"
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdarg.h>
#include <fstream>
#include <cassert>

#include "InitHelp/InitializeOpenGL.h"
#include "VectorMathAndObjects/Vector2D.h"
#include "InitHelp/PolygonInputFileParser.h"
#include "Vector3D.h"
#include "GLObjects/EBO.h"
#include "GLObjects/VAO.h"
#include "GLObjects/VBO.h"

bool restart_gl_log() {
    FILE* file = fopen(GL_LOG_FILE, "w");
    if(!file) {
        fprintf(stderr,
                "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
                GL_LOG_FILE);
        return false;
    }
    time_t now = time(NULL);
    char* date = ctime(&now);
    fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
    fclose(file);
    return true;
}

bool gl_log(const char* message, ...) {
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file){
        fprintf(
                stderr,
                "ERROR: could not open GL_LOG_FILE %s file for appending\n",
                GL_LOG_FILE
               );
        return false;
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

bool gl_log_err(const char* message, ...) {
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file) {
        fprintf(stderr,
                "ERROR: could not open GL_LOG_FILE %s file for appending\n",
                GL_LOG_FILE);
        return false;
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    va_start(argptr, message);
    vfprintf(stderr, message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

void _print_shader_info_log(GLuint shader_index){
    int max_length = 2048;
    int actual_length = 0;
    char shader_log[2048];
    glGetShaderInfoLog(shader_index, max_length, &actual_length, shader_log);
    printf("shader info log for GL index %u: \n%s\n", shader_index, shader_log);
}

void glfw_error_callback(int error, const char* description) {
    gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}


int main(int argc, char* argv[]) {
    if(argc < 4){
        printf("The format should be 2 Shader files, Shape File, Degrees of Rotation");
        return 0;
    }

    //Assert the clearing and opening of the log
    assert(restart_gl_log());
    gl_log("Starting GLFW\n%s\n", glfwGetVersionString());
    glfwSetErrorCallback(glfw_error_callback);


    //Library Initialization
    if(!glfwInit()){
        return -1;
    }


    //Declarations
    int height, width, num_of_inputs, deg_of_rotation, num_of_monitors;
    GLFWmonitor** mon = glfwGetMonitors(&num_of_monitors);
    printf("%p\n", mon);
    const GLFWvidmode* vmode = glfwGetVideoMode(*mon);
    GLFWwindow* window;
    std::ifstream shader_file_input;
    std::string vertex_shader_string, fragment_shader_string;

    VectorSpace2D::Polygon2D p = pif::readPolygonInputFile(argv[3]);

    GLfloat points[] = {
        0.0f, 0.7f, -5.0f,
        0.5f, -0.5f, -5.0f,
        -0.5f, -0.5f, -5.0f,
        0.5f, 0.5f, 5.0f,
        0.5f, -0.5f, 5.0f,
        0.0f, 0.7f, 5.0f,
        -0.5f, 0.5f, 1.0f,
        0.0f, 0.7f, 1.0f,
        -0.5f,-0.5f, 2.0f
    };

    std::vector<VectorSpace3D::Point3D> object_vertices{VectorSpace3D::Point3D{-1.0f,-1.0f,-1.0f,0.0f}, VectorSpace3D::Point3D{1.0f,-1.0f,-1.0f,0.0f},
                                                        VectorSpace3D::Point3D{1.0f,1.0f,-1.0f,0.0f}, VectorSpace3D::Point3D{-1.0f,1.0f,-1.0f,0.0f},
                                                        VectorSpace3D::Point3D{-1.0f,-1.0f,1.0f,0.0f}, VectorSpace3D::Point3D{1.0f,-1.0f,1.0f,0.0f},
                                                        VectorSpace3D::Point3D{1.0f,1.0f,1.0f,0.0f}, VectorSpace3D::Point3D{-1.0f,1.0f,1.0f,0.0f}};
    std::vector<std::vector<int>> object_faces{};
    std::vector<int> fac{}, fac2{};
    fac.push_back(0);
    fac.push_back(1);
    fac.push_back(5);
    fac.push_back(4);
    object_faces.push_back(fac);
    fac.clear();
    fac.push_back(1);
    fac.push_back(2);
    fac.push_back(6);
    fac.push_back(5);
    object_faces.push_back(fac);
    fac.clear();
    fac.push_back(2);
    fac.push_back(3);
    fac.push_back(7);
    fac.push_back(6);
    object_faces.push_back(fac);
    fac.clear();
    fac.push_back(3);
    fac.push_back(0);
    fac.push_back(4);
    fac.push_back(7);
    object_faces.push_back(fac);
    fac.clear();
    fac.push_back(4);
    fac.push_back(5);
    fac.push_back(6);
    fac.push_back(7);
    object_faces.push_back(fac);
    fac.clear();
    fac.push_back(3);
    fac.push_back(2);
    fac.push_back(1);
    fac.push_back(0);
    object_faces.push_back(fac);


    VectorSpace3D::World_Object obj{1,1,1, object_vertices, object_faces, VectorSpace3D::Point3D{0.0f, 0.0f, 0.0f, 0.0f}};

    obj.convertToEyeCoord();
    obj.convertToScreenCoord(std::max(height, width));
    printf("Triangularizing\n");
    obj.triangularizeObject();
    obj.printEyeSpace();


    VectorSpace2D::Triangle2D triangle {VectorSpace2D::Pointf2D{0.0f, 0.5f, 0.5f},
        VectorSpace2D::Pointf2D{0.5f, -0.5f, 0.0f},
        VectorSpace2D::Pointf2D{-0.5f, -0.5f, 0.0f}};

    VectorSpace2D::Pointf2D square_vert[] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

    VectorSpace2D::Polygon2D square {4, {}, square_vert};
    //printf("Number of vertices: %i\n", p.num_of_points);
    //p.triangles = VectorSpace2D::triangularizePolygon(p);

    //printf("Size of triangles %lu\n", square.triangles.size());

    std::vector<VectorSpace2D::Triangle2D> tris {triangle};

    //std::vector<float> new_points = VectorSpace2D::createTriangleArray(p.triangles);
    //Redo the floats as GLFloats, combine into 1 array
    std::vector<GLfloat> new_points = obj.createTriangleArray();
    std::vector<GLfloat> normal_points = obj.createNormalArray(new_points);
    std::vector<GLfloat> color_points = obj.createColorArray(new_points);
    std::vector<GLuint> indices = obj.createIndexArray();

    printf("Number of points: %lu\n", new_points.size());
    for(int i = 0; i < new_points.size(); i+=3){
        printf("Point (%f, %f, %f)\n", new_points[i], new_points[i+1], new_points[i+2]);
    }
    num_of_inputs = new_points.size();
    float* new_float_points = &new_points[0];
    printf("Num of triangles: %i\n", obj.getNumTriangles());


    deg_of_rotation = atof(argv[4]);

    //Parse the shader files
    vertex_shader_string = glhelpers::parseShaderFile(argv[1]);
    const char* vertex_shader = vertex_shader_string.c_str();
    fragment_shader_string = glhelpers::parseShaderFile(argv[2]);
    const char* fragment_shader = fragment_shader_string.c_str();

    //Set OpenGL Version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Only using the CORE functionality of OpenGL, no need for compatability with previous versions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Anti-Aliasing
    //glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(vmode->width, vmode->height, "Window", *mon, NULL);
    if(!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    glfwGetFramebufferSize(window ,&width, &height);
    //glViewport(0,0,width, height);
    //

    VAO object_Vao;
    object_Vao.Bind();

    VBO object_Vbo(&new_points[0], sizeof(points));

    EBO object_Ebo(&indices[0], sizeof(indices));
    //
    //
    /*
    //The VAO must be generated before the VBO
    GLuint vao = 0, snao = 0, colorbufferao = 0;
    GLuint vbo = 0, snbo = 0, colorbuffer = 0;
    //Generate VAO
    glGenVertexArrays(1, &vao);
    //Generate the buffer array bound to vbo
    glGenBuffers(1, &vbo);

    //Bind it
    glBindVertexArray(vao);

    //Bind the vertex buffer to the OpenGL Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (9 * obj.getNumTriangles()) * sizeof(float), points, GL_STATIC_DRAW);

    //0 define the layout for attribute # 0.
    //3 manes the variables are vec3 of type GL_FLOAT
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float) , 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    //glhelpers::initalizeVertexBufferObject(vbo, obj.getNumTriangles(), &new_points[0]);
    glhelpers::initalizeVertexBufferObject(snbo, obj.getNumTriangles(), &normal_points[0]);
    glhelpers::initalizeVertexBufferObject(colorbuffer, obj.getNumTriangles(), &color_points[0]);

    //glGenBuffers(1, &colorbuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    //glhelpers::initalizeVertexBufferObject(vbo, 3, &new_points[0]);
    //glhelpers::initalizeVertexBufferObject(vbo, 2, points);

    glhelpers::initializeVertexArrayObject(vao, vbo);
    glhelpers::initializeNormalArrayObject(snao, snbo);
    //Generate VAO
    glGenVertexArrays(1, &colorbufferao);
    //Bind it
    glBindVertexArray(colorbufferao);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    */
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if(GL_TRUE != params){
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
        _print_shader_info_log(vs);
        return false;
    }
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if(GL_TRUE != params){
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
        _print_shader_info_log(fs);
        return false;
    }
    GLuint shader_programme = glCreateProgram();
    //Attach the shaders to the created program
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    //Links the created shader program into the gl API
    glLinkProgram(shader_programme);

    object_Vao.LinkAttrib(object_Vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    object_Vao.LinkAttrib(object_Vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    object_Vao.Unbind();
    object_Vbo.Unbind();
    object_Ebo.Unbind();

    //Get the uniform value "Scale" from the vertex shader
    GLuint uniID = glGetUniformLocation(shader_programme, "scale");

    //std::vector<
    printf("Size of indicies: %lu ", sizeof(indices));



    //Changes the color of the background
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

    printf("Entering the While Loop\n");
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glUniform1f(uniID, 0.0f);
        object_Vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, num_of_inputs);
        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();

        int mouse_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        int k_state = glfwGetKey(window, GLFW_KEY_K), s_state = glfwGetKey(window, GLFW_KEY_S),
            j_state = glfwGetKey(window, GLFW_KEY_J), d_state = glfwGetKey(window, GLFW_KEY_D);
        int u_state = glfwGetKey(window, GLFW_KEY_U), w_state = glfwGetKey(window, GLFW_KEY_W),
            i_state = glfwGetKey(window, GLFW_KEY_I), e_state = glfwGetKey(window, GLFW_KEY_E);
        int up_state = glfwGetKey(window, GLFW_KEY_UP), left_state = glfwGetKey(window, GLFW_KEY_LEFT),
            down_state = glfwGetKey(window, GLFW_KEY_DOWN), right_state = glfwGetKey(window, GLFW_KEY_RIGHT);
        int back_state = glfwGetKey(window, GLFW_KEY_2), forward_state = glfwGetKey(window, GLFW_KEY_2);
        int close_state = glfwGetKey(window, GLFW_KEY_ESCAPE);

        /*
        if(mouse_state == GLFW_PRESS) {
            //printf("rotating\n");
            VectorSpace2D::rotateShape(deg_of_rotation, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(close_state == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
        if(k_state == GLFW_PRESS) {
            VectorSpace2D::scaleShape(2, 1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }

        if(s_state == GLFW_PRESS) {
            VectorSpace2D::scaleShape(.5, 1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(j_state == GLFW_PRESS) {
            VectorSpace2D::scaleShape(1, 2, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(d_state == GLFW_PRESS) {
            VectorSpace2D::scaleShape(1, .5, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(u_state == GLFW_PRESS) {
            VectorSpace2D::shearShape(2, 1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }

        if(w_state == GLFW_PRESS) {
            VectorSpace2D::shearShape(-2, 1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(i_state == GLFW_PRESS) {
            VectorSpace2D::shearShape(2, 1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(e_state == GLFW_PRESS) {
            VectorSpace2D::shearShape(-2, 0, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(up_state == GLFW_PRESS) {
            VectorSpace2D::translateShape(0, .1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }

        if(left_state == GLFW_PRESS) {
            VectorSpace2D::translateShape(-.1, 0, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(down_state == GLFW_PRESS) {
            VectorSpace2D::translateShape(0, -.1, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(right_state == GLFW_PRESS) {
            VectorSpace2D::translateShape(.1, 0, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);
        }
        if(back_state == GLFW_PRESS) {
            VectorSpace2D::translateShapeZ(-100, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);

        }
        if(forward_state == GLFW_PRESS) {
            VectorSpace2D::translateShapeZ(100, &new_points[0], new_points.size());
            glhelpers::initalizeVertexBufferObject(vbo, p.triangles.size(), &new_points[0]);
            glhelpers::initializeVertexArrayObject(vao, vbo);

        }
        /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        glfwSwapBuffers(window);*/
    }

    object_Vao.Delete();
    object_Vbo.Delete();

    //glDeleteVertexArrays(1, &vao);
    //glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_programme);

    glfwTerminate();
    return 0;
}
