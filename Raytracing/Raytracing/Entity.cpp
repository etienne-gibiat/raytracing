#include "Entity.hpp"

Entity::Entity() {
	this->trans = Matrix();
	this->transInv = this->trans.inverse();
}

Entity::Entity(Matrix trans) {
	this->trans = Matrix(trans);
	this->transInv = this->trans.inverse();
}

void Entity::translate(float x, float y, float z) {
	trans(0, 3) = trans(0, 3) + x;
	trans(1, 3) = trans(1, 3) + y;
	trans(2, 3) = trans(2, 3) + z;
	transInv = trans.inverse();

}

void Entity::scale(float f) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            trans(i, j) = trans(i, j) * f;
        }

    }
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

Point Entity::localToGlobal(Point p) {
	return transInv * p;					 	    	 	 		 
}

Vector Entity::localToGlobal( Vector v) {

	return transInv * v;						 	    	 	 		 
}

Ray Entity::localToGlobal( Ray r) {
	Point p = transInv * (r.origin);
	Vector v = transInv * (r.vector);
	Ray ray(p, v);
	return ray;				 	    	 	 		 

}

Point Entity::globalToLocal(Point p) {
	return trans * p;
}

Vector Entity::globalToLocal(Vector v) {
	return trans * v;
}

Ray Entity::globalToLocal(Ray r) {
	Point p = trans * (r.origin);
	Vector v = trans * (r.vector);
	Ray ray(p, v);
	return ray;
}