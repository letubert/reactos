/*
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * PURPOSE:          Native DirectDraw stubs
 * FILE:             subsys/win32k/ntddraw/stubs.c
 * PROGRAMER:        Peter Bajusz (hyp-x@stormregion.com)
 * REVISION HISTORY:
 *       25-10-2003  PB  Created
 */

#include <w32k.h>

#define NDEBUG
#include <debug.h>

DWORD STDCALL NtGdiDdCreateSurfaceEx(
    HANDLE hDirectDraw,
    HANDLE hSurface,
    DWORD dwSurfaceHandle
)
{
	UNIMPLEMENTED

	return 0;
}

DWORD STDCALL NtGdiDdFlipToGDISurface(
    HANDLE hDirectDraw,
    PDD_FLIPTOGDISURFACEDATA puFlipToGDISurfaceData
)
{
	UNIMPLEMENTED

	return 0;
}

HDC STDCALL NtGdiDdGetDC(
    HANDLE hSurface,
    PALETTEENTRY *puColorTable
)
{
	UNIMPLEMENTED

	return 0;
}

HANDLE STDCALL NtGdiDdGetDxHandle(
    HANDLE hDirectDraw,
    HANDLE hSurface,
    BOOL bRelease
)
{
	UNIMPLEMENTED

	return 0;
}

DWORD STDCALL NtGdiDdLockD3D(
    HANDLE hSurface,
    PDD_LOCKDATA puLockData
)
{
	UNIMPLEMENTED

	return 0;
}

BOOL STDCALL NtGdiDdReleaseDC(
    HANDLE hSurface
)
{
	UNIMPLEMENTED

	return 0;
}

BOOL STDCALL NtGdiDdResetVisrgn(
    HANDLE hSurface,
    HWND hwnd
)
{

	return TRUE;
}

BOOL STDCALL NtGdiDdSetGammaRamp(
    HANDLE hDirectDraw,
    HDC hdc,
    LPVOID lpGammaRamp
)
{
	UNIMPLEMENTED

	return 0;
}

VOID STDCALL NtGdiDdUnattachSurface(
    HANDLE hSurface,
    HANDLE hSurfaceAttached
)
{
	UNIMPLEMENTED
}

DWORD STDCALL NtGdiDdUnlockD3D(
    HANDLE hSurface,
    PDD_UNLOCKDATA puUnlockData
)
{
	UNIMPLEMENTED

	return 0;
}


/* EOF */
