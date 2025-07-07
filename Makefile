# WIRC - Wii IRC Client
# Correct devkitPPC Makefile

TARGET := WIRC
BUILD := build
SOURCE := source
INCLUDE := include
LLIBS := -logc -lwiiuse -lbte -lusb -lfat -lm

# Detect devkitPro install
ifeq ($(DEVKITPRO),)
$(error DEVKITPRO is not set. Please run: source /etc/profile.d/devkit-env.sh)
endif

# Toolchain
CC := $(DEVKITPPC)/bin/powerpc-eabi-gcc
CXX := $(DEVKITPPC)/bin/powerpc-eabi-g++
OBJCOPY := $(DEVKITPPC)/bin/powerpc-eabi-objcopy

CFLAGS := -g -O2 -Wall -mcpu=750 -meabi -mhard-float -mrvl \
-I$(DEVKITPRO)/libogc/include

LDFLAGS := -g -mcpu=750 -meabi -mhard-float -mrvl -Wl,-Map,$(TARGET).map \
-L$(DEVKITPRO)/libogc/lib/wii -specs=nosys.specs

OBJS := $(patsubst $(SOURCE)/%.c,$(BUILD)/%.o,$(wildcard $(SOURCE)/*.c))

.PHONY: all clean

all: $(TARGET).dol

$(TARGET).dol: $(TARGET).elf
	@echo "-> Converting ELF to DOL..."
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf: $(OBJS)
	@echo "-> Linking ELF..."
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BUILD)/%.o: $(SOURCE)/%.c
	@mkdir -p $(dir $@)
	@echo "-> Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).dol
