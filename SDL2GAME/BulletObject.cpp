#include "BulletObject.h"

BulletObject::BulletObject(){
	x_bullet_val_ = 0;
	y_bullet_val_ = 0;
	is_move_ = false;
	bullet_type_ = SPHERE_BULLET;	
}
BulletObject::~BulletObject(){

}

void BulletObject::HandleMove(const int& x_border, const int& y_border){

	if (bullet_dir_ == DIR_RIGHT){
		rect_.x  += x_bullet_val_;
	
		if (rect_.x > x_border){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_LEFT){

		rect_.x -= x_bullet_val_;
		if (rect_.x < 0){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_UP){
		rect_.y -= y_bullet_val_;
		if (rect_.y < 0){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_UP_LEFT){
		rect_.x -= x_bullet_val_;
		if (rect_.x < 0){
			is_move_ = false;
		}
		rect_.y -= y_bullet_val_;
		if (rect_.y < 0){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_UP_RIGHT){
		rect_.x += x_bullet_val_;
		if (rect_.x > x_border){
			is_move_ = false;
		}
		rect_.y -= y_bullet_val_;
		if (rect_.y < 0){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_DOWN){
		rect_.y += y_bullet_val_;
		if (rect_.y > y_border){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_DOWN_LEFT){
		rect_.x -= x_bullet_val_;
		if (rect_.x < 0){
			is_move_ = false;
		}
		rect_.y += y_bullet_val_;
		if (rect_.y > y_border){
			is_move_ = false;
		}
	}else if (bullet_dir_ == DIR_DOWN_RIGHT){
		rect_.x += x_bullet_val_;
		if (rect_.x > x_border){
			is_move_ = false;
		}
		rect_.y += y_bullet_val_;
		if (rect_.y > y_border){
			is_move_ = false;
		}
	}
}

void BulletObject::loadImgBullet(SDL_Renderer* screen){
	if (bullet_type_ == SPHERE_BULLET){
		LoadImg("img//dan.png",screen);
	}else if(bullet_type_ == LAZE_BULLET){	
		LoadImg("img//dan_laze.png",screen);
	}

}


