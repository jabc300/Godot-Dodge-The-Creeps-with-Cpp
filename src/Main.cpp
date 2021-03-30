#include "Main.h"

using namespace godot;

void Main::_register_methods(){
    register_method("_ready", &Main::_ready);
    register_method("game_over", &Main::game_over);
    register_method("new_game", &Main::new_game);
    register_method("_on_StartTimer_timeout", &Main::_on_StartTimer_timeout);
    register_method("_on_ScoreTimer_timeout", &Main::_on_ScoreTimer_timeout);
    register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
}

Main::Main(){
}

Main::~Main(){
}

void Main::_init(){
    score = 0;
}

void Main::_ready(){
    
    mob_timer = cast_to<Timer>(get_node("MobTimer"));
    score_timer = cast_to<Timer>(get_node("ScoreTimer"));
    start_timer = cast_to<Timer>(get_node("StartTimer"));
    hud_node = cast_to<CanvasLayer>(get_node("HUD"));
    music = cast_to<AudioStreamPlayer>(get_node("Music"));
    death_sound = cast_to<AudioStreamPlayer>(get_node("DeathSound"));

    player_node = cast_to<Area2D>(get_node("Player")); //Get the node
    player = cast_to<Player>(player_node); //Get the Player class from the node

    start_position = cast_to<Position2D>(get_node("StartPosition"));
    mob_spawn_location = cast_to<PathFollow2D>(get_node("MobPath/MobSpawnLocation"));

    ResourceLoader *resource_loader = ResourceLoader::get_singleton();

    mob_scene = resource_loader -> load("res://Mob.tscn", "PackedScene");

    start_timer -> connect("timeout", this, "_on_StartTimer_timeout");
    score_timer -> connect("timeout", this, "_on_ScoreTimer_timeout");
    mob_timer -> connect("timeout", this, "_on_MobTimer_timeout");
    hud_node -> connect("start_game", this, "new_game");
    player -> connect("hit", this, "game_over");

    hud = cast_to<HUD>(hud_node);

    srand((unsigned int) time(NULL));
}

void Main::game_over(){
    music -> stop();
    death_sound -> play();
    score_timer -> stop();
    mob_timer -> stop();
    hud -> show_game_over();
    get_tree() -> call_group("mobs", "queue_free");
}

void Main::new_game(){
    music -> play();
    score = 0;
    player -> start(start_position-> get_position());
    hud -> update_score(score);
    hud -> show_message("Get Ready");
    start_timer -> start();
}

void Main::_on_StartTimer_timeout(){
    mob_timer -> start();
    score_timer -> start();
}

void Main::_on_ScoreTimer_timeout(){
    score++;
    hud -> update_score(score);
}

void Main::_on_MobTimer_timeout(){
    mob_spawn_location -> set_offset(rand());
    if(mob_scene.is_valid()){
        mob_node = cast_to<RigidBody2D>(mob_scene -> instance());
        add_child(mob_node);
        float direction = mob_spawn_location -> get_rotation() + Math_PI / 2;
        mob_node -> set_position(mob_spawn_location -> get_position());
        direction +=  ((float) rand() / (float) RAND_MAX) * (Math_PI / 2) - (Math_PI / 4);
        mob_node -> set_rotation(direction);

        mob = cast_to<Mob>(mob_node);
        mob_node -> set_linear_velocity(Vector2((rand() % (mob -> max_speed - mob -> min_speed) + mob -> min_speed), 0));
        mob_node -> set_linear_velocity(mob -> get_linear_velocity().rotated(direction));
    }
}