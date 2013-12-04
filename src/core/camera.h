#ifndef CAMERA_H
#define CAMERA_H

#include "graphics.h"
#include <iostream>

namespace cam {
	const float maxRotationX = 89.0f;
}

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
		glm::mat4 GetProjectionMatrix() const;
		glm::vec3 GetPosition() const;

		void Translate(glm::vec3 vec);
		void Rotate(glm::vec2 rotation);
        void SetFov(float fov);

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
