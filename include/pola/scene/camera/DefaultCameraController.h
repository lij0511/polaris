/*
 * DefaultCameraController.h
 *
 *  Created on: 2016年6月24日
 *      Author: lijing
 */

#ifndef DEFAULTCAMERACONTROLLER_H_
#define DEFAULTCAMERACONTROLLER_H_

#include "pola/scene/camera/CameraController.h"
#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

/*
 *
 */
class DefaultCameraController: public CameraController {
public:
	DefaultCameraController(Camera* camera);
	virtual ~DefaultCameraController();

	virtual bool animate(p_nsecs_t timeMs);
	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

	virtual bool updateTransform();

private:
	float mMoveSpeed;
	float mRotateSpeed;

	int32_t mAnimatingFlag;
	p_nsecs_t mLastAnimatingTime;

	utils::sp<SceneNode> mPitch;
	utils::sp<SceneNode> mYaw;
};

} /* namespace scene */
} /* namespace pola */

#endif /* DEFAULTCAMERACONTROLLER_H_ */
