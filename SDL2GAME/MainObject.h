#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include "Commonfunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED  0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VALUE 25	

class MainObject: public BaseObject{
public:
	MainObject();
	~MainObject();
	
	enum WalkType{
		WARK_NONE = 0,
		WARK_LEFT = 1,
		WARK_RIGHT = 2,
		WARK_JUMP = 3,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen); // load hinh anh cua nhan vat vao screen
	void Show(SDL_Renderer* des); // show ra man hinh destop
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen); // ham xu ly hanh dong cua nhan vat ra scren
	void set_clips(); // xu ly hieu ung animation

	void DoPlayer(Map &data);
	void CheckToMap(Map& map_data);
	void SetMapModeXY(const int map_x, const int map_y){
		map_x_ = map_x;
		map_y_ = map_y;
	}

	void centerEntityOnMap(Map& map_data);
	void updateImgPlayer(SDL_Renderer* des);

	void	 setBulletList(std::vector<BulletObject*> bullet_list){
		p_bullet_list = bullet_list;
	}

	std::vector<BulletObject*> getBulletList() const{
		return p_bullet_list;
	}

	void HandeBullet(SDL_Renderer* des);

	void IncreateMoney();



protected:
	
	std::vector<BulletObject*> p_bullet_list;

	float x_value_; //	tawn len , giam xuong bao nhieu khi an sang trai , hay sang phai
	float y_value_;

	float x_pos_; // vi tri cua nhan vat
	float y_pos_;

	int width_frame_; // lua kich thuoc cua mot frame
	int height_frame_;// mot frame la mot hinh anh cua nhan vat khi chuyen dong
	
	SDL_Rect frame_clip_[8]; // lua cac frame, vowi kich thuoc
	InputAction input_action_type_; // cac hanh dong
	int frame_; // dang o frame nao
	int status_; // trang thai hanh dong

	bool on_ground_; // kiem tra cham dat chua // da tren mat dat chua

	int map_x_; // vi tri cua map ban do mowi
	int map_y_;

	int come_back_time_;
	int money_count_;
};

#endif