# `callShellCommand`

#### `..Root.system.callShellCommand`

Calls the operating system's command processor with the parameter command. 

* **Parameters:** `String` command

* **Return value:** reference to this function

## Child of:

[`system`](docs..Root.system.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("system");

basicOut(system.callShellCommand("cd"));
```

#### Possible output:

```
C:\Easypt
```