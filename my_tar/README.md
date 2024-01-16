# Welcome to My Tar
***

## Task
Task was implement some part of tar linux command. The Linux tar stands for tape archive, is used to create Archive and extract the Archive files.

## Description
Did research but didn't find few information then, asked from peers, asked my from Miranvar (guy who has been struggling with this project for a month and collected huge data ), and complete and my groupmate helped me a lot

## Installation
there is no need to install it, you can check my code at my git profile.

## Usage
my_tar is a command to manipulate tape archive. The first option to tar is a mode indicator from the following list:

-c Create a new archive containing the specified items.
-r Like -c, but new entries are appended to the archive. The -f option is required.
-t List archive contents to stdout.
-u Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive. The -f option is required.
-x Extract to disk from the archive. If a file with the same name appears more than once in the archive, each copy will be extracted, with later copies overwriting (replacing) earlier copies.
In -c, -r, or -u mode, each specified file or directory is added to the archive in the order specified on the command line. By default, the contents of each directory are also archived.

Unless specifically stated otherwise, options are applicable in all operating modes:

-f file Read the archive from or write the archive to the specified file. The filename can be standard input or standard output.
my_tar will not handle file inside subdirectory.
```
./my_tar -tf last.tar

example.c
test.c
last.rb
ex.c

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
