If you want to check if your code is copied correctly, you can check the square at the top right of each code. If it matches the hash of this command, it is correctly copied.

```sh
cat template.cpp | tr -d '[:space:]' | md5sum | head -c 6
```