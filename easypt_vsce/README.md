# Easypt extension

[![vs marketplace](https://img.shields.io/vscode-marketplace/v/Antollo.easypt.svg?label=vs%20marketplace)](https://marketplace.visualstudio.com/items?itemName=Antollo.easypt)
[![downloads](https://img.shields.io/vscode-marketplace/d/Antollo.easypt.svg)](https://marketplace.visualstudio.com/items?itemName=Antollo.easypt)
[![rating](https://img.shields.io/vscode-marketplace/r/Antollo.easypt.svg)](https://marketplace.visualstudio.com/items?itemName=Antollo.easypt)

## Features

Highlight comments, strings and numeric literals in Easypt scripts (`*.ez` files) and basic snippets.

## Requirements

Manually add following `tasks.json` to your project's `.vscode` folder:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Run Easypt source",
            "type": "process",
            "command": "easypyt",
            "args": [
                "-file",
                "${file}"
            ],
            "presentation": {
                "reveal": "always",
                "panel": "new"
            },
            "problemMatcher": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

Add easypt interpreter (`easypt.exe` - Windows or `easypt` - Linux) to PATH. You can get latest interpreter from [here](https://ci.appveyor.com/project/Antollo/easypt).

Now you can run your code with `Ctrl+Shift+B`.

## Last changes

Small snippets changes.

## For more information

* [Easypt on Github](https://github.com/Antollo/Easypt)

**Enjoy!**
