# pest4-recover
This is a C program used to recover deleted photos. https://cs50.harvard.edu/x/2020/psets/4/recover/

This was produced as a part of CS50 - Introduction to Computer Science. Uploading of my solution to Github is considered to be reasonable regarding the academic honesty policy. (https://www.reddit.com/r/cs50/comments/63235w/is_this_reasonable/)

This program was one of the first cases in which I learned how to and applied memory management.

It works by;
- Allocating memory for the memory card file and the 'buffer' which .
- Opening the memory card file and reading through each byte of data contained within this file using a while loop.
- 4 specific sequential chunks of data are looked for during the while loop which signify the start of a JPEG file, when found the data is written to a new file until a new JPEG is found.
- As the JPEGs are back to back, once the first is open the next time the 4 bytes signifying JPEG file are found the current image is closed and a new image is written.
- On the end of the file all memory used is free'd.


*Note* the card.raw file has been omitted due to its size.
