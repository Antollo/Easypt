# `system`

#### `..Root.system`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`

## Members:

- [`osName`](docs..Root.system.osName.md)
- _deprecated_ [`callShellCommand`](docs..Root.system.callShellCommand.md) 
- [`getEnvironmentVariable`](docs..Root.system.getEnvironmentVariable.md)
- [`shellInterface`](docs..Root.system.shellInterface.md)

## Example:

```c
import("system");

if (system.osName.==("windows"), {
    log(system.getEnvironmentVariable("TEMP"));
}, {
    log(system.getEnvironmentVariable("TMPDIR"));
});
```

#### Possible output:

```
C:\Users\XYZ\AppData\Local\Temp
```