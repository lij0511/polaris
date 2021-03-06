/*
 * Camera.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "pola/scene/camera/Camera.h"

namespace pola {
namespace scene {

Camera::Camera() : SceneNode(), mWidth(1), mHeight(1), mUp({0, 1, 0}), mCameraDirty(true), mController(nullptr) {
}

Camera::~Camera() {
	if (mController != nullptr) {
		delete mController;
		mController = nullptr;
	}
}

void Camera::setSize(int32_t width, int32_t height) {
	if (width > 0 && height > 0) {
		mWidth = width;
		mHeight = height;
	}
}

void Camera::setCameraController(CameraController* controller) {
	if (mController == controller) {
		return;
	}
	if (mController != nullptr) {
		delete mController;
	}
	mController = controller;
}

bool Camera::update(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	bool animating = false;
	if (mController != nullptr) {
		animating = mController->animate(timeMs);
	}
	if (mCameraDirty || animating) {
		mMatrixDirty = true;
		mCameraDirty = false;
		graphic->setMatrix(graphic::GraphicContext::PROJECTION, mProjection);
		graphic::mat4 viewInverse;
		viewInverse.loadInverse(getWorldTransform());
//		viewInverse.load(view);
		graphic->setMatrix(graphic::GraphicContext::VIEW, viewInverse);
		mFrustum.setFromMatrix(mProjection * viewInverse);
		return true;
	}
	return false;
}

bool Camera::updateTransform() {
	if (mMatrixDirty) {
		graphic::mat4 m;
		graphic::quat4 quat;
		mRotation.getQuaternion(quat);
		m.compose(mPosition, quat, mScale);
		if (mController != nullptr) {
			mMatrix.loadMultiply(mController->getWorldTransform(), m);
		} else {
			mMatrix.load(m);
		}
		if (mParent != nullptr) {
			mWorldMatrix.loadMultiply(mParent->getWorldTransform(), mMatrix);
		} else {
			mWorldMatrix.load(mMatrix);
		}
		mMatrixDirty = false;
		return true;
	}
	return false;
}

void Camera::lookAt(graphic::vec3 target) {
	graphic::mat4 m;
	m.lookAt(mPosition, target, mUp);
	mRotation.setFromRotationMatrix(m);
	onPropertyChange();
}

const graphic::Frustum& Camera::frustum() const {
	return mFrustum;
}

graphic::mat4 Camera::getProjection() const {
	return mProjection;
}

void Camera::onPropertyChange() {
	SceneNode::onPropertyChange();
	mCameraDirty = true;
}

bool Camera::dispatchKeyEvent(input::KeyEvent& keyEvent) {
	if (mController != nullptr) {
		return mController->dispatchKeyEvent(keyEvent);
	}
	return false;
}

bool Camera::dispatchMouseEvent(input::MouseEvent& mouseEvent) {
	if (mController != nullptr) {
		return mController->dispatchMouseEvent(mouseEvent);
	}
	return false;
}

} /* namespace scene */
} /* namespace pola */
