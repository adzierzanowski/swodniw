#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BTN_ID 1
#define BTN2_ID 2
#define CHECKBOX_ID 3

LPSTR wndcls = "WindowClass";
MSG wndmsg;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND
  btn, btn2, checkbox, textfield, listbox, combobox,
  static_, static_icon;

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
)
{
  WNDCLASSEX wc = {
    .cbSize = sizeof( WNDCLASSEX ),
    .style = CS_DBLCLKS,
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
    hwnd, (HMENU) BTN_ID, hInstance, NULL
  );

  checkbox = CreateWindowEx(
    0,
    "BUTTON",
    "This is a checkbox",
    WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
    10, 50,
    200, 30,
    hwnd, (HMENU) CHECKBOX_ID, hInstance, NULL
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

  SetWindowText(textfield, "This is a text field");

  static_ = CreateWindowEx(
    0,
    "STATIC",
    NULL,
    WS_CHILD | WS_VISIBLE | SS_LEFT,
    10, 130,
    200, 36,
    hwnd, NULL, hInstance, NULL
  );

  SetWindowText(static_, "This is a static label\n"
    "and below is an icon");

  static_icon = CreateWindowEx(
    0,
    "STATIC",
    NULL,
    WS_CHILD | WS_VISIBLE | SS_ICON,
    10, 170,
    48, 48,
    hwnd, NULL, hInstance, NULL
  );

  SendMessage(
    static_icon,
    STM_SETICON,
    (WPARAM) LoadIcon(NULL, IDI_APPLICATION),
    0
  );

  btn2 = CreateWindowEx(
    0,
    "BUTTON",
    "Click me!",
    WS_CHILD | WS_VISIBLE,
    10, 204,
    200, 30,
    hwnd, (HMENU) BTN2_ID, hInstance, NULL
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
    // DROPDOWN = editable, DROPDOWNLIST = not editable
    WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
    220, 210,
    200, 200,
    hwnd, NULL, hInstance, NULL
  );

  SendMessage(combobox, CB_ADDSTRING, 0, (LPARAM) "Hello");
  SendMessage(combobox, CB_ADDSTRING, 0, (LPARAM) "World");
  SendMessage(combobox, CB_SETCURSEL, 0, 0);

  HFONT font = (HFONT) GetStockObject(DEFAULT_GUI_FONT);

  SendMessage(btn, WM_SETFONT, (WPARAM) font, 0);
  SendMessage(btn2, WM_SETFONT, (WPARAM) font, 0);
  SendMessage(checkbox, WM_SETFONT, (WPARAM) font, 0);
  SendMessage(textfield, WM_SETFONT, (WPARAM) font, 0);
  SendMessage(static_, WM_SETFONT, (WPARAM) font, 0);
  SendMessage(listbox, WM_SETFONT, (WPARAM) font, 0);
  SendMessage(combobox, WM_SETFONT, (WPARAM) font, 0);
   
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
        switch (wParam)
        {
          case BTN_ID:
            MessageBox(
              NULL,
              "A command\nand a new line",
              "",
              MB_ICONEXCLAMATION | MB_OK
            );
            break;

          case BTN2_ID:
            MessageBox(
              NULL,
              "Wow, you clicked me!",
              "Wow",
              MB_ICONEXCLAMATION | MB_OK
            );
            break;

          case CHECKBOX_ID:
            if (IsDlgButtonChecked(hwnd, CHECKBOX_ID) == BST_CHECKED)
              CheckDlgButton(hwnd, CHECKBOX_ID, BST_UNCHECKED);
            else
              CheckDlgButton(hwnd, CHECKBOX_ID, BST_CHECKED);
            break;
        }
        break;

      case WM_LBUTTONDBLCLK:
        MessageBox(
          NULL,
          "Hey, you, double-clicker.",
          "Message",
          MB_ICONEXCLAMATION | MB_OK
        );
        break;
       
      default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
   
  return 0;
}

