# Easypt

![https://ci.appveyor.com/api/projects/status/github/Antollo/Easypt?svg=true]( https://ci.appveyor.com/api/projects/status/github/Antollo/Easypt?svg=true)

## Quick example:

```c
import("console");
var name; 
console.write("What's your name?\t");
name.=(console.read());
console.write("Hello ", name);
```

Run with: `easypt -file my_file.ez`. More sophisticated:

```c
import("console");
var main.=({
    var name; 
    console.write("What's your name?\t");
    name.=(console.read());
    console.write("Hello ", name);
});
```

Run with: `easypt -file my_file.ez -entryPoint Root.my_file.main()`


## Overview

__Easypt__ (_blend of easy and script_) is cross-platform structured object-oriented interpreted programming language. Its main goal is to be easy, small and extensible. Project started on 30th August 2018.

### [See Easypt reference](https://antollo.github.io/Easypt)

### [See Easypt tutorial](https://antollo.github.io/Easypt/tutorial)
 
## Artifacts

[https://ci.appveyor.com/project/Antollo/easypt](https://ci.appveyor.com/project/Antollo/easypt)