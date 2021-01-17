# Arduino


Fix error: "Cannot open /dev/ttyS0: Permission denied"

```
  sudo usermod -a -G tty $USER
  ```

```
  sudo usermod -a -G dialout $USER
  ```

This is an example of how to list boards connected to your computer.
* arduino-cli

```
  arduino-cli list board
  ```
