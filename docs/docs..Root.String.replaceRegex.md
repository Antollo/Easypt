# `replaceRegex`

#### `..Root.String.replaceRegex`

Copies this string and replaces all substrings matching regular expression replacement.

* **Parameters:** `String` regex, `String` replacement

* **Return value:** new `String`

## Child of:

[`String`](docs..Root.String.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
basicOut("aBCd".replaceRegex("[a-z]", "e"));
```

#### Expected output:

```
eBCe
```