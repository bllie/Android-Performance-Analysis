/*
 * Performance analysis
 * 
 * Native OpenGL
 * 
 * Copyright (c) Thomas Gummerer 2011 | All rights reserved
 */
#include "glapp.h"

OpenGL::OpenGL()
{
    importGLInit();
    this->windowWidth = 320;
    this->windowHeight = 480;
    this->appInit();
}

OpenGL::~OpenGL()
{
    importGLDeinit();
}

void OpenGL::appInit()
{
    glEnable(GL_NORMALIZE);
    // The diagram will be in 2D, thus no depth test needed
    glDisable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
}

void OpenGL::resize(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
}

void OpenGL::prepareFrame()
{
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void OpenGL::render()
{
    // Prepare OpenGL ES for rendering of the frame.
    this->prepareFrame();
    this->setRGBColor(255, 255, 255, 0);
    this->drawLine(0.85, -0.9, 0.85, 0.9);
    this->drawLine(-0.9, -0.85, 0.9, -0.85);
    this->setRGBColor(120, 120, 255, 0);
    this->drawRectangle(0.85, -0.83, -0.4, 0.2);
    this->setRGBColor(255, 120, 120, 0);
    this->drawRectangle(0.85, -0.81, -0.5, 0.2);
}

// Attention, x, height go from left to right, and y from top to bottom, since diagram
// will be displayed for a rotated phon
void OpenGL::drawRectangle(float x, float y, float height, float width)
{
    GLfloat vertices[] = {x+height,y, x,y+width, x+height,y+width, x+height,y, x,y, x,y+width };
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

// Set colors easier (0-255)
void OpenGL::setRGBColor(int red, int green, int blue, float transparency)
{
    glColor4f((float)red/255, (float)green/255, (float)blue/255, transparency);
}

void OpenGL::drawLine(float p1x, float p1y, float p2x, float p2y)
{
    GLfloat vertices[] = {p1x,p1y, p2x,p2y};
    glEnable(GL_LINE_SMOOTH); // Anti aliasing
    //glLineWidth(1.0f);
    glVertexPointer(2, GL_FLOAT, 0, vertices);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}
