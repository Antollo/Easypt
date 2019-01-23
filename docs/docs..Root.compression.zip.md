# `zip`

#### `..Root.compression.zip`

Compress zip archive. Under the hood:

| OS      | command                                                                                                    | description        |
|---------|------------------------------------------------------------------------------------------------------------|--------------------|
| windows | `powershell -command "Compress-Archive -Path \"`inputPath`\" -Force -DestinationPath \"`pathToZipFile`\""` | [Compress-Archive] |
| linux   | `zip -r "`pathToZipFile`" "`inputPath`"`                                                                   | [zip]              |

[Compress-Archive]:https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.archive/compress-archive?view=powershell-6
[zip]:https://linux.die.net/man/1/zip

(_warning: commands prints own output_)

* **Parameters:** `String` inputPath, `String` pathToZipFile

* **Return value:** reference to pathToZipFile

## Child of:

[`compression`](docs..Root.compression.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("compression");
compression.zip("./contents/*", "pack.zip");
```