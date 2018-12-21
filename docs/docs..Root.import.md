# `import`

Imports source code from another `*.ez` file (source is treated as one big `BlockCallable`, assigned to `Root` with name identical as file name and then called) or from native Easypt library (`*.dll`/`*.so`). Library is searched in current working directory and then in interpreter directory. If both `xyz.ez` and `xyz.dll`/`xyz.so` are present `import("xyz")` imports `xyz.ez`.

#### `..Root.import`

* **Parameters:** `String`

* **Return value:** `BlockCallable`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`NativeCallable`, `Callable`

## Examples:

`lib.ez`:

```c
var add.=({
    return(args[0].get().+(args[1].get()));
});
```

`source.ez`:

```c
import("lib.ez");
var main.=({
    basicOut(lib.add(5 ,7));
});
```

---

```c
import("console");

console.writeLine("What's your name?");
var name.=(console.read());
console.writeLine("Hello, ", name, "!");
```
