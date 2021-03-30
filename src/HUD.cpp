#include "HUD.h"

using namespace godot;

void HUD::_register_methods(){
    register_method("_ready", &HUD::_ready);
    register_method("show_message", &HUD::show_message);
    register_method("show_game_over", &HUD::show_game_over);
    register_method("update_score", &HUD::update_score);
    register_method("_on_StartButton_pressed", &HUD::_on_StartButton_pressed);
    register_method("_on_MessageTimer_timeout", &HUD::_on_MessageTimer_timeout);

    register_method("_on_TimerButton_timeout", &HUD::_on_TimerButton_timeout);
    register_method("_on_TimerGameOver_timeout", &HUD::_on_TimerGameOver_timeout);
    
    register_signal<HUD>("start_game","node", GODOT_VARIANT_TYPE_INT);
}

HUD::HUD(){
}

HUD::~HUD(){
}

void HUD::_init(){
}

void HUD::_ready(){
    score_label = cast_to<Label>(get_node("ScoreLabel"));
    message = cast_to<Label>(get_node("Message"));
    start_button = cast_to<Button>(get_node("StartButton"));
    message_timer = cast_to<Timer>(get_node("MessageTimer"));

    start_button -> connect("pressed", this, "_on_StartButton_pressed");
    message_timer -> connect("timeout", this, "_on_MessageTimer_timeout");

    timer_game_over = Timer()._new();
    timer_start_button = Timer()._new();
    
    timer_game_over -> connect("timeout", this, "_on_TimerGameOver_timeout");
    timer_start_button -> connect("timeout", this, "_on_TimerButton_timeout");
   
    add_child(timer_game_over);
    add_child(timer_start_button);

    timer_game_over -> set_one_shot(true);
    timer_start_button -> set_one_shot(true);

    timer_game_over -> set_wait_time(2);
    timer_start_button -> set_wait_time(1);
    
}

void HUD::show_message(String text){
    message -> set_text(text);
    message -> show();
    message_timer -> start();
}

void HUD::show_game_over(){
    show_message("Game Over");
    timer_game_over -> start();
}

void HUD::update_score(Variant score){
    score_label -> set_text(score);
}

void HUD::_on_StartButton_pressed(){
    start_button -> hide();
    emit_signal("start_game",0);
}

void HUD::_on_MessageTimer_timeout(){
    message -> hide();
}

void HUD::_on_TimerGameOver_timeout(){
    message -> set_text("Dodge the \nCreeps!");
    message -> show();
    timer_start_button -> start();
}

void HUD::_on_TimerButton_timeout(){
    start_button -> show(); 
}