# `write`

#### `..Root.console.write`

Writes all arguments to the standard output.

* **Parameters:** any number of variables of type `Int`, `String`, `Boolean`, `Double` or `Basic`

* **Return value:** reference to this function

## Child of:

[`console`](docs..Root.console.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("console");

console.write("abc");
```