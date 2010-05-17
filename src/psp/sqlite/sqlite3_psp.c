/*
 * sqlite3_psp.c
 *
 *  Created on: 13 mei 2010
 *      Author: joris
 */

#ifdef PSP

#include <pspkernel.h>
#include <psprtc.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3/sqlite3.h>

typedef struct pspFile pspFile;
struct pspFile {
	const sqlite3_io_methods *pMethod;
	SceUID uid;
	char* fullpath;
	char freepathmem;
	char deleteOnClose;
};

static int pspClose(sqlite3_file* file) {
	pspFile *handle = (pspFile*) file;
	int ret;
	if (handle->uid < 0) {
		return SQLITE_IOERR;
	} else {
		ret = sceIoClose(handle->uid);
		if (handle->deleteOnClose) {
			sceIoRemove(handle->fullpath);
		}

		if (handle->freepathmem) {
			free(handle->fullpath);
			handle->fullpath = 0;
		}
	}

	if (ret < 0) {
		return SQLITE_IOERR;
	}
	return SQLITE_OK;
}

int pspRead(sqlite3_file* file, void* pBuf, int iAmt, sqlite3_int64 iOfst) {
	pspFile *handle = (pspFile*) file;
	int got;

	if (handle->uid < 0) {
		return SQLITE_IOERR;
	} else {
		sceIoLseek(handle->uid, iOfst, SEEK_SET);
		got = sceIoRead(handle->uid, pBuf, iAmt);
	}

	if (got == iAmt) {
		return SQLITE_OK;
	} else {
		memset(&((char*) pBuf)[got], 0, iAmt - got);
		return SQLITE_IOERR_SHORT_READ;
	}
}

static int pspWrite(sqlite3_file* file, const void* pBuf, int iAmt,
		sqlite3_int64 iOfst) {
	pspFile *handle = (pspFile*) file;
	int got;

	if (handle->uid < 0) {
		return SQLITE_IOERR;
	} else {
		sceIoLseek(handle->uid, iOfst, PSP_SEEK_SET);
		got = sceIoWrite(handle->uid, pBuf, iAmt);
	}

	if (got == iAmt) {
		return SQLITE_OK;
	} else {
		return SQLITE_FULL;
	}

	return SQLITE_OK;
}

 int pspTruncate(sqlite3_file* file, sqlite3_int64 size) {
	pspFile *handle = (pspFile*) file;
	int ret;
	SceIoStat stat;

	if (handle->uid < 0) {
		return SQLITE_IOERR;
	} else {
		ret = sceIoGetstat(handle->fullpath, &stat);
		if (ret < 0) {
			return SQLITE_ERROR;
		}
		stat.st_size = size;

		ret = sceIoChstat(handle->fullpath, &stat, 0x0004);
		if (ret < 0) {
			return SQLITE_ERROR;
		}
	}
	return SQLITE_OK;
}

 int pspSync(sqlite3_file* file, int flags) {
	return SQLITE_OK;
}

 int pspFileSize(sqlite3_file* file, sqlite3_int64 *pSize) {
	pspFile *handle = (pspFile*) file;
	int ret;
	SceIoStat stat;
	if (handle->uid < 0) {
		return SQLITE_IOERR;
	} else {
		ret = sceIoGetstat(handle->fullpath, &stat);
		if (ret < 0) {
			return SQLITE_ERROR;
		}

		*pSize = stat.st_size;

	}
	return SQLITE_OK;
}

 int pspLock(sqlite3_file* file, int locktype) {
	return SQLITE_OK;
}

 int pspUnlock(sqlite3_file* file, int locktyte) {
	return SQLITE_OK;
}

 int pspCheckReservedLock(sqlite3_file* file, int *pResOut) {
	return SQLITE_OK;
}

 int pspFileControl(sqlite3_file* file, int op, void *pArg) {
	switch (op) {
	case SQLITE_FCNTL_LOCKSTATE:
		*(int*) pArg = SQLITE_LOCK_NONE;
		return SQLITE_OK;
		break;
	}
	return SQLITE_ERROR;
}

 int pspSectorSize(sqlite3_file* file) {
	return 0;
}

 int pspDeviceCharacteristics(sqlite3_file* file) {
	return SQLITE_OK;
}

 int pspOpen(sqlite3_vfs *vfs, const char *zName, sqlite3_file *file, int flags,
		int *pOutFlags) {

	sqlite3_io_methods pspMethods = { 1, pspClose, pspRead, pspWrite, pspTruncate,
			pspSync, pspFileSize, pspLock, pspUnlock, pspCheckReservedLock,
			pspFileControl, pspSectorSize, pspDeviceCharacteristics };

	pspFile *handle = (pspFile*) file;
	handle->pMethod = &pspMethods;

	if (!zName) {
		char tmpnam[64];
		pspTime mTime;
		sceRtcGetCurrentClock(&mTime, 0);
		sprintf(tmpnam, "tmp-%i%i%i%i%i%i%i.tmp", mTime.year, mTime.month,
				mTime.day, mTime.hour, mTime.minutes, mTime.seconds,
				mTime.microseconds);
		handle->uid = sceIoOpen(tmpnam, PSP_O_RDWR | PSP_O_CREAT, 0777);
		handle->deleteOnClose = 1;
		handle->fullpath = malloc(64);
		memcpy(handle->fullpath, tmpnam, 64);
		handle->freepathmem = 1;
	} else {
		handle->uid = sceIoOpen(zName, PSP_O_RDWR | PSP_O_CREAT, 0777);
		handle->fullpath = (char*)zName;
		handle->freepathmem = 0;
	}

	if (handle->uid < 0) {
		return SQLITE_IOERR;
	} else {
		return SQLITE_OK;
	}
}

 int pspDelete(sqlite3_vfs* vfs, const char *zName, int syncDir) {
	if (sceIoRemove(zName) < 0) {
		return SQLITE_IOERR;
	} else {
		return SQLITE_OK;
	}
}

 int pspAccess(sqlite3_vfs* vfs, const char *zName, int flags, int *pResOut) {
	(void) vfs;

	int rc = 0;

	SceIoStat stat;
	int res = sceIoGetstat(zName, &stat);
	char fileExist = res < 0 ? 0 : 1;

	if (flags == SQLITE_ACCESS_EXISTS) {
		if (fileExist) {
			rc = 1;
		}
	} else if (flags == SQLITE_ACCESS_READ) {
		if (fileExist) {
			if (stat.st_mode & FIO_S_IRUSR) {
				rc = 1;
			}
		}
	} else if (flags == SQLITE_ACCESS_READWRITE) {
		if (fileExist) {
			if ((stat.st_mode & FIO_S_IRUSR) & (stat.st_mode & FIO_S_IWUSR)) {
				rc = 1;
			}
		}
	}

	*pResOut = rc;

	return SQLITE_OK;
}

 int pspFullPathname(sqlite3_vfs* vfs, const char *zPath, int nOut, char *zOut) {
	zOut[nOut - 1] = '\0';
	if (zPath[0] == '/') {
		sqlite3_snprintf(nOut, zOut, "%s", zPath);
	} else {
		int nCwd;
		if (getcwd(zOut, nOut - 1) == 0) {
			return SQLITE_ERROR;
		}
		nCwd = (int) strlen(zOut);
		sqlite3_snprintf(nOut - nCwd, &zOut[nCwd], "/%s", zPath);
	}
	return SQLITE_OK;
}

 int pspRandomness(sqlite3_vfs* vfs, int nByte, char *zOut) {
	int i;
	for (i = nByte; i > 0; i--) {
		zOut[i - 1] = rand() % 255;
	}
	return SQLITE_OK;
}

 int pspSleep(sqlite3_vfs* vfs, int microseconds) {
	sceKernelDelayThread(microseconds);
	return SQLITE_OK;
}

 int pspCurrentTime(sqlite3_vfs* vfs, double *prNow) {
	pspTime mTime;
	sceRtcGetCurrentClock(&mTime, 0);

	double now = 0;
	now = mTime.day - 32076 + 1461 * (mTime.year + 4800 + (mTime.month - 14)
			/ 12) / 4 + 367 * (mTime.month - 2 - (mTime.month - 14) / 12 * 12)
			/ 12 - 3 * ((mTime.year + 4900 + (mTime.month - 14) / 12) / 100)
			/ 4;

	now += (mTime.hour + 12.0) / 24.0;
	now += mTime.minutes / 1440.0;
	now += mTime.seconds / 86400.0;

	*prNow = now;

	return SQLITE_OK;
}

 int pspGetLastError(sqlite3_vfs* vfs, int nBuf, char *zBuf) {
	return SQLITE_OK;
}

/*
 ** Initialize and deinitialize the operating system interface.
 */
SQLITE_API int sqlite3_os_init(void) {
	 sqlite3_vfs pspVfs = { 1, /* iVersion */
	sizeof(pspFile), /* szOsFile */
	FILENAME_MAX, /* mxPathname */
	0, /* pNext */
	"psp", /* zName */
	0, /* pAppData */
	pspOpen, /* xOpen */
	pspDelete, /* xDelete */
	pspAccess, /* xAccess */
	pspFullPathname, /* xFullPathname */
	0, /* xDlOpen */
	0, /* xDlError */
	0, /* xDlSym */
	0, /* xDlClose */
	pspRandomness, /* xRandomness */
	pspSleep, /* xSleep */
	pspCurrentTime, /* xCurrentTime */
	pspGetLastError /* xGetLastError */
	};

	sqlite3_vfs_register(&pspVfs, 1);
	return SQLITE_OK;
}
SQLITE_API int sqlite3_os_end(void) {
	return SQLITE_OK;
}
#endif
