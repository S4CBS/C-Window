#include <Windows.h>

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void CenterWindow(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    HICON hIcon = (HICON)LoadImage(NULL, L"default.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);

    if (!hIcon) {
        // Обработка ошибки загрузки иконки
        MessageBox(NULL, L"Failed to load icon", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, hIcon,
        L"MainWndClass", SoftwareMainProcedure);

    if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

    CreateWindow(L"MainWndClass", L"Window", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, NULL, NULL);

    // Получаем дескриптор окна
    HWND hWnd = FindWindow(L"MainWndClass", L"Window");
    if (hWnd == NULL) {
        return -1;
    }

    // Центрируем окно
    CenterWindow(hWnd);

    ShowWindow(hWnd, ncmdshow);
    UpdateWindow(hWnd);

    MSG SotfwareMainMessage = { 0 };
    while (GetMessage(&SotfwareMainMessage, NULL, NULL, NULL)) {
        TranslateMessage(&SotfwareMainMessage);
        DispatchMessage(&SotfwareMainMessage);
    }
    return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
    WNDCLASS NWC = { 0 };
    NWC.hCursor = Cursor;
    NWC.hIcon = Icon;
    NWC.hInstance = hInst;
    NWC.lpszClassName = Name;
    NWC.hbrBackground = BGColor;
    NWC.lpfnWndProc = Procedure;
    return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

void CenterWindow(HWND hWnd) {
    // Получаем размеры экрана
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Получаем размеры окна
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    // Вычисляем координаты центра экрана
    int centerX = (screenWidth - windowWidth) / 2;
    int centerY = (screenHeight - windowHeight) / 2;

    // Перемещаем окно в центр экрана
    SetWindowPos(hWnd, NULL, centerX, centerY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
