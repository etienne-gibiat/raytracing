#pragma once
#include <iostream>
class Color
{
public:
	float tabColor[3];
	Color();
	Color(float r, float g, float b);
	Color(const Color&);
	float operator[](int i);
	friend Color operator+(Color,Color);
	friend Color operator*(Color, Color);
	Color& operator+=(Color);
	Color& operator*(float);
	Color mul(Color c);
	void swap(Color& col);
	Color& operator=(const Color& col);
private:

};


