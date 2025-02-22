import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_test(file_paths):
    plt.figure(figsize=(8, 6))

    for file_path in file_paths:
        data = pd.read_csv(file_path)
        x_column = "t" if "t" in data.columns else data.columns[0]
        y_columns = [col for col in data.columns if col != x_column]

        for y_col in y_columns:
            plt.plot(data[x_column], data[y_col], label=f"{file_path} - {y_col}")
    
    plt.xlabel(x_column)
    plt.ylabel("y")
    plt.legend()
    plt.title("Графики из CSV-файлов")
    plt.grid()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python plot_test.py путь_к_файлу1 [путь_к_файлу2 ...]")
        sys.exit(1)

    plot_test(sys.argv[1:])
