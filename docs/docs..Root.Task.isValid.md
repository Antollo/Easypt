# `isValid`

#### `..Root.Task.isValid`

Checks if task is valid. Task is valid until the first time `get` is called.

* **Return value:** new `Boolean`

## Child of:

[`Task`](docs..Root.Task.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("console");

auto taskA.=(Task(Root, {
    for (auto i.=(0).<, 10, i.++, {
        console.writeLine("A");
    });
    return("Task A ended.");
}));

console.writeLine(taskA.isValid());
console.writeLine(taskA.get());
console.writeLine(taskA.isValid());
```

### Expected output:

```
true
A
A
A
A
A
A
A
A
A
A
Task A ended.
false
```