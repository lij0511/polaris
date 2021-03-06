/*
 * CameraController.cpp
 *
 *  Created on: 2016年6月3日
 *      Author: lijing
 */

#include "pola/scene/camera/CameraController.h"
#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

CameraController::CameraController(Camera* camera) : mCamera(camera) {
}

CameraController::~CameraController() {
}

bool CameraController::animate(p_nsecs_t timeMs) {
	return false;
}

bool CameraController::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	return false;
}

bool CameraController::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	return false;
}

} /* namespace scene */
} /* namespace pola */
