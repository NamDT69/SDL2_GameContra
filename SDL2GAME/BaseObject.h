#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Commonfunc.h"

class BaseObject{
protected:
	SDL_Texture* p_object_;// bien lua hinh anh tung pixel 
	SDL_Rect rect_; // bien lua kich thuoc hinh anh
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y){ 
		rect_.x = x; 
		rect_.y = y;}
	SDL_Rect GetRect() const {return rect_;}// lay kich thuoc hinh anh
	SDL_Texture* GetObject() const {return p_object_;}

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
};

#endif