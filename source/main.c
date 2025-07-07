#include <ogc/video.h>
#include <ogc/system.h>
#include <ogc/console.h>
#include <wiiuse/wpad.h>
#include <stdio.h>

int main(int argc, char **argv) {
    // Initialize video
    VIDEO_Init();
    GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);
    void *xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight,
                 rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    // Initialize input
    WPAD_Init();

    // Print message
    printf("WIRC client stub loaded. Press HOME to exit.\n");

    // Wait for HOME button
    while (1) {
        WPAD_ScanPads();
        u32 buttons = WPAD_ButtonsDown(0);
        if (buttons & WPAD_BUTTON_HOME) break;
        VIDEO_WaitVSync();
    }

    return 0;
}
