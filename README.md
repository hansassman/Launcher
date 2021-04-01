# Launcher
Simple and configurable Qt based application launcher.

![](documentation\Launcher1.png)

![](documentation\Launcher2.png)

## Idea

This utility is intended to create simple and fast application launcher to be used in combination with AutoHotkey. With simple AHK script that implements keyboard shortcuts combined with Launcher user can create a quick launcher solution that behaves correctly when it comes to Windows keyboard focus. 

## Usage and configuration

In configuration user can define items with icon, executable, cli parameters and working directory. When Launcher.exe is executed with configuration it renders a simple, keyboard operated launcher from these items. Configuration is passed to Launcher.exe as first positional command line argument. If configuration file is omitted, Launcher tries to read configuration from `./config.json`. 

After launcher has started, user can navigate between items with arrow keys or tab and launch the program with enter. Application can also be closed with esc and by making it lose focus (eg. clicking anything except the launcher GUI).

Example configuration:

```json
{
  "items": [
    {
      "icon": "C:/Users/User/Pictures/Icons/ubuntu.png",
      "executable": "wt.exe",
      "cliParameters": "-p Ubuntu"
    },
    {
      "icon": "C:/Users/User/Pictures/Icons/debian.png",
      "executable": "wt.exe",
      "cliParameters": "-p Debian"
    },
    {
      "icon": "C:/Users/User/Pictures/Icons/qt.png",
      "executable": "C:/Qt/Tools/Preview/Qt Creator/bin/qtcreator.exe",
      "workingDirectory" : "C:/Users/User"
    }
  ],
  "theme": {
    "background-color": "#333333",
    "selected-color": "#232323",
    "not-selected-color": "#333333"
  }
}

```

## Example AHK Script

Following script launches Launcher with configuration when left Winkey and enter is pressed simultaneously.

```
#NoEnv
SendMode Input
SetWorkingDir %A_ScriptDir%

<#Enter::
	Run *runas C:\Program Files\Launcher\Launcher.exe configuration.json,,, process_id
	WinWait, ahk_pid %process_id%
	WinActivate, ahk_pid %process_id%
	return
```

