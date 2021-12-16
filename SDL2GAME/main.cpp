#include "Commonfunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "impTimer.h"
#include "ThreatObject.h"

BaseObject g_background;

bool InitData(){
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");// set ti le va chat luong hinh anh

	g_window = SDL_CreateWindow("Game Cpp SDL CONTRA", // tao mot man hinh window
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		4);

	if (g_window == NULL){
		success = false;
	}else{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); // lay windown tra ra g_screen
		if (g_screen == NULL)
			success = false;
		else{
			SDL_SetRenderDrawColor(
				g_screen,
				RENDER_DRAW_COLOR,
				RENDER_DRAW_COLOR,
				RENDER_DRAW_COLOR,
				RENDER_DRAW_COLOR);// tra mau sac hinh anh reder ra man hinh 
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))// kiem tra xem cái hình PNG hay JPG đã được tải chưa 
				success = false;
		}
	}

	return success;
}

bool LoadBackground(){
	bool ret  = g_background.LoadImg(const_cast<char*>("img//background.png"), g_screen);
	if (ret == false)
		return false;

	return true;
}

void close(){
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatObject*> MakeThreatObject(){
	std::vector<ThreatObject*> list_threat;

	ThreatObject* threats_objs = new ThreatObject[20];

	for (int i = 0; i < 20; i++){
		ThreatObject* p_threat = (threats_objs + i);

		if (p_threat != NULL){
			p_threat->LoadImg("img//threat_level.png", g_screen);
			p_threat->SetClip();
			p_threat->set_x_pos(700 + i * 1200);
			p_threat->set_y_pos(0);
			
			list_threat.push_back(p_threat);
		}

	}
	return list_threat;

}


int main(int argc, char* argv[]){

	ImpTimer fps_timer;
	if (InitData() == false)
		return -1;

	if (LoadBackground() == false)
		return -1;

	GameMap game_map;
	game_map.LoadMap(const_cast<char*>("map/map01.txt"));
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.set_clips();

	std::vector<ThreatObject*> threat_list = MakeThreatObject();
	bool is_quit = false;
	while (!is_quit){
		fps_timer.start();

		while (SDL_PollEvent(&g_event) != 0){
			if (g_event.type == SDL_QUIT){
				is_quit = true;
			}

			p_player.HandelInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen,  RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		//game_map.DrawMap(g_screen);

		Map map_data = game_map.getMap();

		p_player.HandeBullet(g_screen);
		p_player.SetMapModeXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data); 
		p_player.Show(g_screen);

		game_map.setMap(map_data); // set lai vi tri moi cua map ban do
		game_map.DrawMap(g_screen);

		
			ThreatObject *p_threat = threat_list.at(0);
			
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->DoThreat(map_data);
				p_threat->Show(g_screen);
			

		


		SDL_RenderPresent(g_screen); // up load laij man hinh

		int real_imp_time = fps_timer.getTicks();
		int time_one_frame	= 1000 /  FRAME_PER_SECOND; // thoi gian cua mot frame chay mat bao nhieu lau
		
		if (real_imp_time < time_one_frame){
			int delay_time = -real_imp_time + time_one_frame;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}

	}
	close();
	return 0;
}
