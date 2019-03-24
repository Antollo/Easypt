# `Class`

#### `..Root.Class`

Constructs new `Class` instance. `Class` objects are constructors of another types.

* **Parameters:** firstAncestor, secondAncestor, ..., firstMember, secondMember, ...

* **Return value:** new `Class` instance

### `Class` type signatures:

`Class`

### `Class` type members:

- `classProto` - contains members of new class
- `classSignatures` - contains base classes of new class

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Example:

```c
auto Bird.=(Class(
    Object,
    var color,
    {
        basicOut("bird created");
        color.=(args[0].get());
    }.setName("Bird"),
    {
        basicOut("tweet");
    }.setName("sing"),
    {
        basicOut("bird died");
    }.setName("~~")
));

auto Crow.=(Class(
    Bird,
    var color,
    {
        Bird(args[0].get());
    }.setName("Crow"),
    {
        basicOut("caw");
    }.setName("sing"),
    {
        basicOut("crow died");
    }.setName("~~")
));

auto bird.=(Crow("black"));
bird.sing();
```

#### Expected output:

```
bird created
caw
crow died
```
