# `callShellCommand`

#### `..Root.system.callShellCommand`

Calls the operating system's command processor with concatenation of given parameters. 

* **Parameters:** any number of `String`

* **Return value:** reference to this function

## Child of:

[`system`](docs..Root.system.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("system");

system.callShellCommand("cd");
```

#### Possible output:

```
C:\Easypt
```