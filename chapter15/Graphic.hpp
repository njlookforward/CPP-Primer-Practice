#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

class Geometry {
public:
    virtual ~Geometry() = default;
    virtual double girth() const = 0;
    virtual double area() const = 0;
};

class Rectangle: public Geometry {
public:
    Rectangle(double l, double w): _length(l), _width(w) {}

    double girth() const override;
    double area() const override;

private:
    double _length = 0.0;
    double _width = 0.0;
};

class Circle: public Geometry {
public:
    Circle(double r): _radius(r) {}
    double girth() const override;
    double area() const override;

private:
    double _radius = 0.0;
};

class SolidFigure {
public:
    virtual ~SolidFigure() = default;
    virtual double surfaceArea() const = 0;
    virtual double volume() const = 0;
};

class Sphere: public SolidFigure {
public:
    Sphere(double r): _radius(r) {}
    double surfaceArea() const override;
    double volume() const override;

private:
    double _radius = 0.0;
};

class Cone: public SolidFigure {
public:
    Cone(double r, double h): _radius(r), _height(h) {}
    double surfaceArea() const override;
    double volume() const override;

private:
    double _radius = 0.0;
    double _height = 0.0;
};

#endif