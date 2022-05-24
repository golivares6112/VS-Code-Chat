#ifndef UNICODE
#define UNICODE
#endif

#define CM_MENSAJE 100
#define CM_SALIR  101


#include <windows.h>

//prototipo menu
void InsertarMenu(HWND hWnd);

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
    wincl.hbrBackground = GetSysColorBrush(COLOR_GRAYTEXT);

    /* Registrar la clase de ventana, si falla, salir del programa */
    if(!RegisterClassEx(&wincl)) return 0;

    /* La clase está registrada, crear la ventana */
    hwnd = CreateWindowEx(
           0,                   /* Posibilidades de variación */
           L"WINDOWS_CLASS",     /* Nombre de la clase */
           L"Programa de Chat",  /* Texto del título */
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

    /* Insertar menu */
    InsertarMenu(hwnd);

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



/*  Esta función es invocada por la función DispatchMessage()  - funcion propietaria de cada ventana, dialogo, o que herede de ello*/
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
    switch (mensaje)                  /* manipulador de mensaje */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* Envía el mensaje WM_QUIT a la cola de mensajes */
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case CM_MENSAJE:
                    MessageBox(hwnd, L"Whatsapp konda from C++, your mami give you a computer for christmas?", L"Comando : Mensaje", MB_OKCANCEL);
                break;
            case CM_SALIR:
                    MessageBox(hwnd, L"Bye Bye Konda, be good Jhonny", L"Comando : Salir", MB_OKCANCEL);
                    PostQuitMessage(0);
                break;    
            default:
                break;
            }
        default:                      /* Mensajes que no queremos manejar */
            return DefWindowProc (hwnd, mensaje, wParam, lParam);
    }

    return 0;
}

void InsertarMenu(HWND hWnd)
{
   HMENU hMenu1, hMenu2;
   
   hMenu1 = CreateMenu();
   hMenu2 = CreateMenu();

   AppendMenu(hMenu2, MF_STRING, CM_MENSAJE, L"&Mensaje");
   AppendMenu(hMenu2, MF_SEPARATOR, 0, NULL);
   AppendMenu(hMenu2, MF_STRING, CM_SALIR, L"&Salir");
   AppendMenu(hMenu1, MF_STRING | MF_POPUP, (UINT_PTR)hMenu2, L"&Principal");
   //AppendMenu(hMenu1, MF_STRING, 200, L"&Secundario");
   SetMenu (hWnd, hMenu1);  
}


