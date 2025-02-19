import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys
import matplotlib.animation as animation

def animate_orbit(file_path, speed=20):
    # Загружаем данные
    data = pd.read_csv(file_path)

    # Извлекаем время
    t_values = data["t"].values
    T = t_values[-1]  # Предполагаем, что последний момент времени — полный оборот Луны

    # Инициализируем график
    fig, ax = plt.subplots(figsize=(8, 8))
    ax.set_xlim(-1.5, 1.5)
    ax.set_ylim(-1.5, 1.5)
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_title("Анимация ограниченной задачи трёх тел")
    ax.grid()
    ax.set_aspect("equal")

    # Орбита Луны
    theta = np.linspace(0, 2 * np.pi, 300)
    moon_orbit_x = np.cos(theta)
    moon_orbit_y = np.sin(theta)
    ax.plot(moon_orbit_x, moon_orbit_y, linestyle="dashed", color="gray", label="Орбита Луны")

    # Земля
    ax.scatter(0, 0, color="blue", s=200, label="Земля")

    # Луна (будет двигаться)
    moon, = ax.plot([], [], "o", color="gray", markersize=8, label="Луна")

    # Тело (будет двигаться по траектории)
    body, = ax.plot([], [], "ro", markersize=5, label="Тело")

    # Линия траектории тела
    trajectory, = ax.plot([], [], "r-", lw=1)

    # Значительно увеличиваем шаг (ускоряем анимацию)
    step = max(1, len(data) // (speed * 50))

    # Обновление кадра
    def update(frame):
        idx = frame * step
        if idx >= len(data):
            return body, trajectory, moon

        t = t_values[idx]  # Берем текущее время из данных

        # Двигаем тело
        body.set_data(data["x"][idx], data["y"][idx])

        # Обновляем линию траектории
        trajectory.set_data(data["x"][:idx], data["y"][:idx])

        # Луна движется по окружности с учетом времени t
        moon_x = np.cos(2 * np.pi * t / T)
        moon_y = np.sin(2 * np.pi * t / T)
        moon.set_data(moon_x, moon_y)

        return body, trajectory, moon

    # Количество кадров теперь меньше
    frames = len(data) // step
    ani = animation.FuncAnimation(fig, update, frames=frames, interval=5, blit=True)

    # Показываем график
    plt.legend()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python animate_orbit.py путь_к_файлу [скорость]")
        sys.exit(1)

    file_path = sys.argv[1]
    
    if len(sys.argv) > 2:
        speed = int(sys.argv[2]) 
        animate_orbit(file_path, speed)
    else:
        animate_orbit(file_path)
