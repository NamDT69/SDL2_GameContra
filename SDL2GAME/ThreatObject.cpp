#include "ThreatObject.h"

ThreatObject::ThreatObject(){
	width_frame_ = 0;
	height_frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	on_ground_ = false;
	comback_time_ = 0;
	frame = 0;
}

ThreatObject::~ThreatObject(){

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen){
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true){
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;
}

void ThreatObject::SetClip(){
	if (width_frame_ > 0 && height_frame_ > 0){
		for (int i = 0; i < THREAT_FRAME_NUM; i++){
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	
	}

}

void ThreatObject::Show(SDL_Renderer* des){
	if (comback_time_ == 0){
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;	
		frame++;
		if (frame >= 8){
			frame = 0;
		}
		SDL_Rect* currentClip = &frame_clip_[frame];
		SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
		SDL_RenderCopy(des, p_object_,currentClip, &renderQuad);
	}

}

void ThreatObject::DoThreat(Map& gmap){
	if (comback_time_ == 0){
		x_val_ = 0;
		y_val_ += THREAT_GRAVITI_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED){
			y_val_ = THREAT_MAX_FALL_SPEED;
		}
		CheckToMap(gmap);
	}else if(comback_time_ >0){
		comback_time_ --;
		if (comback_time_ == 0){
			x_val_ = 0;
			y_val_ = 0;
			if (x_pos_ > 256){
				x_pos_ -= 256;
			}else{	
				x_pos_ = 0;
			}
			y_pos_ = 0;
			comback_time_ = 0;
		}

	}
}


void ThreatObject::CheckToMap(Map& map_data){
	int x1 = 0;
	int x2 = 0; // gia tri 4 goc cua mot frame nhan vat a den b
	
	int y1 = 0;
	int y2 = 0;

	int x_value_ = x_val_;
	int y_value_ = y_val_;

	// Check horizontal 
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 =	 (x_pos_ + x_value_) / TILE_SIZE;
	x2 = (x_pos_ + x_value_  + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_ ) / TILE_SIZE;
	y2 =	 (y_pos_ + height_min - 1) /TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
		if (x_value_ > 0) // main object moving to right
		{
			int val1 = map_data.title[y1][x2];
			int val2 = map_data.title[y2][x2];

			
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY)){
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_value_ = 0;
			}

			


			
		}else if (x_value_ < 0){
			int val1 = map_data.title[y1][x1];
			int val2 = map_data.title[y2][x1];
			
				if ((val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY)){
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_value_ = 0;
				}
			

		}
	}



	// check vertical // roi tu do
	int width_min = width_frame_ < TILE_SIZE? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_value_) / TILE_SIZE;
	y2 = (y_pos_ + y_value_ + height_frame_ - 1) / TILE_SIZE;

	if ( x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
		if (y_value_ > 0){
			int val1 = map_data.title[y2][x1];
			int val2 = map_data.title[y2][x2];
			
				if ((val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY)){
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= height_frame_ + 1;
					y_value_ = 0;
					on_ground_ = true;
					

				}
			

			

		}else if (y_value_ < 0) {

			int val1 = map_data.title[y1][x1];
			int val2 = map_data.title[y1][x2];
		
				if ((val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY)){
					y_pos_ = (y1 + 1) * TILE_SIZE ;
					y_value_ = 0;
				}
			
			
		}
	}

	x_pos_ += x_value_;
	y_pos_ += y_value_;

	if (x_pos_ < 0){
		x_pos_ = 0;
	}else if (x_pos_ + width_frame_ > map_data.max_x_){
		x_pos_ = map_data.max_x_ - width_frame_ -1;
	}

	//check vuc tham
	if (y_pos_ > map_data.max_y_){
		comback_time_ = 60;
		
	}

}

