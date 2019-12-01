#pragma once

#include <GL/glew.h>

class Renderbuffer
{
    public:
        Renderbuffer(GLuint w, GLuint h, GLuint s);
        ~Renderbuffer();

        void bind();
        void blit();

    protected:
        GLuint width;
        GLuint height;

        GLuint framebuffer;
        GLuint framebufferMSAA;

        GLuint renderbuffer;
        GLuint renderbufferColor;
        GLuint renderbufferDepth;

        GLuint texture;
};