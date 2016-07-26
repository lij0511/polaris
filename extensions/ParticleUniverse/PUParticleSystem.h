/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef POLA_PUPARTICLESYSTEM_H_
#define POLA_PUPARTICLESYSTEM_H_

#include "pola/graphic/particle/Particle3DSystem.h"
#include <string>

namespace pola {
namespace graphic {

/*
 *
 */
class PUParticleSystem: public Particle3DSystem {
public:
	virtual ~PUParticleSystem();

	static PUParticleSystem* create();
	static PUParticleSystem* create(const std::string& file);
	static PUParticleSystem* create(const std::string& file, const std::string& material);

	bool initSystem(const std::string &filePath);
private:
	PUParticleSystem();

	bool initWithFilePath(const std::string &filePath);
	bool initWithFilePathAndMaterialPath (const std::string &filePath, const std::string &materialPath);
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_PUPARTICLESYSTEM_H_ */
