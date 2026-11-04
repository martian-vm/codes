
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, classification_report

# Load dataset (SMS Spam Collection)
df = pd.read_csv("spam.csv", encoding="latin1")
df = df[["v1", "v2"]]
df.columns = ["label", "message"]

# Convert labels: ham = 0, spam = 1
df["label"] = df["label"].map({"ham": 0, "spam": 1})

df = df.dropna(subset=["label", "message"])

X = df["message"]
y = df["label"]

# Split dataset
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

# Convert text into numerical features
vectorizer = TfidfVectorizer()
X_train = vectorizer.fit_transform(X_train)
X_test = vectorizer.transform(X_test)

# KNN classification
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
knn_pred = knn.predict(X_test)

# SVM classification
svm = SVC(kernel="linear")
svm.fit(X_train, y_train)
svm_pred = svm.predict(X_test)

# Compare performance
for name, pred in [("KNN", knn_pred), ("SVM", svm_pred)]:
    print("\n", name)
    print("Accuracy:", accuracy_score(y_test, pred))
    print(classification_report(y_test, pred, labels=[0, 1], target_names=["Not Spam", "Spam"], zero_division=0))
