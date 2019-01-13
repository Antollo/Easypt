# `writeLine`

#### `..Root.console.writeLine`

Writes all arguments to the standard output followed by newline sequence.

* **Parameters:** any number of variables of type `Int`, `String`, `Boolean`, `Double` or `Basic`

* **Return value:** reference to this function

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