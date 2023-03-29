//Lecture 4 - Problem 1, 2, 3

#include<iostream>
#include<cmath>
using namespace std;

//Defining the class vector and all its data members and member functions 
class Vector
{
	friend ostream& operator<<(ostream& os, const Vector& aVector);

public:
	Vector(float x, float y, float z):
		x(x), y(y), z(z)
	{}

	float length() const;
	Vector crossProduct(const Vector RHS) const;
	float area(Vector RHS) const;

	Vector normalToTriangle(const Vector vecA, const Vector vecB, const Vector vecC) const;
	float areaTriangle(const Vector vecA, const Vector vecB, const Vector vecC) const;


	//operator overloading
	Vector operator+(const Vector& secVector) const;
	Vector operator-(const Vector& secVector) const;
	Vector operator*(const float scalar) const;

private:
	float x, y, z;
};


//Finding the length of a vector 
float Vector::length() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Finding the cross product between the instantiated vector and a second vector RHS (right hand side)
Vector Vector::crossProduct(const Vector RHS) const
{
	return Vector(
		y * RHS.z - z * RHS.y,
		z * RHS.x - x * RHS.z,
		x * RHS.y - y * RHS.x);
}

//Finding the area of the parallelogram locked between the two vectors 
float Vector::area(Vector RHS) const
{
	return crossProduct(RHS).length();
}

//Finding the normal vector to a triangle given the three vectors to the triangle vertices
Vector Vector::normalToTriangle(const Vector vecA, const Vector vecB, const Vector vecC) const
{
	return Vector(vecB.x - vecA.x, vecB.y - vecA.y, vecB.z - vecA.z).crossProduct
	(Vector(vecC.x - vecA.x, vecC.y - vecA.y, vecC.z - vecA.z));
}

//Finding the area of the triangle as the length of the cross product vector halved
float Vector::areaTriangle(const Vector vecA, const Vector vecB, const Vector vecC) const
{
	return (normalToTriangle(vecA, vecB, vecC).length()) * 0.5;
}

//Overloading the << operator to be able to print vectors 
ostream& operator<<(ostream& os, const Vector& aVector)
{
	os << "(" << aVector.x << " , " << aVector.y << " , " << aVector.z << ')';
	return os;
}

//Overloading the + operator to enable vector addition
Vector Vector::operator+(const Vector& secVector) const
{
	return Vector(
	x + secVector.x,
	y + secVector.y,
	z + secVector.z);
}

////Overloading the - operator to enable vector subtraction
Vector Vector::operator-(const Vector& secVector) const
{
	return Vector(
	x - secVector.x,
	y - secVector.y,
	z - secVector.z
	);
}

//Overloading the * operator to enable scalar multiplication with a vector
Vector Vector::operator*(const float scalar) const
{
	return Vector(x * scalar, y * scalar, z * scalar);
}


//Problem 1 - Defining a triangle 
class Triangle
{
public:
	Triangle(Vector A, Vector B, Vector C):
		A(A), B(B), C(C)
	{}
	Vector AB = B - A;
	Vector BC = C - B;
	Vector CA = A - C;


private:
	Vector A, B, C;
};


  
int main()
{
	//Problem 2

	Vector v1(3.5, 0, 0);
	Vector v2(1.75, 3.5, 0);
	cout << "Cross product between (3.5, 0, 0) and (1.75, 3.5, 0): " << v1.crossProduct(v2) << endl;


	Vector v3(3, -3, 1);
	Vector v4(4, 9, 3);
	cout << "Cross product between (3, -3, 1) and (4, 9, 3): " << v3.crossProduct(v4) << endl;
	cout << "Area of parallelogram between the vectors (3, -3, 1) and (4, 9, 3): " << v3.area(v4) << endl;

	Vector v5(-12, 12, -4);
	cout << "Area of parallelogram between the vectors (3, -3, 1) and (-12, 12, -4): " << v3.area(v5) << endl;  
	//they are just scalled => pointing in the same direction => cross product and area are equal to zero


	//Problem 3

	Vector vertex0(-1.75, -1.75, -3);
	Vector vertex1(1.75, -1.75, -3);
	Vector vertex2(0, 1.75, -3);
	cout << "Normal vector: " << vertex0.normalToTriangle(vertex0, vertex1, vertex2) << endl;;

	Vector vertex3(0,0,-1);
	Vector vertex4(1,0,1);
	Vector vertex5(-1,0,1);
	cout << "Normal vector: " << vertex3.normalToTriangle(vertex3, vertex4, vertex5) << endl;

	Vector vertex6(0.56, 1.11, 1.23);
	Vector vertex7(0.44, -2.368, -0.54);
	Vector vertex8(-1.56, 0.15, -1.92);
	cout << "Normal vector: " << vertex7.normalToTriangle(vertex6, vertex7, vertex8) << endl;

	cout << "Area of the triangle 1: " << vertex0.areaTriangle(vertex0, vertex1, vertex2) << endl;
	cout << "Area of the triangle 2: " << vertex3.areaTriangle(vertex3, vertex4, vertex5) << endl;
	cout << "Area of the triangle 3: " << vertex6.areaTriangle(vertex6, vertex7, vertex8) << endl;

	return 0;
}