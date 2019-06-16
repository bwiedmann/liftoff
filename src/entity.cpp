#include "entity.hpp"

Entity::Entity()
{
}

Entity::~Entity()
{
}

bool Entity::sort(const shared_ptr<Entity> &e1, const shared_ptr<Entity> &e2)
{
    return (e1->getPosZ() < e2->getPosZ());
}

bool Entity::isCollider()
{
    return e_type == OBJ_TYPE_COLLIDER;
}

bool Entity::isIdle()
{
    return e_state == OBJ_STATE_IDLE;
}

bool Entity::isGone()
{
    return e_state == OBJ_STATE_GONE;
}

bool Entity::isFocusable()
{
    return focusable;
}

bool Entity::isAlive()
{
    return life > 0;
}

void Entity::activate()
{
    e_state = OBJ_STATE_ACTIVE;
}

void Entity::setType(unsigned short t)
{
    e_type = t;
}

void Entity::setPos(float x, float y, float z)
{
    p_x = x;
    p_y = y;
    p_z = z;
}

void Entity::setPosX(float x)
{
    p_x = x;
}

void Entity::setPosY(float y)
{
    p_y = y;
}

void Entity::setPosZ(float z)
{
    p_z = z;
}

float Entity::getPosX()
{
    return p_x;
}

float Entity::getPosY()
{
    return p_y;
}

float Entity::getPosZ()
{
    return p_z;
}

void Entity::setVelocity(float x, float y, float z)
{
    v_x = x;
    v_y = y;
    v_z = z;
}

float Entity::getVelocityX()
{
    return v_x;
}

float Entity::getVelocityY()
{
    return v_y;
}

float Entity::getVelocityZ()
{
    return v_z;
}

void Entity::setScale(float x, float y, float z)
{
    s_x = x;
    s_y = y;
    s_z = z;
}

float Entity::getScale()
{
    return .333f * (s_x +  s_y + s_z);
}

float Entity::getScaleX()
{
    return s_x;
}

float Entity::getScaleY()
{
    return s_y;
}

float Entity::getScaleZ()
{
    return s_z;
}

void Entity::setAcceleration(float x, float y, float z)
{
    a_x = x;
    a_y = y;
    a_z = z;
}

void Entity::setAccelerationX(float x)
{
    a_x = x;
}

void Entity::setAccelerationY(float y)
{
    a_y = y;
}

void Entity::setAccelerationZ(float z)
{
    a_z = z;
}

void Entity::setRotation(float x, float y, float z)
{
    r_x = x;
    r_y = y;
    r_z = z;
}

float Entity::getRotationX()
{
    return r_x;
}

float Entity::getRotationY()
{
    return r_y;
}

float Entity::getRotationZ()
{
    return r_z;
}

void Entity::setSpin(float x, float y, float z)
{
    w_x = x;
    w_y = y;
    w_z = z;
}

int Entity::getLife()
{
    return life;
}

void Entity::setLife(int l)
{
    life = l;
}

float Entity::calcDistance2D(State &s, shared_ptr<Entity> e)
{
    float x1, y1, x2, y2;

    x1 = E_RELATIVE_MOVEMENT * ((p_x + s.timer_adjustment * v_x) - s.cam_x);
    y1 = E_RELATIVE_MOVEMENT * ((p_y + s.timer_adjustment * v_y) - s.cam_y);

    x2 = E_RELATIVE_MOVEMENT * ((e->getPosX() + s.timer_adjustment * e->getVelocityX()) - s.cam_x);
    y2 = E_RELATIVE_MOVEMENT * ((e->getPosY() + s.timer_adjustment * e->getVelocityY()) - s.cam_y);

    return (1.0f / isqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

float Entity::calcDistance3D(State &s, shared_ptr<Entity> e)
{
    float ds, x1, y1, z1, x2, y2, z2;

    x1 = E_RELATIVE_MOVEMENT * ((p_x + s.timer_adjustment * v_x) - s.cam_x);
    y1 = E_RELATIVE_MOVEMENT * ((p_y + s.timer_adjustment * v_y) - s.cam_y);
    z1 = p_z + s.timer_adjustment * (v_z + E_BASE_SPEED);

    x2 = E_RELATIVE_MOVEMENT * ((e->getPosX() + s.timer_adjustment * e->getVelocityX()) - s.cam_x);
    y2 = E_RELATIVE_MOVEMENT * ((e->getPosY() + s.timer_adjustment * e->getVelocityY()) - s.cam_y);
    z2 = e->getPosZ() + s.timer_adjustment * e->getVelocityZ();

    return (1.0f / isqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2)));
}

bool Entity::isColliding(State &s, shared_ptr<Entity> e)
{
    float r1, r2;

    r1 = getScale()    * (10000.0f + p_z)          * .0001f;
    r2 = e->getScale() * (10000.0f + e->getPosZ()) * .0001f;

    return (calcDistance3D(s, e) < (r1 + r2));
}

void Entity::collide(State &s, shared_ptr<Entity> e)
{
}

bool Entity::damage(State &s, int p)
{
    life -= p;

    if (life <= 0) {
        e_state = OBJ_STATE_GONE;
    }

    return (false == isAlive());
}

void Entity::move(State &s)
{
    p_x += s.timer_adjustment * v_x;
    p_y += s.timer_adjustment * v_y;
    p_z += s.timer_adjustment * (v_z + E_BASE_SPEED);

    r_x += s.timer_adjustment * w_x * .1f;
    if (r_x < 0) r_x += 360.0f;
    if (r_x > 360.0f) r_x -= 360.0f;

    r_y += s.timer_adjustment * w_y * .1f;
    if (r_y < 0) r_y += 360.0f;
    if (r_y > 360.0f) r_y -= 360.0f;

    r_z += s.timer_adjustment * w_z * .1f;
    if (r_z < 0) r_z += 360.0f;
    if (r_z > 360.0f) r_z -= 360.0f;
}

void Entity::resetTarget()
{
    target = nullptr;
}

void Entity::checkTarget(State &s, shared_ptr<Entity> e)
{
    if (calcDistance2D(s, e) < e->getScale()) {
        if (target) {
            if (calcDistance3D(s, e) < calcDistance3D(s, target)) {
                target = e;
            }
        } else {
            target = e;
        }
    }
}

bool Entity::hasTarget(shared_ptr<Entity> e)
{
    return e == target;
}

void Entity::drawCrosshair(State &s, shared_ptr<Entity> me)
{
    float a = float(s.global_alpha) * .01f;
    float scale = 150.0f + ((p_z + 12500.0f) * .00005f);
    float rot, da;

    if (
        isFocusable() == false ||
        getPosZ() < -8000.0f
    ) {
        return;
    }

    // let cross-hair fade out when player dies
    if (isAlive()) {
        da = .85f;
    } else {
        if (da > .01f) {
            da -= s.timer_adjustment * .01f;
        } else {
            da = .0f;
        }
    }

    // let cross-hair fade out when too near
    if (p_z > -1000.0f) {
        da -= .001f * (1000.0f + p_z);
    }

    glLoadIdentity();

    glRotatef(s.tilt_x * -.025f, 0, 1, 0);
    glRotatef(s.tilt_y * -.025f, 1, 0, 0);

    glBindTexture(GL_TEXTURE_2D, *s.textures[T_HUD_3]);

    glTranslatef(
        (p_x - s.cam_x) * E_RELATIVE_MOVEMENT,
        (p_y - s.cam_y) * E_RELATIVE_MOVEMENT,
        (p_z)
    );

    glPushMatrix();

    if (s.player->hasTarget(me)) {
        // target locked (colored)

        glColor4f(t_r, t_g, t_b, a * da);
        glBegin (GL_QUADS);
          glTexCoord2i(0, 0);
          glVertex2f(-scale * .75f, -scale * .75f);

          glTexCoord2i(1, 0);
          glVertex2f(scale * .75f, -scale * .75f);

          glTexCoord2i(1, 1);
          glVertex2f(scale * .75f, scale * .75f);

          glTexCoord2i(0, 1);
          glVertex2f(-scale * .75f, scale * .75f);
        glEnd();
    } else {
        // target not locked (white)

        rot = (180.0f / M_PI) * atan(
            (s.player->getPosY() - getPosY()) /
            (s.player->getPosX() - getPosX())
        );

        if (s.player->getPosX() < getPosX()) {
            rot += 180.0f;
        }

        glColor4f(1.0f, 1.0f, 1.0f, a * da);
        glRotatef(rot, 0, 0, 1);
        glBegin (GL_QUADS);
          glTexCoord2f(.5f, 0);
          glVertex2f(.8f, -scale * .75f);

          glTexCoord2f(1.0f, 0);
          glVertex2f(scale * .75f, -scale * .75f);

          glTexCoord2f(1.0f, 1.0f);
          glVertex2f(scale * .75f, scale * .75f);

          glTexCoord2f(.5f, 1.0f);
          glVertex2f(.8f, scale * .75f);
        glEnd();
        glRotatef(-rot, 0, 0, 1);
    }

    glBegin (GL_QUADS);
      glTexCoord2i(0, 0);
      glVertex2f(-scale, -scale);

      glTexCoord2i(1, 0);
      glVertex2f(scale, -scale);

      glTexCoord2i(1, 1);
      glVertex2f(scale, scale);

      glTexCoord2i(0, 1);
      glVertex2f(-scale, scale);
    glEnd();

    glPopMatrix();
}

