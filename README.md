# Mini Unix Utilities

* This project includes 3 different mini versions of the actual Linux utilities programmed in C.

## my-cat:

* Run: ./my-cat file1 ...

* My-cat will read in file(s) that the user inputs and prints out the contents of specified files to stdout. 
* If my-cat is entered without any arguments, it will do nothing and return 0. 
* If fopen() fails to open a file, it will print out an error to stderr and exit with a 1.
* For reading the file(s), it reads one line at a time using fgets() under a while loop until EOF.
* Closed files handled after each file finishes in order to save resources.

## my-sed:

* Run: ./my-sed "search" "replace" file1 ...

* My-sed will read in at least 4 arguments: executable, search word, replace word, file. It will print out the new contents with the replaced word. If more than one file is specified, it will replace the search word across all file(s).
* If my-sed is entered with only 3 arguments, it will allow the user to manually type out the content and it will replace the word after pressing enter.
* If the user enters less than 3 arguments, it will throw an error to stderr.
* It searches by using two buffers then comparing the current and target strings, once it finds the target, it will execute replace which will replace the matching string.
* If fopen() files to open a file, it will print out an error message to sterr and exit with a 1.
* For reading the file(s), it reads one line at time using getline() under a while loop until EOF.

## my-uniq:

* Run: ./my-uniq file1 ...

* my-uniq reads files line by line using fgets(), storing each line in an array.
  Then prints to stdout, ignoring duplicate adjacent lines.
* It checks for duplicates by setting the previous and current line variables accordingly.
  Then compares them in the searchDup function. If a duplicate is found, it won't print.
* In the case that no file arguments are detected, the program will read from stdin. 
  It will take input until EOF is detected which can be inserted with 'ctrl + d'.
* If fopen() fails to open a file, it will print an error message to stderr and exit with a 1.