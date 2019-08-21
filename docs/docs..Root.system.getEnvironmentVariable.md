# `getEnvironmentVariable`

#### `..Root.system.getEnvironmentVariable`

Returns value of environment variable which name is equal to key.

* **Parameters:** `String` key

* **Return value:** new `String`

## Child of:

[`system`](docs..Root.system.md)

## Signatures:

`NativeCallable`, `Callable`

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