#include "Entity.hpp"


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