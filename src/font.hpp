#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "texture.hpp"
#include "shader.hpp"
#include "view.hpp"

using std::map;
using std::shared_ptr;

struct glyph_t {
    GLuint     texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    FT_Pos     advance;
    FT_Pos     height;
};

class Font : public Quad {
    public:
        Font(const string& filename, shared_ptr<Shader> s, uint8_t q);
        ~Font();

        void                 draw(const string& txt, float x, float y, float s, float r, float g, float b, float a);

    private:
        unique_ptr<View>     view;
        shared_ptr<Shader>   shader;
        map<GLchar, glyph_t> glyphs;

        float                scale;
};
