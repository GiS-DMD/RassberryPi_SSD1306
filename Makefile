# 編譯器與編譯選項
CC = aarch64-linux-gnu-gcc
CFLAGS = -I./include
LDFLAGS = -L./lib -lbcm2835

# 目標檔案與輸出路徑
OBJDIR = build
TARGET = $(OBJDIR)/main

# 源碼文件
SRCS = ./src/main.c ./src/ssd1306.c
OBJS = $(OBJDIR)/main.o $(OBJDIR)/ssd1306.o

# 編譯過程
all: $(TARGET)

# 編譯主程序
$(TARGET): $(OBJS)
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	mv $(TARGET) ./

# 個別文件的編譯
$(OBJDIR)/main.o: src/main.c include/ssd1306.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/ssd1306.o: src/ssd1306.c include/ssd1306.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
	rm -rf $(OBJDIR)
	rm -rf ./main

# 方便查看編譯過程
.PHONY: all clean
