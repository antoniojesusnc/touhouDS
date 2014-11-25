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
	

	float Distance(Vector2 &destination){
		return 0;
	}
	
	~Vector2(void) {
	
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

	// overloading arithmethic operators for Vector2
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
};



#endif
