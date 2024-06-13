#include "Camera.h"

Camera::Camera(glm::vec3 start_position, glm::vec3 start_up, 
			   float start_yaw, float start_pitch, 
			   float start_move_speed, float start_turn_speed)
	: position(start_position), world_up(start_up),
	  yaw(start_yaw), pitch(start_pitch),
	  front(glm::vec3(0.0f, 0.0f, -1.0f)),
	  movement_speed(start_move_speed),
	  turn_speed(start_turn_speed)
{
	update();
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::key_control(bool* keys, float delta_time)
{
	float velocity = movement_speed * delta_time;
	if(keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouse_control(float x_change, float y_change)
{
	if (x_change > 100 || y_change > 100) {
		x_change = 0;
		y_change = 0;
	}

	x_change *= turn_speed;
	y_change *= turn_speed;

	yaw += x_change;
	pitch += y_change;
	
	if(pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if(pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculate_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}
