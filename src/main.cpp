#include <GL/glew.h>
#define GLFW_DLL
#define GL_LOG_FILE "gl.log"
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdarg.h>
#include <fstream>
#include <cassert>

#include "InitHelp/InitializeOpenGL.h"
#include "VectorMathAndObjects/Vector2D.h"

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
    //Declarations
    int height, width, num_of_inputs;
    GLFWwindow *window;
    std::ifstream shader_file_input;
    std::string vertex_shader_string, fragment_shader_string;

    float points[] = {
        0.0f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    VectorSpace2D::Triangle2D triangle {VectorSpace2D::Pointf2D{0.0f, 0.5f, 0.5f},
        VectorSpace2D::Pointf2D{0.5f, -0.5f, 0.0f},
        VectorSpace2D::Pointf2D{-0.5f, -0.5f, 0.0f}};

    VectorSpace2D::Pointf2D square_vert[] = {{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}};

    VectorSpace2D::Polygon2D square {4, {}, square_vert};
    square.triangles = VectorSpace2D::triangularizePolygon(square);

    printf("Size of triangles %lu\n", square.triangles.size());

    std::vector<VectorSpace2D::Triangle2D> tris {triangle};

    std::vector<float> new_points = VectorSpace2D::createTriangleArray(square.triangles);
    printf("triangles size %lu\n", square.triangles.size());
    /*for(VectorSpace2D::Triangle2D t : square.triangles) {
        printf("Triangle Point 0: x, y, z | %f, %f, %f\n", t.t_points[0].x, t.t_points[0].y, t.t_points[0].z);
        printf("Triangle Point 1: x, y, z | %f, %f, %f\n", t.t_points[1].x, t.t_points[1].y, t.t_points[1].z);
        printf("Triangle Point 2: x, y, z | %f, %f, %f\n", t.t_points[2].x, t.t_points[2].y, t.t_points[2].z);
    }*/

    for(float f: new_points) {
        printf("Printing point: %f\n", f);
    }
    num_of_inputs = new_points.size();
    float* new_float_points = &new_points[0];
    for(float f : new_points) {
        printf("%f ", f);
    }
    printf(" | End of float list\n");

    if(argc < 2){
        printf("Needs at least 2 shader file inputs.");
        return 0;
    }
    //Assert the clearing and opening of the log
    assert(restart_gl_log());
    gl_log("Starting GLFW\n%s\n", glfwGetVersionString());
    glfwSetErrorCallback(glfw_error_callback);

    //Parse the shader files
    vertex_shader_string = glhelpers::parseShaderFile(argv[1]);
    const char* vertex_shader = vertex_shader_string.c_str();
    fragment_shader_string = glhelpers::parseShaderFile(argv[2]);
    const char* fragment_shader = fragment_shader_string.c_str();

    //Library Initialization
    if(!glfwInit()){
        return -1;
    }

    //Set OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Anti-Aliasing
    //glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
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
    glDepthFunc(GL_LESS);

    glfwGetFramebufferSize(window ,&width, &height);
    //glViewport(0,0,width, height);

    GLuint vbo = 0;
    glhelpers::initalizeVertexBufferObject(vbo, 2, &new_points[0]);

    GLuint vao = 0, vao2 = 0;
    glhelpers::initializeVertexArrayObject(vao, vbo);
    glhelpers::initializeVertexArrayObject(vao2, vbo);

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
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    //Changes the color of the background
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, num_of_inputs);

        glfwPollEvents();

        glfwSwapBuffers(window);

        /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        glfwSwapBuffers(window);*/
    }

    glfwTerminate();
    return 0;
}
