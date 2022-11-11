#include "Vector.h"

Vector::Vector(double x, double y, double z)
	: x(x), y(y), z(z) {}

double Vector::getX() const {
	return x;
}

void Vector::setX(double x) {
	this->x = x;
}

double Vector::getY() const {
	return y;
}

void Vector::setY(double y) {
	this->y = y;
}

double Vector::getZ() const {
	return z;
}

void Vector::setZ(double z) {
	this->z = z;
}

double Vector::operator[](unsigned int idx) const {
	switch (idx) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		return 0;
	}
}
