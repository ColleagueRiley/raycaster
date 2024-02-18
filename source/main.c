
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
    /*200.0, 200.0, 200.0, 200.0, -10.0, 200.0, 200.0, 200.0, 200.0, 20.0,
    200.0, 200.0, 200.0, 200.0, -8.0, 200.0, 200.0, 200.0, 200.0, 20.0,
    200.0, 200.0, 200.0, 200.0, -6.0, 200.0, 200.0, 200.0, 200.0, 20.0,
    200.0, 200.0, 200.0, 200.0, -4.0, 200.0, 200.0, 200.0, 200.0, 20.0,
    200.0, 200.0, 200.0, 200.0,  0.0, 200.0, 200.0, 200.0, 200.0, 20.0,*/
    200.0, 200.0, 200.0, 200.0,  200.0, 200.0, 200.0, 200.0, 200.0, 20.0,
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

RSGL_window* win;
vector2D player;
float z;
float playerAngle;

i32 precision = 64;
u8 fov = 60;

void castRay(vector2D ray, float rayAngle, u32 x) {
    /*if (rayAngle >= 360.0f)
        rayAngle -= 360.0f;
    else if (rayAngle < 0.0f)
        rayAngle += 360.0f;*/
    

    
    float defaultHeight = (win->r.h / 4.0f);

    vector2D rayComp = VECTOR2D(cos(DEG2RAD * rayAngle) / precision, sin(DEG2RAD * rayAngle) / precision);
    vector2D next = vector_add(ray, rayComp);

    do {   
        if (RSGL_rectCollidePointF(RSGL_RECTF(0, 0, MAP_WIDTH, MAP_HEIGHT), next) == false)
            break;
        
        ray = next; 
        next = vector_add(ray, rayComp);
    } while (MAP_CORDV(ray) == 0 || HMAP_CORDV(ray) < HMAP_CORDV(vector_add(ray, rayComp)));

    /* 
        get the distance, times the cos diff between the ray and the player  
        it is a quick fix to make sure the angle is properly lined up with the player view angle
    */           

    float distance = vector_dist(ray, player) * cos(DEG2RAD * (rayAngle - playerAngle));
    float wallHeight = (size_t)(float)((float)(defaultHeight / distance))  + HMAP_CORDV(ray);
    
    if (RGFW_isPressedI(win, RGFW_Tab))
        RSGL_drawLineF(vector_mul(player, VECTOR2D(20, 20)), vector_mul(ray, VECTOR2D(20, 20)), 1, RSGL_RGBA(0, 255, 0, 100)); 

    RSGL_drawRectF(RSGL_RECTF(x, 0, 1, z + (defaultHeight - wallHeight)), RSGL_RGBA(0, 255, 255, 255));
    RSGL_setTexture(1);
    
    if (MAP_CORDV(ray) && HMAP_CORDV(ray) < HMAP_CORDV(next))
        castRay(next, rayAngle, x);
    
    {
        RSGL_rectF r = RSGL_RECTF(x, z + (defaultHeight - wallHeight), 1, defaultHeight + wallHeight);
        RSGL_point3DF points[] = {{r.x, r.y, 0.0f}, {r.x, r.y + r.h, 0.0f}, {r.x + r.w, r.y + r.h, 0.0f}, {r.x + r.w, r.y, 0.0f}};
        RSGL_pointF texPointsUP[] = {{((i32)ray.x) - ray.x, 0.0f}, {((i32)ray.x) - ray.x, 1.0f}, {(((i32)ray.x) - ray.x) + 0.1 , 1.0f}, {(((i32)ray.x) - ray.x) + 0.1, 0.0f}};
        RSGL_pointF texPointsSIDE[] = {{((i32)ray.y) - ray.y, 0.0f}, {((i32)ray.y) - ray.y, 1.0f}, {(((i32)ray.y) - ray.y) + 0.1 , 1.0f}, {(((i32)ray.y) - ray.y) + 0.1, 0.0f}};

        RSGL_pointF* texPoints = texPointsUP;
        if (RSGL_between(rayAngle, 204, 270) || RSGL_between(rayAngle, 0, 116))
            texPoints = texPointsSIDE;

        RSGL_setTexture(MAP_CORDV(ray));  
        RSGL_basicDraw(RGL_QUADS_2D, (RSGL_point3DF*)points, (RSGL_pointF*)texPoints, r, RSGL_RGB(255, 255, 255), 4);
    }

    RSGL_setTexture(1);
    RSGL_drawLineF(RSGL_POINTF(x, z + (defaultHeight - wallHeight) + defaultHeight + wallHeight), RSGL_POINTF(x, win->r.h * 4), 1, RSGL_RGB(0, 255, 0));
}


int main() {
    win = RSGL_createWindow("name", RSGL_RECT(0, 0, 640, 400), RGFW_CENTER | RSGL_HIDE_MOUSE);

    player = RSGL_POINTF(2, 2); 
    z = 0;
    float jumpZ = 0;
    playerAngle = 90;

    u8 cursor = 0;

    float playerVelocity = 0.25;

    RSGL_loadImage("wall.png"); /* 2 */
    RSGL_loadImage("wall.jpg"); /* 3 */
  
    RSGL_setFont(RSGL_loadFont("SansPosterBold.ttf"));

    u8 running = true; /* 1 - running, 2 - paused*/
  
    RGFW_window_moveMouse(win, win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2));
    
    while (running) {
        while (RSGL_window_checkEvent(win)) {
            if (win->event.type == RSGL_keyPressed && win->event.keyCode == RGFW_Escape) {
                running = 1 + (running != 2);
                continue;
            }
            
            if (win->event.type == RSGL_quit) {
                running = 0;
                break;
            }

            if (running == 2) {
                if (RGFW_isPressedI(win, RGFW_Up))
                    cursor -= cursor ? 1 : -2;
                if (RGFW_isPressedI(win, RGFW_Down))
                    cursor += (cursor < 2) ? 1 : -2;
                if (RGFW_isPressedI(win, RGFW_Return) == false)
                    continue;
                
                switch (cursor) {
                    case 0:
                        running = 1;
                        break;
                    case 1:
                        break;
                    case 2:
                        running = 0;
                    default:
                        break;
                }       

                continue;
            }

            /* simular to rayComp but for player movement */
            vector2D playerComp = VECTOR2D(cos(DEG2RAD * playerAngle) * playerVelocity,  sin(DEG2RAD * playerAngle) * playerVelocity);                
            vector2D playerCompLR = VECTOR2D(cos(DEG2RAD * (playerAngle - 180)) * playerVelocity,  sin(DEG2RAD * (playerAngle - 180)) * playerVelocity);

            if (win->event.type == RSGL_mousePosChanged) {
                if (win->event.x > (win->r.w / 2))
                    playerAngle += 0.02 * win->event.fps;
                if (win->event.x < (win->r.w / 2))
                    playerAngle -= 0.02 * win->event.fps;
                
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
                    playerAngle -= 0.02 * win->event.fps;
                else if (RSGL_isPressedI(win, RGFW_Right))
                    playerAngle += 0.02 * win->event.fps;
                
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

        
        if (win->event.inFocus && running != 2 && RSGL_rectCollidePoint(win->r, RSGL_window_getGlobalMousePoint(win)) == false)
            RGFW_window_moveMouse(win, win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2));


        if (playerAngle >= 365) 
            playerAngle -= 360; 

        if (playerAngle < 0)
            playerAngle += 360;
            
        float rayAngle = playerAngle - ((float)fov / 2.0f);

        for(size_t i = 0; i < win->r.w; i++) {
            castRay(player, rayAngle, i);

            rayAngle += ((float)fov / win->r.w);

            if (RGFW_isPressedI(win, RGFW_Tab)) {
                for (int y = 0; y < MAP_HEIGHT; y++)
                    if (MAP_CORD(i, y))
                        RSGL_drawRect(RSGL_RECT(20 * i, 20 * y, 20, 20), RSGL_RGBA(255, 0, 0, 50));

                RSGL_drawRect(RSGL_RECT(20 * player.x, 20 * player.y, 2, 2), RSGL_RGBA(240, 220, 0, 50));
            }

            if (running != 2)
                continue;
            
            RSGL_drawRect(RSGL_RECT(i, 0, 1, win->r.h), RSGL_RGBA(255, 255, 0, 150));
            RSGL_drawText("Resume\nSettings\nExit", RSGL_CIRCLE(win->r.w / 4.0, win->r.h / 4.0, 40), RSGL_RGB(255, 0, 0));
            RSGL_drawRect(RSGL_RECT((win->r.w / 4.0) - 25, (win->r.h / 4.0) + (40 * cursor) + 20, 20, 10), RSGL_RGB(255, 255, 0));
        }
        
        RSGL_drawText(RSGL_strFmt("FPS : %i\nplayerAngle : %f", win->event.fps, playerAngle), RSGL_CIRCLE(win->r.w - 220, 20, 20), RSGL_RGB(255, 0, 0));

        RSGL_window_clear(win, RSGL_RGB(0, 0, 0));
    }

    RSGL_window_close(win);
}