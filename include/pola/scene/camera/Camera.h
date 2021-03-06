/*
 * Camera.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_CAMERA_H_
#define POLA_CAMERA_H_

#include "pola/input/KeyEvent.h"
#include "pola/input/MouseEvent.h"
#include "pola/graphic/math/Math.h"
#include "pola/scene/node/SceneNode.h"
#include "pola/scene/camera/CameraController.h"

namespace pola {
namespace scene {

class Camera : public SceneNode {
public:
	Camera();
	virtual ~Camera();

	virtual void setSize(int32_t width, int32_t height);

	void setCameraController(CameraController* controller);

	virtual bool dispatchKeyEvent(input::KeyEvent& keyEvent);
	virtual bool dispatchMouseEvent(input::MouseEvent& mouseEvent);

	virtual bool update(graphic::GraphicContext* graphic, p_nsecs_t timeMs);

	const graphic::Frustum& frustum() const;

	virtual bool updateTransform();

	virtual void lookAt(graphic::vec3 target);

	graphic::mat4 getProjection() const;
protected:

	virtual void onPropertyChange();
protected:
	int32_t mWidth;
	int32_t mHeight;
	graphic::vec3 mUp;

	bool mCameraDirty;

	graphic::mat4 mProjection;
	CameraController* mController;

	graphic::Frustum mFrustum;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_CAMERA_H_ */
