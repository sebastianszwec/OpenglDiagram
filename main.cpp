#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cassert>

#include "CollatzConjecture.h"

#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1000

enum class AxisE { X_AXIS, Y_AXIS, NR_OF_AXIS };

typedef struct Color
{
    GLfloat red;
    GLfloat green;
    GLfloat blue;
} Color;

void DrawAxis(bool printXAxisRuler, bool printYAxisRuler);
void drawRuler(AxisE axis, GLfloat axisAdjustment);

void debugLinesRenderer(int collatzTableIndex, int posY);

GLfloat axisXUnit = 80.0f;
GLfloat axisYUnit = 20.0f;
const GLfloat axisAdjustment = SCREEN_WIDTH * 0.01;

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Collatz Conjecture", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    bool drawXAxisRuler = true;
    bool drawYAxisRuler = true;

    CollatzConjecture collatzConjecture1(4, drawXAxisRuler, drawYAxisRuler, axisXUnit, axisYUnit, SCREEN_WIDTH, SCREEN_HEIGHT, axisAdjustment);
    CollatzConjecture collatzConjecture2(8, drawXAxisRuler, drawYAxisRuler, axisXUnit, axisYUnit, SCREEN_WIDTH, SCREEN_HEIGHT, axisAdjustment);

    std::cout << "drawXAxisRuler" << drawXAxisRuler << std::endl;
    std::cout << "drawYAxisRuler" << drawYAxisRuler << std::endl;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);

        // Render OpenGL here
        DrawAxis(drawXAxisRuler, drawYAxisRuler);

        collatzConjecture1.RenderCollatzConjecture();
        collatzConjecture2.RenderCollatzConjecture();
        
        //debugLinesRenderer(16, 2);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void DrawAxis(bool drawXAxisRuler, bool drawYAxisRuler)
{
    GLfloat xAxisVertices[] =
    {
        0.0f, axisAdjustment,
        SCREEN_WIDTH, axisAdjustment,

        axisAdjustment, 0.0f,
        axisAdjustment, SCREEN_HEIGHT
    };

    {
        int step = 0;
        for (int i = 0; i < (int)AxisE::NR_OF_AXIS; i++, step += 4)
        {
            glEnable(GL_LINE_SMOOTH);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 0, xAxisVertices + step);
            glDrawArrays(GL_LINES, 0, 2);
        }
    }

    if (drawXAxisRuler) drawRuler(AxisE::X_AXIS, axisAdjustment);
    if (drawYAxisRuler) drawRuler(AxisE::Y_AXIS, axisAdjustment);
}

void drawRuler(AxisE axis, GLfloat axisAdjustment)
{
    GLfloat rulerHeight = 7.0f;
    GLfloat rulerPos = axisAdjustment;

    int rulerArrOffset;
    int axisLength;
    GLfloat axisUnit;

    if (axis == AxisE::Y_AXIS)
    {
        rulerArrOffset = 4;
        axisLength = SCREEN_HEIGHT;
        axisUnit = axisYUnit;
    }
    else if (axis == AxisE::X_AXIS)
    {
        rulerArrOffset = 0;
        axisLength = SCREEN_WIDTH;
        axisUnit = axisXUnit;
    }
    else
    {
        assert(false);
    }

    for (int i = 0; i <= axisLength / axisUnit; ++i)
    {
        GLfloat ruler[] =
        {
            // x axis
            rulerPos, axisAdjustment + rulerHeight,
            rulerPos, axisAdjustment - rulerHeight,

            // y axis
            axisAdjustment - rulerHeight, rulerPos,
            axisAdjustment + rulerHeight, rulerPos
        };

        glEnable(GL_LINE_SMOOTH);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, ruler + rulerArrOffset);
        glDrawArrays(GL_LINES, 0, 2);

        rulerPos += axisUnit;
    }
}

void debugLinesRenderer(int collatzTableIndex, int posY)
{
    GLfloat y[] =
    {
        0, axisAdjustment + axisYUnit * posY,
        SCREEN_WIDTH, axisAdjustment + axisYUnit * posY
    };

    glEnable(GL_LINE_SMOOTH);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, y);
    glDrawArrays(GL_LINES, 0, 2);

    GLfloat x[] =
    {
        axisAdjustment + (collatzTableIndex * axisXUnit), 0,
        axisAdjustment + (collatzTableIndex * axisXUnit), SCREEN_HEIGHT
    };

    glEnable(GL_LINE_SMOOTH);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, x);
    glDrawArrays(GL_LINES, 0, 2);
}