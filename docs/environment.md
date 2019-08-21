# Prepare environment

> Auto-updates are coming soon!

## 1. Download Easypt interpreter

You can obtain latest interpreter executable here:

- [Windows](https://ci.appveyor.com/api/projects/antollo/easypt/artifacts/artifacts.zip?branch=master&job=Image%3A%20Visual%20Studio%202017)
- [Linux](https://ci.appveyor.com/api/projects/antollo/easypt/artifacts/artifacts.zip?branch=master&job=Image%3A%20Ubuntu)

Unpack `artifacts.zip` and place easypt interpreter in a worthy place.

## 2. Add Easypt interpreter to PATH

- For Windows:

  - Open Control Panel.
  - Go to System and Security then System.
  - Click Advanced System Settings.
  - Click the Environment Variables button.
  - Select Path from the User variables section and click Edit
  - Click the New button and paste path to interpreter.
  - Click Ok.

- For Linux run commands:

  ```bash
  echo "export PATH=\"$PATH:/path/to/interpreter\"" >> ~/.bash_profile
  source ~/.bash_profile
  chmod -R u=rwx /path/to/interpreter
  ```

- For all:
  
  Run command `easypt -entryPoint log(1234);` to verify Easypt interpreter is correctly installed. 


## 3. Download Visual Studio Code

You can download it [here](https://code.visualstudio.com/).

Skip this step if you already have VS Code installed.

## 4. Add Easypt extension to VS Code

You can download it in VS Code extension marketplace.

## 5. When you create new project add following `tasks.json` to project's `.vscode` directory:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Run Easypt source",
            "type": "process",
            "command": "easypt",
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

Now you are able to run Easypt code with VS Code build task (`Ctrl+Shift+B`).

---

[Next lesson (Basics)](basics.md)

[Table of contents](tutorial.md)