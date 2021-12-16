#include "Commonfunc.h"
#include "impTimer.h"

ImpTimer::ImpTimer(){
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

ImpTimer::~ImpTimer(){}

void ImpTimer::start(){
	is_started_ = true;
	is_paused_ =false;
	start_tick_ = SDL_GetTicks(); // lien tuc lay thoi gian da troi qua
}

void ImpTimer::stop(){
	is_started_ = false;
	is_paused_ = false;

}

void ImpTimer::paused(){
	if (is_started_ == true && is_paused_ == false){
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
	}

}

void ImpTimer::unPaused(){
	if (is_paused_ == true){
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0; 
	}

}

int ImpTimer::getTicks(){ // tra ve thoi gian da troi qua
	if (is_started_ == true){
		if (is_paused_ == true){
			return paused_tick_; // tra ve thoi diem khi pause
		}else{
			return SDL_GetTicks()  - start_tick_; // thoi diem hien taij tru di thoi diem bat dau
		}

	}
	return 0;

}

bool ImpTimer::is_Started(){
	return is_started_;
}

bool ImpTimer::is_Paused(){
	return is_paused_;
}
