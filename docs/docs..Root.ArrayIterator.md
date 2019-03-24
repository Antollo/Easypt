# `ArrayIterator`

#### `..Root.ArrayIterator`

Constructs a new `ArrayIterator`, this constructor exists only for internal `Array` purposes. `ArrayIterator` is not memory safe (not aware of `Array` size). For creating `ArrayIterator` pointing to data use `Array.begin()` and `Array.end()`.

### `ArrayIterator` type signatures:

`Object`, `Iterator`, `ArrayIterator` 

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`, `Class`

## Members:

- [`<-`](docs..Root.ArrayIterator.less-.md)
- [`++`](docs..Root.ArrayIterator.++.md)
- [`--`](docs..Root.ArrayIterator.--.md)
- [`==`](docs..Root.ArrayIterator.==.md)
- [`distance`](docs..Root.ArrayIterator.distance.md)
- [`get`](docs..Root.ArrayIterator.get.md)
- [`+`](docs..Root.ArrayIterator.+.md)
- [`-`](docs..Root.ArrayIterator.-.md)
- [`>`](docs..Root.ArrayIterator.greater.md)
- [`<`](docs..Root.ArrayIterator.less.md)
- [`>=`](docs..Root.ArrayIterator.greater=.md)
- [`<=`](docs..Root.ArrayIterator.less=.md)


## Example:

```c
auto arr.=(Array());
arr.pushBack("abc", "def");
for (auto it.=(arr.begin()).!=, arr.end(), it.++, {
    basicOut(it.get());
});
```