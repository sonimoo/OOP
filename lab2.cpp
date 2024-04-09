#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141592653589793;

class Point {};

class Circle : public Point {
public:
    double radius;

    Circle(double radius) {
        this->radius = radius;
    }
};

class Sphere : public Circle {
public:
    Sphere(double radius) : Circle(radius) {}

    double calculateWeight(double density) {
        double volume = (4.0 / 3.0) * PI * pow(radius, 3);
        return volume * density;
    }


    void printInfo(double density) {
        cout << "Radius = " << radius
            << "\nWeight = " << calculateWeight(density) << endl;
    }
};

int main() {

    double radius1, radius2, density;
    cout << "Enter the radius for the first sphere: ";
    cin >> radius1;
    cout << "Enter the radius for the second sphere: ";
    cin >> radius2;
    cout << "Enter the density of the material: ";  // density = плотность
    cin >> density;

    Sphere sphere1(radius1), sphere2(radius2);

    cout << "\nSphere 1:" << endl;
    sphere1.printInfo(density);

    cout << "\nSphere 2:" << endl;
    sphere2.printInfo(density);



    cout << "\nComparison:" << endl;
    if (radius1 > radius2) {
        cout << "Sphere 1 is larger." << endl;
    }
    else if (radius1 < radius2) {
        cout << "Sphere 2 is larger." << endl;
    }
    else {
        cout << "Both spheres are of the same." << endl;
    }

    if (sphere1.calculateWeight(density) > sphere2.calculateWeight(density)) {
        cout << "Sphere 1 is heavier." << endl;
    }
    else if (sphere1.calculateWeight(density) < sphere2.calculateWeight(density)) {
        cout << "Sphere 2 is heavier." << endl;
    }
    else {
        cout << "Both spheres weigh the same." << endl;
    }

    return 0;
}