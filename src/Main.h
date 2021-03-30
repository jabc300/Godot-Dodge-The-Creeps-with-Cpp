#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <Defs.hpp>

#include <SceneTree.hpp>
#include <Timer.hpp>
#include <Area2D.hpp>
#include <Position2D.hpp>
#include <PathFollow2D.hpp>
#include <CanvasLayer.hpp>
#include <AudioStreamPlayer.hpp>

#include <PackedScene.hpp>
#include <RigidBody2D.hpp>

#include <ResourceLoader.hpp>

#include <stdlib.h>
#include <time.h>

#include "Player.h"
#include "Mob.h"
#include "HUD.h"

namespace godot{
class Main : public Node{
    GODOT_CLASS(Main, Node);

private:
    int score;

    Player* player;
    Mob* mob;
    HUD* hud;

    Timer* mob_timer;
    Timer* score_timer;
    Timer* start_timer;
    CanvasLayer* hud_node;
    AudioStreamPlayer* music;
    AudioStreamPlayer* death_sound;
    Area2D* player_node;
    Position2D* start_position;
    PathFollow2D* mob_spawn_location;
    RigidBody2D* mob_node;
    Ref<PackedScene> mob_scene;

public:
    static void _register_methods();

    Main();
    ~Main();

    void _init();
    void _ready();

    void game_over();
    void new_game();

    void _on_StartTimer_timeout();
    void _on_ScoreTimer_timeout();
    void _on_MobTimer_timeout();

};
}

#endif