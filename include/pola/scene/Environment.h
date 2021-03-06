/*
 * Environment.h
 *
 *  Created on: 2016年5月29日
 *      Author: lijing
 */

#ifndef POLA_ENVIRONMENT_H_
#define POLA_ENVIRONMENT_H_

#include "pola/graphic/light/Lights.h"

namespace pola {
namespace scene {

class Environment {
public:
	Environment();
	virtual ~Environment();

	void addLight(graphic::Light* light);
	void removeLight(graphic::Light* light);

	void setAmbientLight(const graphic::FColor3& color);
	graphic::FColor3 ambientLight() const;

	graphic::Lights* lights() const;

private:
	Environment& operator=(const Environment& other);
	Environment(const Environment& other);

private:
	graphic::Lights* mLights;
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ENVIRONMENT_H_ */
