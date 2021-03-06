/*
 * AbsMeshSceneNode.h
 *
 *  Created on: 2016年5月23日
 *      Author: lijing
 */

#ifndef POLA_ABSMESHSCENENODE_H_
#define POLA_ABSMESHSCENENODE_H_

#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/Material.h"
#include "pola/scene/node/IMeshSceneNode.h"
#include "pola/scene/mesh/IMesh.h"

#include <vector>

namespace pola {
namespace scene {

class AbsMeshSceneNode: public IMeshSceneNode {
public:
	AbsMeshSceneNode(IMesh* mesh);
	virtual ~AbsMeshSceneNode();

	void setMaterial(uint16_t index, graphic::Material* material);

	virtual IMesh* mesh();
	virtual graphic::Material* material(uint16_t index) const;

	virtual void render(graphic::GraphicContext* graphic, p_nsecs_t timeMs);
	virtual void render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs);

protected:
	std::vector<graphic::Material*> mMaterials;

	IMesh* mMesh;

};

} /* namespace scene */
} /* namespace pola */

#endif /* POLA_ABSMESHSCENENODE_H_ */
