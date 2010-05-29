/*
 * RenderSystem.cpp
 *
 *  Created on: 26 mei 2010
 *      Author: Joris Vergeer
 */

#include <gfx/RenderSystem.h>

using namespace Ofes;
using namespace Gfx;

RenderSystem* RenderSystem::m_Singleton = 0;

RenderSystem RenderSystem::getSingleton(){
	if(m_Singleton == 0){
		m_Singleton = new RenderSystem();
	}
	return (*m_Singleton);
}

RenderSystem* RenderSystem::getSingletonPtr(){
	if(m_Singleton == 0){
		m_Singleton = new RenderSystem();
	}
	return (m_Singleton);
}

RenderSystem::RenderSystem(){

}

#ifdef GENERIC

int RenderSystem::initRenderSystem(){
	return 0;
}

#endif
