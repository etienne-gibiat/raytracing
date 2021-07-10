#include "Color.hpp"

Color::Color() {
	tabColor[0] = 0.;
	tabColor[1] = 0.;
	tabColor[2] = 0.;
}

Color::Color(float r, float g, float b) {

	if ( r > 1.)
		r = 1.;
	if ( r < 0.)
		r = 0.;
	if ( g > 1.)
		g = 1.;
	if ( g < 0.)
		g = 0.;
	if ( b > 1.)
		b = 1.;
	if ( b < 0.)
		b = 0.;

	tabColor[0] = r;
	tabColor[1] = g;
	tabColor[2] = b;
}

Color::Color(const Color& c) {
	tabColor[0] = c.tabColor[0];
	tabColor[1] = c.tabColor[1];
	tabColor[2] = c.tabColor[2];
}

float Color::operator[](int i) {
	return tabColor[i];
}

Color Color::mul(Color c) {
	float r = this->tabColor[0] * c[0];
	float g = this->tabColor[1] * c[1];
	float b = this->tabColor[2] * c[2];
	return Color(r, g, b);
}

void Color::swap(Color& col) {
	std::swap(tabColor, col.tabColor);
}

Color& Color::operator=(const Color& col)
{
	Color tmp = col;
	swap(tmp);
	return *this;
}

Color operator+(Color c, Color c2) {
	float r = c[0] + c2[0];
	float g = c[1] + c2[1];
	float b = c[2] + c2[2];
	return Color(r, g, b);
}

Color& Color::operator+=(Color c) {
	this->tabColor[0] += c[0];
	this->tabColor[1] += c[1];
	this->tabColor[2] += c[2];
	return *this;

}

Color& Color::operator*(float a) {
	this->tabColor[0] *= a;
	this->tabColor[1] *= a;
	this->tabColor[2] *= a;
	return *this;
}