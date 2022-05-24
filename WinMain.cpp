#ifdef UNICODE
#define UNICODE
#endif

#include <windows.h>


LRESULT CALLBACK WindProcedure(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nFunsterStil)
{
    HWND win_manipulator;
    MSG messages;
    WNDCLASSEX wincl;

    //definition of the structure
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = L"WINDOW_CLASS"; //nombre de la clase de la ventana
    wincl.lpfnWndProc = WindProcedure; //funcion prototipo
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    //icon and pointer mouse definition
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    //backgroudn color
    wincl.hbrBackground = GetSysColorBrush(COLOR_GRAYTEXT);

    //structure register
    if(!RegisterClassEx(&wincl)) return 0;

    //it its the class register? then
    //create the window
    win_manipulator = CreateWindowEx
    (
            0,                   /* Posibilidades de variación */
            L"WINDOW_CLASS",     /* Nombre de la clase */
            L"Messenger",       /* Texto del título */
            WS_OVERLAPPEDWINDOW, /* Tipo por defecto */
            CW_USEDEFAULT,       /* Windows decide la posición */
            CW_USEDEFAULT,       /* donde se coloca la ventana */
            544,                 /* Ancho */
            375,                 /* Alto en pixels */
            HWND_DESKTOP,        /* La ventana es hija del escritorio */
            NULL,                /* Sin menú */
            hThisInstance,       /* Manipulador de instancia */
            NULL                 /* No hay datos de creación de ventana */
    );

    //ventan creada, se debe mostrar con una funcion
    ShowWindow(win_manipulator, SW_SHOWDEFAULT);

    /* Bucle de mensajes, se ejecuta hasta que haya error o GetMessage devuelva FALSE */
    while(TRUE == GetMessage(&messages, NULL, 0, 0))
    {
        /* Traducir mensajes de teclas virtuales a mensajes de caracteres */
        TranslateMessage(&messages);
        /* Enviar mensaje al procedimiento de ventana */
        DispatchMessage(&messages);
    }

    /* Salir con valor de retorno */
    return messages.wParam;

}