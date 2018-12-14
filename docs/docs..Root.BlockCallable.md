# `BlockCallable`

#### `..Root.BlockCallable`

Constructs empty `BlockCallable`. To create non empty `BlockCallable` use curly braces operator `{`...`}`.

* **Return value:** new `BlockCallable`

### `BlockCallable` type signatures:

`Object`, `Callable`, `BlockCallable`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Members:

- [`return`](docs..Root.BlockCallable.return.md)
- [`if`](docs..Root.BlockCallable.if.md)
- [`while`](docs..Root.BlockCallable.while.md)
- [`for`](docs..Root.BlockCallable.for.md)
- [`throw`](docs..Root.BlockCallable.throw.md)
- [`try`](docs..Root.BlockCallable.try.md)
- [`callOperator`](docs..Root.BlockCallable.callOperator.md)

## Example:

```c
var fun.=({
    basicOut("a");
    basicOut("b");
    return("c");
    basicOut("d");
});

basicOut(fun());
```