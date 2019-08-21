# `sleep`

#### `..Root.time.sleep`

Blocks the execution of the current thread for given number of milliseconds.

* **Parameters:** `Int` milliseconds

* **Return value:** reference to this (`time.sleep`)

## Child of:

[`time`](docs..Root.time.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("time");
log(time.secondsSinceEpoch());
time.sleep(2000);
log(time.secondsSinceEpoch());
```



