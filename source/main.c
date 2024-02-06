
#define RSGLDEF
#include <RSGL.h>
#include <stdio.h>

#include "vector.h"

u8 map[] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 3, 3, 0, 3, 0, 0, 2,
    2, 0, 0, 3, 0, 0, 3, 0, 0, 2,
    2, 0, 0, 3, 0, 0, 3, 0, 0, 2,
    2, 0, 0, 3, 0, 3, 3, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

float hMap[] = {
    20.0, 20.0, 20.0, 20.0, 20.0, 10.0, 20.0, 20.0, 20.0, 20.0,
    20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 10.0, 10.0, 0.0, 100.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 10.0, 0.0, 0.0, 10.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 10.0, 0.0, 0.0, 10.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 10.0, 0.0, 10.0, 10.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0,
    20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 20.0,
    20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0, 20.0,
};

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define MAP_CORD(x, y) map[(x) + (y) * MAP_WIDTH]
#define MAP_CORDV(v) MAP_CORD((size_t)v.x, (size_t)v.y)

#define HMAP_CORD(x, y) hMap[(x) + (y) * MAP_WIDTH]
#define HMAP_CORDV(v) HMAP_CORD((size_t)v.x, (size_t)v.y)

#define RGL_LINES_2D                                0x0011      /* GL_LINES */
#define RGL_TRIANGLES_2D                            0x0014      /* GL_TRIANGLES */
#define RGL_QUADS_2D                                0x0017      /* GL_QUADS */

unsigned char icon[4 * 9 * 9] = {
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    
    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,    0xFF, 0xFF, 0x00, 0xFF,    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,    0xFF, 0xFF, 0x00, 0xFF,    0xFF, 0xFF, 0x00, 0xFF,    
    
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,  0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,    0x00, 0x00, 0x00, 0x00,     0xFF, 0xFF, 0x00, 0xFF,   0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,
};


int main() {
    RSGL_window* win = RSGL_createWindow("name", RSGL_RECT(0, 0, 640, 400), RGFW_CENTER | RSGL_HIDE_MOUSE);
    //RGFW_window_moveMouse(win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2));

    RSGL_pointF player = RSGL_POINTF(2, 2); 
    float z = 0, jumpZ = 0;
    float playerAngle = 90;

    i32 precision = 64;
    u8 fov = 60;
    
    float defaultHeight = (win->r.h / 4.0f);

    float playerVelocity = 0.25;

    u32 wallTexture = RSGL_loadImage("wall.png");
    u32 wall2Texture = RSGL_loadImage("wall2.png");
  
//    RSGL_setFont(RSGL_loadFont("SansPosterBold.ttf"));

    bool running = true;

    RSGL_point mouse = RSGL_POINT(win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2));
    RGFW_window_moveMouse(win, win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2));

    while (running) {
        while (RSGL_window_checkEvent(win)) {
            if (win->event.type == RSGL_quit || RSGL_isPressedI(win, RGFW_Escape)) {
                running = false;
                break;
            }

            /* simular to rayComp but for player movement */
            vector2D playerComp = VECTOR2D(cos(DEG2RAD * playerAngle) * playerVelocity,  sin(DEG2RAD * playerAngle) * playerVelocity);                
            vector2D playerCompLR = VECTOR2D(cos(DEG2RAD * (playerAngle - 180)) * playerVelocity,  sin(DEG2RAD * (playerAngle - 180)) * playerVelocity);

            if (win->event.type == RSGL_mousePosChanged) {
                if (win->event.x > (win->r.w / 2))
                    playerAngle += 2;
                if (win->event.x < (win->r.w / 2))
                    playerAngle -= 2;
                
                if (win->event.y > (win->r.h / 2))
                    z -= 5;
                if (win->event.y < (win->r.h / 2))
                    z += 5;
                
                RGFW_window_moveMouse(win, win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2));
            }

            if (win->event.type == RGFW_keyPressed) {
                if ((RGFW_isPressedI(win, RGFW_w)) && MAP_CORDV(vector_add(player, playerComp)) == 0)
                    player = vector_add(player, playerComp);
                else if ((RGFW_isPressedI(win, RGFW_s)) && MAP_CORDV(vector_sub(player, playerComp)) == 0)
                    player = vector_sub(player, playerComp);
                else if (RGFW_isPressedI(win, RGFW_d) && MAP_CORDV(vector_add(player, playerCompLR)) == 0)
                    player = vector_add(player, playerCompLR);
                else if (RGFW_isPressedI(win, RGFW_a) && MAP_CORDV(vector_sub(player, playerCompLR)) == 0)
                    player = vector_sub(player, playerCompLR);

                else if (RSGL_isPressedI(win, RGFW_Left))
                    playerAngle -= 5;
                else if (RSGL_isPressedI(win, RGFW_Right))
                    playerAngle += 5;
                
                else if (RGFW_isPressedI(win, RGFW_Down) && z > -300)
                    z -= 5;
                else if (RGFW_isPressedI(win, RGFW_Up) && z < 300)
                    z += 5;
                    
                else if (RGFW_isPressedI(win, RGFW_Space) && jumpZ == 0)
                    z += jumpZ = 30;
            }        
        }

        if (jumpZ > 0) {
            jumpZ -= 0.5;
            z -= 0.5;
        }

        if (RGFW_isPressedI(win, RGFW_Tab)) {
            for (int y = 0; y < MAP_HEIGHT; y++)
                for (int x = 0; x < MAP_WIDTH; x++) {
                    RSGL_drawRect(RSGL_RECT(20 * x, 20 * y, 20, 20), RSGL_RGB(MAP_CORD(x, y) ? 255 : 0, 0, 0));
                }

            RSGL_drawRect(RSGL_RECT(20 * player.x, 20 * player.y, 2, 2), RSGL_RGB(240, 220, 0));
        }
        
        float rayAngle = playerAngle - ((float)fov / 2.0f);

        for(size_t i = 0; i < win->r.w; i++) {
            RSGL_pointF ray = player;

            /*
                x comp of ray / precision
                y comp of ray / precision

                This is so it checks one (block / precision) at a time
            */
            vector2D rayComp = VECTOR2D(cos(DEG2RAD * rayAngle) / precision, sin(DEG2RAD * rayAngle) / precision);
            static vector2D vectors[20];
            size_t vIndex = 0;

            do { 
                if (MAP_CORDV(ray) && HMAP_CORDV(ray) < HMAP_CORDV(vector_add(ray, rayComp))) {
                    vectors[vIndex] = ray;
                    vIndex++;
                }

                ray = vector_add(ray, rayComp); 
            }
            while (MAP_CORDV(ray) == 0 || HMAP_CORDV(ray) < HMAP_CORDV(vector_add(ray, rayComp)));
            
            RSGL_pointF rayI = ray;

            /* 
                get the distance, times the cos diff between the ray and the player  
                it is a quick fix to make sure the angle is properly lined up with the player view angle
            */           
            float distance = vector_dist(ray, player) * cos(DEG2RAD * (rayAngle - playerAngle));
            float wallHeight = (size_t)(float)((float)(defaultHeight / distance))  + HMAP_CORDV(ray);
            
            if (RGFW_isPressedI(win, RGFW_Tab) == false) {                
                RSGL_drawRectF(RSGL_RECTF(i, 0, 1, z + (defaultHeight - wallHeight)), RSGL_RGB(0, 255, 255));
                RSGL_color color = RSGL_RGB(100, 100, 100);

                for (u32 i = 0; i < vIndex; i++) {
                    vector2D ray = vectors[i];

                    float distance = vector_dist(ray, player) * cos(DEG2RAD * (rayAngle - playerAngle));
                    float wallHeight = (size_t)(float)((float)(defaultHeight / distance))  + HMAP_CORDV(ray);     
                    
                    {           
                        RSGL_rectF r = RSGL_RECTF(i, z + (defaultHeight - wallHeight), 1, z + defaultHeight + wallHeight);
                        RSGL_point3DF points[] = {{r.x, r.y, 0.0f}, {r.x, r.y + r.h, 0.0f}, {r.x + r.w, r.y + r.h, 0.0f}, {r.x + r.w, r.y, 0.0f}};
                        RSGL_point3DF texPoints[] = {{((i32)ray.x) - ray.x, 0.0f, 0.0f}, {((i32)ray.x) - ray.x, 1.0f, 0.0f}, {(((i32)ray.x) - ray.x) + 0.1 , 1.0f, 0.0f}, {(((i32)ray.x) - ray.x) + 0.1, 0.0f, 0.0f}};

                        RSGL_basicDraw(RGL_QUADS_2D, (RSGL_point3DF*)points, (RSGL_point3DF*)texPoints, r, RSGL_RGB(255, 255, 255), 4);
                        RSGL_setTexture(MAP_CORDV(ray)); 
                        printf("%i\n", MAP_CORDV(ray));
                    }
                }
                
                if (HMAP_CORDV(ray) == 20)
                    color = RSGL_RGB(255, 0, 0);

                {                
                    RSGL_rectF r = RSGL_RECTF(i, z + (defaultHeight - wallHeight), 1, z + defaultHeight + wallHeight);
                    RSGL_point3DF points[] = {{r.x, r.y, 0.0f}, {r.x, r.y + r.h, 0.0f}, {r.x + r.w, r.y + r.h, 0.0f}, {r.x + r.w, r.y, 0.0f}};
                    RSGL_point3DF texPoints[] = {{((i32)ray.x) - ray.x, 0.0f, 0.0f}, {((i32)ray.x) - ray.x, 1.0f, 0.0f}, {(((i32)ray.x) - ray.x) + 0.1 , 1.0f, 0.0f}, {(((i32)ray.x) - ray.x) + 0.1, 0.0f, 0.0f}};

                    RSGL_basicDraw(RGL_QUADS_2D, (RSGL_point3DF*)points, (RSGL_point3DF*)texPoints, r, RSGL_RGB(255, 255, 255), 4);
                    RSGL_setTexture(MAP_CORDV(ray));  
                }
                
                RSGL_drawLineF(RSGL_POINTF(i, z + defaultHeight + wallHeight), RSGL_POINTF(i, win->r.h * 4), 1, RSGL_RGB(0, 255, 0));
                //RSGL_drawRectF(RSGL_RECTF(i, z + defaultHeight + wallHeight, 1, win->r.h), RSGL_RGB(0, 255, 0));                   
                RSGL_setTexture(1);
            }
            
            else 
                RSGL_drawLineF(vector_mul(player, VECTOR2D(20, 20)), vector_mul(ray, VECTOR2D(20, 20)), 1, RSGL_RGB(0, 255, 0));

            rayAngle += ((float)fov / win->r.w);
        }
    
        RSGL_window_clear(win, RSGL_RGB(0, 0, 0));
    }

    RSGL_window_close(win);
}