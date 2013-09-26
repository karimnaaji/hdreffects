#ifndef CAMERA_H
#define CAMERA_H

#include "graphics.h"
#include <iostream>

// inspired from http://tomdalling.com/blog/modern-opengl/04-cameras-vectors-and-input/

class Camera {
	public:
		Camera();
		~Camera();

		void SetAspectRatio(float ratio);
		void SetPosition(glm::vec3 position);

		glm::vec3 Forward() const;
		glm::vec3 Up() const;
		glm::vec3 Right() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetRotationMatrix() const;
		glm::vec3 GetPosition() const;

		void Translate(glm::vec3 vec);
		void Rotate(glm::vec2 rotation);

		void LookAt(glm::vec3 point);
		void NormalizeAngles();

	private:
		glm::vec3 position;
		glm::vec2 rotation;

        float aspectRatio;
        float fov;
        float near;
        float far;
};

#endif