#include "Player.h"

using namespace godot;

void Player::_register_methods(){
    register_method("_ready", &Player::_ready);
    register_method("_process", &Player::_process);
    register_method("start", &Player::start);
    register_method("_on_Player_body_entered", &Player::_on_Player_body_entered);

    register_property<Player, int>("speed", &Player::speed, 400);

    //Compiling in MSVC 2019 is geting an ambiguity problem while declaring signals without arguments (register_signal<Player>("hit")).
    //To keep using GODOT.hpp without altering it, the signal was declared this way.
    register_signal<Player>("hit","node", GODOT_VARIANT_TYPE_INT);
}

Player::Player(){
}

Player::~Player(){
}

void Player::_init(){
    speed = 400;
    
}

void Player::_ready(){
    screen_size = get_viewport_rect().size;
    anim_sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
    col_shape = cast_to<CollisionShape2D>(get_node("CollisionShape2D"));
    connect("body_entered", this, "_on_Player_body_entered");
    
    hide();
}

void Player::_process(float delta){
    Vector2 velocity;
    Input* input = Input::get_singleton();

    if(input -> is_action_pressed("ui_right")){
        velocity.x += 1;
    }
    if(input -> is_action_pressed("ui_left")){
        velocity.x -= 1;
    }
    if(input -> is_action_pressed("ui_down")){
        velocity.y += 1;
    }
    if(input -> is_action_pressed("ui_up")){
        velocity.y -= 1;
    }
    if(velocity.length() > 0){
        velocity = velocity.normalized() * speed;
        anim_sprite -> play();
    }
    else{
        anim_sprite -> stop();
    }

    set_position(get_position() + velocity * delta);
    
    set_position(Vector2 (Math::clamp(get_position().x, real_t(0), screen_size.x), Math::clamp(get_position().y, real_t(0), screen_size.y)));

    if(velocity.x != 0){
        anim_sprite -> set_animation("walk");
        anim_sprite -> set_flip_v(false);

        anim_sprite -> set_flip_h(velocity.x < 0);
    }
    else if (velocity.y != 0){
        anim_sprite -> set_animation("up");
        anim_sprite -> set_flip_v(velocity.y > 0);
    }
}

void Player::start(Vector2 pos){
    set_position(pos);
    show();
    anim_sprite -> set_flip_v(false);
    anim_sprite -> set_flip_h(false);
    anim_sprite -> set_animation("walk");
    col_shape -> set_disabled(false);
}

void Player::_on_Player_body_entered(Variant body){
    hide();
    emit_signal("hit",0);
    col_shape -> set_deferred("disable", true);
}