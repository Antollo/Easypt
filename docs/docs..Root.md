# `Root`

#### `..Root`

## Child of:

_Mysterious dot. (joke)_

## Signatures:

_none_

## Members:

- [`apply`](docs..Root.apply.md)
- [`basicOut`](docs..Root.basicOut.md)
- [`debugTree`](docs..Root.debugTree.md)
- [`import`](docs..Root.import.md)
- [`instanceOf`](docs..Root.instanceOf.md)
- [`Exception`](docs..Root.Exception.md)
- [`except`](docs..Root.except.md)
- [`WrongTypeOfArgumentException`](docs..Root.WrongTypeOfArgumentException.md)
- [`WrongNumberOfArgumentsException`](docs..Root.WrongNumberOfArgumentsException.md)
- [`FileNotFoundException`](docs..Root.FileNotFoundException.md)
- [`OutOfRangeException`](docs..Root.OutOfRangeException.md)
- [`NotSupportedOnThisOSException`](docs..Root.NotSupportedOnThisOSException.md)
- [`InvalidValueException`](docs..Root.InvalidValueException.md)
- [`ParserException`](docs..Root.ParserException.md)
- [`NotFoundException`](docs..Root.NotFoundException.md)
- [`Object`](docs..Root.Object.md)
- [`Basic`](docs..Root.Basic.md)
- [`Iterable`](docs..Root.Iterable.md)
- [`Iterator`](docs..Root.Iterator.md)
- [`Container`](docs..Root.Container.md)
- [`String`](docs..Root.String.md)
- [`StringIterator`](docs..Root.StringIterator.md)
- [`Int`](docs..Root.Int.md)
- [`Double`](docs..Root.Double.md)
- [`Boolean`](docs..Root.Boolean.md)
- `true`
- `false`
- [`BlockCallable`](docs..Root.BlockCallable.md)
- [`Array`](docs..Root.Array.md)
- [`ArrayIterator`](docs..Root.ArrayIterator.md)
- [`parse`](docs..Root.parse.md)

## Example:

```c
{
    var Int.=({ return(5); });
    basicOut(Int());
    basicOut(Root.Int());
}();
```

#### Expected output:

```
5
0
```

# Standard libraries

## `algorithm`

Provides functions for a variety of purposes (e.g. `min`, `forEach`, `sort`) including ones that operates on `Iterator`s and `Container`s.

- [`algorithm`](docs..Root.algorithm.md)

## `compression`

Provides basic compression and decompression services.

- [`compression`](docs..Root.compression.md)

## `console`

Provides standard input and output operations.

- [`console`](docs..Root.console.md)

## `docs`

Makes documentation.

- [`docs`](docs..Root.docs.md)

## `file`

Provides file input and output.

- [`File`](docs..Root.File.md)

## `math`

Provides mathematical constants and functions.

- [`math`](docs..Root.math.md)

## `memory`

Provides access to raw memory.

- [`ByteView`](docs..Root.ByteView.md)
- [`ByteViewIterator`](docs..Root.ByteViewIterator.md)
- [`ByteWrapper`](docs..Root.ByteWrapper.md)

## `network`

Provides basic network features.

- [`network`](docs..Root.network.md)

## `system`

Provides utilities for interactions with operating system.

- [`system`](docs..Root.system.md)

## `time`

Provides utilities for measuring time.

- [`time`](docs..Root.time.md)
- [`Clock`](docs..Root.Clock.md)
