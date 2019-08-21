# `network`

#### `..Root.network`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Members:

- [`downloadFile`](docs..Root.network.downloadFile.md)

## Example:

```c
import("network");
import("file");

network.downloadFile("https://raw.githubusercontent.com/Antollo/Easypt/master/README.md", "readme.txt");
auto file.=(File());
file.open("readme.txt");
log(file.readAll());
```