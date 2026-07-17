import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report

print("Lendo os dados de um Dataframe para uma variavel df:")
df = pd.read_csv("/home/pedrolucas/ADS/Personal_Repository/MÓDULO III/IA/MARÇO/dadoshahaha/iris.data", names = ["A", "B", "C", "D", "class"])
print("Arquivo lido com sucesso!")
print("Dimensoes:", df.shape)

X = df[['A', 'B', 'C', 'D']]
y= df["class"]
print(X.head())
print(y.head())

#Separar em training & test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

enc= LabelEncoder()

y_train = enc.fit_transform(y_train)
model = RandomForestClassifier()
