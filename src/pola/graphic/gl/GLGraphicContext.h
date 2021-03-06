/*
 * GLGraphicContext.h
 *
 *  Created on: 2016年5月20日
 *      Author: lijing
 */

#ifndef POLA_GLGRAPHICCONTEXT_H_
#define POLA_GLGRAPHICCONTEXT_H_

#include "pola/graphic/gl/GL.h"
#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/Material.h"
#include "pola/graphic/math/Math.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/gl/GLCaches.h"
#include "pola/graphic/gl/GLRenderTarget.h"

namespace pola {
namespace graphic {

class GLGraphicContext: public GraphicContext {
public:
	GLGraphicContext();
	virtual ~GLGraphicContext();

	virtual void setViewport(int32_t width, int32_t height);

	virtual RenderTarget* createRenderTarget(uint32_t width, uint32_t height, PixelFormat format = PixelFormat::RGBA8888);

	virtual void setRenderTarget(RenderTarget* renderTarget);

	virtual void beginFrame(const FColor4& clearColor = {0.f, 0.f, 0.f, 0.f});
	virtual void endFrame();

	virtual void clear(const FColor4& clearColor = {0.f, 0.f, 0.f, 0.f}, bool depth = true);

	virtual void renderGeometry(Geometry* geometry, uint32_t start, uint32_t end, Material* material = nullptr);
	virtual void renderGeometry(Geometry* geometry, uint32_t start, uint32_t end, const GraphicParameter& parameter, Material* material = nullptr);

protected:
	void renderGeometry(Geometry2D* geometry, uint32_t start, uint32_t end, const GraphicParameter& parameter, Material* material = nullptr);
	void renderGeometry(Geometry3D* geometry, uint32_t start, uint32_t end, const GraphicParameter& parameter, Material* material = nullptr);

	virtual Texture* doLoadTexture(io::InputStream* is);

private:
	GLProgram* currentProgram(Material* material);

	GLCaches& mCaches;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GLGRAPHICCONTEXT_H_ */
