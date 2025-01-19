# ApexBIOS 项目

## 欢迎探索 ApexBIOS！

这是一个开源的 BIOS 项目，旨在为qemu平台提供灵活、可定制的启动固件。我们的目标是创建一个稳定、高效且易于扩展的 BIOS 系统，以满足不同用户的需求。

### 核心功能

- **多指令集支持**：自动检测并初始化 SSE、AVX 和 FPU 指令集，充分发挥 CPU 的计算能力。
- **丰富的硬件兼容性**：支持 Q35、i440FX 等多种芯片组，以及 AHCI、IDE、软盘等多种存储设备。
- **图形化界面**：基于 RAMFB 的图形显示驱动，提供清晰的启动界面和设备信息显示。
- **灵活的启动选项**：可从硬盘设备启动，支持启动设备的自动检测。

### 技术细节

#### 保护模式入口

BIOS 在启动时会进入保护模式，这是通过 `protectedmode.c` 实现的。在保护模式下，BIOS 可以访问更多的内存和系统资源，提供更强大的功能。以下是保护模式入口的主要步骤：

1. **初始化指令集**：检测并初始化 SSE、AVX 和 FPU 指令集。
2. **初始化硬件**：初始化 PIC、PS/2、软盘、RAMFB 等硬件设备。
3. **显示启动信息**：使用 RAMFB 显示启动界面和系统信息。
4. **检测存储设备**：检测并显示 AHCI、IDE、软盘等存储设备的状态。
5. **尝试引导**：从检测到的存储设备中尝试引导系统。

#### 传统读盘 55AA 方式启动

BIOS 支持传统的 55AA 方式启动，这是通过读取硬盘的 MBR（主引导记录）来实现的。具体步骤如下：

1. **清空启动扇区**：使用 `memset` 清空 0x7C00 地址处的 512 字节。
2. **读取 MBR**：使用 `ata_read_lba` 从硬盘的 LBA 0 位置读取 512 字节到 0x7C00 地址。
3. **检查启动标志**：检查 0x7DFE 位置的值是否为 0xAA55，这是有效的 MBR 启动标志。
4. **跳转到启动代码**：如果启动标志有效，跳转到 0x7C00 地址执行启动代码。

### 项目架构

- **保护模式入口**：`protectedmode.c` 作为 BIOS 的核心入口，负责初始化各个硬件组件和系统服务。
- **内存管理**：`memory.c` 提供了高效的内存检测和管理功能，确保系统启动过程中的内存分配和使用。
- **位图字体与图像解析**：`bmpfont.c` 和 `bitmap.c` 实现了位图字体和图像的解析与显示，为图形化界面提供了基础支持。
- **字符串处理**：`cstring.c` 提供了基本的字符串处理功能，方便系统内部的文本操作和显示。
- **字节序转换**：`endianness.c` 实现了不同字节序之间的转换，确保数据在不同硬件平台上的正确传输和处理。
- **硬件驱动**：包括 PCI、PS2、ATAPI、AHCI、软盘等硬件驱动，实现了对各种硬件设备的检测、初始化和操作。

### 开发与贡献

我们欢迎所有对 BIOS 开发感兴趣的开发者加入我们的项目！无论你是硬件专家、软件工程师还是开源爱好者，都可以在这里找到适合自己的贡献方式。

- **代码贡献**：如果你熟悉 C 语言和硬件编程，可以参与代码的编写和优化，帮助我们改进 BIOS 的功能和性能。
- **文档编写**：良好的文档对于项目的成功至关重要。你可以帮助我们编写技术文档、用户手册或开发指南，让其他开发者和用户更容易理解和使用我们的 BIOS。
- **测试与反馈**：在qemu平台上测试 BIOS，提供详细的测试报告和反馈，帮助我们发现和修复潜在的问题。

### 联系我们

- **项目主页**：[https://github.com/ViudiraTech/ApexBIOS](https://github.com/ViudiraTech/ApexBIOS)
