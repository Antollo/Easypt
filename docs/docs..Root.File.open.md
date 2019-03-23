# `open`

#### `..Root.File.open`

Opens file pointed by a given path (creates such file if it does not exist). Moves _read position indicator_ to the begin of file.

* **Parameters:** `String` path

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
    basicOut("Ok");
}, {
    basicOut("Error");
})
```