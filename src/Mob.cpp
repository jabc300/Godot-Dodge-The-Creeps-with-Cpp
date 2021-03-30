#include "Mob.h"

using namespace godot;

void Mob::_register_methods(){
    register_method("_ready", &Mob::_ready);
    register_method("_on_VisibilityNotifier2D_screen_exited", &Mob::_on_VisibilityNotifier2D_screen_exited);

    register_property<Mob,int>("min_speed", &Mob::min_speed, 150);
    register_property<Mob,int>("max_speed", &Mob::max_speed, 250);
}

Mob::Mob(){
}

Mob::~Mob(){
}

void Mob::_init(){
    min_speed = 150;
    max_speed = 250;
}

void Mob::_ready(){
    anim_sprite = cast_to<AnimatedSprite>(get_node("AnimatedSprite"));
    visibility_notifier = cast_to<VisibilityNotifier2D>(get_node("VisibilityNotifier2D"));
    
    visibility_notifier -> connect("screen_exited", this, "_on_VisibilityNotifier2D_screen_exited");

    PoolStringArray mob_types = anim_sprite -> get_sprite_frames() -> get_animation_names();

    anim_sprite -> set_animation(mob_types[rand() % mob_types.size()]);
}

void Mob::_on_VisibilityNotifier2D_screen_exited(){
    queue_free();
}