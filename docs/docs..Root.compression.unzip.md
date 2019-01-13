# `unzip`

#### `..Root.compression.unzip`

Decompress the zip archive. Under the hood:

| OS      | command                                                                                                       | description      |
|---------|---------------------------------------------------------------------------------------------------------------|------------------|
| windows | `powershell -command "Expand-Archive -Path \"`pathToZipFile`\" -Force -DestinationPath \"`destinationPath`\"` | [Expand-Archive] |
| linux   | `unzip -o "`pathToZipFile`" -d "`destinationPath`"`                                                           | [unzip]          |

[Expand-Archive]:https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.archive/expand-archive?view=powershell-6
[unzip]:https://linux.die.net/man/1/unzip

(_warning: commands prints own output_)

* **Parameters:** `String` pathToZipFile, `String` destinationPath

* **Return value:** reference to destinationPath

## Child of:

[`compression`](docs..Root.compression.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("network");
import("compression");

network.downloadFile("https://ci.appveyor.com/api/projects/antollo/easypt/artifacts/artifacts.zip?branch=master&job=Image%3A%20Visual%20Studio%202017", "update.zip");
compression.unzip("update.zip", "./");
```