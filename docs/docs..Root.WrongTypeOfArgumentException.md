# `WrongTypeOfArgumentException`

#### `..Root.WrongTypeOfArgumentException`

Constructs new `WrongTypeOfArgumentException` which is thrown when variable with not appropriate type was passed to throwing function.

* * **Parameters:** any number of `String` type variables

* * **Return value:** new `WrongTypeOfArgumentException`

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
    basicOut("This is one String: ", args[0].get());
});
myFunction("my argument");
```

#### Expected output:

```
my argument
```