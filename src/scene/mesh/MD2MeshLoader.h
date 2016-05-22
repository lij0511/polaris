/*
 * MD2MeshLoader.h
 *
 *  Created on: 2016年5月21日
 *      Author: lijing
 */

#ifndef POLA_MD2MESHLOADER_H_
#define POLA_MD2MESHLOADER_H_

#include "scene/mesh/MeshLoader.h"

namespace pola {
namespace scene {

class MD2MeshLoader: public MeshLoader {
public:
	MD2MeshLoader();
	virtual ~MD2MeshLoader();

	virtual AnimationMesh* loadMesh(io::InputStream* is);
};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_MD2MESHLOADER_H_ */