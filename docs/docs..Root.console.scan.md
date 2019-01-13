# `scan`

#### `..Root.console.scan`

Reads new arguments' values from the standard input.

(_Similar concept to C's `scanf`, types of arguments are used insted of formatter._)

* **Parameters:** any number of variables of type `Int`, `String`, `Boolean` or `Double`

* **Return value:** reference to this function

## Child of:

[`console`](docs..Root.console.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("console");

var a.=(Int());
var b.=(Double());
var c.=(String());
console.scan(a, b, c);
console.writeLine("a: ", a, "\nb: ", b, "\nc: ", c);
```