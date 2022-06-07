#include "raylib.h"
#include <random> 
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <sstream>

using namespace std;

//Declaring global vars that are used a bunch
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);
std::uniform_real_distribution<double> distribution(0.0,1.0);
const double height {1080};
const double width {1920};
const double radius {20};
bool hit{false};
double tempx{0};
double tempy{0};
double color_num[3] = {250, 250, 250}; 
bool hit_corner = false;
int trace_color = 0;
bool temp_bool{false};
bool good_hit{false};
int frames{-1};
const char* print_time = "60";
//For Pong: Player lengths
double player_legnth{height*0.25};
double player_bottom_top[2][2];
double players_xLoc[2];
int score[2] = {0,0};
int wins[2] = {0,0};

bool left_clicked{false};
bool right_clicked{true};
bool begun{false};
double orig_vel_mag{5};

bool boot_up_screen(){
    bool player_closed{false};
    int opening_timer{0};
    bool leave{false};
    double top_title[2] = {741, 429};
    Music Opening_mu_start = LoadMusicStream("./Sound/Music/Begin_open.wav");
    PlayMusicStream(Opening_mu_start);
    while (leave == false){
        if (WindowShouldClose()){
            leave = true;
            player_closed = true;
        }
        UpdateMusicStream(Opening_mu_start);
        BeginDrawing();
        opening_timer += 1;
        DrawText("A GAME BY MR.", width/2 - 200, height * 0.4, 50, WHITE);
        DrawText("DIEGO GARCIA", width/2 - 500, height * 0.5, 150, GREEN);
        // DrawRectangle(top_title[0], top_title[1], 600, 50, RED);
        // DrawRectangle(449, 554, 1200, 150, RED);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            leave = true;
        }
        if (opening_timer < 360){
            top_title[0] += 1.3;
            DrawRectangle(top_title[0], top_title[1], 600, 50, BLACK);
            DrawRectangle(449, 554, 1200, 150, BLACK);

        }
        if (opening_timer > 23.5 * 60){
            leave = true;
        }
        ClearBackground(BLACK);
        EndDrawing();
        
    }
    StopMusicStream(Opening_mu_start);
    UnloadMusicStream(Opening_mu_start);
    return player_closed;
}

bool boot_title_screen(Music * mu){
  int opening_timer{0};
  
  int music_timer{0};
  int mousex{};
  int mousey{};
  double top_title[2] = {width/2 - 500, -150};
  bool leave{false};
  bool player_closed{false};
  bool change_start_color{false};
//   PlayMusicStream(*mu);
  while (leave == false){
    if (WindowShouldClose()){
        leave = true;
        player_closed = true;
    }
    UpdateMusicStream(*mu);
    opening_timer += 1;
    music_timer += 1;
    DrawText("PONGO", width/2 - 400-40, top_title[1], 250, WHITE);
    if (music_timer % 63 == 0){
        if (change_start_color){
            change_start_color = false;
        }
        else{
            change_start_color = true;
        }
    }
    if (change_start_color){
        DrawRectangle(730-40, 500, 520, 150, RED);
    }
    else{
        DrawRectangle(730-40, 500, 520, 150, BLUE);
    }
    DrawText("START", width/2 - 150-40, 530, 100, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      mousex = GetTouchX();
      mousey = GetTouchY();
      if ((730-40 < mousex) & (mousex < 1250-40)){
          if ((500 < mousey) & (mousey < 650 )){
              leave = true;
          }
      }
    
    }
    if (opening_timer < 360){
      top_title[1] += 1;
    }
    
    ClearBackground(BLACK);
    EndDrawing();
  }
  StopMusicStream(*mu);
  return player_closed;
}

bool title_screen(Music * mu){
  int opening_timer{0};
  int music_timer{0};
  int mousex{};
  int mousey{};
  double top_title[2] = {width/2 - 500, -150};
  bool leave{false};
  bool player_closed{false};
  bool change_start_color{false};
  PlayMusicStream(*mu);
  int shift{40};
  const char* player_1_wins = "0";
  stringstream strs;
  strs << wins[0];
  string temp_str = strs.str();
  player_1_wins = (char*) temp_str.c_str();

  const char* player_2_wins = "0";
  stringstream strs2;
  strs2 << wins[1];
  string temp_str2 = strs2.str();
  player_2_wins = (char*) temp_str2.c_str();

  while (leave == false){
    if (WindowShouldClose()){
        leave = true;
        player_closed = true;
    }
    UpdateMusicStream(*mu);
    opening_timer += 1;
    music_timer += 1;
    DrawText("PONGO", width/2 - 400-shift, top_title[1], 250, WHITE);
    DrawText("Player 1 Wins", 150, top_title[1]-150, 50, BLUE);
    DrawText("Player 2 Wins", width - 500, top_title[1]-150, 50, RED);
    DrawText(player_1_wins, 150+150, top_title[1]-150+70, 50, BLUE);
    DrawText(player_2_wins, width - 500+160, top_title[1]-150+70, 50, RED);
    if (music_timer % 63 == 0){
        if (change_start_color){
            change_start_color = false;
        }
        else{
            change_start_color = true;
        }
    }
    if (change_start_color){
        DrawRectangle(730-shift, 500, 520, 150, RED);
    }
    else{
        DrawRectangle(730-shift, 500, 520, 150, BLUE);
    }
    DrawText("START", width/2 - 150 -shift, 530, 100, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      mousex = GetTouchX();
      mousey = GetTouchY();
      if ((730 - shift < mousex) & (mousey < 1250 - shift)){
          if ((500 < mousey) & (mousey < 650 )){
              leave = true;
          }
      }
    
    }
    if (opening_timer < 360){
      top_title[1] += 1;
    }
    
    ClearBackground(BLACK);
    EndDrawing();
  }
  StopMusicStream(*mu);
  return player_closed;
}

bool end_screen(Music * mu){
  bool leave{false};
  int music_timer{0};
  int flash_timer{0};
  int mousex{};
  int mousey{};
  bool player_closed{false};
  bool change_start_color{false};
  int name_y{-10};
  const char* player_1_score = "0";
  stringstream strs;
  strs << score[0];
  string temp_str = strs.str();
  player_1_score = (char*) temp_str.c_str();

  const char* player_2_score = "0";
  stringstream strs2;
  strs2 << score[1];
  string temp_str2 = strs2.str();
  player_2_score = (char*) temp_str2.c_str();
  if (score[0] > score[1]){
      wins[0] += 1;
  }
  else if (score[0] < score[1]){
      wins[1] += 1;
  }

  PlayMusicStream(*mu);
  while (leave == false){
    music_timer += 1;
    if (WindowShouldClose()){
        leave = true;
        player_closed = true;
    }

    if (music_timer < 240){
        name_y += 1;
    }
    else{
        if (music_timer > 260){
          DrawText(player_1_score, width*0.2+70, name_y + 75, 65, BLUE);
          DrawText(player_2_score, width*0.68+70, name_y + 75, 65, RED); 
        
          if (music_timer > 280){
            if (music_timer > 28.6*60){
                leave = true;
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                mousex = GetTouchX();
                mousey = GetTouchY();
                if ((730-50 < mousex) & (mousex < 730-50 + 520)){
                    if ((500 < mousey) & (mousey < 650 )){
                        leave = true;
                    }
                }
                
            }
            flash_timer += 1;
            if (flash_timer % 63 == 0){
              if (change_start_color){
                change_start_color = false;
              }
              else{
                change_start_color = true;
              }
            }
            if (score[0] > score[1]){
                DrawRectangle(730-50, 500, 520, 150, BLUE);
                if (change_start_color == false){
                    DrawText("PLAYER 1", 705, 530, 100, BLACK);
                }
                else{
                    DrawText("WINS", width/2 - 150, 530, 100, BLACK);
                }
            }
            
            else if (score[0] < score[1]){
                DrawRectangle(730-50, 500, 520, 150, RED);
                if (change_start_color == false){
                    DrawText("PLAYER 2", 690, 530, 100, BLACK);
                }
                else{
                    DrawText("WINS", width/2 - 150, 530, 100, BLACK);
                }
            }
            else{
                if (change_start_color){
                    DrawRectangle(730-50, 500, 520, 150, BLUE);
                }
                else{
                    DrawRectangle(730-50, 500, 520, 150, RED);
            }
            DrawText("TIE", width/2 - 120, 530, 100, BLACK);
            }

          }

        }
        
    }
    DrawText("Player 1", width*0.2, name_y, 50, BLUE);
    DrawText("Player 2", width*0.68, name_y, 50, RED);
    
    UpdateMusicStream(*mu);
    
    ClearBackground(BLACK);
    EndDrawing();
  }
  StopMusicStream(*mu);
  return player_closed;
}

double gen_rand_angle(){ //Generates random angle between [-45,45] or [135, 225]
    double angle = distribution(generator) * 90 - 45;
    double direction = distribution(generator);
    if (direction < 0.5){ //Points left then
        angle = 180 - angle;
    }
    angle = angle * PI/180;
    return angle;
}

void update_player_loc(){
    if (IsKeyDown(KEY_W)){
                    player_bottom_top[0][0] -= 10;
                    player_bottom_top[0][1] -= 10;
        }
    if (IsKeyDown(KEY_UP)){
                    player_bottom_top[1][0] -= 10;
                    player_bottom_top[1][1] -= 10;
        }
    if (IsKeyDown(KEY_S)){
                    player_bottom_top[0][0] += 10;
                    player_bottom_top[0][1] += 10;
        }
    if (IsKeyDown(KEY_DOWN)){
                    player_bottom_top[1][0] += 10;
                    player_bottom_top[1][1] += 10;
        }
    if (player_bottom_top[0][0] > height){
        player_bottom_top[0][0] = height;
        player_bottom_top[0][1] = player_bottom_top[0][0] - player_legnth;
    }
    else if (player_bottom_top[0][1] < 0){
        player_bottom_top[0][0] = player_legnth;
        player_bottom_top[0][1] = 0;
    }
    if (player_bottom_top[1][0] > height){
        player_bottom_top[1][0] = height;
        player_bottom_top[1][1] = player_bottom_top[1][0] - player_legnth;
    }
    else if (player_bottom_top[1][1] < 0){
        player_bottom_top[1][0] = player_legnth;
        player_bottom_top[1][1] = 0;
    }
}

void update_loc(double pos[2], double vel[2], CLITERAL(Color) * col_def_pt, Sound * scorefx){
    //For Ball Collisions with players
    double s1{};
    double check_y{};
    bool hit_player{false};

    //For scoring
    bool reset_ball{false};

    //Updating player loc
    update_player_loc();
    //Updates location array and color if necessary
    tempx = pos[0] + vel[0];
    tempy = pos[1] + vel[1];
    if (tempx < players_xLoc[0] + radius){ //Checking if past player1
        s1 = (players_xLoc[0] + radius - pos[0])/vel[0];
        check_y = s1 * vel[1] + pos[1];
        if ((check_y < player_bottom_top[0][0]) & (check_y > player_bottom_top[0][1])){
            //Hits player and bounces back
            hit = true;
            pos[0] = players_xLoc[0] + radius;
            hit_player = true;
            vel[0] = - vel[0];
        }
        else{
            if (tempx > radius){ //Passes player and continues
                pos[0] = tempx;
            }
            else{
                //Player 2 scores and reset ball
                reset_ball = true;
                score[1] += 1;
            }
        }
    }
    else if ((tempx > players_xLoc[1] - radius)){//Checking if past player2
        s1 = (players_xLoc[1] - radius - pos[0])/vel[0];
        check_y = s1 * vel[1] + pos[1];
        if ((check_y < player_bottom_top[1][0]) & (check_y > player_bottom_top[1][1])){
            //Hits player and bounces back
            hit = true;
            pos[0] = players_xLoc[1] - radius;
            hit_player = true;
            vel[0] = - vel[0];
        }
        else{
            if (tempx < width){ //Passes player and continues
                pos[0] = tempx;
            }
            else{
                //Player 1 scores and reset ball
                reset_ball = true;
                score[0] += 1;
            }
        }
    }
    else{
        pos[0] = tempx;
    }
    //Checking if it hits top or bottom
    if (radius < tempy){
        //If false hits bottom of box
        if (tempy < height - radius){
            pos[1] = tempy;
        }
        else{
            //If false hits top of box
            hit = true;
            pos[1] = height - radius;
            vel[1] = -vel[1];
        }
    }
    else {
        hit = true;
        pos[1] = radius;
        vel[1] = -vel[1];
    }

    if (hit){
        if (hit_player){

            good_hit = true;
            trace_color = 4;
            color_num[0] = 250*distribution(generator);
            color_num[1] = 250*distribution(generator);
            color_num[2] = 250*distribution(generator);
            *col_def_pt = {(unsigned char) color_num[0], (unsigned char) color_num[1], (unsigned char)color_num[2], (unsigned char)250};
            vel[0] *= 1.3;
            vel[1] *= 1.2;
        }
    }
    else if (reset_ball){
        PlaySoundMulti(*scorefx);
        double angle1 = gen_rand_angle();
        *col_def_pt = {(unsigned char)250, (unsigned char)250, (unsigned char)250, (unsigned char)250};
        pos[0] = width/2;
        pos[1] = height/2;
        vel[0] = orig_vel_mag * cos(angle1);
        vel[1] = orig_vel_mag * sin(angle1);
    }
    hit = false;
}

int main(){
    int game_screen{0};
    bool player_closed{false};

    player_bottom_top[0][0] = 0.5 *height + 0.5* player_legnth; //Player 1 Bottom
    player_bottom_top[0][1] = 0.5 *height - 0.5* player_legnth; //Player 1 Bottom
    player_bottom_top[1][0] = 0.5 *height + 0.5* player_legnth; //Player 2 Bottom
    player_bottom_top[1][1] = 0.5 *height - 0.5* player_legnth; //Player 2 Bottom
    players_xLoc[0] = 0.025* width;
    players_xLoc[1] = 0.975* width;

    //Time for game
    int time{60};
    bool game_over{false};
    //Code to make ball bounce around the stuff and change color, will stick to wall for a sec
    double velocity_mag = orig_vel_mag;
    double angle2 = gen_rand_angle();

    // In pixels per loop lol
    double ball_velocity[2]={velocity_mag * cos(angle2), velocity_mag* sin(angle2)};
    double ball_pos[2]={width*0.5, height*0.5};
    CLITERAL(Color) Ball_col = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)250};
    CLITERAL(Color) old_col4 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)200};
    CLITERAL(Color) old_col3 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)150};
    CLITERAL(Color) old_col2 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)100};
    CLITERAL(Color) old_col1 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)50};

    //Trace
    double old_locs[4][2];
    for (int i = 0; i < 4; i++) {
        old_locs[i][0] = ball_pos[0];
        old_locs[i][1] = ball_pos[1];
    }

    //Define Pointers
    CLITERAL(Color) * Ball_col_pt;

    //Pointers 
    Ball_col_pt = &Ball_col;
    
    InitWindow(width, height,"Pong_De_Diago");
    InitAudioDevice();
    Sound hitfx = LoadSound("./Sound/Sound_effect/Hit_sound.wav");
    Sound scorefx = LoadSound("./Sound/Sound_effect/ScoreFx.wav");
    Sound * scorefx_pt = &scorefx;
    Music background_mu = LoadMusicStream("./Sound/Music/Background_loop.wav");
    Music Opening_mu_loop = LoadMusicStream("./Sound/Music/Opening_loop.wav");
    Music * Opening_mu_loop_pt = &Opening_mu_loop;
    Music end_music = LoadMusicStream("./Sound/Music/Ending.wav");
    Music * end_mu_loop_pt = &end_music;

    // Music Ending_mu = LoadMusicStream();

    SetSoundVolume(hitfx, 0.2f);
    SetMusicVolume(background_mu, 0.3f);
    SetTargetFPS(60);
    player_closed = WindowShouldClose();
    while (player_closed == false){
        if (game_screen == 1){
            player_closed = title_screen(Opening_mu_loop_pt);
            game_screen = 2;
        }
        else if (game_screen == 2){
            frames = -1;
            PlayMusicStream(background_mu);
            time = 60;
            while (game_over == false){
                if (frames == -1){
                frames = 0;
                }
                if (good_hit){
                    good_hit = false;
                    PlaySoundMulti(hitfx);
                }
                BeginDrawing();
                frames += 1;
                player_closed = WindowShouldClose();
                if (player_closed){
                    game_over = true;
                }
                UpdateMusicStream(background_mu);
                if(frames == 60){
                    // cout << time << "\n";
                    frames = 0;
                    time += -1;
                    stringstream strs;
                    strs << time;
                    string temp_str = strs.str();
                    print_time = (char*) temp_str.c_str();
                    if (time == 0){
                        game_over = true;
                    }
                }
                DrawText("Time Remaining", width/2 - 180, height/2 - 100, 50, WHITE);
                DrawText(print_time, width/2, height/2, 50, WHITE);

                //Drawing Players
                DrawLine(players_xLoc[0], player_bottom_top[0][0], players_xLoc[0], player_bottom_top[0][1], BLUE);
                DrawLine(players_xLoc[1], player_bottom_top[1][0], players_xLoc[1], player_bottom_top[1][1], RED);

                //Drawing Trail and ball
                DrawCircle(old_locs[0][0], old_locs[0][1], radius*0.2, old_col1);
                DrawCircle(old_locs[1][0], old_locs[1][1], radius*0.4, old_col2);
                DrawCircle(old_locs[2][0], old_locs[2][1], radius*0.6, old_col3);
                DrawCircle(old_locs[3][0], old_locs[3][1], radius*0.8, old_col4);
                DrawCircle(ball_pos[0], ball_pos[1], radius, Ball_col);

                for (int i = 0; i < 3; i++) {
                    old_locs[i][0] = old_locs[i+1][0];
                    old_locs[i][1] = old_locs[i+1][1];
                }
                old_locs[3][0] = ball_pos[0];
                old_locs[3][1] = ball_pos[1];
                update_loc(ball_pos, ball_velocity, Ball_col_pt, scorefx_pt);
                for (int i = 0; i < 3; i++) {
                old_locs[i][0] = old_locs[i+1][0];
                old_locs[i][1] = old_locs[i+1][1];
                }
                old_locs[3][0] = ball_pos[0];
                old_locs[3][1] = ball_pos[1];

                update_loc(ball_pos, ball_velocity, Ball_col_pt, scorefx_pt);

                if (trace_color != 0){
                    if (trace_color == 4){
                        old_col4 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)200};
                    }
                    else if (trace_color == 3){
                        old_col3 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)150};
                    }
                    else if (trace_color == 2){
                        old_col2 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)100};
                    }
                    else{
                        old_col1 = {(unsigned char)color_num[0], (unsigned char)color_num[1],(unsigned char) color_num[2], (unsigned char)50};
                    }
                    trace_color -= 1;
                }
                ClearBackground(BLACK);
                EndDrawing();
            }
            game_screen = 3;
            game_over = false;
        }
        else if(game_screen == 3){
            StopMusicStream(background_mu);
            player_closed = end_screen(end_mu_loop_pt);
            game_screen = 1;
            score[0] = 0;
            score[1] = 0;
        }

        else if (game_screen == 0){ //Bootup_screent
            player_closed = boot_up_screen();
            game_screen += 1;
            if (player_closed == false){
                PlayMusicStream(Opening_mu_loop);
                player_closed = boot_title_screen(Opening_mu_loop_pt);
            }
            game_screen = 2;
            // game_screen = 1;
        }
        ClearBackground(BLACK);
        EndDrawing();
    }
    
    CloseAudioDevice(); 
}