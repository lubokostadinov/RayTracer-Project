#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <thread>
#include <mutex>
#include "Camera.h"
#include "Shape.h"
#include "Vector3.h"
#include "Vector2.h"
//#include "Maths.h"
#include "Ray.h"
#define PI 3.1415926f


void rayTrace(sf::Image& image, Camera* camera, Shape* scene, int width, int height, Light light_source)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			Vector2 screenCoord((2.0f * x) / width - 1.0f,
				(-2.0f * y) / height + 1.0f);

			Ray ray = camera->makeRay(screenCoord);

			Intersection intersection(ray);
						
			if (scene->intersect(intersection))
			{				
				Ray shadow_ray = scene->makeRay(intersection, light_source);
				Intersection shadow(shadow_ray);
				if (scene->intersect(shadow))
				{
					intersection.color = sf::Color::Black;
				}
				else
				{
					scene->setColor(intersection, scene, shadow, light_source);	
				}	
				image.setPixel(x, y, intersection.color);
			}
			else
			{
				image.setPixel(x, y,sf::Color::Black);
			}
		}
	}
}

std::mutex mutex;

struct Job
{
	sf::Image& image;
	Camera* camera;
	Shape* scene;
	int width;
	int height;
	Light light_source;
	int x;
};

void Render(Job the_job)
{
	for (the_job.x; the_job.x < the_job.width; the_job.x += 4)
	{
		for (int y = 0; y < the_job.height; y++)
		{

			Vector2 screenCoord((2.0f * the_job.x) / the_job.width - 1.0f,
				(-2.0f * y) / the_job.height + 1.0f);

			Ray ray = the_job.camera->makeRay(screenCoord);

			Intersection intersection(ray);

			if (the_job.scene->intersect(intersection))
			{
				Ray shadow_ray = the_job.scene->makeRay(intersection, the_job.light_source);
				Intersection shadow(shadow_ray);
				if (the_job.scene->intersect(shadow))
				{
					intersection.color = sf::Color::Black;
				}
				else
				{
					mutex.lock();

					the_job.scene->setColor(intersection, the_job.scene, shadow, the_job.light_source);

					mutex.unlock();
				}

				the_job.image.setPixel(the_job.x, y, intersection.color);
			}
			else
			{
				the_job.image.setPixel(the_job.x, y, sf::Color::Black);
			}
		}
	}
}

int main(int argc, char* argv[])
{
    int width = 800;
    int height = 640;
    sf::Image image;
    image.create(width, height, sf::Color::Yellow);
	PerspectiveCamera camera(Point(-5.0f, 1.0f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), 25.0f * PI / 180.0f,
		(float)width / (float)height);

	ShapeSet scene;

	Plane floor(Point(0.0f, 0.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), 1);
	scene.addShape(&floor);
	Sphere sphere(Point(2.0f, 1.0f, -1.0f), 1.0f, sf::Color(255,0,0), 1);
	scene.addShape(&sphere);
	Sphere sphere1(Point(5.5f, 1.0f, 1.5f), 1.0f, sf::Color(0,0,255), 2);
	scene.addShape(&sphere1);

	Light light_source(Point(-6.0f,10.0f,5.0f));

	rayTrace(image, &camera, &scene, width, height, light_source);

	/*std::thread thread1 = std::thread(Render, Job{ image, &camera, &scene, width, height, light_source,0 });
	std::thread thread2 = std::thread(Render, Job{ image, &camera, &scene, width, height, light_source,1 });
	std::thread thread3 = std::thread(Render, Job{ image, &camera, &scene, width, height, light_source,2 });
	std::thread thread4 = std::thread(Render, Job{ image, &camera, &scene, width, height, light_source,3 });

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();*/


    if (!image.saveToFile("result.png"))
        return -1;

}