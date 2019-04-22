# `get`

#### `..Root.Task.get`

Waits until the task ends and return its result.

* **Return value:** any type

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

console.writeLine(taskA.get());
```

### Expected output:

```
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
```