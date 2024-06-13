#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 start_position, glm::vec3 start_up, float start_yaw, float start_pitch, float start_move_speed, float start_turn_speed);
	Camera();
	~Camera();

	void key_control(bool* keys, float delta_time);
	void mouse_control(float x_change, float y_change);

	glm::mat4 calculate_view_matrix();

	glm::vec3 get_camera_position() { return position; }
	glm::vec3 get_camera_direction() { return glm::normalize(front); }
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;

	float yaw;
	float pitch;

	float movement_speed;
	float turn_speed;

	void update();
};

