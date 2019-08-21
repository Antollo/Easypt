# `pushBack`

#### `..Root.String.pushBack`

Same functionality as `str.=(str+.(character[0].get()))` but faster. Argument must be one character string.

* **Parameters:** `String` character

* **Return value:** reference to this `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
auto n.=(10);
auto str.=(String());
auto condition.=(n.--().toBoolean());
while(condition, {
    str.pushBack("a");
    condition.=(n.--().toBoolean());
});
log(str);
```

#### Expected output:

```
aaaaaaaaaa
```