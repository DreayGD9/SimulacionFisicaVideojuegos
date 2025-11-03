#pragma once

#include <cmath>
#include <ostream>
using namespace std;

class Vector3D
{
public:
	Vector3D(float x = 0, float y = 0, float z = 0) : xV(x), yV(y), zV(z) {};

	Vector3D normalize() {
		return Vector3D(xV/magnitude(), yV/magnitude(), zV/magnitude());
	}
	float magnitude() {
		return std::sqrt(xV*xV + yV*yV + zV*zV);
	}

	Vector3D& operator=(const Vector3D& otro) { // constructor por copia
		if (this != &otro) {
			xV = otro.xV;
			yV = otro.yV;
			zV = otro.zV;
		}
		return *this;
	}

	Vector3D operator+(const Vector3D& otro) { // suma
		return Vector3D(this->xV + otro.xV, this->yV + otro.yV, this->zV + otro.zV);
	}
	Vector3D operator+=(const Vector3D& otro) { // suma
		this->xV += otro.xV;
		this->yV += otro.yV;
		this->zV += otro.zV;
		return *this;
	}

	Vector3D operator-(const Vector3D& otro) { // resta
		return Vector3D(this->xV - otro.xV, this->yV - otro.yV, this->zV - otro.zV);
	}
	Vector3D operator-=(const Vector3D& otro) { // resta
		this->xV -= otro.xV;
		this->yV -= otro.yV;
		this->zV -= otro.zV;
		return *this;
	}

	Vector3D operator*(const float scalar) { // producto por escalar
		return Vector3D(this->xV * scalar, this->yV * scalar, this->zV * scalar);
	}
	Vector3D operator*=(const float scalar) { // producto por escalar
		this->xV *= scalar;
		this->yV *= scalar;
		this->zV *= scalar;
		return *this;
	}

	Vector3D operator/(const float scalar) { // división por escalar
		return Vector3D(this->xV / scalar, this->yV / scalar, this->zV / scalar);
	}

	float operator*(const Vector3D& otro) { // producto escalar de dos vectores
		return (this->xV * otro.xV) + (this->yV * otro.yV) + (this->zV * otro.zV);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
		os << "(" << v.xV << ", " << v.yV << ", " << v.zV << ")";
		return os;
	}

	float x() { return xV; };
	float y() { return yV; };
	float z() { return zV; };

	float xV, yV, zV;
};

