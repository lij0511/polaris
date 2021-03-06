/*
 * Material.cpp
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#include <typeinfo>
#include "pola/graphic/material/Material.h"

#include "pola/utils/StringBuffer.h"

#ifdef OGL_RENDERER
#include "pola/graphic/gl/GLProgram.h"
#include "pola/graphic/gl/GLShaderLib.h"
#include "pola/graphic/gl/GLTexture.h"
#include "pola/graphic/gl/GLRenderTarget.h"
#include "pola/graphic/gl/GLCaches.h"
#endif

namespace pola {
namespace graphic {

Material::Material(const FColor4& color, Texture* textureMap)
	: mColor(color), mTextureMap(textureMap) {
	mBlendEnable = false;
	mBlendFunc = {FACTOR_ONE, FACTOR_ONE_MINUS_SRC_ALPHA};
}

Material::~Material() {
}

bool Material::hasTextureMap() const {
	return mTextureMap != nullptr;
}

bool Material::hasA8TextureMap() const {
	return hasTextureMap() && mTextureMap->format == PixelFormat::ALPHA8;
}

const utils::String Material::getVertexShader() {
	if (mVertexShader.isEmpty()) {
		mVertexShader = generateVertexShader();
	}
	return mVertexShader;
}

const utils::String Material::getFragmentShader() {
	if (mFragmentShader.isEmpty()) {
		mFragmentShader = generateFragmentShader();
	}
	return mFragmentShader;
}

void Material::bind(GraphicContext* graphic, Program* program) {
#ifdef OGL_RENDERER
	GLProgram* glProgram = (GLProgram*) program;

	GLUniform* uniform = glProgram->fetchUniform("u_color");
	if (uniform != nullptr && uniform->location >= 0) {
		glUniform4f(uniform->location, mColor.r * mColor.a, mColor.g * mColor.a, mColor.b * mColor.a, mColor.a);
	}
	if (hasTextureMap()) {
		GLTexture* glTexture = (GLTexture*) mTextureMap;
		GLCaches& cache = GLCaches::get();
		if (glTexture->generateTexture()) {
			cache.activeTexture(cache.activeTexture() + 1);
			cache.bindTexture(glTexture->id);
			uniform = glProgram->fetchUniform("u_textureMap");
			if (uniform != nullptr && uniform->location >= 0) {
				glUniform1i(uniform->location, cache.activeTexture());
			}
		}
	}
#endif
}

const char* Material::getMaterialType() const {
	if (isShaderMaterial()) {
		return nullptr;
	} else {
		return typeid(*this).name();
	}
}

const utils::String Material::generateVertexShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::VS_Para_TextureMap())
		.append("void main()"
			"{")
		.append(GLShaderLib::VS_TextureMap())
		.append(GLShaderLib::VS_MainPosition())
		.append("}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

const utils::String Material::generateFragmentShader() {
	utils::StringBuffer sb(256);
#ifdef OGL_RENDERER
	sb.append(GLShaderLib::FS_MainHeader())
		.append(GLShaderLib::FS_Para_TextureMap())
		.append("uniform vec4 u_color;"
			"void main()"
			"{")
		.append(GLShaderLib::FS_DiffuseColor())
		.append("  diffuseColor = u_color;")
		.append(GLShaderLib::FS_TextureMap())
		.append("  gl_FragColor = diffuseColor;"
			"}");
#endif
	utils::String s;
	sb.release(s);
	return s;
}

bool Material::isShaderMaterial() const {
	return false;
}

} /* namespace graphic */
} /* namespace pola */
