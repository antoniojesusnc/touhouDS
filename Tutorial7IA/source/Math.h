#ifndef __MATH_H__
#define __MATH_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes propietarios NDS
#include <nds.h>

// Defines
#define PI 3.14159265358979;
#define HALF_PI 1.57079632679;


class Vector2{
	public:
	
	s16 x;
	s16 y;
	
	Vector2(){
		x = 0;
		y = 0;
	}

	Vector2(s16 varX, s16 varY){
		x = varX;
		y = varY;
	}

	Vector2(const Vector2 &vector){
		x = vector.x;
		y = vector.y;
	}
	

	float Distance(Vector2 &destination){
		return 0;
	}
	
	~Vector2(void) {
		//delete &x;
		//delete &y;
	}

	// overloading asisingment operators for Vector2
	Vector2& operator =(const Vector2 &v2){
		x = v2.x;
		y = v2.y;
		return *this;
	} // operator = vector2

	Vector2& operator =(const s16 &number){
		x = number;
		y = number;
		return *this;
	} // operator = number

	// equality ooperators
	bool operator ==(const Vector2 &v){
		return (x == v.x) && (y == v.y);
	} // operator == vector2

	bool operator !=(const Vector2 &v){
		return !(*this == v);
	} // operator == vector2

	Vector2& operator+=(const Vector2 &v2){
		x += v2.x;
		y += v2.y;
		return *this;
	} // operator+= vector2

	Vector2& operator+=(const s16 &number){
		x += number;
		y += number;
		return *this;
	} // operator+= float

	Vector2& operator-=(const Vector2 &v2){
		x -= v2.x;
		y -= v2.y;
		return *this;
	} // operator-= vector2

	Vector2& operator-=(const s16 &number){
		x -= number;
		y -= number;
		return *this;
	} // operator-= float

	Vector2& operator*=(const s16 &number){
		x *= number;
		y *= number;
		return *this;
	} // operator*= float

	Vector2& operator/=(const s16 &number){
		x /= number;
		y /= number;
		return *this;
	} // operator*= float

	// vector2 to vector2 operators
	const Vector2 operator+(const Vector2 &v) const{
		Vector2 r(*this);
		return r += v;
	} // operator + float

	const Vector2 operator-(const Vector2 &v) const{
		Vector2 r(*this);
		return r -= v;
	} // operator - float

	// vector2 to float operators
	const Vector2 operator*(const s16 &number) const{
		Vector2 r(*this);
		return r *= number;
	} // operator + float

	const Vector2 operator/(const s16 &number) const{
		Vector2 r(*this);
		return r /= number;
	} // operator - float


	s16 getX(){return x;}
	s16 getY(){return y;}

	void setX(s16 xVar){x = xVar; }
	void setY(s16 yVar){y = yVar; }
	
	void setXY(s16 xVar, s16 yVar){setX(xVar);setY(yVar);}
	void setXY(const Vector2 &pos){setX(pos.x);setY(pos.y);}
};

class Rect{


	s16 x;
	s16 y;
	s16 width;
	s16 height;

	public:	

	Rect(){
		x = 0;
		y = 0;
		width = 0;
		height =0;
	}

	Rect(s16 rX, s16 rY, s16 rWidth, s16 rHeight){
		x = rX;
		y = rY;
		width = rWidth;
		height = rHeight;
	}

	Rect(const Rect &rect){
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
	}

	bool colisionWithPoint(s16 pointX, s16 pointY){
		return	x < pointX && pointX < x+width &&
				y < pointY && pointY < y+height;
	}

	bool collisionBetweenRect(Rect *rect){
		if(rect == NULL)
			return false;
		return collisionBetweenRect(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
	}

	bool collisionBetweenRect(s16 rX, s16 rY, s16 rWidth, s16 rHeight){
		return	x <= rX + rWidth	&&
				x + width >= rX		&&
				y <= rY + rHeight	&&
				y + height >= rY	;
	}

	s16 getX(){return x;}
	s16 getY(){return y;}
	s16 getWidth(){return width;}
	s16 getHeight(){return height;}

	void setX(s16 newX){x = newX;}
	void setY(s16 newY){y = newY;}
	void setWidth(s16 newWidth){width = newWidth;}
	void setHeight(s16 newHeight){height = newHeight;}
};


#endif
