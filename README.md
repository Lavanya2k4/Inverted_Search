**PROJECT TITLE**

Inverted Search Project – Word Search Using Hash Table and Linked Lists

**Description**

1.This project is implemented in Data Structures to search and index words from multiple text files.

2.It creates an inverted index that tells in which file a word is present and how many times it occurs.

3.The project uses hash table and linked lists for storing words (main_node) and filenames (sub_node).

**Files in This Project**

1.create_database.c – Builds the database from input text files

2.display_database.c – Displays the database in a readable format

3.search_database.c -  search the database from input text files

3.save_database.c – Saves the database into a text file

4.update_database.c – Updates the database from an existing file

5.main.c – Main file with menu-driven program

6.inverted_search.h – Header file with structures and function prototypes

**Features**

1.Reads multiple text files and indexes all words.

2.Stores each word only once, linked with all filenames where it appears.

3.Maintains count of word occurrences in each file.

**Supports:**

1.Creating database

2.Displaying database

3.searching database

4.Saving database into file

5.Updating database from file

**USAGE**

./a.out file1.txt file2.txt file3.txt


1.User gives text files as input.

2.Database is created with words, filenames, and counts.

3.Menu is provided to display, save, and update database.

**Example**

**Input Files:**

file1.txt → hi welcome
file2.txt → hi hello

Database Format:

#h;hi;2;file1.txt;1;file2.txt;1;#
#w;welcome;1;file1.txt;1;#
#h;hello;1;file2.txt;1;#

**How It Works**

1.Read words from text files.

2.Hash function decides index for storing words.

3.Insert word into main_node if new, else update sub_node.

4.Count occurrences of word per file.

5.Update database by removing old entries and adding fresh data.

6.Save/Display database in required format.

**Author**

Lavanya Chintala

📧 Email: chintalalavanya634@gmail.com
