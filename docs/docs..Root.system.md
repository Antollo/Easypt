# `system`

#### `..Root.system`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`

## Members:

- [`osName`](docs..Root.system.osName.md)
- [`callShellCommand`](docs..Root.system.callShellCommand.md)
- [`getEnvironmentVariable`](docs..Root.system.getEnvironmentVariable.md)

## Example:

```c
import("system");

if (system.osName.==("windows"), {
    basicOut(system.getEnvironmentVariable("TEMP"));
}, {
    basicOut(system.getEnvironmentVariable("TMPDIR"));
});
```

#### Possible output:

```
C:\Users\XYZ\AppData\Local\Temp
```