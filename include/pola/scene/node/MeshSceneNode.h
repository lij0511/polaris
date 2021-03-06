/*
 * MeshSceneNode.h
 *
 *  Created on: 2016年8月24日
 *      Author: lijing
 */

#ifndef POLA_MESHSCENENODE_H_
#define POLA_MESHSCENENODE_H_

#include "pola/graphic/GraphicContext.h"
#include "pola/graphic/material/Material.h"
#include "pola/scene/node/IMeshSceneNode.h"
#include "pola/scene/mesh/Mesh.h"
#include "pola/scene/Animatable.h"

#include <vector>

namespace pola {
namespace scene {

/*
 *
 */
class MeshSceneNode: public IMeshSceneNode, public Animatable {
public:
	MeshSceneNode(Mesh* mesh);
	virtual ~MeshSceneNode();

	void setMaterial(uint16_t index, graphic::Material* material);

	virtual IMesh* mesh();
	virtual graphic::Material* material(uint16_t index) const;

	void setAnimation(unsigned index);
	void setAnimation(const std::string& name);

	virtual void update(p_nsecs_t timeMs);

	virtual void render(graphic::GraphicContext* graphic, p_nsecs_t timeMs);
	virtual void render(graphic::GraphicContext* graphic, graphic::Material* m, p_nsecs_t timeMs);

protected:
	std::vector<graphic::Material*> mMaterials;
	Mesh* mMesh;
	pola::utils::sp<Animation> mAnimation;
};

} /* namespace scene */
} /* namespace pola */

#endif /* MESHSCENENODE_H_ */
