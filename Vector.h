#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
private:
	double x;
	double y;
	double z;
	
public:
	Vector(double x, double y, double z);
	
	double getX() const;
	void setX(double x);
	
	double getY() const;
	void setY(double y);
	
	double getZ() const;
	void setZ(double z);
	
	double operator[](unsigned int idx) const;
};

#endif // _VECTOR_H
