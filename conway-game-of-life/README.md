# Conway's Game of Life
All code and documents are from Berkeley CS-61C

## Command
On CentOS
```
To get the `convert` command for GIF:
>> sudo yum install ImageMagick

Install csh
>> sudo yum install tcsh
```

Give the script permission
```
>> chmod +x frames.csh
```

Generate Game of Life GIF
```
>> make gameoflife
>> ./frames.csh blinkerH 0x1808 10
```

## PPM Format
```
P3
4 5
255
  0   0   0     0   0   0     0   0   0     0   0   0
255 255 255   255 255 255   255 255 255     0   0   0
  0   0   0     0   0   0     0   0   0     0   0   0
  0   0   0     0   0   0     0   0   0     0   0   0
  0   0   0     0   0   0     0   0   0     0   0   0
```

The first line of the header, "P3", tells us that this is a PPM file of format P3.

The second line tells us the width and the height of our image. In this case, our image is 4 pixels wide and 5 pixels tall.

The final line of the header, “255”, gives us the scale with which we are describing colors. In this case, color values will range from 0 to 255.

The rest of the file describes the actual pixels in the image - each pixel is described by three numbers, representing the red, green, and blue values in that pixel. The content in the body of the file confirms the information in the header: since each pixel needs 3 numbers, we have 4 pixels per row and 5 rows.

## Steganography
Steganography is the process of hiding a message in an image or similar file.

## The Game of Life
The Game of Life is usually played on a bitmap (black and white) image over many timesteps, in which each pixel (or bit) is either 1 (alive) or 0 (dead). The original rules for the Game of Life are reprinted below:

- Any live cell with two or three live neighbours (in the surrounding 8 cells) survives to the next generation.
- Any dead cell with three live neighbours becomes a live cell in the next generation.
- All other live cells die in the next generation. Similarly, all other dead cells stay dead.

We can encode this rule into a number:  
[0 0 0 0 0 1 1 0 0] [0 0 0 0 0 1 0 0 0] which is 0x1808

The first half parts indicates the next state if current state is alive (1), The second half parts indicates the next state if current state is dead (0).  

When the i-th bit is 1, it means if there are i alive cells around me, then I can be alive in the next second, otherwise dead.

## Notes
### Fixed-width integer
The stdint.h header file, which defines the `uint32_t` data type, was introduced in the `C99` standard. This standard was published in 1999 and introduced a number of new features to the C programming language, including support for fixed-width integer data types, complex numbers, and variable-length arrays.  

In C programming, `%u` is a format specifier that specifies the type of the argument in a printf or scanf function. It indicates that the argument is an unsigned integer. 

`uint8_t` aka `unsigned char`

### Difference between cstdio and stdio.h
The difference is that stdio.h and other C-like libraries when imported in a C++ file may pollute the global namespace, while the corresponding C++ headers (cstdio, cstdlib, cassert) place the corresponding functions, variables, etc., in the std namespace.

### C Function
`long strtol(const char* str, char** endptr, int base)`  

In `stdlib,h`, it converts the initial part of the string in str to a long value according to the given base, which must be between 2 and 36 inclusive, or be the special value 0.  
If the base is 0, the number is assumed to be a decimal, unless, the converted number starts with O (for Octal) or Ox (for hexadecimal).

```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *str = "1092";
    char *ptr;
    long val;

    // Convert the string to a long integer
    val = strtol(str, &ptr, 16);

    // Check for errors
    if (ptr == str)
    {
        printf("Error converting string to long integer!\n");
        return 1;
    }

    // Print the result 4242
    printf("The string '%s' was converted to the long integer %ld\n", str, val);

    return 0;
}
```

### Format Output
```
printf("%3d %3d %3d   ", r, g, b);
```
Here, the formatted string "%3d" specifies that an integer should be output and occupy 3 characters. This causes the integer 123 to be output as the string " 123", taking up 3 characters and aligned to the right.

Note that in the code above, we added the number 3 before the integer formatting specifier d in the formatted string. This number specifies the number of character positions that the output integer should occupy. In this example, we specify that the output integer should occupy 3 character positions.

If the number you want to output is less than 3 digits, the extra character positions will be filled with spaces. For example, if you output the integer 12, it will be output as the string " 12", with the extra character position filled with a space.

Additionally, if the number you want to output is more than 3 digits, the number 3 in the formatted string will not have any effect on the output. For example, if you output the integer 1234, it will be output as the string "1234" and will not be aligned to the right.