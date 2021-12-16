#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_


#include "Commonfunc.h"
#include "BaseObject.h"

#define THREAT_MAX_FALL_SPEED 10	
#define THREAT_GRAVITI_SPEED 0.8
#define THREAT_FRAME_NUM 8
class ThreatObject: public BaseObject{
public: 
	ThreatObject();
	~ThreatObject();

	void set_x_val(const float& xVal){
		x_val_ = xVal;
	}
	void set_y_val(const float & yVal){
		y_val_ = yVal;
	}
	void set_x_pos(const float& xPos){
		x_pos_ = xPos;
	}
	void set_y_pos(const float& yPos){
		y_pos_ = yPos;
	}



	float get_x_pos() const {
		return x_pos_;
	}
	float get_y_pos() const{	
		return y_pos_;
	}

	void SetMapXY(const int& xMap, const int& yMap){
		map_x_ = xMap;
		map_y_ = yMap;
	}

	void SetClip();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	
	int getWidthFrame(){
		return width_frame_;
	}
	int getHeghtFrame(){
		return height_frame_;
	}
	void DoThreat(Map& gmap);

	void CheckToMap(Map& gmap);



private:

	float x_val_;
	float y_val_;

	int map_x_;
	int map_y_;

	float x_pos_;
	float y_pos_;

	bool on_ground_;
	int comback_time_;
	int frame;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[THREAT_FRAME_NUM];	
};
#endif