CC = g++
CFLAGS = -std=c++17
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lODESolvers

INCLUDE_DIR = ../ODESolvers/include
ODESOLVERS_SRC = ../ODESolvers/src/*cpp
LIB_DIR = ../lib
LIB_TARGET = $(LIB_DIR)/libODESolvers.a

BIN_DIR = ../bin

TEST_DIR = test
TEST_TARGET = $(BIN_DIR)/test_solver
ERROR_TARGET = $(BIN_DIR)/test_error
MAIN_TARGET = $(BIN_DIR)/orbit_solver

PYTHON = python3
SCRIPTS_DIR = ../scripts
PlOT_ORBIT = $(PYTHON) $(SCRIPTS_DIR)/plot_orbit.py
PlOT_TEST = $(PYTHON) $(SCRIPTS_DIR)/plot_test.py
PlOT_ERROR = $(PYTHON) $(SCRIPTS_DIR)/plot_error.py
ANIMATE_ORBITE = $(PYTHON) $(SCRIPTS_DIR)/animate_orbite.py

CSV_PATH = ../data
CSV = $(CSV_PATH)/three_body_orbit.csv
CSV_TEST = $(CSV_PATH)/test.csv
CSV_ERROR = $(CSV_PATH)/test_error.csv

REQUIREMENTS_PATH = ../requirements.txt

TO_FORMAT_FILES := $(wildcard *.cpp) $(wildcard $(INCLUDE_DIR)/*.hpp) $(ODESOLVERS_SRC) $(wildcard $(TEST_DIR)/*.cpp)
FORMAT_PATH := ../materials/linters/.clang-format

all: calc

req-install:
	@pip install -r $(REQUIREMENTS_PATH)

lib: $(LIB_TARGET)
$(LIB_TARGET): $(ODESOLVERS_SRC)
	@echo "Собираем $(LIB_TARGET)..."
	@mkdir -p $(LIB_DIR) $(BIN_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $(BIN_DIR)/ODESolver.o
	@ar rcs $@ $(BIN_DIR)/ODESolver.o

$(TEST_TARGET): $(TEST_DIR)/test_solver.cpp $(LIB_TARGET)
	@echo "Собираем $(TEST_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(MAIN_TARGET): orbit_solver.cpp $(LIB_TARGET)
	@echo "Собираем $(MAIN_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(ERROR_TARGET): $(TEST_DIR)/test_error.cpp $(LIB_TARGET)
	@echo "Собираем $(ERROR_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

build: $(LIB_TARGET) $(MAIN_TARGET) $(TEST_TARGET) $(ERROR_TARGET)

calc: calc_main

calc_all: calc_test calc_error calc_main

calc_main: $(MAIN_TARGET)
	@echo "Производим вычисления для $(CSV)..."
	@$(MAIN_TARGET) $(CSV)

calc_test: $(TEST_TARGET)
	@echo "Производим вычисления для $(CSV_TEST)..."
	@$(TEST_TARGET) $(CSV_TEST)
	
calc_error: $(ERROR_TARGET)
	@echo "Производим вычисления для $(CSV_ERROR)..."
	@$(ERROR_TARGET) $(CSV_ERROR)

$(CSV): calc_main
$(CSV_TEST): calc_test
$(CSV_ERROR): calc_error

plot_orbit: $(CSV)
	@echo "Рисуем орбиту..."
	@$(PlOT_ORBIT) $(CSV)

plot_test: $(CSV_TEST)
	@echo "Рисуем график для теста..."
	@$(PlOT_TEST) $(CSV_TEST)

plot_error: $(CSV_ERROR)
	@echo "Рисуем график ошибок..."
	@$(PlOT_ERROR) $(CSV_ERROR)

animation: $(CSV)
	@echo "Анимируем движение тела..."
	@$(ANIMATE_ORBITE) $(CSV)

format: check-style
	@echo "Форматирование исходного кода с помощью clang-format..."
	@clang-format -i -style=file:$(FORMAT_PATH) $(TO_FORMAT_FILES)

check-style:
	@echo "Проверка стиля кода с помощью clang-format..."
	@clang-format -n -style=file:$(FORMAT_PATH) $(TO_FORMAT_FILES)

clean: clean_main clean_test clean_error clean_csv clean_lib

clean_main:
	@echo "Очистка $(MAIN_TARGET)..."
	@rm -f $(MAIN_TARGET)

clean_test:
	@echo "Очистка $(TEST_TARGET)..."
	@rm -f $(TEST_TARGET)

clean_error:
	@echo "Очистка $(ERROR_TARGET)..."
	@rm -f $(ERROR_TARGET)

clean_csv:
	@echo "Очистка csv..."
	@rm -f $(CSV_PATH)/*.csv

clean_lib:
	@echo "Очистка библиотеки..."
	@rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/ODESolver.o