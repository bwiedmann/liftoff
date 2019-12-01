#pragma once

#include "entity.hpp"
#include "explosion.hpp"
#include "powerup.hpp"

class Cargo : public Entity
{
    public:
        Cargo();
        ~Cargo();

        bool  damage(State &s, int p);
        void  update(State &s);
        void  draw(State &s);

    private:
        float counter = 0;
        bool  yield   = false;
};
