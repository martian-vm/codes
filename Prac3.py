# 1. Import libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import (confusion_matrix, accuracy_score, precision_score, recall_score, classification_report)
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Input
from tensorflow.keras.callbacks import EarlyStopping

# 2. Load the dataset
df = pd.read_csv("Churn_Modelling.csv")

# 3. Remove unnecessary columns, if present
df = df.drop(columns=["RowNumber", "CustomerId", "Surname"], errors="ignore")
df = df.dropna().copy()

# 5. Encode categorical columns
for col in ["Geography", "Gender"]:
    if col in df.columns:
        df = pd.get_dummies(df, columns=[col], drop_first=True, dtype=int)

# 6. Separate features and target
X = df.drop("Exited", axis=1)
y = df["Exited"]

# 7. Split into training and testing data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

# 8. Scale the input features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# 9. Build the neural network
model = Sequential([
    Input(shape=(X_train.shape[1],)),
    Dense(16, activation="relu"),
    Dense(8, activation="relu"),
    Dense(1, activation="sigmoid")
])

# 10. Compile the model
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])

# 11. Train the model
early_stop = EarlyStopping(monitor="val_loss", patience=5, restore_best_weights=True)
history = model.fit(X_train, y_train, epochs=50, batch_size=32, validation_split=0.2, callbacks=[early_stop], verbose=1)

# 12. Predict on test data
probabilities = model.predict(X_test, verbose=0).ravel()
y_pred = (probabilities >= 0.5).astype(int)

# 13. Evaluate the model
print("\nConfusion Matrix:")
print(confusion_matrix(y_test, y_pred))
print("\nAccuracy:", round(accuracy_score(y_test, y_pred), 4))
print("Precision:", round(precision_score(y_test, y_pred, zero_division=0), 4))
print("Recall:", round(recall_score(y_test, y_pred, zero_division=0), 4))
print("\nClassification Report:")
print(classification_report(y_test, y_pred, zero_division=0))

# 14. Predict for one customer
sample_customer = X_test[0].reshape(1, -1)
churn_probability = model.predict(sample_customer, verbose=0)[0][0]

print("\nSample Customer Churn Probability:",
      round(float(churn_probability), 4))

if churn_probability >= 0.5:
    print("Prediction: Customer is likely to leave the bank.")
else:
    print("Prediction: Customer is likely to stay with the bank.")
