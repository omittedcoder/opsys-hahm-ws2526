# Wildcards and Filters

1. Create in your home directory a directory VariousFiles. Navigate to this directory and create these files:

```bash
touch abcdefg.bat cdata3.sav cdata7.sav file3.txt file7.txt abcxyz.bat cdata4.sav file10.txt file4.txt file8.txt cdata1.sav cdata5.sav file1.txt file5.txt file9.txt cdata2.sav cdata6.sav file2.txt file6.txt xyzabc.bat
```

2. Which command can be used to print out a list of all files in the directory, whose filenames start with the pattern file?

```bash
ls *file*
# file10.txt  file1.txt  file2.txt  file3.txt  file4.txt  file5.txt  file6.txt  file7.txt  file8.txt  file9.txt
```

3. Which command can be used to print out a list of all files in the directory, whose filenames contain the pattern cd?

```bash
ls *cd*
# abcdefg.bat  cdata1.sav  cdata2.sav  cdata3.sav  cdata4.sav  cdata5.sav  cdata6.sav  cdata7.sav
```

4. Which command can be used to print out a list of the files cdata2.sav, ..., cdata5.sav in the directory?

```bash
ls cdata*
# cdata1.sav  cdata2.sav  cdata3.sav  cdata4.sav  cdata5.sav  cdata6.sav  cdata7.sav
```

5. Which command can be used to print out a list of all files in the directory, whose filenames contain the characters c or z on position 3?

```bash
ls ??[cz]*
# abcdefg.bat  abcxyz.bat  xyzabc.bat
```

6. Which command can be used to print out a list of all files in the directory, whose filenames start with the character a and end with the character t and also contain the character c on any position?

```bash
ls [a]*c*[t]
# abcdefg.bat  abcxyz.bat
```

7. Which command can be used to print out a list of the files file1.txt, ..., file9.txt in the directory but without the files file3.txt and file4.txt.

```bash
ls file?.txt | grep -v 'file[34].txt'
# file1.txt
# file2.txt
# file5.txt
# file6.txt
# file7.txt
# file8.txt
# file9.txt

# or

ls file[1256789].txt
# file1.txt  file2.txt  file5.txt  file6.txt  file7.txt  file8.txt  file9.txt
```

