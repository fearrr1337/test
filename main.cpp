#include <iostream>
#include <cmath>
#include <vector>

struct Point3D {
	double x;
	double y;
	double z;

	Point3D(double px, double py, double pz) : x(px), y(py), z(pz) {}

	void print() {
		std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
	}
};

class Curve {
public:
	virtual ~Curve() = default;

	virtual Point3D getPoint(double t) = 0;

	virtual Point3D getDerivative(double t) = 0;
};

class Circle : public Curve {
private:
	double radius;
public:
	Circle(double r) : radius(r) {
		if (radius < 0) throw std::invalid_argument("Радиус не может быть отрицательным");
	}

	Point3D getPoint(double t) {
		double x = radius * std::cos(t);
		double y = radius * std::sin(t);
		double z = 0;

		return { x,y,z };
	}

	Point3D getDerivative(double t) {
		double x = -radius * std::sin(t);
		double y = radius * std::cos(t);
		double z = 0;

		return { x,y,z };
	}
};

class Elipse : public Curve {
private:
	double radiusX;
	double radiusY;
public:
	Elipse(double rx, double ry) : radiusX(rx), radiusY(ry) {
		if (radiusX < 0 || radiusY < 0) throw std::invalid_argument("Неверные радиусы (<0)");
	}

	Point3D getPoint(double t) {
		double x = radiusX * std::cos(t);
		double y = radiusY * std::sin(t);
		double z = 0;

		return { x,y,z };
	}

	Point3D getDerivative(double t) {
		double x = -radiusX * std::sin(t);
		double y = radiusY * std::cos(t);
		double z = 0;

		return { x,y,z };
	}
};


int main() {
	std::vector<Curve*> curves;

	curves.push_back(new Circle(5));
	curves.push_back(new Elipse(3, 2));

	double t = 3.14159265358979323846 / 4;

	for (const auto& curve : curves) {
		curve->getPoint(t).print();
		curve->getDerivative(t).print();
	}

	for (auto curve : curves) {
		delete curve;
	}

	return 0;
}