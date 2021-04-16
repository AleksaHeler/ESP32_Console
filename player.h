#ifndef PLAYER_H
#define PLAYER_H

#include "engine.h"
#include "game_data.h"
#include <math.h>

extern camera_t player_camera;

void player_init();

void player_update();

camera_t player_camera;

void player_init() {
    player_camera.pos_x = 22.5, player_camera.pos_y = 12.5;  // player x and y start position
    player_camera.dir_x = -1, player_camera.dir_y = 0; // initial player direction vector

    // Camera plane is perpendicular to the direction, but we 
    //  can change the length of it. The ratio between the length
    //  of the direction and the camera plane determinates the FOV.
    //  FOV is 2 * atan(0.66/1.0)=66°, which is perfect for a first person shooter game
    player_camera.plane_x = 0, player_camera.plane_y = 0.66; // the 2d raycaster version of camera plane
}

void player_update() {
    /////////////////////////////////////
    // Poll controls:
    // The speed modifiers use frameTime, and a constant value, to 
    // determinate the speed of the moving and rotating of the input 
    // keys. Thanks to using the frameTime, we can make sure that the 
    // moving and rotating speed is independent of the processor speed
    //double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    //double rotSpeed = frameTime * 3.0;  //the constant value is in radians/second
    // TODO: make speeds relate to time and not FPS
    
    double move_speed = 5.0/30.0;
    double rotation_speed = 3.0/30.0;
    double player_width = 0.3;

    char inA = 0;
    char inS = 0;
    char inD = 0;
    char inW = 0;
    if (Serial.available() >= 4) {
      // read the incoming byte:
      inA = Serial.read();
      inS = Serial.read();
      inD = Serial.read();
      inW = Serial.read();
      
      while(Serial.available() > 0) {
        char t = Serial.read();
      }
     
      // Move forward if no wall in front of the player
      if(inW == 'w') {
          if(world_map[(int)(player_camera.pos_x + player_camera.dir_x * move_speed + player_camera.dir_x*player_width)][(int)player_camera.pos_y] == 0) 
              player_camera.pos_x += player_camera.dir_x * move_speed;
          if(world_map[(int)(player_camera.pos_x)][(int)(player_camera.pos_y + player_camera.dir_y * move_speed + player_camera.dir_y*player_width)] == 0) 
              player_camera.pos_y += player_camera.dir_y * move_speed;
      }
      // Move backwards if no wall behind the player
      if(inS == 's') {
          if(world_map[(int)(player_camera.pos_x - player_camera.dir_x * move_speed - player_camera.dir_x*player_width)][(int)player_camera.pos_y] == 0) 
              player_camera.pos_x -= player_camera.dir_x * move_speed;
          if(world_map[(int)(player_camera.pos_x)][(int)(player_camera.pos_y - player_camera.dir_y * move_speed - player_camera.dir_y*player_width)] == 0) 
              player_camera.pos_y -= player_camera.dir_y * move_speed;
      }
  
      // Rotate to the right
      if(inD == 'd') {
          // Both camera direction and camera plane must be rotated
          // Rotating vectors by multiplying it with rotation matrix:
          //   [ cos(a) -sin(a) ]
          //   [ sin(a)  cos(a) ]
          double old_dir_x = player_camera.dir_x;
          player_camera.dir_x = player_camera.dir_x * cos(-rotation_speed) - player_camera.dir_y * sin(-rotation_speed);
          player_camera.dir_y = old_dir_x * sin(-rotation_speed) + player_camera.dir_y * cos(-rotation_speed);
          double old_plane_x = player_camera.plane_x;
          player_camera.plane_x = player_camera.plane_x * cos(-rotation_speed) - player_camera.plane_y * sin(-rotation_speed);
          player_camera.plane_y = old_plane_x * sin(-rotation_speed) + player_camera.plane_y * cos(-rotation_speed);
      }
      // Rotate to the left
      if(inA == 'a') {
          // Both camera direction and camera plane must be rotated
          double old_dir_x = player_camera.dir_x;
          player_camera.dir_x = player_camera.dir_x * cos(rotation_speed) - player_camera.dir_y * sin(rotation_speed);
          player_camera.dir_y = old_dir_x * sin(rotation_speed) + player_camera.dir_y * cos(rotation_speed);
          double old_plane_x = player_camera.plane_x;
          player_camera.plane_x = player_camera.plane_x * cos(rotation_speed) - player_camera.plane_y * sin(rotation_speed);
          player_camera.plane_y = old_plane_x * sin(rotation_speed) + player_camera.plane_y * cos(rotation_speed);
      }
    }
}

#endif
