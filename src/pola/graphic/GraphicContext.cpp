/*
 * GraphicContext.cpp
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/Material.h"
#include "pola/io/FileInputStream.h"

namespace pola {
namespace graphic {

GraphicContext::GraphicContext() : mWidth(0), mHeight(0) {
	mLights = nullptr;
	mDefaultMaterial = new Material;
	mRenderTarget = nullptr;
}

GraphicContext::~GraphicContext() {
	delete mDefaultMaterial;
}

void GraphicContext::setViewport(int32_t width, int32_t height) {
	mWidth = width;
	mHeight = height;
}

Texture* GraphicContext::loadTexture(const char* file) {
	io::FileInputStream is(file);
	return doLoadTexture(&is);
}

void GraphicContext::setRenderTarget(RenderTarget* renderTarget) {
	mRenderTarget = renderTarget;
}

void GraphicContext::beginFrame(const FColor4& clearColor) {
}

void GraphicContext::endFrame() {
}

void GraphicContext::setLights(Lights* lights) {
	mLights = lights;
}

Lights* GraphicContext::lights() const {
	return mLights;
}

void GraphicContext::setMatrix(MatrixType type, const mat4& matrix) {
	switch (type) {
		case VIEW:
			mViewMatrix = matrix;
			break;
		case MODEL:
			mModelMatrix = matrix;
			break;
		case PROJECTION:
			mProjectionMatrix = matrix;
			break;
		default:
			break;
	}
}

} /* namespace graphic */
} /* namespace pola */
