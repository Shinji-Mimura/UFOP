from matplotlib import table
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from sklearn.model_selection import cross_val_score
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error
from sklearn.preprocessing import StandardScaler
from tabulate import tabulate
import numpy as np

def load_data():
    return pd.read_csv('../Data/Crimes_Violentos/dados_finais.csv', delimiter=';')



def compare_models(predictions_dict, true_values):
    # predictions_dict é um dicionário que contém as previsões de cada modelo
    # por exemplo, predictions_dict = {'Linear Regression': predictions_lr, 'Decision Tree': predictions_dt, 'Random Forest': predictions_rf}
    # true_values é um array ou lista com os valores reais do conjunto de teste

    # Calculando o MAE de cada modelo
    mae_dict = {}
    for model_name, predictions in predictions_dict.items():
        mae = np.mean(np.abs(predictions - true_values))
        mae_dict[model_name] = mae

    # Criando o gráfico de barras
    plt.figure(figsize=(10, 6))
    plt.bar(mae_dict.keys(), mae_dict.values(), color='skyblue')
    plt.xlabel('Modelos')
    plt.ylabel('Erro Absoluto Médio (MAE)')
    plt.title('Comparação de Desempenho dos Modelos')
    plt.xticks(rotation=45)

    # Exibindo os valores de MAE acima das barras
    for model_name, mae in mae_dict.items():
        plt.text(model_name, mae + 0.001, f'{mae:.3f}', ha='center', va='bottom')

    # Exibindo o gráfico
    plt.tight_layout()
    plt.show()


def perform_eda(data):
    data_transposed = data.describe()

        # Criando a figura de tabela
    # Criando a figura de tabela
    plt.figure(figsize=(12, 8))
    ax = plt.subplot(111, frame_on=False)  # Criando um eixo vazio para a tabela
    ax.xaxis.set_visible(False)  # Removendo o eixo x
    ax.yaxis.set_visible(False)  # Removendo o eixo y

    # Criando a tabela diretamente a partir do DataFrame
    table = pd.plotting.table(ax, data_transposed, loc='center', fontsize=12, colWidths=[0.15]*len(data_transposed.columns))

    # Exibindo a tabela em formato de imagem
    plt.tight_layout()
    plt.savefig('tabela_estatisticas_descritivas.png', dpi=300)
    # Plota um histograma da coluna 'Registros'
    sns.histplot(data['Registros'])
    plt.xlabel('Registros')
    plt.ylabel('Frequência')
    plt.title('Histograma dos Registros')
    plt.savefig(f'../Resultados/Histograma.png')
    plt.show()
  
    # Plota um boxplot com 'Natureza' no eixo X e 'Registros' no eixo Y
    plt.figure(figsize=(10, 6))
    sns.boxplot(x='Natureza', y='Registros', data=data)
    plt.xlabel('Natureza')
    plt.ylabel('Registros')
    plt.title('Boxplot dos Registros por Natureza')
    plt.xticks(rotation=45, ha='right', fontsize=8)  # Rotaciona os rótulos do eixo X
    plt.tight_layout()  # Ajusta o layout para evitar corte dos elementos
    plt.savefig('../Resultados/RegistrosNatureza.png')    
    plt.show()


def prepare_data(data):
    data['Natureza'] = data['Natureza'].astype('category')
    data = pd.get_dummies(data)
    train = data[data['Ano'] < 2021]
    test = data[data['Ano'] == 2021]
    X_train = train.drop('Registros', axis=1)
    X_test = test.drop('Registros', axis=1)
    y_train = train['Registros']
    y_test = test['Registros']
    feature_names = X_train.columns # Save feature names before normalization
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)
    return X_train, X_test, y_train, y_test, feature_names

def train_and_evaluate(models, X_train, X_test, y_train, y_test):
    results = pd.DataFrame(y_test)
    results.index.name = 'Index'
    for model_name, model in models.items():
        cross_val_scores = cross_val_score(model, X_train, y_train, cv=5)
        print(f"Validação cruzada para {model_name}: {cross_val_scores.mean()}")
        model.fit(X_train, y_train)
        predictions = model.predict(X_test)
        predictions = np.round(predictions)
        results[model_name] = predictions
        mae = mean_absolute_error(y_test, predictions)
        print(f"Erro Absoluto Médio (MAE) para {model_name}: {mae}")
    compare_models({model_name: results[model_name] for model_name in models}, y_test)
    return results, models['Random Forest']

def save_results(results):
    results.to_csv('../Resultados/resultados_finais.csv', index=False)

def plot_feature_importance(feature_importance, feature_names):
# Criar um dicionário para mapear as abreviações das características
    plt.figure(figsize=(10, len(feature_names)*0.5))  # Ajusta o tamanho da figura
    plt.barh(feature_names, feature_importance, color='b')
    plt.title('Importância das Características')
    plt.xlabel('Importância')
    plt.ylabel('Características')
    
    # Ajusta o espaçamento para evitar corte dos nomes das características
    plt.tight_layout()
    plt.savefig(f'../Resultados/Importancia_Caracteristicas.png')
    plt.show()
    
def generate_table_image(results):
    fig, ax = plt.subplots(figsize=(10, 6)) # criar um subplot para a tabela

    # criar a tabela no subplot
    table = plt.table(cellText=results.values[:20], colLabels=results.columns, loc="center", cellLoc = 'center')

    # esconder o eixo do gráfico
    ax.axis('off')

    # ajustar o layout
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.scale(1, 1.5)

    plt.savefig("../Resultados/comparativo-algoritmos.png")

    return fig

    
def main():
    data = load_data()
    perform_eda(data)
    X_train, X_test, y_train, y_test, feature_names = prepare_data(data)
    models = {
        "Linear Regression": LinearRegression(),
        "Decision Tree": DecisionTreeRegressor(),
        "Random Forest": RandomForestRegressor(n_estimators=100)
    }
    results, rf_model = train_and_evaluate(models, X_train, X_test, y_train, y_test)
    print(tabulate(results.head(), headers='keys', tablefmt='psql'))
    generate_table_image(results)
    save_results(results)
    plot_feature_importance(rf_model.feature_importances_, feature_names)

if __name__ == "__main__":
    main()
