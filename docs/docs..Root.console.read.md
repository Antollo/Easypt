# `read`

#### `..Root.console.read`

Reads the characters from the standard input until first whitespace is encountered.

* **Return value:** new `String`

## Child of:

[`console`](docs..Root.console.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("console");

while (true, {
    if (console.read().==("beep"), {
        console.beep();
        console.writeLine(">_<");
    });
});
```