/*
 * MD2AnimatedMeshSceneNode.cpp
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#include "pola/scene/node/MD2MeshSceneNode.h"

namespace pola {
namespace scene {

MD2MeshSceneNode::MD2MeshSceneNode(MD2AnimatedMesh* mesh) : AnimatedMeshSceneNode(mesh), mMesh(mesh) {
	setFrameLoop(0, mMesh->getFrameCount());
	setFramesPerSecond(25);
	setAnimationType(MD2_AT_STAND);
}

MD2MeshSceneNode::~MD2MeshSceneNode() {
}

void MD2MeshSceneNode::setAnimationType(MD2_ANIMATION_TYPE type) {
	if (type < 0 || type >= MD2_AT_COUNT) {
		return;
	}
	int32_t begin, end, fps;
	mMesh->getFrameLoop(type, begin, end, fps);
	setFrameLoop(begin, end);
	setFramesPerSecond((float) fps);
}

IMesh* MD2MeshSceneNode::mesh() {
	return mMesh;
}

void MD2MeshSceneNode::update(p_nsecs_t timeMs) {
	AnimatedMeshSceneNode::update(timeMs);
	mMesh->updateMeshBuffer(getCurrentFrame(), getStartFrameLoop(), getEndFrameLoop());
}

} /* namespace scene */
} /* namespace pola */
