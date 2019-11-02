#include "asteroid.hpp"

Asteroid::Asteroid() : Entity()
{
    e_obj = OBJ_ASTEROID_1;
    e_type = E_TYPE_COLLIDER;
    e_state = E_STATE_IDLE;
}

Asteroid::~Asteroid()
{
}

bool Asteroid::damage(State &s, int p)
{
    bool damaged = Entity::damage(s, p);

    if (damaged && !isAlive()) {
        unsigned short m = int(getScale() * .5f);

        s.audio.playSample(SFX_EXPLOSION_2, 192, 180);

        s.entities.push_back(make_shared<Explosion>(OBJ_EXPLOSION_2, p_x, p_y, p_z));
        s.entities.push_back(make_shared<Explosion>(OBJ_EXPLOSION_3, p_x, p_y, p_z + 5.0f));
        s.entities.push_back(make_shared<Explosion>(OBJ_EXPLOSION_4, p_x, p_y, p_z + 10.0f));

        s.addMessage(m, MSG_MONEY);
        s.player->addMoney(m);
    }

    return damaged;
}

void Asteroid::update(State &s)
{
    Entity::update(s);

    if (p_z > 0) {
        e_state = E_STATE_GONE;
    }
}
