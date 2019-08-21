# `clear`

#### `..Root.File.clear`

Clears contents of opened file. Moves _read position indicator_ to the begin of file.

* **Return value:** reference to this function

## Child of:

[`File`](docs..Root.File.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("file");

auto f.=(File());

f.open("a.txt");
f.clear();
f.write("Mad scientist.");

if (f.read().==("Mad").&&(f.readAll().==("Mad scientist.")), {
    log("Ok");
}, {
    log("Error");
})
```