#include "drawing.h"
#include <stdio.h> 

void DashedLine(int line);
void Stairs(int stairs);
void Flower(int a, int b);
void Meadow();
void FlowerinMeadow();
void MeadowRow(int meadowsirka);
void Animace();
void NemeckoVLajka();

int main() {

  clear_screen();

  int drawing = 0;
  scanf("%d", &drawing);

  int stairs = 10;
  int line = 20;

  int a = 9;
  int b = 9;

  switch (drawing)
  {
  case 0:
    DashedLine(line);
    break;
  case 1:
    Stairs(stairs);
    break;
  case 2:
    Flower(a, b);
    break;
  case 3:
    Meadow();
    break;
  case 4:
    Animace();
    break;
  default:
    break;
  }

  end_drawing();
  return 0;
}

void Animace(){
    for (int i = 2; i < 10; i++)
    {
        move_to(i, i*2);
        NemeckoVLajka();
        animate_ms(500);
        clear_screen();
    }
    
}

void NemeckoVLajka(){
    set_black_color();
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            draw_pixel();
            move_right();
        }
        for (int i = 0; i < 20; i++)
        {
            move_left();
        }
        move_down();
    }
    reset_color();
    set_red_color();
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            draw_pixel();
            move_right();
        }
        for (int i = 0; i < 20; i++)
        {
            move_left();
        }
        move_down();
    }
    reset_color();
    set_yellow_color();
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            draw_pixel();
            move_right();
        }
        for (int i = 0; i < 20; i++)
        {
            move_left();
        }
        move_down();
    }   
    
}

void Meadow(){
    int meadowsirka = 48;
    set_green_color();
    for (int j = 0; j < canvas_height; j++)
    {
        for (int i = 0; i < meadowsirka; i++)
        {
            draw_pixel();
            move_right();
        }
        move_to(j+1, 0);
    }
    reset_color();
    move_to(1, 1);

    MeadowRow(meadowsirka);
    move_to(canvas_height/2, 1);
    MeadowRow(meadowsirka);
    
}

void MeadowRow(int meadowsirka){
    for (int i = 0; i < meadowsirka/4; i++)
    {
        FlowerinMeadow();
        move_right();
        move_right();
        move_up();
    }
}

void FlowerinMeadow(){
    set_blue_color();
    move_down();
    draw_pixel();
    move_right();
    move_up();
    draw_pixel();
    move_down();
    move_down();
    draw_pixel();
    move_up();
    set_yellow_color();
    draw_pixel();
    set_blue_color();
    move_right();
    draw_pixel();
}

void DashedLine(int line){  
    set_blue_color();
    for (int i = 0; i < line; i++)
    {
        draw_pixel();
        move_right();
        move_right();
    }
}

void Stairs(int stairs){
    set_blue_color();
    for (int i = 0; i < stairs; i++)
    {
        draw_pixel();
        move_right();
        move_down();
    }   
}

void Flower(int a, int b){
    move_to(0, 0);
    for (int i = 0; i < b; i++)
    {
        if (i == 0 || i == b/2 || i == b-1)
        {
            set_red_color();
            draw_pixel();
            move_right();
        }
        else
        {
            move_right();
        }
        reset_color();        
    }
    move_to(2, 0);
    for (int j = 0; j < a/2-2; j++)
    {
        for (int i = 0; i < b; i++)
        {
            set_red_color();
            draw_pixel();
            move_right();
        }
        move_to(2+j+1, 0);
    }
    move_to(a-a/2-1, b-b/2);
    for (int i = 0; i < a/2+2; i++)
    {
        set_green_color();
        if (i == 1)
        {

            draw_pixel();
            move_right();
            move_right();
            draw_pixel();
            move_down();
            draw_pixel();
            move_left();
            draw_pixel();
            move_left();
            draw_pixel();
            move_down();
            move_right();
            draw_pixel();
            move_left();
            draw_pixel();
            
        }
        else
        {
            draw_pixel();
            move_down();
        }
    }

    

    

    
    
}