# `read`

#### `..Root.File.read`

Reads the characters from the file starting at position pointed by _read position indicator_  until first whitespace is encountered. Moves _read position indicator_ to next non whitespace character.


* **Return value:** new `String`

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
f.write("alpha beta\ngamma");

basicOut(f.read());
basicOut(f.read());
basicOut(f.read());

f.write("delta");

basicOut(f.read());
```

#### Possible output:

```
alpha
beta
gamma
alpha
```