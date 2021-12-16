
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>// phong chu
#include <vector>

static SDL_Window* g_window = NULL;//xay dung form window cho game , gom size , position, boder , full screen , etc.../ sdl_window is a struct
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event ; // su kien chuot , hanh dong , ban phim

const int FRAME_PER_SECOND = 25;// so frame tren mot giay // hay fps hay 25 hinh tren giay

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT	= 640;
const int SCREEN_BPP = 32; // pixel

// mau background
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0XFF;

#define BLANK_TILE 0
#define TILE_SIZE 64 // chieu dai , chieu rong cua mot o ( pixel)

#define MAX_MAP_X 400   // chieu dai so o can find
#define MAX_MAP_Y 10	// chieu rong so o can find


#define STATE_MONEY 4
#define MAX_TILE 7			// so hinh map

struct InputAction{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

struct Map{

	int start_x_;	// vi tri dau tien cua map (picel);
	int start_y_;

	int max_x_;			// chieu dai toi da cua map (pixel)
	int max_y_;

	int title[10][400]; // lua cac so cua map minh truyen file text vao
	char* file_name_;
};


#endif