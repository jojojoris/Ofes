/*
 * RenderSystem.h
 *
 *  Created on: 26 mei 2010
 *      Author: Joris Vergeer
 */

#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_

namespace Ofes{
namespace Gfx{

class RenderSystem{
public:
	static RenderSystem getSingleton();
	static RenderSystem* getSingletonPtr();

	int initRenderSystem();
private:
	RenderSystem();
	static RenderSystem* m_Singleton;
};

}
}

#endif /* RENDERSYSTEM_H_ */
