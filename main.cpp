#include <fstream>
#include "vec3.h"
#include "sphere.h"
#include "hitableList.h"
#include <float.h>
#define DEBUG 0

Vec3 color(const Ray & r, Hitable * world) {
    hit_record rec;
    if( world->hit(r, 0.0, MAXFLOAT, rec) ) {
        Vec3 N = rec.normal;
        return 0.5*Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    else {
        Vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        Vec3 result = (1.0 - t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
        return result;
    }
}

int main () {
    std::ofstream new_file("image.ppm");
    
    int nx = 200;
    int ny = 100;
    new_file << "P3\n" << nx << " " << ny << "\n255\n";

    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0,0.0,0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    Hitable * list[2];
    list[0] = new Sphere(Vec3(0,0,-1), 0.5);
    list[1] = new Sphere(Vec3(-0, -100.5, -1), 100);
    Hitable * world = new Hitable_list(list, 2);
    for(int j=ny-1; j>=0; j--) {
        for (int i=0; i<nx; i++) {
        
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            //Vec3 p = r.point_at_parameter(2.0);
            Vec3 col = color(r, world);

            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());
            new_file << ir <<" "<< ig <<" "<< ib << "\n";
            if(DEBUG) {
                if (ir <0 || ig < 0 || ib < 0)
                    std::cout << ir <<" "<< ig <<" "<< ib << "\n";
            }
        }
    }

    return 0;
}