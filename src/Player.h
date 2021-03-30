#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Input.hpp>
#include <Math.hpp>

#include <Area2D.hpp>
#include <AnimatedSprite.hpp>
#include <CollisionShape2D.hpp>

namespace godot{
class Player : public Area2D{
    GODOT_CLASS(Player, Area2D);

private:
    int speed;

    Vector2 screen_size;

    AnimatedSprite* anim_sprite;
    CollisionShape2D* col_shape;

public:
    static void _register_methods();

    Player();
    ~Player();

    void _init();
    void _ready();
    void _process(float delta);
    void start(Vector2 pos);
    void _on_Player_body_entered(Variant body);
};    
}

#endif