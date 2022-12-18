## Makefile Notes

```
.c.o:
    $(CC) -c $(CFLAGS) $<
```
`.c.o` means building ".o" (object files) from ".c" (source files).  

For example, the suffix rule .c.o tells make how to build an object file from a C source file. If you have a C source file called main.c, the corresponding object file would be main.o. The .c suffix refers to the source file and the .o suffix refers to the object file. The rule specifies that to build main.o, make should use a C compiler to compile main.c.

`$<` means the first prerequisite (usually a source file).  
`$@` is the name of the target being generated.

## Run
```
>> make all
>> ./vector-test
>> make vector-memcheck
```

## Valgrind
```
>> valgrind --tool=memcheck --leak-check=full --track-origins=yes [OS SPECIFIC ARGS] ./<executable>
```