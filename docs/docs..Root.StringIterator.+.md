# `+`

#### `..Root.StringIterator.+`

Returns new `StringIterator` moved forward by arguments value;

* **Parameters:** `Int`

* **Return value:** new `StringIterator`

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:



```c
auto str.=("Hello world!");
auto x.=(str.begin().+(4));
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    if (it.==(x), { log(it.get()) });
});
```