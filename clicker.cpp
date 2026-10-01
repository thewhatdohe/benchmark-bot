#include <iostream> // standard io/stream
#include <windows.h> // windows standard library
#include <chrono> // time
#include <thread> // cpu stuff


void leftClick() {
    INPUT inputs[2] = {};

    // .type is the hardware you want to use, keyboard/mouse etc
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // mi/MouseInput, dwFlags/what to do or execute
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    // send the input to the OS
    SendInput(2, inputs, sizeof(INPUT));
}

int main() {
    // enable s and ms for chrono sleep for
    using namespace std::chrono_literals;
    // define before to access in other places
    int TpixelColor_R;
    int TpixelColor_G;
    int TpixelColor_B;
    int TcursorPos_x;
    int TcursorPos_y;
    COLORREF pixelColor;

    std::cout << "Move your mouse to the target and press Z...\n";

    // loop to gather information about the pixel the user wants to use
    while (true) {
        short key_state = GetAsyncKeyState(0x5a); // short is 16 bit signed (-128 / 128), GetAsyncKeyState checks if a current key is being held, 
                                                  // and returns a 16 bit integer depending on the result
                                                  // 0  0x0000  0000 0000 0000 0000 Key is not currently pressed and was not pressed since the last call
                                                  // 1  0x0001  0000 0000 0000 0001 Key is not currently pressed, but was pressed since the last call
                                                  // -32768 0x8000  1000 0000 0000 0000 Key is currently pressed and was not pressed since the last call
                                                  // -32767 0x8001  1000 0000 0000 0001 Key is currently pressed and was also pressed since the last call



        // this is only to gather data about the target pixel. not the mouse automation loop                            
        if (key_state < 0){
            POINT cursorPos;
            HDC hScreenDC = GetDC(NULL);
            if (hScreenDC != NULL && GetCursorPos(&cursorPos))
            {
                TcursorPos_x = cursorPos.x;
                TcursorPos_y = cursorPos.y;
                pixelColor = GetPixel(hScreenDC, cursorPos.x, cursorPos.y);
                std::cout << "DEBUG: " << pixelColor;
                // GetNValue() where N is R or G or B
                // T for TARGET
                TpixelColor_R = GetRValue(pixelColor);
                TpixelColor_G = GetGValue(pixelColor);
                TpixelColor_B = GetBValue(pixelColor);

                std::cout << cursorPos.x << "x" << "\n" << cursorPos.y << "y\n";
                std::cout << TpixelColor_R << "R\n";
                std::cout << TpixelColor_G << "G\n";
                std::cout << TpixelColor_B << "B\n";
                ReleaseDC(NULL, hScreenDC);
                break;
            }
        }
    }

    // remove do because completely unnecessary
    // main clicking loop
    while (true) {
        HDC hScreenDC = GetDC(NULL);
        if (hScreenDC != NULL) {
            pixelColor = GetPixel(hScreenDC, TcursorPos_x, TcursorPos_y);
            ReleaseDC(NULL, hScreenDC);
        }
        if (GetRValue(pixelColor) == TpixelColor_R && GetGValue(pixelColor) == TpixelColor_G && GetBValue(pixelColor) == TpixelColor_B) {
            leftClick();
            std::this_thread::sleep_for(3ms);
            leftClick();
        }
        std::this_thread::sleep_for(3ms);
    }
    return 0;
}