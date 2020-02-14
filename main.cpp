#include <fstream>
#include "vec3.h"
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "material.h"

#include <float.h>
#define DEBUG 0

Hitable * random_scene()
{
    int n = 500;
    Hitable **list = new Hitable *[n + 1];
    list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -1; b < 11; b++)
        {
            float choose_mat = drand48();
            Vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - Vec3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8) // Diffuse
                {
                    list[i++] = new Sphere(center, 0.2, new Lambertian(Vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                }
                else if (choose_mat < 0.95) // Metal
                {
                    list[i++] = new Sphere(center, 0.2, new Metal(Vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
                }
                else
                {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

    return new Hitable_list(list, i);
}

Vec3 color(const Ray &r, Hitable *world, int depth)
{
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        Vec3 attenuation;
        Ray scattered;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return Vec3(0, 0, 0);
        }
    }
    else
    {
        Vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        Vec3 result = (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
        if (result.x() < 0 || result.y() < 0 || result.z() < 0)
        {
            std::cout << "Erreur: élément négatif, sans collision" << std::endl;
        }
        return result;
    }
}

int main()
{
    std::ofstream new_file("image.ppm");

    int nx = 1200;
    int ny = 800;
    int ns = 10;
    new_file << "P3\n"
             << nx << " " << ny << "\n255\n";

    Hitable *world = random_scene();

    Vec3 lookfrom(13,2,3);
    Vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    Camera cam(lookfrom, lookat, Vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray r = cam.get_ray(u, v);
                Vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = Vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            new_file << ir << " " << ig << " " << ib << "\n";
            if (DEBUG)
            {

                std::cout << ir << " " << ig << " " << ib << "\n";
            }
        }
    }

    return 0;
}