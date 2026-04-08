# GuiToolkit - MFC Extension Library

A comprehensive MFC (Microsoft Foundation Class) extension library providing enhanced GUI controls and frameworks for Windows applications.

## Overview

GuiToolkit is a free MFC extension library that provides a wide range of UI controls and framework enhancements for building professional Windows applications with Visual C++ and MFC.

## Features

- **Docking System**: Advanced dockable toolbars and control bars
- **Tab Controls**: Enhanced tabbed interfaces (CGuiTab, CBaseTab)
- **Office-style UI**: Outlook, PowerPoint, and Word-inspired navigation panels
- **Custom Controls**: 
  - CGuiEditView - Enhanced edit view
  - GuiButton - Custom button controls
  - GuiComboBoxExt - Extended combo box
  - GuiListCtrl - Enhanced list control
  - GuiMiniSplitter - Splitter controls
- **MDI Support**: Enhanced MDI frame and window management
- **Theme Support**: UxTheme integration for Windows XP+ visual styles

## Project Structure

```
GuiToolkit/
├── GuiLib/           # Core library source code
├── Samples/          # Sample applications demonstrating features
├── bin/              # Compiled binaries
└── Uxtheme.h         # Theme API headers
```

## Sample Applications

The `Samples/` directory contains numerous demo projects:

| Sample | Description |
|--------|-------------|
| CGuiAccess | Access-style interface demo |
| CGuiOfficeDemo | Office-style UI demo |
| CGuiPowerPoint | PowerPoint-like interface |
| GuiPanelAccessDemo | Panel access control demo |
| OutlookDemo | Outlook-style navigation |
| SDIDemo | SDI application framework |
| ToolBarsDemo | Toolbar customization demo |

## Requirements

- Visual C++ 6.0 or later (compiled with VC6)
- MFC library
- Windows SDK

## License

This project is released under the **GNU General Public License v3.0** (GPL-3.0).

See the [LICENSE](LICENSE) file for details.

## Author

- **Original Author**: Francisco Campos G.
- **Website**: [beyondata.com](http://www.beyondata.com)
- **Email**: fcampos@beyondata.com

## Note

This library is provided "as is" without warranty of any kind. You are free to use it in any application (Freeware, Shareware, Commercial), but please preserve the header information in the source files.

## Building

1. Open `GuiToolkit.dsw` in Visual C++ 6.0
2. Build the GuiLib project first
3. Build individual sample projects as needed

## Acknowledgments

Special thanks to Francisco Campos for creating and releasing this toolkit as free code for the developer community.
