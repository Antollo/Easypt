# `WrongNumberOfArgumentsException`

#### `..Root.WrongNumberOfArgumentsException`

Constructs new `WrongNumberOfArgumentsException` which is thrown when wrong number of variables was passed to throwing function.

* **Parameters:** any number of `String` type variables

* **Return value:** new `WrongNumberOfArgumentsException`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto myFunction.=({
    if(args.size().!=(1), {
        throw(WrongNumberOfArgumentsException("More or less than one arguments passed!"));
    });
    if(instanceOf(args[0].get(), String).!(), {
        throw(WrongTypeOfArgumentException("This is not String!"));
    });
    log("This is one String: ", args[0].get());
});
myFunction("my argument");
```

#### Expected output:

```
my argument
```