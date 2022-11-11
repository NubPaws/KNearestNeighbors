#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
private:
	double x;
	double y;
	double z;
public:
	Vector(double x, double y, double z);
	~Vector();
	
	double getX() const;
	void setX(double x);
	
	double getY() const;
	void setY(double x);
	
	double getY() const;
	void setY(double x);
};

#endif // _VECTOR_H
