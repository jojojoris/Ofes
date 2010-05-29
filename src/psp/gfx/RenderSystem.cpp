/*
 * RenderSystem.cpp
 *
 *  Created on: 26 mei 2010
 *      Author: Joris Vergeer
 */

#include <gfx/RenderSystem.h>

#ifdef PSP

#include <pspdisplay.h>
#include <pspgu.h>

using namespace Ofes;
using namespace Gfx;

static unsigned int __attribute__((aligned(16))) list[262144];

int RenderSystem::initRenderSystem() {
	sceGuInit();

	sceGuStart(GU_DIRECT, list);
	sceGuDrawBuffer(GU_PSM_8888, (void*)0, 512);
	sceGuDispBuffer(480, 272, (void*)0x88000, 512);
	sceGuDepthBuffer((void*)0x110000, 512);
	sceGuOffset(2048 - (480 / 2), 2048 - (272 / 2));
	sceGuViewport(2048, 2048, 480, 272);
	sceGuDepthRange(65535, 0);
	sceGuScissor(0, 0, 480, 272);
	sceGuEnable( GU_SCISSOR_TEST);
	sceGuDepthFunc( GU_GEQUAL);
	sceGuEnable( GU_DEPTH_TEST);
	sceGuFrontFace( GU_CW);
	sceGuShadeModel( GU_SMOOTH);
	sceGuEnable( GU_CULL_FACE);
	sceGuEnable( GU_TEXTURE_2D);
	sceGuEnable( GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0, 0);

	sceDisplayWaitVblankStart();
	sceGuDisplay( GU_TRUE);
	return 0;
}

#endif
