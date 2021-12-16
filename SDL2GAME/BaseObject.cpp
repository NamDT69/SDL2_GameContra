
#include "BaseObject.h"

BaseObject::BaseObject(){
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.h = 0;
	rect_.w = 0;
}

BaseObject::~BaseObject(){
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen){
	Free();
	SDL_Texture* new_texture =  NULL;// bien ket qua, ket cau cua mot hinh 
	SDL_Surface * load_surface = IMG_Load(path.c_str());// thu hinh anh tung pixel 1 , lay hinh bang cpu
	if (load_surface != NULL){
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));// lam phan background trung mau
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);// gan hinh anh vao mot cai new ket qua hinh
		if (new_texture != NULL){
			rect_.w = load_surface->w;// lay kich thuoc hinh anh
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);// xoa di bien thu thap hinh anh
	}
	p_object_ = new_texture;
	return p_object_ != NULL;
}

// sdl_renderer la cai nen cua doi tuong nao do
// base object day mot cai hinh co vi tri hinh anh tu p_object , rect len cai hinh nen des
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip){
	SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RenderCopy(des, p_object_, clip, &renderquad);
	// day toan bo thong so p_object len des vs kich thuoc vi tri o renderquad
	//SDL_RenderPresent(g_screen);
}

void BaseObject::Free(){
	if (p_object_ != NULL){
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;	
		rect_.w = 0;
		rect_.h = 0;

	}
}

