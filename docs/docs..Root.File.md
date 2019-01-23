# `File`

#### `..Root.File`

Constructs new `File`. `File` provides basic read and write operations on files.

* **Return value:** new `File`

### `File` type signatures:

`Object`, `File`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`clear`](docs..Root.File.clear.md)
- [`write`](docs..Root.File.write.md)
- [`read`](docs..Root.File.read.md)
- [`open`](docs..Root.File.open.md)
- [`readAll`](docs..Root.File.readAll.md)

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