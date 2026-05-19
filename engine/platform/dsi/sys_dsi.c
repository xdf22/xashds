#include "common.h"
#include "system.h"
#include "platform.h"
#include "client.h"
#include "keydefs.h"

#include <nds.h>

// just a stub for most functions, atleast for now

void Platform_Shutdown(void) {}
int Platform_JoyInit(int numjoy) { return 0; }
void Platform_SetMousePos(int x, int y) {}
void Platform_PreCreateMove(void) {}
void Platform_Vibrate(float life, char flags) {}
void Platform_SetClipboardText(const char *buffer, size_t size) {}
void Platform_Sleep(int msec) {}
void Platform_ShellExecute(const char *path, const char *parms) {}

void Platform_Init(void)
{
    keyboardDemoInit(); // initialize keyboard graphics
}

void Platform_RunEvents(void)
{
    scanKeys();
    static uint last_buttons;
    uint16_t buttons = keysHeld();

    // macro makes things shorter
    #define bind(dsbutton, key) \
        if ((last_buttons ^ buttons) & (dsbutton)) \
            Key_Event((key), (buttons & (dsbutton)) != 0)

    bind(KEY_B,     K_JOY1);
    bind(KEY_A,     K_JOY2);
    bind(KEY_Y,     K_JOY3);
    bind(KEY_X,     K_JOY4);
    bind(KEY_START, K_ESCAPE);
    bind(KEY_UP,    K_UPARROW);
    bind(KEY_DOWN,  K_DOWNARROW);
    bind(KEY_LEFT,  K_LEFTARROW);
    bind(KEY_RIGHT, K_RIGHTARROW);
    bind(KEY_L,     K_L1_BUTTON);
    bind(KEY_R,     K_R1_BUTTON);

    last_buttons = buttons;

    // OSK
    int16_t c = keyboardUpdate();
    if (c != -1)
    {
        if (c == '\b')
        {
            Key_Event(K_BACKSPACE, true);
            Key_Event(K_BACKSPACE, false);
        }
        else if (c >= 32)
        {
            Key_Event(c, true);
            Key_Event(c, false);
        }
    }
}

double Platform_DoubleTime(void)
{
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

void Platform_MessageBox(const char *title, const char *message, qboolean parentMainWindow)
{
    printf("%s: %s\n", title, message);
}

void Platform_GetMousePos(int *x, int *y)
{
    touchPosition touch;
    touchRead(&touch);

    if(x) *x = touch.px;
    if(y) *y = touch.py;
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

void Platform_EnableTextInput(qboolean enable)
{
    if (enable)
        keyboardShow();
    else
        keyboardHide();
}

void *Platform_GetNativeObject(const char *name)
{
    return NULL;
}
