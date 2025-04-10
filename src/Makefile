CC = clang++
CFLAGS = -std=c++17
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lode_solvers -lode_models

SOLVERS_DIR = ode_solvers
SOLVERS_INCLUDE_DIR = $(SOLVERS_DIR)/include
SOLVERS_SRC = $(SOLVERS_DIR)/src/*cpp

MODELS_DIR = ode_models
MODELS_INCLUDE_DIR = $(MODELS_DIR)/include
MODELS_SRC = $(MODELS_DIR)/src/*cpp

LIB_DIR = ../lib
LIB_SOLVERS_TARGET = $(LIB_DIR)/libode_solvers.a
LIB_MODELS_TARGET = $(LIB_DIR)/libode_models.a

APPS_DIR = apps

BIN_DIR = ../bin
BUILD_DIR = ../build

TEST_DIR = tests
TEST_TARGET = $(BIN_DIR)/test_solver
ERROR_TARGET = $(BIN_DIR)/test_error
MAIN_TARGET = $(BIN_DIR)/orbit_solver

PYTHON = python3
SCRIPTS_DIR = ../scripts
PlOT_ORBIT = $(PYTHON) $(SCRIPTS_DIR)/plot_orbit.py
PlOT_TEST = $(PYTHON) $(SCRIPTS_DIR)/plot_test.py
PlOT_ERROR = $(PYTHON) $(SCRIPTS_DIR)/plot_error.py
ANIMATE_ORBITE = $(PYTHON) $(SCRIPTS_DIR)/animate_orbite.py

CSV_DIR = ../data
CSV = $(CSV_DIR)/three_body_orbit.csv
CSV_TEST = $(CSV_DIR)/test.csv
CSV_ERROR = $(CSV_DIR)/test_error.csv

REQUIREMENTS_DIR = ../requirements.txt

TO_FORMAT_FILES := $(wildcard *.cpp) $(wildcard $(SOLVERS_INCLUDE_DIR)/*.hpp) $(SOLVERS_SRC) $(wildcard $(TEST_DIR)/*.cpp)
FORMAT := ../materials/linters/.clang-format

all: calc

req-install:
	@pip install -r $(REQUIREMENTS_DIR)

solvers: $(LIB_SOLVERS_TARGET)
$(LIB_SOLVERS_TARGET): $(wildcard $(SOLVERS_SRC))
	@echo "Собираем $(LIB_SOLVERS_TARGET)..."
	@mkdir -p $(LIB_DIR) $(BUILD_DIR) $(BIN_DIR)
	@for file in $^; do \
		$(CC) $(CFLAGS) -I$(SOLVERS_INCLUDE_DIR) -c $$file -o $(BUILD_DIR)/$$(basename $$(basename $$file)).o; \
	done
	@ar rcs $@ $(BUILD_DIR)/*.o

$(LIB_MODELS_TARGET): $(wildcard $(MODELS_SRC))
	@echo "Собираем $(LIB_MODELS_TARGET)..."
	@mkdir -p $(LIB_DIR) $(BUILD_DIR) $(BIN_DIR)
	@for file in $^; do \
		obj=$$(basename $$(basename $$file)).o; \
		$(CC) $(CFLAGS) -I$(MODELS_INCLUDE_DIR) -c $$file -o $(BUILD_DIR)/$$obj; \
	done
	@ar rcs $@ $(BUILD_DIR)/*.o

$(MAIN_TARGET): $(APPS_DIR)/orbit_solver.cpp $(LIB_SOLVERS_TARGET) $(LIB_MODELS_TARGET)
	@echo "Собираем $(MAIN_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(TEST_TARGET): $(TEST_DIR)/test_solver.cpp $(LIB_SOLVERS_TARGET) $(LIB_MODELS_TARGET)
	@echo "Собираем $(TEST_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

$(ERROR_TARGET): $(TEST_DIR)/test_error.cpp $(LIB_SOLVERS_TARGET) $(LIB_MODELS_TARGET)
	@echo "Собираем $(ERROR_TARGET)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

build: $(LIB_SOLVERS_TARGET) $(MAIN_TARGET) $(TEST_TARGET) $(ERROR_TARGET)

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
	@clang-format -i -style=file:$(FORMAT) $(TO_FORMAT_FILES)

check-style:
	@echo "Проверка стиля кода с помощью clang-format..."
	@clang-format -n -style=file:$(FORMAT) $(TO_FORMAT_FILES)

clean: clean_build clean_bin clean_lib clean_csv

clean_bin:
	@echo "Очистка $(BIN_DIR)..."
	@rm -f $(MAIN_TARGET)
	@rm -f $(TEST_TARGET)
	@rm -f $(ERROR_TARGET)

clean_build:
	@echo "Очистка $(BIN_DIR)..."
	@rm -f $(CSV_DIR)/*.csv

clean_csv:
	@echo "Очистка $(CSV_DIR)..."
	@rm -f $(CSV_DIR)/*.csv

clean_lib:
	@echo "Очистка $(LIB_DIR)..."
	@rm -rf $(LIB_DIR)/*.a