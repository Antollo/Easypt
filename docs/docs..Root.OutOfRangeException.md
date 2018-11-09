# `OutOfRangeException`

#### `..Root.OutOfRangeException`

Constructs new `OutOfRangeException` which is thrown when an illegal range was used (indexes and string to number conversions).

* **Parameters:** any number of `String` type variables

* **Return value:** new `OutOfRangeException`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Examples:

```c
var arr.=(Array(3, "x");
arr[7].get();
```

```c
var str.=("abc");
str.pushBack("");
```

```c
var bigNumber.=("99999999999999999999999999");
basicOut(bigNumber.toInt());
```