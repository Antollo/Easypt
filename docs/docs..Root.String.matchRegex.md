# `matchRegex`

#### `..Root.String.matchRegex`

Determines if the regular expression matches this string.

* **Parameters:** `String` regex

* **Return value:** new `Boolean`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
basicOut("aaaa".matchRegex("[a-z]+"));
basicOut("aAaa".matchRegex("[a-z]+"));
```

#### Expected output:

```
true
false
```