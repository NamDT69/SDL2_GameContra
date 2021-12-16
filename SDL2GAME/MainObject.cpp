#include "MainObject.h"



MainObject::MainObject(){
	x_value_ = 0;
	y_value_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	width_frame_ = 0;
	width_frame_ = 0;
	frame_ = 0;
	status_ = WARK_NONE;
	input_action_type_.left_ = 0;
	input_action_type_.right_ = 0;
	input_action_type_.jump_ = 0;
	input_action_type_.down_ = 0;
	input_action_type_.up_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time_ = 0;
	money_count_ = 0;

}

MainObject::~MainObject(){
	
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen){
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true){
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h ;
	}

	return ret;
}

void MainObject::set_clips(){
	if (width_frame_ > 0 && height_frame_ > 0){
		for (int i = 0; i < 8; i++){
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void MainObject::Show(SDL_Renderer* des){
	updateImgPlayer(des);

	if (input_action_type_.left_ == 1||input_action_type_.right_ == 1){
		frame_++;
	}else{
		frame_ = 0;
	}

	if (frame_ >= 8)
		frame_ = 0;

	if (come_back_time_ == 0){
		
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;

		SDL_Rect* current_clip = &frame_clip_[frame_];

		SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen){
	
	if (events.type == SDL_KEYDOWN){
		switch (events.key.keysym.sym){
			case SDLK_RIGHT:
				{
					status_ = WARK_RIGHT;
					
					input_action_type_.right_ = 1;
					input_action_type_.left_ = 0;
					input_action_type_.jump_ = 0;
					updateImgPlayer(screen);


				}
				break;
			case SDLK_LEFT:
				{
					status_ = WARK_LEFT;	
					
					input_action_type_.left_ = 1;
					input_action_type_.right_ = 0;
					input_action_type_.jump_ = 0;
					updateImgPlayer(screen);
				}
				break;
			case SDLK_UP :
				{
					status_ = WARK_JUMP;	
					if (on_ground_ == true)
					input_action_type_.jump_ = 1;
					//input_action_type_.left_ = 0;
					//input_action_type_.right_ = 0;
					updateImgPlayer(screen);
					
				//	input_action_type_.left_ = 0;
				//	input_action_type_.right_ = 0;
				}
				break;
			case SDLK_SPACE:
				{
					BulletObject* p_bullet = new BulletObject();
					//p_bullet->setBulletType(BulletObject::LAZE_BULLET);
					p_bullet->loadImgBullet(screen);

					if (status_ == WARK_LEFT){
						p_bullet->setBulletDir(BulletObject::DIR_LEFT);	
						p_bullet->SetRect(this->rect_.x , this->rect_.y + height_frame_ * 0.3);
					}else if (status_ == WARK_RIGHT){
						p_bullet->setBulletDir(BulletObject::DIR_RIGHT);
						p_bullet->SetRect(this->rect_.x + width_frame_ - 15, this->rect_.y + height_frame_ * 0.3);
					}else{
						p_bullet->setBulletDir(BulletObject::DIR_RIGHT);
						p_bullet->SetRect(this->rect_.x + width_frame_ - 15, this->rect_.y + height_frame_ * 0.3);
					}


					
					p_bullet->set_x_value(20);
					p_bullet->set_y_value(20);
					p_bullet->set_is_move(true);

					p_bullet_list.push_back(p_bullet);
				}
			break;

			default:
				break;

		}

	}else if(events.type == SDL_KEYUP){
		switch (events.key.keysym.sym){
			case SDLK_RIGHT:
				{
					
					input_action_type_.right_ = 0;
				}
				break;
			case SDLK_LEFT:
				{
					
					input_action_type_.left_ = 0;
				}
				break;
			case SDLK_UP:
				{
					input_action_type_.jump_ = 0;
				}
			


			default:
				break;

		}
	}
	
/*
	if (events.type == SDL_MOUSEBUTTONDOWN){
		if (events.button.button == SDL_BUTTON_RIGHT){
			input_action_type_.jump_ = 1;
		}

	}*/


}

void MainObject::HandeBullet(SDL_Renderer* des){
	for (int i = 0; i < p_bullet_list.size(); i++){

		BulletObject* p_bullet = p_bullet_list.at(i);

		if (p_bullet != NULL){

			if (p_bullet->get_is_move() == true){
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}else{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != NULL){
					delete p_bullet;
					p_bullet = NULL;
				}

				
			}

		}

	}

}


void MainObject::DoPlayer(Map& map_data){
	
	if (come_back_time_ == 0 ){
		
		x_value_ = 0;
		y_value_ += GRAVITY_SPEED;
		if (y_value_ >= MAX_FALL_SPEED){
			y_value_ = MAX_FALL_SPEED;
		}

		if (input_action_type_.left_ == 1){
			x_value_ -= PLAYER_SPEED;
			
		}else if( input_action_type_.right_ ==1){
			x_value_ += PLAYER_SPEED;
			
		}
		
		if (input_action_type_.jump_ == 1){
		
			if (on_ground_ == true)	{ // dang tren mat dat
				y_value_ = - PLAYER_JUMP_VALUE;
				on_ground_ = false;
			}

		//	input_action_type_.jump_ = 0;
		}

		CheckToMap(map_data);
		centerEntityOnMap(map_data);
	}

	if (come_back_time_ > 0){
		come_back_time_ --;
		if (come_back_time_ == 0){
			on_ground_ = false;
			y_pos_ = 0;
			x_value_ = 0;
			y_value_ = 0;
			if (x_pos_ > 256	){
				x_pos_ -= 256; // tru di  4 o tile map
				map_x_ -= 256;
			}else{
				x_pos_ = 0;
			}
		}

	}

}

void  MainObject::IncreateMoney(){
	money_count_ ++;
}

void MainObject::CheckToMap(Map& map_data){
	int x1 = 0;
	int x2 = 0; // gia tri 4 goc cua mot frame nhan vat a den b
	
	int y1 = 0;
	int y2 = 0;

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

			if (val1 == STATE_MONEY || val2 == STATE_MONEY){
				map_data.title[y1][x2] = 0;
				map_data.title[y2][x2] = 0;
				IncreateMoney();

			}else{	
			
				if (map_data.title[y1][x2] != BLANK_TILE || map_data.title[y2][x2] != BLANK_TILE){
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_value_ = 0;
				}

			}


			
		}else if (x_value_ < 0){
			int val1 = map_data.title[y1][x1];
			int val2 = map_data.title[y2][x1];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY){
				map_data.title[y1][x1] = 0;
				map_data.title[y2][x1] = 0;
				IncreateMoney();

			}else {
				if (map_data.title[y1][x1] != BLANK_TILE || map_data.title[y2][x1] != BLANK_TILE){
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_value_ = 0;
				}
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
			if (val1 == STATE_MONEY || val2 == STATE_MONEY){
				map_data.title[y2][x1] = 0;
				map_data.title[y2][x2] = 0;
				IncreateMoney();
			}else{
				if (map_data.title[y2][x1] != BLANK_TILE || map_data.title[y2][x2] != BLANK_TILE){
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= height_frame_ + 1;
					y_value_ = 0;
					on_ground_ = true;
					if (status_ == WARK_NONE){
						status_ = WARK_RIGHT;
					}

				}
			}

			

		}else if (y_value_ < 0) {

			int val1 = map_data.title[y1][x1];
			int val2 = map_data.title[y1][x2];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY){
				map_data.title[y1][x1] = 0;
				map_data.title[y1][x2] = 0;
				IncreateMoney();
			}else{
				if (map_data.title[y1][x1] != BLANK_TILE || map_data.title[y1][x2] != BLANK_TILE){
					y_pos_ = (y1 + 1) * TILE_SIZE ;
					y_value_ = 0;
				}
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
		come_back_time_ = 60;
		
	}

}

void MainObject::centerEntityOnMap(Map& map_data){
	map_data.start_x_ = x_pos_ - SCREEN_WIDTH / 2;
	if (map_data.start_x_ < 0){
		map_data.start_x_ = 0; // ko cho phep lui them nua
	}else if (map_data.start_x_  + SCREEN_WIDTH >= map_data.max_x_){
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - SCREEN_HEIGHT /2;
	if (map_data.start_y_ < 0) {
		map_data.start_y_ = 0;
	}else if( map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_){
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}

}


void MainObject::updateImgPlayer(SDL_Renderer* des){
	if (on_ground_ == true){
		
		if(status_ == WARK_JUMP){
			LoadImg("img//jum_right.png", des);
		}else if (status_ == WARK_LEFT){
			LoadImg("img//player_left.png", des);
		}else if(status_ == WARK_RIGHT){
			LoadImg("img//player_right.png", des);
		}
	}else{
		if (status_ == WARK_LEFT){
			LoadImg("img//jum_left.png", des);
		}else if (status_ == WARK_RIGHT){
			LoadImg("img//jum_right.png", des);
		}

	}

}



