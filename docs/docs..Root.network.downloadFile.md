# `downloadFile`

#### `..Root.network.downloadFile`

| OS      | command                                                                                 | description         |
|---------|-----------------------------------------------------------------------------------------|---------------------|
| windows | `powershell -command "Invoke-WebRequest -Uri \"`URL`\" -OutFile \"`destinationPath`\""` | [Invoke-WebRequest] |
| linux   | `wget -O "`destinationPath`" "`URL`"`                                                   | [wget]              |

[Invoke-WebRequest]:(https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.utility/invoke-webrequest?view=powershell-6)
[wget]:(https://linux.die.net/man/1/wget)

(_warning: commands prints own output_)

* **Parameters:** `String` URL, `String` destinationPath

* **Return value:** reference to destinationPath

## Child of:

[`network`](docs..Root.network.md)

## Signatures:

`Object`, `Callable`, `BlockCallable`

## Example:

```c
import("network");
import("file");

network.downloadFile("https://raw.githubusercontent.com/Antollo/Easypt/master/README.md", "readme.txt");
var file.=(File());
file.open("readme.txt");
basicOut(file.readAll());
```