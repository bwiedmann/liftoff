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

#include <memory>

#include "entity.hpp"
#include "message.hpp"
#include "particles.hpp"

class Powerup : public Entity {
    public:
        Powerup(State* s, float x, float y, float z);
        ~Powerup();

        bool                       damage(int p);
        void                       collide(shared_ptr<Entity> e);
        void                       update();
        void                       draw();

    private:
        unique_ptr<ParticleEngine> particles;
        float                      counter;
};
