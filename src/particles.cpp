#include "particles.hpp"

ParticleEngine::ParticleEngine()
{
    pemitter = EMITTER_JET;

    c_r = 1.0f;
    c_g = 1.0f;
    c_b = 1.0f;
    c_a = 1.0f;

    pscale = 1.0f;
}

ParticleEngine::~ParticleEngine()
{
}

void ParticleEngine::setup(short emitter, short particles, float dx, float dy, float dz, float decay, float size)
{
    int i;

    if (particles > DEFAULT_GFX_PARTICLES) {
        pnum = DEFAULT_GFX_PARTICLES;
    } else {
        pnum = particles;
    }

    pdecay = decay;
    psize = size;
    pdx = dx;
    pdy = dy;
    pdz = dz;
    pemitter = emitter;
    pnum_max = pnum;

    switch (pemitter) {
        case EMITTER_JET:
            continuous = true;
            c_a = .5f;

            for (i=0; i<pnum; i++) {
                p[i].lifetime = 1.0f;
                p[i].fading = float(10 + rand() % 10) / 80.0f;

                p[i].dx = dx;
                p[i].dy = dy;
                p[i].dz = dz;

                p[i].px = .0f;
                p[i].py = .0f;
                p[i].pz = float(rand() % 1000) * .001f;
            }
            break;

        case EMITTER_EXPLOSION:
            continuous = false;

            for (i=0; i<pnum; i++) {
                p[i].lifetime = 1.0f;
                p[i].fading = decay * (float(rand() % 100) * .001f + .05f);
                p[i].dx = -pdx*.5f + float(rand() % int(pdx*100.0f)) *.01f;
                p[i].dy = -pdy*.5f + float(rand() % int(pdy*100.0f)) *.01f;
                p[i].dz = -pdz*.5f + float(rand() % int(pdz*100.0f)) *.01f;
                if ((p[i].dx < -pdx) || (p[i].dx > pdx)) p[i].dx *= .5f;
                if ((p[i].dy < -pdy) || (p[i].dy > pdy)) p[i].dy *= .5f;
                if ((p[i].dz < -pdz) || (p[i].dz > pdz)) p[i].dz *= .5f;
                if ((p[i].dx > -.05f) && (p[i].dx < .05f)) p[i].dx += -.05f + float(rand() % 20)*.01f;
                if ((p[i].dy > -.05f) && (p[i].dy < .05f)) p[i].dy += -.05f + float(rand() % 20)*.01f;
                if ((p[i].dz > -.05f) && (p[i].dz < .05f)) p[i].dz += -.05f + float(rand() % 20)*.01f;
                p[i].px = -psize*.5f + float(rand() % int(psize*100)) * .01f;
                p[i].py = -psize*.5f + float(rand() % int(psize*100)) * .01f;
                p[i].pz = -psize*.5f + float(rand() % int(psize*100)) * .01f;
            }
            break;
    }
}

void ParticleEngine::setColor(float r, float g, float b)
{
    c_r = r;
    c_g = g;
    c_b = b;
}

void ParticleEngine::setAlpha(float a)
{
    c_a = a;
}

void ParticleEngine::setSize(float size)
{
    psize = size;
}

void ParticleEngine::setScale(float scale)
{
    pscale = scale;
}

void ParticleEngine::setContinuous(bool c)
{
    // explosion emitter + continuous mode = plasma ball
    continuous = c;
}

void ParticleEngine::update(State &s)
{
    if (pemitter == EMITTER_EXPLOSION) {
        for (int i = 0; i < pnum_max; i++) {
            p[i].px += p[i].dx * p[i].lifetime * s.timer_adjustment;
            p[i].py += p[i].dy * p[i].lifetime * s.timer_adjustment;
            p[i].pz += p[i].dz * p[i].lifetime * s.timer_adjustment;

            p[i].lifetime -= p[i].fading * s.timer_adjustment;

            if (continuous && p[i].lifetime < 0) {
                p[i].px = 0;
                p[i].py = 0;
                p[i].pz = 0;

                p[i].lifetime += 1.0f;
                p[i].fading = pdecay * (float(rand() % 100) * .001f + .05f);
            }
        }
    } else {
        for (int i = 0; i<pnum_max; i++) {
            p[i].lifetime -= s.timer_adjustment * p[i].fading;
            p[i].px += (p[i].dx * (.75f + .25f * p[i].fading)) * s.timer_adjustment;
            p[i].py += (p[i].dy * (.75f + .25f * p[i].fading)) * s.timer_adjustment;
            p[i].pz += (p[i].dz * (.75f + .25f * p[i].fading)) * s.timer_adjustment;

            if (continuous && p[i].lifetime < 0) {
                p[i].px = 0;
                p[i].py = 0;
                p[i].pz = 0;

                p[i].lifetime += 1.0f;
                p[i].fading = float(10 + rand() % 10) / 80.0f;
            }
        }
    }
}

void ParticleEngine::draw(State &s, float px, float py, float pz, float rx, float ry, float rz)
{
    float m[16];
    float a = s.global_alpha * .01f;

    glDisable(GL_DEPTH_TEST);

    s.shaders[S_TEXTURE]->bind();

    // render particles
    for (int i = 0; i < pnum; i++) {
        if (p[i].lifetime <= 0) {
            continue;
        }

        s.shaders[S_TEXTURE]->update(UNI_COLOR, glm::vec4(c_r * a, c_g * a, c_b * a, c_a * p[i].lifetime * a));
        s.shaders[S_TEXTURE]->update(UNI_MVP, s.view.transform(
            px + (p[i].px * pscale),
            py + (p[i].py * pscale),
            pz,

            0,
            0,
            0,

            psize,
            psize,
            0
        ));

        s.textures[T_STAR]->draw();
    }

    s.shaders[S_TEXTURE]->unbind();

    glEnable(GL_DEPTH_TEST);
}
