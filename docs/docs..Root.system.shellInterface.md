# `shellInterface`

#### `..Root.system.shellInterface`

Calls the operating system's command processor.

- Unix-like systems: uses `popen`
- Windows: creates `powershell` process with `-nologo` option and pipes command to it

Replaces `${n}` tokens with n-th argument of function.


* **Parameters:** `String` pattern, any number of `Basic`

* **Return value:** new `String`
  - Unix-like systems: stdout of process created with `popen`
  - Windows: stdout of `powershell -nologo` excluding lines consisting of whitespaces only and powershell prompt lines (marked internally with `<PS_PROMPT_TOKEN>` token)

## Child of:

[`system`](docs..Root.system.md)

## Signatures:

`NativeCallable`, `Callable`

## Example:

```c
import("system");

system.shellInterface("echo ${1}", "ABC");
```

#### Expected output:

```
ABC
```