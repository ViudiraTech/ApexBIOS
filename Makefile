ifeq ($(VERBOSE), 1)
  V=
  Q=
else
  V=@printf "\033[1;32m[Build]\033[0m $@ ...\n";
  Q=@
endif

ASM			= nasm
ASMFLAGS	= -fbin

CC			= gcc
CFLAGS		= -m32 -ffreestanding -fno-pic -w -Os -I ./src/include/

LD			= ld
LDFLAGS		= -nostdlib -static -T scripts/linker.ld

SRCDIR		:= src
OBJDIR		:= build

rwildcard	= $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
reverse		= $(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1)))) $(firstword $(1))
SRC			= $(call rwildcard,$(SRCDIR),*.c)
OBJS		= $(call reverse,$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC)))

OUTFILE		= bios.rom

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(V)$(CC) $(CFLAGS) -c $^ -o $@

build: clean $(OBJS)
	@$(LD) $(LDFLAGS) $(OBJS) src/lib/logo.lib src/lib/EPA.lib -o build/c_entry.bin
	@printf "\n\033[1;32m[LINK]\033[0m Linking..."

	@stat -L -c "" build/c_entry.bin
	@$(ASM) $(ASMFLAGS) src/entry16.asm -o $(OUTFILE)
	@printf "\033[1;32m[Done]\033[0m Compilation complete.\n\n"

clean:
	@rm -rf build bios.rom
	@printf "\033[1;32m[Done]\033[0m Clean done.\n\n"

run:
	qemu-system-x86_64 -bios $(OUTFILE) -serial stdio -vga none -device ramfb -m 256M
