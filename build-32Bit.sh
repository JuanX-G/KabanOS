#!/usr/bin/env bash
set -e

BUILD=./build
ISO=iso

echo "[*] Cleaning..."
rm -rf $BUILD
mkdir -p $BUILD

echo "[*] Assembling ASM files..."

ASM_FILES=$(find kernel -name "*.asm")

for f in $ASM_FILES; do
    name=$(basename "$f" .asm)
    echo "  ASM $f"
    nasm -f elf32 "$f" -o "$BUILD/$name.o"
done

echo "[*] Compiling C files..."

C_FILES=$(find kernel -name "*.c")

for f in $C_FILES; do
    name=$(basename "$f" .c)
    echo "  C   $f"
    x86_64-elf-gcc \
        -m32 \
        -ffreestanding \
        -fno-stack-protector \
        -fno-pic \
        -O2 \
	-mno-sse \
        -Wall \
        -Wextra \
        -Ikernel \
        -c "$f" \
        -o "$BUILD/$name.o"
done

echo "[*] Linking kernel..."

BOOT="$BUILD/boot32.o"

if [ ! -f "$BOOT" ]; then
    echo "ERROR: boot32.o not found!"
    exit 1
fi

OBJS=$(ls $BUILD/*.o | grep -v boot32.o)

x86_64-elf-ld \
    -m elf_i386 \
    -T kernel/linker.ld \
    $BOOT \
    $OBJS \
    -o $BUILD/kernel.elf

echo "[*] Building ISO..."

mkdir -p $ISO/boot/grub
cp $BUILD/kernel.elf $ISO/boot/
cp grub/grub.cfg $ISO/boot/grub/

grub-mkrescue -o os.iso $ISO

echo
echo "[#] Build complete"
echo

