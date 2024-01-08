# 04_gpio_driver

## Step 0: Check the documentation of gpio of Orange Pi PC (Allwinner H3)

Based on the [Sunxi GPIO](https://linux-sunxi.org/GPIO)

| CON3 | Allwinners H3 | gpio |
|------|---------------|------|
|  7   |    PA6        |gpio-6|
|  11  |    PA1        |gpio-1|


> (position of letter in alphabet - 1) * 32 + pin number

## Step 1: Compile

```bash
make
```
The expected output is a *.ko* file.

## Step 2: Load Kernel Module

```bash
sudo insmod gpio_driver.ko
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
sudo chmod 666 /dev/my_gpio_driver
```
Check out that all users can read and write but cannot execute the character file.

```console
orangepi@orangepipc:~/.../04_gpio_driver$ ls -l /dev/my_gpio_driver
crw-rw-rw- 1 root root 240, 0 Jan  3 19:02 /dev/my_gpio_driver
```
## Step 4: Test the `my_gpio_driver`

Turn on/turn off the LED.  The LED is hooked up in pin 7 of CON3.

```bash
orangepi@orangepipc:~/.../04_gpio_driver$ echo 1 > /dev/my_gpio_driver
```
Read the button status. The button is hooked up in pin 11 of CON3.

```bash
orangepi@orangepipc:~/.../04_gpio_driver$ head -1 /dev/my_gpio_driver 
```
## Step 5: Remove the module

```bash
 sudo rmmod gpio_driver
```
