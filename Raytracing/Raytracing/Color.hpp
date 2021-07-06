#pragma once
#include <iostream>
class Color
{
public:
	float tabColor[3];
	Color();
	Color(int r, int g, int b);
	Color(const Color&);
	float operator[](int i);
	friend Color operator+(Color,Color);
	void operator+=(Color);
	Color operator*(float);
	Color mul(Color c);
	void swap(Color& col);
	Color& operator=(const Color& col);
private:

};


