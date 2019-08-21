# `write`

#### `..Root.File.write`

Appends data to a file. Moves _read position indicator_ to the begin of file.

* **Parameters:** any number of variables of type `Basic`

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
f.write("afpha beta\ngamma");

log(f.read());
log(f.read());
log(f.read());

f.write("delta");

log(f.read());
```

#### Possible output:

```
alpha
beta
gamma
alpha
```