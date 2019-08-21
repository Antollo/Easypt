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
auto arr.=(Array(3, "x");
arr[7].get();
```

```c
auto str.=("abc");
str.pushBack("");
```

```c
auto bigNumber.=("99999999999999999999999999");
log(bigNumber.toInt());
```