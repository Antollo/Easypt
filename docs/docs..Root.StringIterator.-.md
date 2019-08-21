# `-`

#### `..Root.StringIterator.-`

Returns new `StringIterator` moved backward by arguments value;

* **Parameters:** `Int`

* **Return value:** new `StringIterator`

## Child of:

[`StringIterator`](docs..Root.StringIterator.md)

## Signatures:

`NativeCallable`, `Callable`


## Example:



```c
auto str.=("Hello world!");
auto x.=(str.end().-(4));
for (auto it.=(str.begin()).!=, str.end(), it.++, {
    if (it.==(x), { log(it.get()) });
});
```