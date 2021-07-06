#include "Color.hpp"

Color::Color() {
	tabColor = new float[3];
	tabColor[0] = 1.;
	tabColor[1] = 1.;
	tabColor[2] = 1.;
}

Color::Color(int r, int g, int b) {

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

	tabColor = new float[3];
	tabColor[0] = r;
	tabColor[1] = g;
	tabColor[2] = b;
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

Color Color::operator+(Color c) {
	float r = this->tabColor[0] + c[0];
	float g = this->tabColor[1] + c[1];
	float b = this->tabColor[2] + c[2];
	return Color(r, g, b);
}

void Color::operator+=(Color c) {
	this->tabColor[0] += c[0];
	this->tabColor[1] += c[1];
	this->tabColor[2] += c[2];

}

Color Color::operator*(float a) {
	float r = this->tabColor[0] * a;
	float g = this->tabColor[1] * a;
	float b = this->tabColor[2] * a;
	return Color(r, g, b);
}