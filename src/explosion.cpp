#include "explosion.hpp"

Explosion::Explosion(unsigned short int type, float x, float y, float z) : Entity()
{
    e_obj = type;
    e_type = E_TYPE_SCENERY;
    e_state = E_STATE_ACTIVE;

    setPos(x, y, z);
    setRot(float(rand() % 360), float(rand() % 360), float(rand() % 360));

    particles = new ParticleEngine();

    switch (type) {
        // green laser gun impact
        case OBJ_EXPLOSION_1:
            particles->setup(EMITTER_EXPLOSION, 20, .85f, .85f, .85f, .75f, 4.0f);
            timer = 750;
            break;

        // explosion smoke
        case OBJ_EXPLOSION_2:
            particles->setup(EMITTER_EXPLOSION, 15, 5.0f, 5.0f, 5.0f, .1f, 5.0f);
            timer = 4000;
            break;

        // explosion sparks
        case OBJ_EXPLOSION_3:
            particles->setup(EMITTER_EXPLOSION, 20, 25.0f, 25.0f, 25.0f, .5f, 10.0f);
            timer = 2000;
            break;

        // explosion fireball
        case OBJ_EXPLOSION_4:
            particles->setup(EMITTER_EXPLOSION, 15, .5f, .5f, .5f, .4f, 10.0f);
            timer = 1000;
            break;

        // collision sparks
        case OBJ_EXPLOSION_5:
            timer = 200;
            break;
    }
}

Explosion::~Explosion()
{
    delete particles;
}

void Explosion::move(State &s)
{
    Entity::move(s);

    particles->move(s);

    timer -= s.timer_adjustment * 10.0f;

    if (timer < 0 || getPosZ() > 100.0f) {
        e_state = E_STATE_GONE;
    }
}

void Explosion::draw(State &s)
{
    float counter;

    glLoadIdentity();
    glEnable(GL_BLEND);

    switch (e_obj) {

        // green laser gun impact
        case OBJ_EXPLOSION_1:
            counter = (750.0f - timer) * .001333f;
            particles->setAlpha(.5f - counter);
            particles->setColor(.5f, 1.0f, .8f);
            particles->setSize(4.0f - 2.0f * counter);
            particles->setScale(2.5f + counter);

            s.textures[T_EXPLOSION_1]->bind();
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;

        // explosion smoke
        case OBJ_EXPLOSION_2:
            counter = (4000.0f - timer) * .00025f;
            particles->setColor(.5f - counter, .5f - counter, .45f - counter);
            particles->setAlpha(.5f - counter * .5f);
            particles->setSize(5.0f + ((1.0f - (counter * counter)) * 75.0f));
            particles->setScale(1.0f + 7.5f * (counter * counter));

            s.textures[T_EXPLOSION_2]->bind();
            break;

        // explosion sparks
        case OBJ_EXPLOSION_3:
            counter = (2000.0f - timer) * .0005f;
            particles->setSize(10.0f - ((counter * counter) * 10.0f));

            s.textures[T_EXPLOSION_1]->bind();
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;

        // explosion fireball
        case OBJ_EXPLOSION_4:
            counter = (1000.0f - timer) * .001f;
            particles->setColor(1.0f, 1.0f - counter * .15f, 1.0f - counter * .3f);
            particles->setAlpha(.35f - counter * .35f);
            particles->setScale(.5f + counter * 12.5f);
            particles->setSize(10.0f + ((1.0f - (counter * counter)) * 10.0f));

            s.textures[T_EXPLOSION_1]->bind();
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;

        // collision sparks
        case OBJ_EXPLOSION_5:
            counter = (200.0f - timer) * .005f;
            particles->setSize(10.0f - ((counter * counter) * 10.0f));

            s.textures[T_EXPLOSION_1]->bind();
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;
    }

    glRotatef(s.tilt_x * -.035f, 0, 1, 0);
    glRotatef(s.tilt_y * -.035f, 1, 0, 0);

    glShadeModel(GL_FLAT);
    glPushMatrix();

    particles->draw(s,
        (getPosX() - s.cam_x) * E_RELATIVE_MOVEMENT,
        (getPosY() - s.cam_y) * E_RELATIVE_MOVEMENT,
        (getPosZ()),
        (getRotX()),
        (getRotY()),
        (getRotZ())
    );

    glPopMatrix();
    glShadeModel(GL_SMOOTH);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
