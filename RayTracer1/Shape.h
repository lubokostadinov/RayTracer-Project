#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <cmath>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Vector3.h"
#include "Vector2.h"
//#include "Maths.h"
#include "ray.h"

class Light
{
public:
	Point position;
	Light(const Point& position);
	virtual ~Light();


};

class Shape
{
public:

	sf::Color color;

	int material;

	Ray makeRay(Intersection& intersection, Light light_source);

	virtual ~Shape() { }

	virtual bool intersect(Intersection& intersection) = 0;

	virtual bool doesIntersect(const Ray& ray) = 0;

	virtual void setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source) = 0;

	virtual Ray returnNormal(Intersection& intersection) = 0;

	virtual Ray makeReflectedRay(Intersection& intersection) = 0;

	virtual Ray makeRefractionRay(Intersection& intersection) = 0;

	virtual sf::Color Trace(Ray& ray, Shape* scene, Light light_source) = 0;

};

class ShapeSet : public Shape
{
protected:

	std::vector<Shape*> shapes;
	
public:

	ShapeSet();

	virtual ~ShapeSet();

	void addShape(Shape* shape);

	virtual bool intersect(Intersection& intersection);

	virtual bool doesIntersect(const Ray& ray);

	virtual void setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source);

	virtual Ray returnNormal(Intersection& intersection);

	virtual Ray makeReflectedRay(Intersection& intersection);

	virtual Ray makeRefractionRay(Intersection& intersection);

	virtual sf::Color Trace(Ray& ray, Shape* scene, Light light_source);
	
};

class Plane : public Shape
{
protected:

	Point position;

	Vector normal;
	
public:

	Plane(const Point& position, const Vector& normal, int material);

	virtual ~Plane();

	virtual bool intersect(Intersection& intersection);

	virtual bool doesIntersect(const Ray& ray);

	virtual void setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source);

	virtual Ray returnNormal(Intersection& intersection);

	virtual Ray makeReflectedRay(Intersection& intersection);

	virtual Ray makeRefractionRay(Intersection& intersection);

	virtual sf::Color Trace(Ray& ray, Shape* scene, Light light_source);
	
};

class Sphere : public Shape
{
protected:

	Point centre;

	float radius;

public:

	Sphere(const Point& centre, float radius, sf::Color color, int material);

	virtual ~Sphere();

	virtual bool intersect(Intersection& intersection);

	virtual bool doesIntersect(const Ray& ray);

	virtual Ray makeReflectedRay(Intersection& intersection);

	virtual void setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source);

	virtual Ray returnNormal(Intersection& intersection);

	virtual Ray makeRefractionRay(Intersection& intersection);

	virtual sf::Color Trace(Ray& ray, Shape* scene, Light light_source);

};



#endif // SHAPE_H
