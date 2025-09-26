#pragma once

#include <cmath>
using namespace std;

class Vector3D
{
public:
	Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {};

	Vector3D normalize() {
		return Vector3D(1,1,1);
	}
	float magnitude() {
		return std::sqrt(x*x + y*y + z*z);
	}

	Vector3D& operator=(const Vector3D& otro) {
		if (this != &otro) {
			x = otro.x;
			y = otro.y;
			z = otro.z;
		}
		return *this;
	}
	Vector3D operator+(const Vector3D& otro) { // suma
		return Vector3D(this->x + otro.x, this->y + otro.y, this->z + otro.z);
	}
	Vector3D operator-(const Vector3D& otro) { // resta
		return Vector3D(this->x - otro.x, this->y - otro.y, this->z - otro.z);
	}
	Vector3D operator*(const float scalar) { // producto por escalar
		return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
	}
	float operator*(const Vector3D& otro) { // producto escalar de dos vectores
		return (this->x * otro.x) + (this->y * otro.y) + (this->z * otro.z);
	}

private:
	float x, y, z;
};

