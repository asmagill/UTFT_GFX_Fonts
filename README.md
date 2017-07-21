UTFT_GFX_Fonts
==============

This library allows [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library) compatible TFT displays to use font files designed to be used with the [UTFT library](http://www.rinkydinkelectronics.com/library.php?id=51).

Some example fonts can be found [here](http://www.rinkydinkelectronics.com/r_fonts.php).

### Notes

Requires [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library) to provide drawing primitives.

This library has been tested with an Arduino UNO and the _Seeed TFT Touch Shield V1_ (see https://github.com/asmagill/Seeed_GFX_TFT) though it uses stock Adafruit_GFX library calls so it should work with any supported TFT shield.

Portions based on code from [UTFT library](http://www.rinkydinkelectronics.com/library.php?id=51).

### Known Issues / Limitations

* Requires use of library methods to print with UTFT style fonts; does not comply with the Print class so Stream and Print methods are not available for output yet.  This may be added in the future.
* Only implements the functions of the UTFT library necessary for font rendering.
* Examples need to be provided.

### References
* [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
* [UTFT library](http://www.rinkydinkelectronics.com/library.php?id=51)
* [Example Fonts](http://www.rinkydinkelectronics.com/r_fonts.php)
* [Adafruit GFX class for Seeed TFT Touch Shield V1](https://github.com/asmagill/Seeed_GFX_TFT)

### License

> The MIT License (MIT)
>
> Copyright (c) 2017 Aaron Magill
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
