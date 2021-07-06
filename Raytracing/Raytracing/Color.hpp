#pragma once

class Color
{
public:
	float* tabColor;
	Color();
	Color(int r, int g, int b);
	float operator[](int i);
	Color operator+(Color);
	void operator+=(Color);
	Color operator*(float);
	Color mul(Color c);

private:

};


