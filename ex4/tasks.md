## 3 Files and Directories

1. Create in your home directory a directory **OpSys**.
    ```bash
    cd
    #cd ~
    #cd /home/user
    mkdir OpSys
    ```

2. Navigate to the directory **OpSys** and create inside an empty file with the filename **File1.txt**. (Do not use an editor application to create the file, but a command line command.)
    ```bash
    cd OpSys
    touch File1.txt
    ```

3. Check the file size of the file **File1.txt**.
    ```bash
    ls -lh
    ```

4. Change the modification time of the file **File1.txt** to your birth date.
    ```bash
    # [[CC]YY]MMDDhhmm[.ss]
    touch --time modify -t 197001010000 File1.txt
    # YYYY-MM-DD
    touch -m -d "1970-01-01" File1.txt
    ```

5. Print out the first line of the file **File2.txt** in the shell.
    ```bash
    head -n 1 File2.txt
    #cat File2.txt | head -n 1
    ```

6. Append the content of **File2.txt** to **File1.txt**. (Do not use an editor application, but a command line command.)
    ```bash
    cat File2.txt >> File1.txt
    ```

7. Create in your home directory, a directory with the directory name **OpSys_new_semester**.
    ```bash
    mkdir ../OpSys_new_semester
    ```

8. Copy the files **File1.txt** and **File2.txt** from the directory **OpSys** into the directory **OpSys_new_semester**.
    ```bash
    cp File1.txt File2.txt ../OpSys_new_semester/
    ```

9. Erase the directory OpSys.
    ```bash
    cd ..
    rm -r OpSys
    ```


## 4 Links

1. Create in your home directory a directory with the name **OpSys_Links**. Navigate to the new directory and try to erase the entry **.**.
    ```bash
    mkdir OpSys_Links
    cd OpSys_Links
    rm -r .
    ```

2. Create in the directory **OpSys_Links**...
    - an empty file **Original**.
    - a hard link **HardLink**, which points to the file **Original**.
    - a symbolic link **SymLink**, which points to the file **Original**.
    ```bash
    touch Original
    ln -T Original Hardlink
    ln -s Original Symlink
    ```

3. Check the inodes of the file **Original** and of both links via **ls -li**.
    - Hardlinks have same inode number

4. Is it possible to copy hard links? Try to copy the link.
    - Yes, but they have a different inode number

5. Is it possible to copy symbolic links? Try to copy the link.
    - Yes, they have no link

6. Check the result of your copying via **ls -li**. What are your conclusions?
    - the copy of the Hardlink has a different inode number
    - original hardlink has link count of 2 now
    - the copy of the symlink has no link
    - original symlink still has link count of 1

7. The so called *link count* of files indicates the number of directory entries, which refer to an inode. What indicates the link count of directories and what influences the link count of directories?
    
