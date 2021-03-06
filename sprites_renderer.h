#ifndef SPRITES_H
#define SPRITES_H

#include <math.h>
#include <stdint.h>
#include "game_data.h"
#include "engine.h"

///////////////////////////////////////////////////////////////////////////////
// Functions:
void draw_sprite(const uint8_t*, uint16_t, uint16_t, uint16_t, uint16_t);
void swap(int*, double*, int*, double*);
int partition(int*, double*, int, int);
void quick_sort(int*, double*, int, int);
void sort_sprites(int*, double*, camera_t*, int);

///////////////////////////////////////////////////////////////////////////////
// Draws whole sprite at the given location:
void draw_sprite(const uint8_t* src_p, uint16_t src_w, uint16_t src_h, uint16_t dst_x, uint16_t dst_y) {
    // Prodje kroz region na ekranu na kom treba biti iscrtano, i za svaki piksel nadje vrednost
    for(uint16_t x = 0; x < src_w; x++){ 
        for(uint16_t y = 0; y < src_h; y++){
            uint8_t r = src_p[y*src_w*4 + 4*x+2];
            uint8_t g = src_p[y*src_w*4 + 4*x+1];
            uint8_t b = src_p[y*src_w*4 + 4*x];

            setp(dst_x+x, dst_y+y, r, g, b);
            //vga.dot(dst_x+x, dst_y+y, vga.RGB(r*2, g*2, b*2));
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Sorting sprites by distance to player so that closer ones are rendered last (over the others) 
void swap(int* order1, double* dist1, int* order2, double* dist2){
    int temp_order = *order1;
    double temp_dist = *dist1;

    *order1 = *order2;
    *dist1 = *dist2;

    *order2 = temp_order;
    *dist2 = temp_dist;
}

int partition(int* order, double* dist, int begin, int end){
    double pivot_dist = dist[end];

    int i = begin - 1;

    for (int j = begin; j < end; j++){
        if(dist[j] > pivot_dist){
            i++;
            swap(&order[i], &dist[i], &order[j], &dist[j]);
        }
    }

    swap(&order[i + 1], &dist[i + 1], &order[end], &dist[end]);

    return i + 1;
}

void quick_sort(int* order, double* dist, int begin, int end){
    if(begin < end){
        int index = partition(order, dist, begin, end);

        quick_sort(order, dist, begin, index - 1);
        quick_sort(order, dist, index + 1, end);
    }
}

// From farthest to nearest
void sort_sprites(int* order, double* dist, camera_t* cam, int amount){
    // First calculate the distane frome player for each sprite
    for(int i = 0; i < num_sprites; i++) {
        order[i] = i;
        // Sqrt not taken, only relative distance is enough
        dist[i] = ((cam->pos_x - sprites_data[i].x) * (cam->pos_x - sprites_data[i].x) + (cam->pos_y - sprites_data[i].y) * (cam->pos_y - sprites_data[i].y));
    }
    // Then sort them
    quick_sort(order, dist, 0, amount - 1);
}

#endif // SPRITES_H
