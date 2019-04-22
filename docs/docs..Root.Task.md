# `Task`

#### `..Root.Task`

The `Task` class represents an asynchronous operation. It runs the function f asynchronously (independently of the main program flow) with its remaining arguments as arguments and p as its parent. It is guaranteed that there are no data races.

**Exceptions:** Exception thrown in f makes task finished and is propagated through `get`.

* **Parameters:** any p, `Callable` f, _any number of any variables_

* **Return value:** new `Task`

### `Task` type signatures:

`Object`, `Task`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- [`get`](docs..Root.Task.get.md)
- [`isValid`](docs..Root.Task.isValid.md)
- [`isReady`](docs..Root.Task.isReady.md)

## Example:

```c
import("console");

auto taskA.=(Task(Root, {
    for (auto i.=(0).<, 10, i.++, {
        console.writeLine("A");
    });
    return("Task A ended.");
}));

auto taskB.=(Task(Root, {
    for (auto i.=(0).<, 10, i.++, {
        console.writeLine("B");
    });
    return("Task B ended.");
}));

console.writeLine(taskA.get());
console.writeLine(taskB.get());
```

### Expected output:

```
A
B
A
B
A
B
A
B
A
B
A
B
A
B
A
B
A
B
A
B
Task A ended.
Task B ended.
```