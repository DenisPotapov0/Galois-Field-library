
CC = gcc
CFLAGS = -Wall -Wextra -g -I../src
LDFLAGS = -lm

# Имя тестового исполняемого файла
TARGET = test_Galua_Field_256

# Исходные файлы тестов
TEST_SRCS = test_Galua_Field_256.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Путь к исходникам библиотеки
LIB_SRCS = ../src/Galua_Field_256.c
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Цели
.PHONY: all clean run valgrind help

all: $(TARGET)

# Сборка тестового исполняемого файла
$(TARGET): $(TEST_OBJS) $(LIB_OBJS)
	$(CC) $(TEST_OBJS) $(LIB_OBJS) -o $@ $(LDFLAGS)

# Правило для компиляции .c файлов в .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

../src/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Запуск тестов
run: $(TARGET)
	@echo "========================================"
	@echo "Запуск тестов"
	@echo "========================================"
	./$(TARGET)
	@echo "========================================"
	@echo "Все тесты завершены"

# Очистка
clean:
	rm -f $(TEST_OBJS) $(LIB_OBJS) $(TARGET)
	rm -f *.gcda *.gcno *.gcov

# Информация
help:
	@echo "Доступные цели для тестов:"
	@echo "  all      - собрать тесты"
	@echo "  run      - собрать и запустить тесты"
	@echo "  clean    - очистить файлы тестов"
