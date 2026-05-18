#include "common.h"
#include "system.h"
#include "platform.h"

// just a stub for most functions, atleast for now

void Platform_Init(void) {}
void Platform_Shutdown(void) {}
int Platform_JoyInit(int numjoy) { return 0; }
void Platform_EnableTextInput(qboolean enable) {}
void Platform_RunEvents(void) {}
void Platform_GetMousePos(int *x, int *y) { if(x) *x = 0; if(y) *y = 0; }
void Platform_SetMousePos(int x, int y) {}
void Platform_PreCreateMove(void) {}
void Platform_Vibrate(float life, char flags) {}
void Platform_SetClipboardText(const char *buffer, size_t size) {}
void Platform_Sleep(int msec) {}
void Platform_ShellExecute(const char *path, const char *parms) {}

double Platform_DoubleTime(void)
{
    static double t = 0.0;
    t += 0.016;
    return t;
}

void Platform_MessageBox(const char *title, const char *message, qboolean parentMainWindow)
{
    printf("%s: %s\n", title, message);
}

void Platform_MouseMove(float *x, float *y)
{
    if(x) *x = 0;
    if(y) *y = 0;
}

void Platform_GetClipboardText(char *buffer, size_t size)
{
    if(buffer && size) buffer[0] = 0;
}

void *Platform_GetNativeObject(const char *name)
{
    return NULL;
}
