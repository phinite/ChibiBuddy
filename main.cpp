#include "render.h"
#include "bitmap.h"
#include "window.h"
#include <commctrl.h>


// TODO:
/*
Nest it in the taskbar
Have it create a child window to adjust settings
Search and load bitmaps from a directory 
*/


const wchar_t szWindowClass[] = L"ChibiBuddy";

int APIENTRY wWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPWSTR cmdLine, _In_ int cmdShow)
{

    int bitmapHeight = 64;
    int bitmapWidth = 64;

    // Adjust this so it's no longer a constant
    Window* window = new Window();
    if (!window->Init(hInst, L"Image.png", bitmapWidth, bitmapHeight))
    {
        delete window;
        return -1;
    }

    Render* render = new Render();
    if (!render->Init(window->windowHandle))
    {
        delete render;
        return -1;
    }

    ShowWindow(window->windowHandle, cmdShow);
    UpdateWindow(window->windowHandle);

    // Create the system tray icon
    NOTIFYICONDATA trayDat;


    trayDat.cbSize = sizeof(NOTIFYICONDATA);
    trayDat.hWnd = window->windowHandle;
    //trayDat.uID = NULL;
    //trayDat.uFlags = NIF_MESSAGE;
    //trayDat.uCallbackMessage = 
    trayDat.dwState = NIS_HIDDEN;

    LoadIconMetric(hInst, MAKEINTRESOURCE(IDI_APPLICATION), LIM_SMALL, &trayDat.hIcon);


    Shell_NotifyIconW(NIM_ADD, &trayDat);


    
    Bitmap* bitmap = new Bitmap(L"Image.png", render, bitmapWidth, bitmapHeight);

    // Modularize this
    MSG message;
    message.message = WM_NULL;

    int frame = 0;
    int frames_in_bitmap = 4;
    int frame_change = 10;

    while (message.message != WM_QUIT)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            DispatchMessage(&message);
        else {
            frame++;

            render->BeginDraw();

            render->ClearScreen((1/255.0f), 0.0f, 0.0f);
            bitmap->Draw((frame / frame_change) % frames_in_bitmap, 0, 0 );

            render->EndDraw();
        }
    }
    
    delete render;
    delete bitmap;
    return TRUE;
}