#!/bin/bash

# Exit on error
set -e

echo "Compiling JavaInit with GraalVM native-image..."

# Create build directory
mkdir -p build/javaos

# Compile Java classes to native binary
native-image \
  --no-fallback \
  --static \
  -march=x86-64 \
  -cp /home/ben/Documents/GitHub/java-os/java-ui/out/production/java-ui \
  org.javaos.init.JavaInit \
  build/javaos/javainit


echo "Native image compilation complete."

# Create initramfs directory structure
echo "Setting up initramfs structure..."
rm -rf initramfs_root
mkdir -p initramfs_root/bin
mkdir -p initramfs_root/dev
mkdir -p initramfs_root/proc
mkdir -p initramfs_root/sys

# Copy native binary as init
echo "Copying native binary to initramfs..."
cp build/javaos/javainit initramfs_root/init
chmod +x initramfs_root/init

echo "Initramfs setup complete."
