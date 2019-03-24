# `StringIterator`

#### `..Root.StringIterator`

Constructs a new `StringIterator`, this constructor exists only for internal `String` purposes. `StringIterator` is not memory safe (not aware of `String` size). For creating `StringIterator` pointing to data use `String.begin()` and `String.end()`.

### `StringIterator` type signatures:

`Object`, `Iterator`, `StringIterator` 

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- [`<-`](docs..Root.StringIterator.less-.md)
- [`++`](docs..Root.StringIterator.++.md)
- [`--`](docs..Root.StringIterator.--.md)
- [`==`](docs..Root.StringIterator.==.md)
- [`distance`](docs..Root.StringIterator.distance.md)
- [`get`](docs..Root.StringIterator.get.md)
- [`+`](docs..Root.StringIterator.+.md)
- [`-`](docs..Root.StringIterator.-.md)
- [`>`](docs..Root.StringIterator.greater.md)
- [`<`](docs..Root.StringIterator.less.md)
- [`>=`](docs..Root.StringIterator.greater=.md)
- [`<=`](docs..Root.StringIterator.less=.md)

## Example:

```c
auto str.=("Hello world!");
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    basicOut(it.get());
});
```