# More sources

## 1. Modular programming

> Modular programming is a software design technique that emphasizes separating the functionality of a program into independent, interchangeable modules, such that each contains everything necessary to execute only one aspect of the desired functionality. A module interface expresses the elements that are provided and required by the module. The elements defined in the interface are detectable by other modules. The implementation contains the working code that corresponds to the elements declared in the interface. Modular programming is closely related to structured programming and object-oriented programming, all having the same goal of facilitating construction of large software programs and systems by decomposition into smaller pieces, and all originating around the 1960s.
> 
> [_From Wikipedia_](https://en.wikipedia.org/wiki/Modular_programming)

## 2. Time to use shell

1. Create file `a.ez` and paste there following content:

   ```c
   var add.=({
       var return.=(args[0].get().+(args[1].get()));
   });

   basicOut(add(5 ,7));
   ```
   
   Run it with `easypt --file a.ez`

2. It would be better to divide it into two files:
   
   `a.ez`:
   
   ```c
   var add.=({
       var return.=(args[0].get().+(args[1].get()));
   });
   ```

   `b.ez`:
   
   ```c
   basicOut(a.add(5 ,7));
   ```

   _(Now it's `a.add`, huh? That's because all local variables in `some_file.ez` are added as children to `Root.some_file` node.)_

   Command `easypt --file a.ez --file b.ez` works like a charm, but `easypt --file b.ez --file a.ez` doesn't and throws exception:

   ```
   Exception at: ..Root.import
   Exception at: ..Root.b
   Exception at: ..Root.b.callOperator
   Exception at: ..Root.b
   Exception at: ..Root
   Exception at: .
   NotFoundException: Cannot find a in .
   ```

   That's because the fact that `a` must be executed before `b`.

3. `--entryPoint`
   
   Try running command `easypt --entryPoint "basicOut(\"Hello there!\");"`

   (`\"` quote escaping works at least in Windows cmd, if you don't see `Hello there!` output try something shell independent e.g. `easypt --entryPoint basicOut(1234);`)

   As you can see `--entryPoint` argument is executed (in `EntryPointBlockCallable` node that is not attached as child to `Root` for your curiosity) as normal code (called after last file from `--file`).

   You might have heard about something called _main function_ in other languages. In Easypt it is done as following:

   `a.ez`:

   ```c
   var add.=({
       var return.=(args[0].get().+(args[1].get()));
   });
   ```

   `b.ez`:
   
   ```c
   var main.=({
       basicOut(a.add(5 ,7));
   });
   ```

   Now this two files project can be executed with the far more beautiful command:

   `easypt --file b.ez --file a.ez --entryPoint b.main();`

## 3. Import

> Many programming languages and other computer files have a directive, _called import or include_, that causes the contents of a second file to be _available in_ the original file. [...] They are often used to define the physical layout of program data, pieces of procedural code and/or forward declarations while promoting encapsulation and the reuse of code. The include directive allows libraries of code to be developed which help to:
> - ensure that everyone uses the same version of a data layout definition or procedural code throughout a program.
> - easily cross-reference where components are used in a system.
> - easily change programs when needed (only one master file to change).
> - save time by not needing to code extensive data layouts (minor, but useful).
> 
> [_From Wikipedia, modified (marked with italic) to match Easypt `import`_](https://en.wikipedia.org/wiki/Include_directive)

`import` function works in the same way as `--file` argument. In fact `--file` is handled by calling `import`. See example:

`lib.ez`:

```c
var add.=({
    var return.=(args[0].get().+(args[1].get()));
});
```

`source.ez`:
   
```c
import("lib.ez");
var main.=({
    basicOut(lib.add(5 ,7));
});
```

Run it with command:

`easypt --file source.ez --entryPoint source.main();`
  

---

[Next lesson (Libraries)](library.md)

[Table of contents](tutorial.md)