# Permissions

## Calculation

Letter | Permissinos | Value
-------|-------------|------
 r     | read        | 4
 w     | write       | 2
 x     | execute     | 1
 \-    | none        | 0

## Commands

- `whoami`: current user
- `chmod 3x(0-7 or u+-rwx) file`: change permissions
- `touch file`: create file
- `ls -a (show hidden files) -1 (list with linebreaks) -l (show metadata) *?[abc123]`: list files for directory with pattern(**\*** any char of any number, **?** any one char, [abc123] any char of the set {a,b,c,1,2,3})