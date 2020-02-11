#include <fstream>
#include "vec3.h"
#include "ray.h"

#define CHAP1 0
#define CHAP2 0
#define CHAP3 0
#define CHAP4 0
#define CHAP5 1

#if CHAP4 || CHAP5
bool hit_sphere(const Vec3 & center, float radius, const Ray & r) {
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction()); 
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
#if CHAP5 
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - sqrt(discriminant) )/ (2.0*a);
    }
# else
    return (discriminant > 0);
#endif
}
#endif

Vec3 color(const Ray & r) {
#if CHAP4
    if (hit_sphere(Vec3(0,0,-1), 0.5, r)) {
        return Vec3(1,0,0);
    }
#endif
    Vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

int main () {
    std::ofstream new_file("image.ppm");
    
    int nx = 200;
    int ny = 100;
    new_file << "P3\n" << nx << " " << ny << "\n255\n";
#if CHAP3 || CHAP4
    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0,0.0,0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);
#endif
    for(int j=ny-1; j>=0; j--) {
        for (int i=0; i<nx; i++) {
            
#if CHAP1 // Chapitre 1
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
#endif
#if CHAP2 // Capitre 2
            Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
#endif
#if CHAP3 || CHAP4// Chapitre 3
    float u = float(i) / float(nx);
    float v = float(j) / float(ny);
    Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
    Vec3 col = color(r);
#endif
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
            new_file << ir <<" "<< ig <<" "<< ib << "\n";
        }
    }

    return 0;
}