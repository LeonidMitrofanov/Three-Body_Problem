import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_error(file_paths):
    # Создаем фигуру с двумя субплотами
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
    
    for file_path in file_paths:
        # Читаем CSV-файл
        data = pd.read_csv(file_path)
        
        ax1.plot(data['h'], data['e'], marker='o', label=file_path)
        ax2.plot(data['h'], data['e/h^4'], marker='o', label=file_path)
    
    # Настройка первого графика
    ax1.set_title('Зависимость ошибки(e) от шага(h)')
    ax1.set_xlabel('h')
    ax1.set_ylabel('e')
    ax1.grid(True)
    ax1.legend()
    
    # Настройка второго графика
    ax2.set_title('Зависимость ошибки(e/h^4) от шага(h)')
    ax2.set_xlabel('h')
    ax2.set_ylabel('e/h^4')
    ax2.grid(True)
    ax2.legend()
    
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python plot_script.py путь_к_файлу1 [путь_к_файлу2 ...]")
        sys.exit(1)
    
    plot_error(sys.argv[1:])