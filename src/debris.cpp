#include "debris.hpp"

Debris::Debris() : Entity()
{
    e_obj = OBJ_DEBRIS_1;
    e_type = E_TYPE_SCENERY;
    e_state = E_STATE_IDLE;

    p_x = -600.0f + float(rand() % 1200);
    p_y = -400.0f + float(rand() % 800);
    p_z = -8000.0f;

    w_x = float(rand() % 100) * .1f;
    w_y = float(rand() % 100) * .1f;
    w_z = float(rand() % 100) * .1f;

    s_x = 20.0f + float(rand() % 400) * .2f;
    s_y = 20.0f + float(rand() % 400) * .2f;
    s_z = 20.0f + float(rand() % 400) * .2f;

    c_r = .6f;
    c_g = .6f;
    c_b = .6f;
}

Debris::~Debris()
{
}

void Debris::update(State &s)
{
    Entity::update(s);

    if (p_z > 0) {
        e_state = E_STATE_GONE;
    }
}

void Debris::draw(State &s)
{
    float a = float(s.global_alpha) * .01f;
    float scale = (10000.0f + p_z) * .0001f;

    s.models[e_obj]->draw(s.view.transform(
        E_RELATIVE_MOVEMENT * (p_x - s.cam_x),
        E_RELATIVE_MOVEMENT * (p_y - s.cam_y),
        p_z,

        r_x,
        r_y,
        r_z,

        s_x * scale,
        s_y * scale,
        s_z * scale
    ), glm::vec4(c_r * a, c_g * a, c_b * a, c_a));
}
