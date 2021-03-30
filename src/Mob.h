#ifndef MOB_H
#define MOB_H

#include <Godot.hpp>

#include <RigidBody2D.hpp>
#include <AnimatedSprite.hpp>
#include <SpriteFrames.hpp>
#include <VisibilityNotifier2D.hpp>

#include <stdlib.h> 

namespace godot{
class Mob : public RigidBody2D{
    GODOT_CLASS(Mob, RigidBody2D);

private:
    AnimatedSprite* anim_sprite;
    VisibilityNotifier2D* visibility_notifier;

public:
    int min_speed;
    int max_speed;

    static void _register_methods();

    Mob();
    ~Mob();

    void _init();
    void _ready();
    void _on_VisibilityNotifier2D_screen_exited();
};
}

#endif