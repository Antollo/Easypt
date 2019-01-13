# `beep`

#### `..Root.console.beep`

Plays the sound of a beep (writes `\a` to the standard output).

(_`\a` = 7 in ASCII encoding_)

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