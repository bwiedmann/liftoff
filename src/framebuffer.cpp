/*
 *  Copyright (C) 2019 René Pollesch <poliander@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "framebuffer.hpp"

Framebuffer::Framebuffer(GLuint w, GLuint h, GLuint s) : Quad() {
    width = w;
    height = h;
    samples = s;

    // color
    glGenTextures(1, &buffers[FB_BUFFER_COLOR]);
    glBindTexture(GL_TEXTURE_2D, buffers[FB_BUFFER_COLOR]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (s == 0) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // depth
    glGenRenderbuffers(1, &buffers[FB_BUFFER_DEPTH]);
    glBindRenderbuffer(GL_RENDERBUFFER, buffers[FB_BUFFER_DEPTH]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);

    // framebuffer
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffers[FB_BUFFER_COLOR], 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffers[FB_BUFFER_DEPTH]);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    glDeleteTextures(1, &buffers[FB_BUFFER_COLOR]);
    glDeleteRenderbuffers(1, &buffers[FB_BUFFER_DEPTH]);
    glDeleteFramebuffers(1, &framebuffer);
}

void Framebuffer::bind() {
    glGetIntegerv(GL_VIEWPORT, originalViewport);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &originalFramebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, width, height);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, originalFramebuffer);
    glViewport(originalViewport[0], originalViewport[1], originalViewport[2], originalViewport[3]);
}

void Framebuffer::clear() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::draw() {
    glBindTexture(GL_TEXTURE_2D, buffers[FB_BUFFER_COLOR]);

    if (samples > 0) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Quad::draw();

    glBindTexture(GL_TEXTURE_2D, 0);
}
