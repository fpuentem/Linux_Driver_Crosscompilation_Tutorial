# Linux Driver Tutorial (Crosscompilation)

Here you can find examples of simple Linux Kernel Modules and Linux Drivers. In order to make more generic development, all examples use an x86-64 host machine to generate the *.ko files, later these files are copied to the embedded system (Orange Pi) with ssh for testing.

## Preparation

### Host Machine
We are using a Ubuntu 22.04 x86_64 as a host machine to compile the kernel modules to Orange Pi.

 1. Install tools

    ```sh
        sudo apt install git make gcc g++ device-tree-compiler bc bison flex libssl-dev libncurses-dev python3-ply python3-git libgmp3-dev libmpc-dev
    ```
 2. Install an up-to-date cross compiler and associated toolset. This may be obtained from https://snapshots.linaro.org/gnu-toolchain/. The directory `arm-linux-gnueabihf` contains the necessary compiler for ARM 32-bit(Allwinners H3 processor) and the directory `aarch64-linux-gnu` for ARM 64-bit.
Choose the version suited to your development machine's architecture. For example, at the present time, for use on 64-bit Ubuntu 22.04 on an Intel-based development machine, the appropriate version is `gcc-linaro-14.0.0-2023.06-x86_64_arm-linux-gnueabihf.tar.xz`.

    ```sh
        wget https://snapshots.linaro.org/gnu-toolchain/14.0-2023.06-1/arm-linux-gnueabihf/gcc-linaro-14.0.0-2023.06-x86_64_arm-linux-gnueabihf.tar.xz
        sudo tar xf gcc-linaro-14.0.0-2023.06-x86_64_arm-linux-gnueabihf.tar.xz -C /opt
    ```
    
 3. Get Linux Kernel Sources (try to avoid linux-next which tends to be unstable)

    ```sh
        git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
    ```
    
 4. Move into the repository folder and setup cross-compiler (for ARM 64-bit replace `ARCH=arm` with `ARCH=arm64`):

    ```sh
        cd linux
        export ARCH=arm
        export CROSS_COMPILE=/opt/gcc-linaro-14.0.0-2023.06-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
    ```

 5. Choose the kernel configuration. To do this, you need to know what model of System on a Chip (SoC) is used on your board. 
Run in your Orange Pi PC Board

    ```sh
        sudo modprobe configs; zcat /proc/config.gz > .config
    ```
, and then copy the .config file to your development folder.

    ```sh
        make olddefconfig
    ```

 6. At this point you can modify the configuration using, for instance, `menuconfig`. 

    ```sh
        make menuconfig
    ```

 7. Build the kernel, the modules and the device tree blobs:

    ```sh
        make 
    ```
 To speed up compilation on a multicore machine, add the argument `-j <number_of_cores+1>` to the above command.
 
 8. Installing Modules
To use these modules on your target system, they need to be installed. You can install the modules with the make modules_install command, which will copy them to the appropriate directory (usually /lib/modules/<kernel-version>/ on your target system). Since you're compiling for an ARM device on an x86_64 host, you might be cross-compiling. If that's the case, make modules_install will not install the modules to your host's /lib/modules directory by default; it would install them to a directory within the build directory of the kernel source. You need to specify the INSTALL_MOD_PATH parameter to direct where the modules should be installed.
     
     ```sh
        sudo make modules_install INSTALL_MOD_PATH=/path/to/target/root/filesystem 
     ```
     Replace /path/to/target/root/filesystem with the path to the mounted or extracted root filesystem of your target ARM device.
     
 9. Generate a `uInitrd` file for an Orange Pi with a 32-bit ARM processor
  
  * Step 1: Install Necessary Tools
    Make sure you have the necessary tools installed on your Ubuntu host machine:

    ```sh
        sudo apt update
        sudo apt install u-boot-tools
    ```

  * Step 2: Create the Initial Ramdisk Image (`initrd`)
    You can use `mkinitramfs` or `update-initramfs` to create the `initrd` image. Here is an example using `mkinitramfs`:

    ```sh
        sudo mkinitramfs -d /media/fabricio/ef562603-e8f6-49b8-90af-342297571004/etc/initramfs-tools/ -o initrd.img-<kernel-version> <kernel-version> INSTALL_MOD_PATH=/media/fabricio/ef56203-e8f6-49b8-90af-34229757100  
    ```

    Make sure to replace `<kernel-version>` with the version number of the kernel you have compiled. 
    **Ensure the `initramfs.conf` Exists**: The `initramfs.conf` file should exist in the `/path/to/target/root/filesystem/etc/initramfs-tools/` directory on your build system. If it doesn't, you need to check why it's missing and restore it from backups or reinstall the necessary package.

  * Step 3: Convert the `initrd` to `uInitrd` Using `mkimage`
    Once you have the `initrd` image, you can convert it to a `uInitrd` image with the `mkimage` command:

    ```sh
        mkimage -A arm -O linux -T ramdisk -C none -n "Custom Initrd" -d initrd.img-6.6.0 uInitrd-6.6.0
    ```

### Embedded System(Orange Pi)
I used a Orange Pi (Allwinner H3 processor) to develop and test my modules and drivers. To compile them, you need to download the crosscompilation toolchain.

On Raspbian you can do this with the following command:



Raspberry Pi OS is only installs the latest kernel headers. So, make sure, you are running the latest kernel. You can do this by running: 

```bash
sudo apt upgrade
```

You also need the build utils (make, gcc, ...) but they come preinstalled on Raspbian.

## Content

In this repo you can find examples for:
1. Simple Kernel Module
2. Device Numbers and Device Files
3. Create device file in driver and callbacks
4. GPIO Driver
5. Text LCD Driver
6. PWM Module
7. Temperature Sensor (I2C)
8. Timer in Linux Kernel Modules
9. High Resolution Timer in Linux Kernel Modules
10. Accessing SPI with a Linux Kernel Module (BMP280 sensor again)
11. Using a GPIO Interrupt in a Linux Kernel Module
12. Using Parameters in a Linux Kernel Module
13. IOCTL in a Linux Kernel Module
14. Threads in a Linux Kernel Module
15. Sending a signal from a Linux Kernel Module to an userspace application
16. The poll callback
17. Waitqueues in a Linux Kernel Module
18. Create procfs entries from a Linux Kernel Module
19. Create sysfs entries from a Linux Kernel Module
20. Parse the device tree from a Linux Kernel Module to get the deivce properties of a specific device
21. Device Tree GPIO Driver 
22. Device Tree Driver for I2C Device
23. Dynamical memory management in a Linux Kernel module
24. Serial (UART) Driver
25. Industrial IO compatible driver for an ATMEGA I2C ADC
26. Device Tree SPI Driver (IIO compatible driver for Atmega SPI ADC)
27. Misc Device


## More Information

For more information about my Linux Driver examples check out my [videos and my playlist](https://www.youtube.com/watch?v=x1Y203vH-Dc&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa)

## Support me

If you want to support me, you can buy me a coffee [buymeacoffee.com/johannes4linux](https://www.buymeacoffee.com/johannes4linux).
