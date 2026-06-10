from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split

iris = load_iris()

X = iris.data
y = iris.target

X_train, X_test, y_train, y_test= train_test_split(X, y, test_size= 0.2)

model = RandomForestClassifier()
model.fit(X_train, y_train)
yhat = model.predict(X_test)
acuracia = accuracy_score(y_test, yhat)

print(acuracia)