# GuiToolkit - MFC 扩展库

一个全面的 MFC（Microsoft Foundation Class）扩展库，为 Windows 应用程序提供增强的 GUI 控件和框架。

## 概述

GuiToolkit 是一个免费的 MFC 扩展库，提供丰富的 UI 控件和框架增强功能，用于使用 Visual C++ 和 MFC 构建专业的 Windows 应用程序。

## 功能特性

- **停靠系统**: 先进的可停靠工具栏和控制栏
- **标签控件**: 增强的标签页界面（CGuiTab、CBaseTab）
- **Office 风格 UI**: Outlook、PowerPoint 和 Word 风格的导航面板
- **自定义控件**: 
  - CGuiEditView - 增强型编辑视图
  - GuiButton - 自定义按钮控件
  - GuiComboBoxExt - 扩展组合框
  - GuiListCtrl - 增强列表控件
  - GuiMiniSplitter - 分割器控件
- **MDI 支持**: 增强型 MDI 框架和窗口管理
- **主题支持**: UxTheme 集成，支持 Windows XP+ 视觉样式

## 项目结构

```
GuiToolkit/
├── GuiLib/           # 核心库源代码
├── Samples/          # 示例应用程序
├── bin/              # 编译后的二进制文件
└── Uxtheme.h         # 主题 API 头文件
```

## 示例应用程序

`Samples/` 目录包含多个演示项目：

| 示例 | 描述 |
|------|------|
| CGuiAccess | Access 风格界面演示 |
| CGuiOfficeDemo | Office 风格 UI 演示 |
| CGuiPowerPoint | PowerPoint 风格界面 |
| GuiPanelAccessDemo | 面板访问控件演示 |
| OutlookDemo | Outlook 风格导航 |
| SDIDemo | SDI 应用程序框架 |
| ToolBarsDemo | 工具栏自定义演示 |

## 系统要求

- Visual C++ 6.0 或更高版本（使用 VC6 编译）
- MFC 库
- Windows SDK

## 许可证

本项目采用 **GNU General Public License v3.0**（GPL-3.0）许可证。

详见 [LICENSE](LICENSE) 文件。

## 作者

- **原作者**: Francisco Campos G.
- **网站**: [beyondata.com](http://www.beyondata.com)
- **邮箱**: fcampos@beyondata.com

## 使用说明

本库按"原样"提供，不提供任何形式的担保。您可以自由使用于任何应用程序（免费软件、共享软件、商业软件），但请保留源文件中的头部信息。

## 构建方法

1. 在 Visual C++ 6.0 中打开 `GuiToolkit.dsw`
2. 首先构建 GuiLib 项目
3. 根据需要构建各个示例项目

## 致谢

特别感谢 Francisco Campos 创建并将此工具包作为免费代码发布给开发者社区。
