# `readAll`

#### `..Root.File.readAll`

Returns the contents of the file.

* **Return value:** new `String`

## Child of:

[`File`](docs..Root.File.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("file");

var f.=(File());

f.open("a.txt");
f.clear();
f.write("Mad scientist.");

if (f.read().==("Mad").&&(f.readAll().==("Mad scientist.")), {
    basicOut("Ok");
}, {
    basicOut("Error");
})
```