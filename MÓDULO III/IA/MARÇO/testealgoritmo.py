from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
import pandas as pd
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
# Aqui vai ser com um dado simulado através do sklearn



X,y = make_classification(n_samples=5000, n_features=8, n_informative=5, n_redundant=2, n_classes=2)

print(X.shape, y.shape)

X_train, X_test, y_train, y_test = train_test_split(X,y, test_size=0.2)
print(X_train.shape, X_train.shape, y_train.shape, y_test.shape)

model = RandomForestClassifier()
model.fit(X_train, y_train)

yhat=model.predict(X_test)

acc = accuracy_score(y_test, yhat)
print(acc)