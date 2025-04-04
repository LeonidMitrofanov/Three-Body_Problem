import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_error(file_paths):
    # Создаем фигуру с четырьмя субплотами
    fig, axs = plt.subplots(2, 2, figsize=(15, 10))
    
    for file_path in file_paths:
        # Читаем CSV-файл
        data = pd.read_csv(file_path)
        
        # Графики для y1
        axs[0, 0].plot(data['h'], data['e_y1'], marker='o', label=f'{file_path} (y1)')
        axs[0, 1].plot(data['h'], data['e_y1/h^4'], marker='o', label=f'{file_path} (y1)')
        
        # Графики для y2
        axs[1, 0].plot(data['h'], data['e_y2'], marker='o', label=f'{file_path} (y2)')
        axs[1, 1].plot(data['h'], data['e_y2/h^4'], marker='o', label=f'{file_path} (y2)')
    
    # Настройка графиков для y1
    axs[0, 0].set_title('Ошибка e от шага h для y1')
    axs[0, 0].set_xlabel('h')
    axs[0, 0].set_ylabel('e')
    axs[0, 0].grid(True)
    axs[0, 0].legend()
    
    axs[0, 1].set_title('Отношение e/h^4 от шага h для y1')
    axs[0, 1].set_xlabel('h')
    axs[0, 1].set_ylabel('e/h^4')
    axs[0, 1].grid(True)
    axs[0, 1].legend()
    
    # Настройка графиков для y2
    axs[1, 0].set_title('Ошибка e от шага h для y2')
    axs[1, 0].set_xlabel('h')
    axs[1, 0].set_ylabel('e')
    axs[1, 0].grid(True)
    axs[1, 0].legend()
    
    axs[1, 1].set_title('Отношение e/h^4 от шага h для y2')
    axs[1, 1].set_xlabel('h')
    axs[1, 1].set_ylabel('e/h^4')
    axs[1, 1].grid(True)
    axs[1, 1].legend()
    
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python plot_script.py путь_к_файлу1 [путь_к_файлу2 ...]")
        sys.exit(1)
    
    plot_error(sys.argv[1:])