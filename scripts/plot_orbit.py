import pandas as pd
import matplotlib.pyplot as plt
import sys
import numpy as np

def plot_orbit(file_path):
    data = pd.read_csv(file_path)

    # Настройка графика
    plt.figure(figsize=(8, 8))

    # Рисуем орбиту Луны (окружность радиусом 1)
    theta = np.linspace(0, 2 * np.pi, 300)
    moon_orbit_x = np.cos(theta)
    moon_orbit_y = np.sin(theta)
    plt.plot(moon_orbit_x, moon_orbit_y, linestyle="dashed", color="gray", label="Орбита Луны")

    # Рисуем траекторию тела
    plt.plot(data["x"], data["y"], label="Траектория тела")

    # Рисуем Землю в центре
    plt.scatter(0, 0, color="blue", s=200, label="Земля")

    # Оформление
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.title("Ограниченная задача трёх тел")
    plt.grid()
    plt.axis("equal")  # Сохраняем пропорции
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Использование: python plot_orbit.py путь_к_файлу")
        sys.exit(1)
    
    plot_orbit(sys.argv[1])
