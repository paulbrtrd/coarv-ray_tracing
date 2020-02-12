#pragma once
#include "ray.h"
#include "hitable.h"
#include "camera.h"

Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

bool refract(const Vec3 & v, const Vec3 &n, float ni_over_nt, Vec3 &refracted)
{
    Vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else
        return false;
}

class Material
{
public:
    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vec3 &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vec3 &a) : albedo(a) {}
    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Vec3 albedo;
};

class Metal : public Material
{
public:
    Metal(const Vec3 &a, float f) : albedo(a)
    {
        if (f < 1)
            fuzz = f;
        else
            fuzz = 1;
    }
    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    Vec3 albedo;
    float fuzz;
};

class Dielectric : public Material {
        public:
            Dielectric(float ri) : ref_idx(ri) {}
            virtual bool scatter(const Ray & r_in, const hit_record& rec,
                Vec3 & attenuation, Ray & scattered) const
            {
                Vec3 outward_normal;
                Vec3 reflected = reflect(r_in.direction(), rec.normal);
                float ni_over_nt;
                attenuation = Vec3(1.0, 1.0, 1.0);
                Vec3 refracted;
                if (dot(r_in.direction(), rec.normal) > 0) {
                     outward_normal = -rec.normal;
                     ni_over_nt = ref_idx;
                }
                else {
                     outward_normal = rec.normal;
                     ni_over_nt = 1.0 / ref_idx;
                }
                if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
                   scattered = Ray(rec.p, refracted);
                else {
                   scattered = Ray(rec.p, reflected);
                   return false;
                }
                return true;
            }

            float ref_idx;
    };