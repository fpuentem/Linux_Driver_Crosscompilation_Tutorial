# 01_simple_LKM
Hello world Linux kernel module. 

## Step 1:  Compile the kernel module

```bash
 make
```
Note: 
 * Check out if the header files are installed in `/lib/modules/$(uname -r)/build`.
 * You can get the header files *.deb* from the Armbian compilation dolder `build/output/debs`.
 
The expected output is a *.ko* file.

## Step 2: Install module

```bash
 sudo insmod mymodule.ko
```

Check out that the installation of the kernel module is okay with `lsmod | grep mymodule`. [Youtube](https://youtu.be/4tgluSJDA_E?t=671).

## Step 3: Verify the dmesg 

```bash
 sudo dmesg | tail -n 5
```
And you should get a **"Hello, Kernel!"** message in the terminal.

## Step 4: Remove the module

```bash
 sudo rmmod mymodule
```

