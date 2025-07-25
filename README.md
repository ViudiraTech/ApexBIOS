# ApexBIOS Project

## Welcome to explore ApexBIOS!

This is an open source BIOS project that aims to provide flexible and customizable boot firmware for the qemu platform. Our goal is to create a stable, efficient and easily extensible BIOS system to meet the needs of different users.

### Core functions

- **Multiple instruction set support**: Automatically detect and initialize SSE, AVX and FPU instruction sets to give full play to the computing power of the CPU.
- **Rich hardware compatibility**: Supports multiple chipsets such as Q35, i440FX, and multiple storage devices such as AHCI, IDE, and floppy disks.
- **Graphical interface**: Graphical display driver based on RAMFB, providing a clear startup interface and device information display.
- **Flexible startup options**: Can be started from a hard disk device, supporting automatic detection of the startup device.

### Technical details

#### Protected mode entry

BIOS will enter protected mode at startup, which is implemented by `protectedmode.c`. In protected mode, BIOS can access more memory and system resources, providing more powerful functions. The following are the main steps of protected mode entry:

1. **Initialize instruction set**: Detect and initialize SSE, AVX and FPU instruction sets.
2. **Initialize hardware**: Initialize PIC, PS/2, floppy disk, RAMFB and other hardware devices.
3. **Display startup information**: Use RAMFB to display the startup interface and system information.
4. **Detect storage device**: Detect and display the status of storage devices such as AHCI, IDE, floppy disk.
5. **Try to boot**: Try to boot the system from the detected storage device.

#### Traditional disk reading 55AA method boot

BIOS supports traditional 55AA booting, which is achieved by reading the MBR (Master Boot Record) of the hard disk. The specific steps are as follows:

1. **Clear boot sector**: Use `memset` to clear 512 bytes at address 0x7C00.
2. **Read MBR**: Use `ata_read_lba` to read 512 bytes from LBA 0 of the hard disk to address 0x7C00.
3. **Check boot flag**: Check if the value at position 0x7DFE is 0xAA55, which is a valid MBR boot flag.
4. **Jump to boot code**: If the boot flag is valid, jump to address 0x7C00 to execute the boot code.

### Project architecture

- **Protected mode entry**: `protectedmode.c` is the core entry of BIOS, responsible for initializing various hardware components and system services.
- **Memory management**: `memory.c` provides efficient memory detection and management functions to ensure memory allocation and use during system startup.
- **Bitmap font and image parsing**: `bmpfont.c` and `bitmap.c` implement the parsing and display of bitmap fonts and images, providing basic support for the graphical interface.
- **String processing**: `cstring.c` provides basic string processing functions to facilitate text operations and display within the system.
- **Byte order conversion**: `endianness.c` implements conversion between different byte orders to ensure correct transmission and processing of data on different hardware platforms.
- **Hardware driver**: Including PCI, PS2, ATAPI, AHCI, floppy disk and other hardware drivers, realizing the detection, initialization and operation of various hardware devices.

### Development and contribution

We welcome all developers interested in BIOS development to join our project! Whether you are a hardware expert, software engineer or open source enthusiast, you can find a contribution method that suits you here.

- **Code Contribution**: If you are familiar with C language and hardware programming, you can participate in code writing and optimization to help us improve the functions and performance of BIOS.

- **Documentation**: Good documentation is crucial to the success of the project. You can help us write technical documents, user manuals or development guides to make it easier for other developers and users to understand and use our BIOS.

- **Testing and Feedback**: Test the BIOS on the qemu platform, provide detailed test reports and feedback, and help us find and fix potential problems.

### Contact us

- **Project Homepage**: [https://github.com/ViudiraTech/ApexBIOS](https://github.com/ViudiraTech/ApexBIOS)
