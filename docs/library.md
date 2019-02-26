# Libraries

## 1. More on import

`import` is not only for importing `*.ez` sources, but also native Easypt libraries (like `*.dll`, `*.so` etc.). Easypt interpreter executable contain only core of Easypt features and its main features are being extensible and flexible. I present 3 simple libraries here:

- `console`
  - `console.write`
    - prints passed arguments
    - _parameters:_ `Basic` type, any number of parameters
    - _return value:_ `console`
  - `console.writeLine`
    - prints passed arguments and newline character
    - _parameters_
    - _return value:_ `console`
  - `console.read`
    - read input from console until whitespace
    - _no parameters_
    - _return value:_ new `String`
  - `console.readLine`
    - read input from console until newline
    - _no parameters_
    - _return value:_ new `String`
  - `console.scan`
    - read input from console as data of type of passed arguments and store it in arguments
    - _parameters:_ `Int`, `Double`, `String` or `Boolean` type, any number of parameters
    - _return value:_ `console`
  - `console.beep`
    - beeps
    - _no parameters_
    - _return value:_ `console`

- `system`
  - `system.callShellCommand`
    - call shell command
    - _parameters:_ `String`
    - _return value:_ `system`
  - `system.getEnvironmentVariable`
    - get environmental variable
    - _parameters:_ `String`
    - _return value:_ `String`

- `time`
  - `time.secondsSinceEpoch`
    - get time as seconds that have elapsed since 00:00:00 UTC, Thursday, 1 January 1970 ([_Read more, Wikipedia_](https://en.wikipedia.org/wiki/Unix_time))
    - _no parameters_
    - _return value:_ `Int`
  - `time.sleep`
    - blocks the execution of the current thread for provided milliseconds
    - _parameters:_ `Int`
    - _return value:_ `time`
  - `Clock`
    - construct new `Clock`
    - _no parameters_
    - _return value:_ new `Clock`
  - `Clock.getElapsedMilliseconds`
    - get the time elapsed since the last `restart` or the construction of this `Clock` as milliseconds
    - _no parameters:_
    - _return value:_ elapsed milliseconds as `Int`
  - `Clock.restart`
    - puts the time counter back to zero
    - _no parameters_
    - _return value:_ this `Clock`

## 2. Finally some input

```c
import("console");

console.writeLine("What's your name?");
var name.=(console.read());
console.writeLine("Hello, ", name, "!");
```

## 3. Bigger example

This source will measure speed of Easypt's console output functions:

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

Possible output:

[...]

```
basicOut: 4923 ms
console.writeLine: 4243 ms
console.write: 3384 ms
console.fast.writeInt: 2569 ms
```

---

[Next lesson (More on classes)](classes2.md)

[Table of contents](tutorial.md)