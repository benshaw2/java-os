# Java-OS: A Custom Linux-Based Operating System for Mobile and Desktop

![Architecture](https://img.shields.io/badge/Architecture-x86__64%20%7C%20ARM64-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Pre--alpha-red)

---

## 🧭 Overview

**Java-OS** is a Linux-based operating system inspired by **Ubuntu Touch**, aimed at delivering a full-featured, privacy-respecting mobile experience while also supporting traditional desktop environments.

Built from the ground up using custom kernels and minimal root filesystems, the OS supports both **x86_64** and **ARM64** (e.g., Raspberry Pi, PinePhone, ARM laptops) architectures.

### Key Features:
- A hybrid **mobile/desktop** experience
- Clean shell-based bootstrap (BusyBox)
- Modular design for UI, drivers, and user-space
- Compatible with both **QEMU** and real hardware

---

## 📸 Screenshots (WIP)

> UI is in early design stages. Expect updates as development progresses.

---

## 🚀 Features & Goals

- ✅ **Custom kernel (x86_64 + ARM64)**
- ✅ **BusyBox init system**
- ✅ **Root filesystem via CPIO initramfs**
- ⬜ **UI built in Java or lightweight graphics framework**
- ⬜ **Telephony (calls, SMS, data)**
- ⬜ **Package manager for updates**
- ⬜ **Touchscreen input, power mgmt, sleep modes**
- ⬜ **Secure sandboxing (Flatpak or custom)**
- ⬜ **Application layer**

---

## 🧪 Current Status

| Component       | x86_64             | ARM64              |
|----------------|--------------------|--------------------|
| Kernel boots    | ✅                  | ✅                  |
| Shell launches  | ✅ `/bin/sh`        | ✅ `/bin/sh`        |
| QEMU works      | ✅                  | ✅                  |
| Init system     | ✅ BusyBox          | ✅ BusyBox          |
| UI layer        | 🚧 WIP              | 🚧 WIP              |
| Real hardware   | 🚧 Planned          | 🚧 Planned          |

---

## 🏗️ Build Instructions (Manual)

### ✅ Prerequisites

- `gcc`, `make`, `libncurses-dev`, `qemu`, `busybox`
- Cross-compilers:
  - `aarch64-linux-gnu-gcc` (for ARM64)
- Optional: `git-filter-repo`, `cpio`, `xz-utils`

---

### 💻 Build Steps

#### 1. **Clone Project**

```bash
git clone https://github.com/benshaw2/java-os.git
cd java-os
```

#### 2. **Build the Linux Kernel**

<details>
<summary><strong>For ARM64 (e.g. Raspberry Pi, QEMU)</strong></summary>

```bash
cd linux-arm64-build

# Configure for ARM64 (virt machine)
make ARCH=arm64 defconfig

# Build using cross-compiler
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
```

This will produce a kernel image at:

```bash
arch/arm64/boot/Image
```

</details>

<details>
<summary><strong>For x86_64 (QEMU or PC hardware)</strong></summary>

```bash
cd linux-x86_64-build

# Configure defaults
make defconfig

# Build
make -j$(nproc)
```

This will produce a kernel image at:

```bash
arch/x86/boot/bzImage
```

</details>

#### 3. **Build BusyBox (Static)**

```bash
cd busybox-source

# Generate default config for ARM64
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig

# Enable static binary support
sed -i 's/# CONFIG_STATIC is not set/CONFIG_STATIC=y/' .config

# Build and install
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- install
```

This will install files to:

```bash
busybox-source/_install/
```

#### 4. **Create Initramfs (Root Filesystem)**

```bash
cd busybox-source/_install

# Create basic directory structure
mkdir -p proc sys dev etc/init.d

# Add init script
echo -e '#!/bin/sh\nmount -t proc proc /proc\nexec /bin/sh' > etc/init.d/rcS
chmod +x etc/init.d/rcS

# Set init link
ln -sf /bin/busybox init

# Package initramfs
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../../../arm64-rootfs.cpio.gz
```

This creates a minimal root filesystem using BusyBox and your init script.

#### 5. **Boot with QEMU**

<details>
<summary><strong>ARM64 (virt machine)</strong></summary>

```bash
qemu-system-aarch64 \
  -M virt \
  -cpu cortex-a53 \
  -m 512M \
  -nographic \
  -kernel linux-arm64-build/arch/arm64/boot/Image \
  -initrd arm64-rootfs.cpio.gz \
  -append "console=ttyAMA0 rdinit=/bin/sh"
```

</details>

<details>
<summary><strong>x86_64</strong></summary>

```bash
qemu-system-x86_64 \
  -m 512M \
  -nographic \
  -kernel linux-x86_64-build/arch/x86/boot/bzImage \
  -initrd x86_64-rootfs.cpio.gz \
  -append "console=ttyS0 rdinit=/bin/sh"
```

</details>

---

✅ **Result:**  
If everything works, you should be dropped into a shell prompt.

---

