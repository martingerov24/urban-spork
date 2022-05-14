#pragma once
#include <Utils.hpp>
struct Camera {
	const vec3 worldUp = { 0, 1, 0 };
	float aspect;
	vec3 origin;
	vec3 llc;
	vec3 left;
	vec3 up;

	void lookAt(float verticalFov, const vec3& lookFrom, const vec3& lookAt) {
		origin = lookFrom;
		const float theta = degToRad(verticalFov);
		float half_height = tan(theta / 2);
		const float half_width = aspect * half_height;

		const vec3 w = (origin - lookAt).normalized();
		const vec3 u = cross(worldUp, w).normalized();
		const vec3 v = cross(w, u);
		llc = origin - half_width * u - half_height * v - w;
		left = 2 * half_width * u;
		up = 2 * half_height * v;
	}

	Ray getRay(float u, float v) const {
		return Ray(origin, (llc + u * left + v * up - origin).normalized());
	}
};
