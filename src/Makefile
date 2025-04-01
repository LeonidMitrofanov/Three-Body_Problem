CC = g++
CFLAGS = -std=c++17 -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lODESolver

INCLUDE_DIR = ../ODESolver/include
ODESOLVER_SRC = ../ODESolver/src/ODESolver.cpp
LIB_DIR = ../lib
LIB_TARGET = $(LIB_DIR)/libODESolver.a

TEST_TARGET = test_solver
MAIN_TARGET = orbit_solver

PYTHON = python3
SCRIPTS_PATH = ../scripts
PlOT_ORBIT = $(PYTHON) $(SCRIPTS_PATH)/plot_orbit.py
PlOT_TEST = $(PYTHON) $(SCRIPTS_PATH)/plot_test.py
ANIMATE_ORBITE = $(PYTHON) $(SCRIPTS_PATH)/animate_orbite.py

CSV_PATH = ../data
CSV = $(CSV_PATH)/three_body_orbit.csv
CSV_TEST = $(CSV_PATH)/test.csv

REQUIREMENTS_PATH = ../requirements.txt

TO_FORMAT_FILES := $(wildcard $(*.cpp)) $(wildcard $(INCLUDE_DIR)/*.hpp) $(ODESOLVER_SRC)
FORMAT_PATH := ../materials/linters/.clang-format


all: build

requirements:
	@pip install -r $(REQUIREMENTS_PATH)

$(LIB_TARGET): $(ODESOLVER_SRC)
	@echo "Собираем $(LIB_TARGET)..."
	@mkdir -p $(LIB_DIR)
	@$(CC) $(CFLAGS) -c $< -o $(LIB_DIR)/ODESolver.o
	@ar rcs $@ $(LIB_DIR)/ODESolver.o

$(TEST_TARGET): $(TEST_TARGET).cpp $(LIB_TARGET)
	@echo "Собираем $(TEST_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(MAIN_TARGET): $(MAIN_TARGET).cpp $(LIB_TARGET)
	@echo "Собираем $(MAIN_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

build: $(LIB_TARGET) $(MAIN_TARGET) $(TEST_TARGET)

run_test: $(TEST_TARGET)
	@./$(TEST_TARGET)

run_main: $(MAIN_TARGET)
	@./$(MAIN_TARGET)

$(CSV): run_main
$(CSV_TEST): run_test

plot: $(CSV)
	@echo "Рисуем орбиту..."
	@$(PlOT_ORBIT) $(CSV)

plot_test: $(CSV_TEST)
	@echo "Рисуем график для теста..."
	@$(PlOT_TEST) $(CSV_TEST)

animate: $(CSV)
	@echo "Анимируем движение тела..."
	@$(ANIMATE_ORBITE) $(CSV)

# Форматирование кода
format: check-style
	@echo "Форматирование исходного кода с помощью clang-format..."
	@clang-format -i -style=file:$(FORMAT_PATH) $(TO_FORMAT_FILES)

# Проверка стиля кода
check-style:
	@echo "Проверка стиля кода с помощью clang-format..."
	@clang-format -n -style=file:$(FORMAT_PATH) $(TO_FORMAT_FILES)

clean: clean_main clean_test clean_csv clean_lib

clean_main:
	@echo "Очистка $(MAIN_TARGET)..."
	@rm -f $(MAIN_TARGET)

clean_test:
	@echo "Очистка $(TEST_TARGET)..."
	@rm -f $(TEST_TARGET)

clean_csv:
	@echo "Очистка csv..."
	@rm -f $(CSV_PATH)/*.csv

clean_lib:
	@echo "Очистка библиотеки..."
	@rm -rf $(LIB_DIR)