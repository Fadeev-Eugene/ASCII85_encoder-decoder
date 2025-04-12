# ASCII85_encoder-decoder
Autor: Fadeev Eugene

Contacts: st128225@student.spbu.ru

# Description 
This program is ASCII85 encoder/decoder. It receives data from standart input, processes it and put into standart output. Decoder is implemented by usage of C++ and tested by Google tests and python utility base64

# Build
__make__ - to build project 

__make tests__ - to build tests and run it

__make clean__ - to clean files
# Project run
## Syntax
Use ___"./ascii85 [-e/-d]"___ to start program. Use key "-e" (or no key) if you want use it like encoder. Use "-d" if you want to use it like decoder.
## Recomendation 
If you want to use program on small amount of data, bettter use ___"echo -n "your messege" | ./ascii85 [-e/-d]"___.

If you want to use program on big amount of data, better use ___"./ascii85 [-e/-d] < input.txt > output.txt"___.

After all, program can be used to process from console or terminal.

