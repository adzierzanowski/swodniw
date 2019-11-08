#include <stdio.h>
#include <windows.h>

LPSTR wndcls = "Klasa Okienka";
MSG wndmsg;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND btn, checkbox, textfield, listbox, combobox;

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
)
{
  WNDCLASSEX wc = {
    .cbSize = sizeof( WNDCLASSEX ),
    .style = 0,
    .lpfnWndProc = WndProc,
    .cbClsExtra = 0,
    .cbWndExtra = 0,
    .hInstance = hInstance,
    .hIcon = LoadIcon( NULL, IDI_APPLICATION ),
    .hCursor = LoadCursor( NULL, IDC_ARROW ),
    .hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 ),
    .lpszMenuName = NULL,
    .lpszClassName = wndcls,
    .hIconSm = LoadIcon( NULL, IDI_APPLICATION )
  };
 
  if (!RegisterClassEx(&wc))
  {
    MessageBox(
      NULL,
      "Failed to register window class",
      "Error",
      MB_ICONEXCLAMATION | MB_OK
    );
    return 1;
  }
   
  HWND hwnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    wndcls,
    "This is a window",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    640,
    480,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  btn = CreateWindowEx(
    0,
    "BUTTON",
    "This is a button",
    WS_CHILD | WS_VISIBLE,
    10, 10,
    200, 30,
    hwnd, NULL, hInstance, NULL
  );

  checkbox = CreateWindowEx(
    0,
    "BUTTON",
    "This is a checkbox",
    WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
    10, 50,
    200, 30,
    hwnd, NULL, hInstance, NULL
  );

  textfield = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    "EDIT",
    NULL,
    WS_CHILD | WS_VISIBLE | WS_BORDER,
    10, 90,
    200, 24,
    hwnd, NULL, hInstance, NULL
  );

  listbox = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    "LISTBOX",
    NULL,
    WS_CHILD | WS_VISIBLE | WS_BORDER,
    220, 10,
    200, 200,
    hwnd, NULL, hInstance, NULL
  );

  SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM) "A quick");
  SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM) "Brown fox");
  SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM) "Jumps over");
  SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM) "the lazy dog");

  combobox = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    "COMBOBOX",
    NULL,
    WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN,
    220, 210,
    200, 200,
    hwnd, NULL, hInstance, NULL
  );

  SendMessage(combobox, CB_ADDSTRING, 0, (LPARAM) "Hello");
  SendMessage(combobox, CB_ADDSTRING, 0, (LPARAM) "World");
   
  if (!hwnd)
  {
    MessageBox(
      NULL,
      "Failed to create window",
      "Error",
      MB_ICONEXCLAMATION
    );
    return 1;
  }
   
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);
   
  while(GetMessage(&wndmsg, NULL, 0, 0))
  {
    TranslateMessage(& wndmsg);
    DispatchMessage(& wndmsg);
  }

  return wndmsg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
      case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
       
      case WM_DESTROY:
        PostQuitMessage(0);
        break;

      case WM_COMMAND:
        if ((HWND) lParam == btn)
        {
          MessageBox(
            NULL,
            "A command\n",
            "",
            MB_ICONEXCLAMATION | MB_OK);
        }
        break;
       
      default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
   
  return 0;
}

