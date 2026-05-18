#include "common.h"
#include "system.h"
#include "platform.h"

#include <nds.h>

// GL functions are stubbed because this is a software renderer (using a framebuffer)
// yes, i know the ds has a gl-ish library (gl2d), but im not too good at it right now

static u8 *videobuffer = NULL;
static u16 palette[256];

void GL_SwapBuffers(void) {}
void GL_UpdateSwapInterval(void) {}
int GL_SetAttribute(int attr, int val) { return 0; }
int GL_GetAttribute(int attr, int *val) { if(val) *val = 0; return 0; }

qboolean R_Init_Video(const int type)
{
    return true;
}

void R_Free_Video(void)
{
    if(videobuffer)
        free(videobuffer);
    videobuffer = NULL;
}

qboolean VID_SetMode(void)
{
    return true;
}

rserr_t R_ChangeDisplaySettings(int width, int height, qboolean fullscreen)
{
    return rserr_ok;
}

int R_MaxVideoModes(void)
{
    return 1;
}

struct vidmode_s *R_GetVideoMode(int num)
{
    return NULL;
}

void *GL_GetProcAddress(const char *name)
{
    return NULL;
}

void *SW_LockBuffer(void)
{
    return videobuffer;
}

void SW_UnlockBuffer(void)
{
    u16 *framebuffer = (u16*)VRAM_A;

    for(int i = 0; i < 256 * 192; i++)
        framebuffer[i] = palette[videobuffer[i]];

    swiWaitForVBlank();
}

qboolean SW_CreateBuffer(int width, int height, uint *stride, uint *bpp, uint *r, uint *g, uint *b)
{
    *stride = 256;
    *bpp = 1;

    *r = 31;
    *g = 63 << 5;
    *b = 31 << 11;

    videobuffer = (u8*)malloc(256 * 192);
    if (!videobuffer)
        return false;

    memset(videobuffer, 0, 256 * 192);

    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);

    return true;
}
