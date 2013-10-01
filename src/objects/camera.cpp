#include "camera.h"

Camera::Camera() :
    position(0.0f, 0.0f, 5.0f),
    rotation(0.0f, 0.0f),
    aspectRatio(4/3),
    fov(50.0f),
    near(0.01f),
    far(100.0f)
{}

Camera::~Camera() {}

void Camera::SetAspectRatio(float ratio) {
	aspectRatio = ratio;
}

glm::mat4 Camera::GetRotationMatrix() const {
	glm::mat4 rotationMatrix;
    rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0, 1, 0));
    return rotationMatrix;
}

void Camera::Translate(glm::vec3 vec) {
	position += vec;
}

glm::vec3 Camera::Forward() const {
	glm::vec4 forward = glm::inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}

glm::vec3 Camera::Up() const {
	glm::vec4 up = glm::inverse(GetRotationMatrix()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
}

glm::vec3 Camera::Right() const {
	glm::vec4 right = glm::inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}

glm::vec3 Camera::GetPosition() const {
	return position;
}

void Camera::SetPosition(glm::vec3 position_) {
	position = position_;
}

void Camera::Rotate(glm::vec2 rotation_) {
    rotation += rotation_;
    NormalizeAngles();
}

glm::mat4 Camera::GetViewMatrix() const {
	glm::mat4 view = glm::perspective(fov, aspectRatio, near, far);
	view *= GetRotationMatrix();
	view = glm::translate(view, -position);
	return view;
}

void Camera::LookAt(glm::vec3 point) {
	glm::vec3 direction = glm::normalize(position - point);
	rotation.x = rad2deg(atan2f(direction.x, direction.z));
	rotation.y = rad2deg(acosf(direction.y));

	NormalizeAngles();
}

void Camera::NormalizeAngles() {
	rotation.y = fmodf(rotation.y, 360.0f);
	rotation.y = rotation.y < 0.0f ? rotation.y + 360.0f : rotation.y;
	rotation.x = clamp(rotation.x, -cam::maxRotationX, cam::maxRotationX);
}
