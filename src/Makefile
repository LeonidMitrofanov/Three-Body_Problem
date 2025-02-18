CC = g++
CFLAGS = -std=c++17

TARGET = orbit_solver

MY_ODE_LIB = ../ODESolver/src/ODESolver.cpp
SRC_FILES = orbit_solver.cpp $(MY_ODE_LIB)

PYTHON = python3
SCRIPTS_PATH = ../scripts
PlOT_ORBIT = $(PYTHON) $(SCRIPTS_PATH)/plot_orbit.py
PlOT_TEST = $(PYTHON) $(SCRIPTS_PATH)/plot_test.py
ANIMATE_ORBITE = $(PYTHON) $(SCRIPTS_PATH)/animate_orbite.py

CSV_PATH = ../data
CSV = $(CSV_PATH)/three_body_orbit.csv
CSV_TEST = $(CSV_PATH)/test.csv

REQUIREMENTS_PATH = ../requirements.txt

all: build

requirements:
	@pip install -r $(REQUIREMENTS_PATH)


build: $(TARGET)

$(TARGET): $(SRC_FILES)
	@echo "Собираем $(TARGET)..."
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

run: $(TARGET)
	@./$(TARGET)

$(CSV): run
$(CSV_TEST): run

plot: $(CSV)
	@echo "Рисуем орбиту..."
	@$(PlOT_ORBIT) $(CSV)

plot_test: $(CSV_TEST)
	@echo "Рисуем график для теста..."
	@$(PlOT_TEST) $(CSV_TEST)

animate: $(CSV)
	@echo "Анимацию движение тела..."
	@$(ANIMATE_ORBITE) $(CSV)

clean: clean_csv
	@echo "Очистка $(TARGET)..." 
	@rm -f $(TARGET)

clean_csv:
	@echo "Очистка csv..."
	@rm -f $(CSV_PATH)/*.csv