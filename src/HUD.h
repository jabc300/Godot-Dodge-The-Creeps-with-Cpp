#ifndef HUD_H
#define HUD_H

#include <Godot.hpp>

#include <CanvasLayer.hpp>
#include <Label.hpp>
#include <Button.hpp>
#include <Timer.hpp>

namespace godot{
class HUD : public CanvasLayer {
    GODOT_CLASS(HUD, CanvasLayer);
private:
    Label* score_label;
    Label* message;
    Button* start_button;
    Timer* message_timer;
    Timer* timer_start_button;
    Timer* timer_game_over;

public:
    static void _register_methods();

    HUD();
    ~HUD();

    void _init();
    void _ready();

    void show_message(String text);
    void show_game_over();
    void update_score(Variant score);
    void _on_StartButton_pressed();
    void _on_MessageTimer_timeout();
    void _on_TimerButton_timeout();
    void _on_TimerGameOver_timeout();
};
}


#endif