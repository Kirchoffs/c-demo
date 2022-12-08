# Notes

## Function Pointers
```
int sum(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int (*f)(int, int) = sum;
f = sub;
```

## Miscellaneous
### Asterisk of Pointers
C emphasizes expressions, so a C programmer prefer `int *p` because it shows `*p` is an `int`.  
C++ emphasizes types, so a C++ programmer prefer `int* p` because it shows `p` is a pointer to an `int`.

Also, for a function pointer, asterisk is placed next to the function name: `int (*f)(int, int) = sum;`, so from this point of view, C style is more consistent.
