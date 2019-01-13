# `getElapsedMilliseconds`

#### `..Root.Clock.getElapsedMilliseconds`

Get the elapsed time as milliseconds.

* **Return value:** new `Int` milliseconds

## Child of:

[`Clock`](docs..Root.Clock.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("time");
import("console");

var name.=(console.read());
var test1;
var test2;
var test3;
var test4;

var clock.=(time.Clock());
for (var i.=(0).<, 10000, i.++, {
    basicOut(i);
});
test1.=(clock.getElapsedMilliseconds());

clock.restart();
for (var i.=(0).<, 10000, i.++, {
    console.writeLine(i);
});
test2.=(clock.getElapsedMilliseconds());

clock.restart();
for (var i.=(0).<, 10000, i.++, {
    console.write(i);
});
test3.=(clock.getElapsedMilliseconds());

clock.restart();
for (var i.=(0).<, 10000, i.++, {
    console.fast.writeInt(i);
});
test4.=(clock.getElapsedMilliseconds());

console.write("\nbasicOut: ", test1, " ms\n");
console.write("console.writeLine: ", test2, " ms\n");
console.write("console.write: ", test3, " ms\n");
console.write("console.fast.writeInt: ", test4, " ms\n");
```

#### Possible output:

[...]

```
basicOut: 4923 ms
console.writeLine: 4243 ms
console.write: 3384 ms
console.fast.writeInt: 2569 ms
```