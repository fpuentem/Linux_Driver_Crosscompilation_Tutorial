# 03_read_write

## Step 1: Compile

```bash
make
```
The expected output is a *.ko* file.

## Step 2: Load Kernel Module

```bash
sudo insmod read_write.ko
```
Check out that the installation of the kernel module is okay.

```console
foo@bar:~$ sudo dmesg | tail -n 4
[   71.762637] systemd[1368]: memfd_create() called without MFD_EXEC or MFD_NOEXEC_SEAL set
[10616.632285] read_write: loading out-of-tree module taints kernel.
[10616.632848] Hello, Kernel!
[10616.632865] read_write - Device Nr. Major: 240, Minor: 0 was registered!
```
Note:
 * Device Nr. Major could be another number it depends of your board.
 
## Step 3: Change the Access Permissions

```bash
sudo chmod 666 /dev/dummydriver
```
Check out that all users can read and write but cannot execute the character file.

```console
orangepi@orangepipc:~/.../03_read_write$ ls -l /dev/dummydriver
crw-rw-rw- 1 root root 240, 0 Jan  3 19:02 /dev/dummydriver
```
## Step 4: Test the `dummydriver`

Write some text string:

```bash
echo "This is a test" > /dev/dummydriver
```
Read the same string:

```console
orangepi@orangepipc:~/.../03_read_write$ head -1 /dev/dummydriver 
This is a test
```
## Step 5: Remove the module

```bash
 sudo rmmod read_write
```
