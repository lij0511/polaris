/*
 * AnimatedMeshSceneNode.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/utils/Math.h"
#include "pola/scene/node/AnimatedMeshSceneNode.h"

namespace pola {
namespace scene {

AnimatedMeshSceneNode::AnimatedMeshSceneNode(AnimatedMesh* mesh) : AbsMeshSceneNode(mesh),
	mStartFrameLoop(0), mEndFrameLoop(mesh->getFrameCount()), mFramesPerSecond(mesh->getFramesPerSecond()), mCurrentFrame(0), mLastTimeMs(0) {
}

AnimatedMeshSceneNode::~AnimatedMeshSceneNode() {
}

void AnimatedMeshSceneNode::setFrameLoop(int32_t startFrame, int32_t endFrame) {
	mStartFrameLoop = startFrame;
	mEndFrameLoop = endFrame;
	if (mFramesPerSecond < 0) {
		setCurrentFrame((float) mEndFrameLoop);
	} else {
		setCurrentFrame((float) mStartFrameLoop);
	}
}

float AnimatedMeshSceneNode::getCurrentFrame() const {
	return mCurrentFrame;
}

int32_t AnimatedMeshSceneNode::getStartFrameLoop() const {
	return mStartFrameLoop;
}

int32_t AnimatedMeshSceneNode::getEndFrameLoop() const {
	return mEndFrameLoop;
}

void AnimatedMeshSceneNode::setFramesPerSecond(float fps) {
	mFramesPerSecond = fps;
}

void AnimatedMeshSceneNode::setCurrentFrame(float frame) {
	mCurrentFrame = utils::fclamp<float>(frame, (float) mStartFrameLoop, (float) mEndFrameLoop);
}

void AnimatedMeshSceneNode::update(p_nsecs_t timeMs) {
	buildCurrentFrame(timeMs);
	((AnimatedMesh*) mMesh)->updateMeshBuffer(getCurrentFrame(), getStartFrameLoop(), getEndFrameLoop());
}

void AnimatedMeshSceneNode::buildCurrentFrame(p_nsecs_t timeMs) {
	if (mLastTimeMs == 0) {
		mLastTimeMs = timeMs;
	}

	p_nsecs_t interval = timeMs - mLastTimeMs;
	mLastTimeMs = timeMs;

	if (mStartFrameLoop == mEndFrameLoop) {
		mCurrentFrame = mStartFrameLoop;
	} else {
		// play animation looped
		mCurrentFrame += interval * mFramesPerSecond / 1000.f;

		// We have no interpolation between EndFrame and StartFrame,
		// the last frame must be identical to first one with our current solution.
		if (mFramesPerSecond > 0.f) //forwards...
		{
			if (mCurrentFrame > mEndFrameLoop)
				mCurrentFrame = mStartFrameLoop + fmod(mCurrentFrame - mStartFrameLoop, (float) (mEndFrameLoop - mStartFrameLoop));
		}
		else //backwards...
		{
			if (mCurrentFrame < mStartFrameLoop)
				mCurrentFrame = mEndFrameLoop - fmod(mEndFrameLoop - mCurrentFrame, (float) (mEndFrameLoop - mStartFrameLoop));
		}
	}
}

} /* namespace scene */
} /* namespace pola */
