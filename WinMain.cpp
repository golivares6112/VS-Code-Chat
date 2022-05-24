#ifndef UNICODE
#define UNICODE
#endif

//DEFINICION DE UNICODE ARRIBA

#include <windows.h>

/*  Declaración del procedimiento de ventana  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    
    HWND hwnd;               /* Manipulador de ventana */
    MSG mensaje;             /* Mensajes recibidos por la aplicación */
    WNDCLASSEX wincl;        /* Estructura de datos para la clase de ventana */

    /* Estructura de la ventana */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = L"WINDOWS_CLASS";
    wincl.lpfnWndProc = WindowProcedure;      /* Esta función es invocada por Windows */
    wincl.style = CS_DBLCLKS;               /* Captura los doble-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Usar icono y puntero por defector */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* Sin menú */
    wincl.cbClsExtra = 0;                      /* Sin información adicional para la */
    wincl.cbWndExtra = 0;                      /* clase o la ventana */
    /* Usar el color de fondo por defecto para la ventana */
    wincl.hbrBackground = GetSysColorBrush(COLOR_DESKTOP);

    /* Registrar la clase de ventana, si falla, salir del programa */
    if(!RegisterClassEx(&wincl)) return 0;

    /* La clase está registrada, crear la ventana */
    hwnd = CreateWindowEx(
           0,                   /* Posibilidades de variación */
           L"WINDOWS_CLASS",     /* Nombre de la clase */
           L"Ejemplo 001",       /* Texto del título */
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

    /* Mostrar la ventana */
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    /* Bucle de mensajes, se ejecuta hasta que haya error o GetMessage devuelva FALSE */
    while(TRUE == GetMessage(&mensaje, NULL, 0, 0))
    {
        /* Traducir mensajes de teclas virtuales a mensajes de caracteres */
        TranslateMessage(&mensaje);
        /* Enviar mensaje al procedimiento de ventana */
        DispatchMessage(&mensaje);
    }



    /* Salir con valor de retorno */
    return mensaje.wParam;
}


/*  Esta función es invocada por la función DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
    switch (mensaje)                  /* manipulador de mensaje */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* Envía el mensaje WM_QUIT a la cola de mensajes */
            break;
        default:                      /* Mensajes que no queremos manejar */
            return DefWindowProc (hwnd, mensaje, wParam, lParam);
    }

    return 0;
}