#ifndef GAME_MAP_Hv
#define GAME_MAP_Hv
#include "Commonfunc.h"
#include "BaseObject.h"

class TileMat : public BaseObject{
public:
	TileMat(){;};// ham load tat ca mot object lat gach
	~TileMat(){;};
};

class GameMap{
private:
	Map game_map_; // lua 
	TileMat tile_mat[MAX_TILE];// lua tat ca cac hinh anh lat gach cua map
public:
	GameMap(){;};
	~GameMap(){;};
	void LoadMap(char* name);// doc file text lua vi tri hinh anh
	void LoadTiles(SDL_Renderer* screen);// load toan bo hinh anh cho tilemat
	void DrawMap(SDL_Renderer* screen);// dien hinh anh vao cac vi tri
	Map getMap() const {
		return game_map_;
	}

	Map setMap(Map& map_data) {
		game_map_ = map_data;
		return game_map_;
	}


};
#endif