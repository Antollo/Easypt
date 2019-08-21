# `osName`

#### `..Root.system.osName`

A string identifying the operating system on which the Easypt interpreter is running.

Currently possible values are:

* `windows`
* `linux`

## Child of:

[`system`](docs..Root.system.md)

## Signatures:

`Object`, `Basic`, `Iterable`, `Container`, `String`

## Example:

```c
import("system");

log(system.osName);
```

#### Possible output:

```
linux
```