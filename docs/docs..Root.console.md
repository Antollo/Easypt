# `console`

#### `..Root.console`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`

## Members:

- [`write`](docs..Root.console.write.md)
- [`writeLine`](docs..Root.console.writeLine.md)
- [`read`](docs..Root.console.read.md)
- [`readLine`](docs..Root.console.readLine.md)
- [`scan`](docs..Root.console.scan.md)
- [`beep`](docs..Root.console.beep.md)
- [`controlSequence`](docs..Root.console.controlSequence.md)
- [`fast`](docs..Root.console.fast.md)

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

