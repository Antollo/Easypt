# `isReady`

#### `..Root.Task.isReady`

Checks if task has finished.

* **Return value:** new `Boolean`

## Child of:

[`Task`](docs..Root.Task.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("console");
import("time");

auto taskA.=(Task(Root, {
    for (auto i.=(0).<, 10, i.++, {
        console.writeLine("A");
    });
    return("Task A ended.");
}));

console.writeLine(taskA.isReady());
time.sleep(3);
console.writeLine(taskA.isReady());
time.sleep(3);
console.writeLine(taskA.isReady());
time.sleep(3);
console.writeLine(taskA.isReady());

console.writeLine(taskA.get());
```

### Possible output:

```
false
A
A
A
A
A
A
A
false
A
A
A
true
true
Task A ended.
```

