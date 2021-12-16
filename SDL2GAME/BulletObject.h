#ifndef BULLET_OBJECT
#define BULLET_OBJECT

#include "BaseObject.h"
#include "Commonfunc.h"

class BulletObject :public BaseObject{
public:
	BulletObject();
	~BulletObject();


	enum BulletDir{
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP = 22,
		DIR_UP_LEFT = 23,
		DIR_UP_RIGHT = 24,
		DIR_DOWN = 25,
		DIR_DOWN_RIGHT = 26,
		DIR_DOWN_LEFT = 27,

	};

	enum BulletType{	
		SPHERE_BULLET = 50,
		LAZE_BULLET = 51,
	};
	void set_x_value(const int& xVal){
		x_bullet_val_ = xVal;
	}
	void set_y_value(const int& yVal){
		y_bullet_val_ = yVal;
	}
	
	int get_x_value() const {return x_bullet_val_;}
	int get_y_value() const {
		return y_bullet_val_;
	}

	void set_is_move(const bool& isMove){
		is_move_ = isMove;
	}
	bool get_is_move() const {
		return is_move_;
	}

	void HandleMove(const int& x_border, const int& y_border);

	void setBulletDir(const unsigned int& bulletDir){
		bullet_dir_ = bulletDir;
	}

	unsigned int getBulletDir() const{
		return bullet_dir_;
	}


	unsigned int getBulletType() const{
		return bullet_type_;
	}
	void setBulletType(const unsigned int& bullet_type) {
		bullet_type_ = bullet_type;
	}


	void loadImgBullet(SDL_Renderer* screen);


private:
	int x_bullet_val_;
	int y_bullet_val_;

	bool is_move_;

	unsigned int bullet_dir_;
	unsigned int bullet_type_;
};


#endif