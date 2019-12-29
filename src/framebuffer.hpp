/*
 *  LIFT-OFF: BEYOND GLAXIUM
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

#pragma once

#include "quad.hpp"

enum fbo_buffer_indices_e {
    FB_BUFFER_COLOR,
    FB_BUFFER_DEPTH,

    FB_MSAA_BUFFER_COLOR,
    FB_MSAA_BUFFER_DEPTH
};

class Framebuffer : public Quad {
    public:
        Framebuffer(GLuint w, GLuint h, GLuint s);
        ~Framebuffer();

        void   bind();
        void   unbind();
        void   clear();
        void   draw();

        operator GLuint() {
            return framebuffer;
        }

    protected:
        GLuint width;
        GLuint height;
        GLuint samples;

        GLint  originalViewport[4];
        GLint  originalFramebuffer;

        GLuint buffers[4];
        GLuint framebuffer;
};
