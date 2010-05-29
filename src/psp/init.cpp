#ifdef PSP

#include <init.h>
#include <gfx/RenderSystem.h>

#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("Ofes_mod", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-2048);

namespace Ofes {

int pspExitCallback(int a1, int a2, void* a3) {
	sceKernelExitGame();
	return 0;
}

int pspExitCallbackThread(unsigned int a1, void* a2) {
	int cbid;
	cbid = sceKernelCreateCallback("ExitCallback", pspExitCallback, NULL);
	if (cbid >= 0) {
		sceKernelRegisterExitCallback(cbid);
	}
	sceKernelSleepThreadCB();
	return 0;
}

int pspSetupExitCallback() {
	int thid = 0;

	thid = sceKernelCreateThread("ExitCallbackThread", pspExitCallbackThread,
			0x11, 0xFA0, 0, 0);
	if (thid >= 0) {
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

int initDevice() {
	pspSetupExitCallback();
	Gfx::RenderSystem::getSingletonPtr()->initRenderSystem();
	pspDebugScreenInit();
	return 0;
}

int deinitDevice() {
	sceKernelDelayThread(100000);
	sceKernelExitGame();
	return 0;
}

}

#endif
