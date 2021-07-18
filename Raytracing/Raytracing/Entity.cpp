#include "Entity.hpp"

Entity::Entity() {
	this->trans = Matrix();
	this->transInv = this->trans.inverse();
}

Entity::Entity(Matrix trans) {
	this->trans = trans;
	this->transInv = this->trans.inverse();
}

void Entity::translate(float x, float y, float z) {
	Matrix m;
	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;
	trans = m * trans;
	transInv = trans.inverse();

}

void Entity::scale(float f) {
	Matrix m;
	m(0, 0) = f;
	m(1, 1) = f;
	m(2, 2) = f;
	trans = m * trans;
	transInv = trans.inverse();
}


void Entity::rotateX(float deg) {

	Matrix tmp;
	tmp(1, 1) = cos(deg);
	tmp(1, 2) = -sin(deg);
	tmp(2, 1) = sin(deg);
	tmp(2, 2) = cos(deg);
	trans = tmp * trans;
	transInv = trans.inverse();
}

void Entity::rotateY(float deg) {
	Matrix tmp;
	tmp(0, 0) = cos(deg);
	tmp(0, 2) = sin(deg);
	tmp(2, 0) = -sin(deg);
	tmp(2, 2) = cos(deg);
	trans = tmp * trans;
	transInv = trans.inverse();
}

void Entity::rotateZ(float deg) {
	Matrix tmp;
	tmp(0, 0) = cos(deg);
	tmp(0, 1) = -sin(deg);
	tmp(1, 0) = sin(deg);
	tmp(1, 1) = cos(deg);
	trans = tmp * trans;
	transInv = trans.inverse();
}

Point Entity::localToGlobal(const Point& p) const {
	return transInv * p;					 	    	 	 		 
}

Vector Entity::localToGlobal(const Vector& v) const {

	return transInv * v;						 	    	 	 		 
}

Ray Entity::localToGlobal(const Ray& r) const {
	Point p = transInv * (r.origin);
	Vector v = transInv * (r.vector);
	Ray ray(p, v);
	return ray;				 	    	 	 		 

}

Point Entity::globalToLocal(const Point& p) const {
	return trans * p;
}

Vector Entity::globalToLocal(const Vector& v) const {
	return trans * v;
}

Ray Entity::globalToLocal(const Ray& r) const {
	Point p = trans * (r.origin);
	Vector v = trans * (r.vector);
	Ray ray(p, v);
	return ray;
}