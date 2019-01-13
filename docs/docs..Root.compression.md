# `compression`

#### `..Root.compression`

## Child of:

[`Root`](docs..Root.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Members:

- [`unzip`](docs..Root.compression.unzip.md)
- [`zip`](docs..Root.compression.zip.md)

## Example:

```c
import("network");
import("compression");

network.downloadFile("https://ci.appveyor.com/api/projects/antollo/easypt/artifacts/artifacts.zip?branch=master&job=Image%3A%20Visual%20Studio%202017", "update.zip");
compression.unzip("update.zip", "./");
```