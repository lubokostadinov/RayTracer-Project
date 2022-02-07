#include "Shape.h"

Ray Shape::makeRay(Intersection& intersection, Light light_source)
{
	Vector direction = light_source.position - intersection.position();//?

	return Ray((intersection.position() ), direction.normalized());
}



//Shapeset
ShapeSet::ShapeSet()
{
	
}

ShapeSet::~ShapeSet()
{

}

void ShapeSet::addShape(Shape* shape)
{
	shapes.push_back(shape);
}

bool ShapeSet::intersect(Intersection& intersection)
{
	bool doesIntersect = false;

	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape* curShape = *iter;
		if (curShape->intersect(intersection))
			doesIntersect = true;
	}

	return doesIntersect;
}

bool ShapeSet::doesIntersect(const Ray& ray)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape* curShape = *iter;
		if (curShape->doesIntersect(ray))
			return true;
	}

	return false;
}

void ShapeSet::setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape* curShape = *iter;
	    curShape->setColor(intersection, scene, shadow, light_source);
	}
}

Ray ShapeSet::returnNormal(Intersection& intersection)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape* curShape = *iter;
		return curShape->returnNormal(intersection);
	}
}

Ray ShapeSet::makeReflectedRay(Intersection& intersection)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape* curShape = *iter;
		return curShape->makeReflectedRay(intersection);
	}
}

Ray ShapeSet::makeRefractionRay(Intersection& intersection)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape* curShape = *iter;
		return curShape->makeRefractionRay(intersection);
	}
}

sf::Color ShapeSet::Trace(Ray& ray, Shape* scene, Light light_source)
{
	Intersection intersection(ray);
	if (scene->intersect(intersection))
	{
		return intersection.pShape->Trace(ray, scene, light_source);
	}
	else return sf::Color::Black;
}




//Plane
Plane::Plane(const Point& position, const Vector& normal, int material)
	: position(position),
	normal(normal)
{	
	this->material = material;
}

Plane::~Plane()
{

}

bool Plane::intersect(Intersection& intersection)
{
	// First, check if we intersect
	float dDotN = dot(intersection.ray.direction, normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	float t = dot(position - intersection.ray.origin, normal)
		/ dDotN;

	if (t <= RAY_T_MIN || t >= intersection.t)
	{
		// Outside relevant range
		return false;
	}
	intersection.t = t;
	intersection.pShape = this;
	intersection.color = color;

	return true;
}

bool Plane::doesIntersect(const Ray& ray)
{
	// First, check if we intersect
	float dDotN = dot(ray.direction, normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	float t = dot(position - ray.origin, normal) / dDotN;

	if (t <= RAY_T_MIN || t >= ray.tMax)
	{
		// Outside relevant range
		return false;
	}

	return true;
}

Ray Plane::returnNormal(Intersection& intersection)
{
	Ray normal = Ray(intersection.position(), this->normal.normalized());
	return normal;
}

Ray Plane::makeReflectedRay(Intersection& intersection)
{
	Vector reflected = intersection.ray.direction.normalized() - (2 * (dot(intersection.ray.direction.normalized(), normal.normalized()) * normal.normalized()));
	return Ray(intersection.position(), reflected.normalized());
}

Ray Plane::makeRefractionRay(Intersection& intersection)
{
	float c1 = -dot(normal, intersection.ray.direction);
	float n1 = 1;
	float n2 = 1.3;
	float n = n1 / n2;
	float c2 = sqrt(1 - n * n * (1 - c1 * c1));
	Vector refracted = (n * intersection.ray.direction) + (n * c1 - c2) * normal;
	return Ray(intersection.position(), refracted.normalized());
}

void Plane::setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source)
{
		color = scene->Trace(intersection.ray, scene, light_source);

		Ray normal = this->returnNormal(intersection);
		float index = -dot(normal.direction, shadow.ray.direction);
		this->color.r = color.r * index;
		this->color.g = color.g * index;
		this->color.b = color.b * index;
	
}

sf::Color Plane::Trace(Ray& ray, Shape* scene, Light light_source)
{
	    Intersection intersection(ray);
		if (scene->intersect(intersection))
		{
			if (intersection.pShape->material == 1)
			{
				int X = round(intersection.position().x / 1.0f);
				int Z = round(intersection.position().z / 1.0f);

				if (X % 2 == 0)
				{
					if (Z % 2 == 0)
					{
						color = sf::Color(0, 200, 200);
					}
					else
					{
						color = sf::Color(200, 200, 200);
					}

				}
				else
				{

					if (Z % 2 == 0)
					{
						color = sf::Color(200, 200, 200);
					}
					else
					{
						color = sf::Color(0, 200, 200);
					}
				}
				return color;
			}
		}
		else return sf::Color::Green;
	
}




//Sphere
Sphere::Sphere(const Point& centre, float radius,sf::Color color, int material)
	: centre(centre),
	radius(radius)
{
	this->color = color;
	this->material = material;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Intersection& intersection)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = intersection.ray;
	localRay.origin -= centre;

	// Calculate quadratic coefficients
	float a = localRay.direction.length2();
	float b = 2 * dot(localRay.direction, localRay.origin);
	float c = localRay.origin.length2() - sqr(radius);

	// Check whether we intersect
	float discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	// First check if close intersection is valid
	if (t1 > RAY_T_MIN && t1 < intersection.t)
	{
		intersection.t = t1;
	}
	else if (t2 > RAY_T_MIN && t2 < intersection.t)
	{
		intersection.t = t2;
	}
	else
	{
		// Neither is valid
		return false;
	}

	// Finish populating intersection
	intersection.pShape = this;
	intersection.color = color;

	return true;
}

bool Sphere::doesIntersect(const Ray& ray)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = ray;
	localRay.origin -= centre;

	// Calculate quadratic coefficients
	float a = localRay.direction.length2();
	float b = 2 * dot(localRay.direction, localRay.origin);
	float c = localRay.origin.length2() - sqr(radius);

	// Check whether we intersect
	float discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	if (t1 > RAY_T_MIN && t1 < ray.tMax)
		return true;

	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	if (t2 > RAY_T_MIN && t2 < ray.tMax)
		return true;

	return false;
}

Ray Sphere::makeReflectedRay(Intersection& intersection)
{
	Ray normal = this->returnNormal(intersection);
	Vector reflected = intersection.ray.direction.normalized() - (2 * (dot(intersection.ray.direction.normalized(), normal.direction.normalized()) * normal.direction.normalized()));
	return Ray(intersection.position(), reflected.normalized());
}

Ray Sphere::makeRefractionRay(Intersection& intersection)
{
	Vector direction = this->centre - intersection.position();
	Ray normal = Ray(intersection.position(), direction.normalized());
	float c1 = -dot(normal.direction, intersection.ray.direction);
	float n1 = 1.0f;
	float n2 = 1.3f;
	float n = n1 / n2;
	float c2 = sqrt(1 - (n * n) * (1 - (c1 * c1)));
	Vector refracted = (n * intersection.ray.direction) + (n * c1 - c2) * this->returnNormal(intersection).direction;
	return Ray(intersection.position(), refracted.normalized());
}

Ray Sphere::returnNormal(Intersection& intersection)
{
	Vector direction = this->centre - intersection.position();
	Ray normal = Ray(intersection.position(), direction.normalized());
	return normal;
}

void Sphere::setColor(Intersection& intersection, Shape* scene, Intersection& shadow, Light light_source)
{
	if (this->material == 1)
	{
		color = scene->Trace(intersection.ray, scene, light_source);
		
		Ray normal = this->returnNormal(intersection);
		float index = -dot(normal.direction, shadow.ray.direction);
		this->color.r = color.r * index;
		this->color.g = color.g * index;
		this->color.b = color.b * index;
	}
	else if (this->material == 2)
	{
		Ray reflected_ray = this->makeReflectedRay(intersection);
		Intersection reflected(reflected_ray);
		if (scene->intersect(reflected))
		{
			color = scene->Trace(reflected_ray, scene, light_source);
		}
		else
		{
			color = sf::Color(20, 20, 20);
		}
		
		Ray normal = this->returnNormal(intersection);
		float index = -dot(normal.direction, shadow.ray.direction);
		this->color.r = color.r * index;
		this->color.g = color.g * index;
		this->color.b = color.b * index;
	}
	else if (this->material == 3)
	{
		Ray refraction_ray = this->makeRefractionRay(intersection);
		Intersection reflected(refraction_ray);
		if (scene->intersect(reflected))
		{
			color = scene->Trace(refraction_ray, scene, light_source);
		}
		else
		{
			color = sf::Color(20, 20, 20);
		}
	
		Ray normal = this->returnNormal(intersection);
		float index = -dot(normal.direction, shadow.ray.direction);
		this->color.r = color.r * index;
		this->color.g = color.g * index;
		this->color.b = color.b * index;
	}
	else
	{
		color = sf::Color::Green;
	}
	
}

sf::Color Sphere::Trace(Ray& ray, Shape* scene, Light light_source)
{
	Intersection intersection(ray);
	if (this->intersect(intersection))
	{
		//Ray shadow_ray = scene->makeRay(intersection, light_source);
		//Intersection shadow(shadow_ray);
		
			if (intersection.pShape->material == 1)
			{
				/*if (scene->intersect(shadow))
				{
					return sf::Color::Black;
				}
				else
				{
					Vector direction = this->centre - intersection.position();
					Ray normal = Ray(intersection.position(), direction.normalized());
					float index = -dot(normal.direction, shadow.ray.direction);
					this->color.r = sf::Color(255, 0, 0).r * index;
					this->color.g = sf::Color(255, 0, 0).g * index;
					this->color.b = sf::Color(255, 0, 0).b * index;
					return color;
				}*/
				return sf::Color::Red;
			}

			if (intersection.pShape->material == 2)
			{
				Ray reflected_ray = scene->makeReflectedRay(intersection);

				return scene->Trace(reflected_ray, scene, light_source);
			}

			if (intersection.pShape->material == 3)
			{
				Ray refracted_ray = scene->makeRefractionRay(intersection);
				return scene->Trace(refracted_ray, scene, light_source);
			}
			else return sf::Color::Green;
	}
		
	
	else return sf::Color::Green;
}



//Light
Light::Light(const Point& position) : position(position)
{

}

Light::~Light()
{

}
