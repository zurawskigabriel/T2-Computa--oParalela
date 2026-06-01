import sys
import csv
import plotly.graph_objects as go

ARQUIVO = "resultados.txt"

# Leitura do arquivo CSV gerado pelo benchmark.sh
tamanhos = []
tempos = []

with open(ARQUIVO, newline="") as arquivo_csv:
    leitor = csv.DictReader(arquivo_csv)
    for linha in leitor:
        tamanhos.append(int(linha["tamanho"]))
        tempos.append(float(linha["tempo_segundos"]))

# Gráfico de linha com Plotly
figura = go.Figure()

figura.add_trace(go.Scatter(
    x=tamanhos,
    y=tempos,
    mode="lines+markers",
    name="Tempo medido",
    line=dict(color="#378ADD", width=2),
    marker=dict(size=8, color="#185FA5"),
))

figura.update_layout(
    title="Crescimento do tempo de execução — Multiplicação de Matrizes (sequencial)",
    xaxis_title="Tamanho da matriz (N x N)",
    yaxis_title="Tempo de execução (segundos)",
    xaxis=dict(tickmode="array", tickvals=tamanhos),
    hovermode="x unified",
    template="plotly_white",
    font=dict(size=13),
)

figura.write_html("benchmarkGrafico.html")
print("Gráfico salvo em: benchmarkGrafico.html")
