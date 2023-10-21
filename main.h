#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "raincloud/raincloud.h"

class RkBody {
private:
	rc::vec2 position = {}, velocity = {}, force = {};
	float mass = {}, radius = {};
public:
	RkBody(rc::vec2 pos, float rd, rc::vec2 f, float m) : position(pos), radius(rd), force(f), mass(m) {};
	~RkBody() {};
	void Update(double deltaTime) {
        rc::vec2 k1v = (force / mass) * deltaTime;
        rc::vec2 k1x = velocity * deltaTime;

        rc::vec2 k2v = (force + k1v / 2) / mass * deltaTime;
        rc::vec2 k2x = (velocity + k1v / 2) * deltaTime;

        rc::vec2 k3v = (force + k2v / 2) / mass * deltaTime;
        rc::vec2 k3x = (velocity + k2v / 2) * deltaTime;

        rc::vec2 k4v = (force + k3v) / mass * deltaTime;
        rc::vec2 k4x = (velocity + k3v) * deltaTime;

        velocity = velocity + (k1v + k2v * 2 + k3v * 2 + k4v) / 6;
        position = position + (k1x + k2x * 2 + k3x * 2 + k4x) / 6;

        if (velocity.y > 0 && position.y + radius > 600) {
            position.y = 600 - radius;
            velocity.y *= -1;
        }
        if (velocity.x > 0 && position.x + radius > 1024) {
            position.x = 1024 - radius;
            velocity.x *= -1;
        }
        if (velocity.x < 0 && position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -1;
        }
	}
    void Draw(rc::Camera cam) {
        rc::draw_circle(cam, position, radius, { 0, 1, 0, 1 });
    }
};

class EulerBody {
private:
    rc::vec2 position = {}, velocity = {}, force = {};
    float mass = {}, radius = {};
public:
    EulerBody(rc::vec2 pos, float rd, rc::vec2 f, float m) : position(pos), radius(rd), force(f), mass(m) {};
    ~EulerBody() {};
    void Update(double deltaTime) {
        rc::vec2 acceleration = force / mass;
        position = position + (velocity * deltaTime);
        velocity = velocity + (acceleration * deltaTime);

        if (velocity.y > 0 && position.y + radius > 600) {
            position.y = 600 - radius;
            velocity.y *= -1;
        }
        if (velocity.x > 0 && position.x + radius > 1024) {
            position.x = 1024 - radius;
            velocity.x *= -1;
        }
        if (velocity.x < 0 && position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -1;
        }
    }
    void Draw(rc::Camera cam) {
        rc::draw_circle(cam, position, radius, { 1, 0, 0, 1 });
    }
};

class SemiEulerBody {
private:
    rc::vec2 position = {}, velocity = {}, force = {};
    float mass = {}, radius = {};
public:
    SemiEulerBody(rc::vec2 pos, float rd, rc::vec2 f, float m) : position(pos), radius(rd), force(f), mass(m) {};
    ~SemiEulerBody() {};
    void Update(double deltaTime) {
        rc::vec2 acceleration = force / mass;
        velocity = velocity + (acceleration * deltaTime);
        position = position + (velocity * deltaTime);

        if (velocity.y > 0 && position.y + radius > 600) {
            position.y = 600 - radius;
            velocity.y *= -1;
        }
        if (velocity.x > 0 && position.x + radius > 1024) {
            position.x = 1024 - radius;
            velocity.x *= -1;
        }
        if (velocity.x < 0 && position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -1;
        }
    }
    void Draw(rc::Camera cam) {
        rc::draw_circle(cam, position, radius, { 1, 0, 1, 1 });
    }
};

class MidpointBody {
private:
    rc::vec2 position = {}, velocity = {}, force = {};
    float mass = {}, radius = {};
public:
    MidpointBody(rc::vec2 pos, float rd, rc::vec2 f, float m) : position(pos), radius(rd), force(f), mass(m) {};
    ~MidpointBody() {};
    void Update(double deltaTime) {
        rc::vec2 acceleration = force / mass;
        rc::vec2 h = velocity + acceleration * (deltaTime / 2);
        position = position + h * deltaTime;
        velocity = h + acceleration * (deltaTime / 2);

        if (velocity.y > 0 && position.y + radius > 600) {
            position.y = 600 - radius;
            velocity.y *= -1;
        }
        if (velocity.x > 0 && position.x + radius > 1024) {
            position.x = 1024 - radius;
            velocity.x *= -1;
        }
        if (velocity.x < 0 && position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -1;
        }
    }
    void Draw(rc::Camera cam) {
        rc::draw_circle(cam, position, radius, { 1, 1, 1, 1 });
    }
};

class LeapfrogBody {
private:
    rc::vec2 position = {}, velocity = {}, force = {};
    float mass = {}, radius = {};
public:
    LeapfrogBody(rc::vec2 pos, float rd, rc::vec2 f, float m) : position(pos), radius(rd), force(f), mass(m) {};
    ~LeapfrogBody() {};
    void Update(double deltaTime) {
        position = position + velocity * deltaTime + (force / (2 * mass)) * (deltaTime * deltaTime);
        velocity = velocity + (force / mass) * deltaTime;

        if (velocity.y > 0 && position.y + radius > 600) {
            position.y = 600 - radius;
            velocity.y *= -1;
        }
        if (velocity.x > 0 && position.x + radius > 1024) {
            position.x = 1024 - radius;
            velocity.x *= -1;
        }
        if (velocity.x < 0 && position.x - radius < 0) {
            position.x = radius;
            velocity.x *= -1;
        }
    }
    void Draw(rc::Camera cam) {
        rc::draw_circle(cam, position, radius, { 0, 0, 1, 1 });
    }
};

class VerletBody {
private:
    rc::vec2 position = {}, old_position = {}, force = {};
    float mass = {}, radius = {};
public:
    VerletBody(rc::vec2 pos, float rd, rc::vec2 f, float m) : position(pos), old_position(pos), radius(rd), force(f), mass(m) {};
    ~VerletBody() {};
    void Update(double deltaTime) {
        rc::vec2 velocity = position - old_position;
        old_position = position;
        rc::vec2 acceleration = force / mass;

        if (acceleration.y > 0 && position.y + radius > 600) {
            position.y = 600 - radius;
            acceleration.y *= -1;
        }
        if (acceleration.x > 0 && position.x + radius > 1024) {
            position.x = 1024 - radius;
            acceleration.x *= -1;
        }
        if (acceleration.x < 0 && position.x - radius < 0) {
            position.x = radius;
            acceleration.x *= -1;
        }
        position = position + velocity + acceleration * (deltaTime * deltaTime);
    }
    void Draw(rc::Camera cam) {
        rc::draw_circle(cam, position, radius, { 1, 1, 0, 1 });
    }
};
#endif
