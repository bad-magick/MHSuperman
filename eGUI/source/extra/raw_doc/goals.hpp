namespace egui {

/** 
@page goals eGUI - goals

- Make C++ a RAD
  - Make GUI code simple and easy to understand
  - Make GUI programming safe
  - Make it easy to handle events and manipulate standard controls
  - Bridge the gap between STL & GUI, allowing for truly generic solutions
- support for Unicode

- No #include <windows.h> in your code
  - when using this lib, when you include its headers, they DONOT include <windows.h> header.

- no HWND ever
  - you need not know about the existance of HWND at all

- forget about WM_ messages, LPARAM, WPARAM, etc!

- Usage : similar to Windows Forms/ manipulation of windows, and of items and properties
- properties of existing controls: thread-safe by default
- Keep the good things from my previous library (win32gui)
- I will create building blocks, make the modules very flexible, and while I focus on new modules, other people can extend this library.
- Integrate it 100% with the Visual Studio 2005+
  - No message maps like MFC 
  - switching from code/form design easy and quickly
  - handling events can be set from the resource editor - events will be shown in user friendly manner
- Component/modular design - users will be able to select which modules they want to use
- Ease of use: code will be easy to understand and read and use (again, similar to Windows Forms)
- Easy to extend: each module will contain at least 2 examples of how to extend it
- Fast compile times 



*/

}
