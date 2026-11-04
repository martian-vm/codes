
import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

# 1. Load the dataset
df = pd.read_csv("uber.csv")

# 2. Select required columns
columns = ["fare_amount", "pickup_longitude", "pickup_latitude", "dropoff_longitude", "dropoff_latitude", "passenger_count"]
df = df[columns].copy()

# 3. Clean missing and invalid values
df = df.replace([np.inf, -np.inf], np.nan).dropna()
df = df[(df["fare_amount"] > 0) & (df["passenger_count"] > 0) &
    (df["pickup_longitude"].between(-180, 180)) & (df["dropoff_longitude"].between(-180, 180)) &
    (df["pickup_latitude"].between(-90, 90)) & (df["dropoff_latitude"].between(-90, 90))].copy()

# 4. Calculate geographic distance using the Haversine formula
def haversine_distance(lat1, lon1, lat2, lon2):
    earth_radius = 6371  # kilometres
    lat1, lon1, lat2, lon2 = np.radians([lat1, lon1, lat2, lon2])
    dlat = lat2 - lat1
    dlon = lon2 - lon1
    a = (np.sin(dlat / 2) ** 2 + np.cos(lat1) * np.cos(lat2) * np.sin(dlon / 2) ** 2)
    return 2 * earth_radius * np.arcsin(np.sqrt(np.clip(a, 0, 1)))

df["distance_km"] = haversine_distance(df["pickup_latitude"], df["pickup_longitude"], df["dropoff_latitude"], df["dropoff_longitude"])

# 5. Select features and target
features = ["pickup_longitude", "pickup_latitude", "dropoff_longitude", "dropoff_latitude", "passenger_count", "distance_km"]

X = df[features]
y = df["fare_amount"]

# 6. Split into training and testing data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 7. Train Linear Regression
linear_model = LinearRegression()
linear_model.fit(X_train, y_train)
linear_predictions = linear_model.predict(X_test)

# 8. Train Random Forest Regression
forest_model = RandomForestRegressor(n_estimators=100, random_state=42, n_jobs=-1)
forest_model.fit(X_train, y_train)
forest_predictions = forest_model.predict(X_test)

# 9. Evaluate the models
def evaluate_model(name, actual, predicted):
    mae = mean_absolute_error(actual, predicted)
    rmse = np.sqrt(mean_squared_error(actual, predicted))
    r2 = r2_score(actual, predicted)

    print(f"\n{name}")
    print(f"MAE  : {mae:.2f}")
    print(f"RMSE : {rmse:.2f}")
    print(f"R2   : {r2:.4f}")

evaluate_model("Linear Regression", y_test, linear_predictions)
evaluate_model("Random Forest Regression", y_test, forest_predictions)

# 10. Predict a sample ride fare
sample_ride = pd.DataFrame([{"pickup_longitude": -73.985, "pickup_latitude": 40.758,
    "dropoff_longitude": -73.978, "dropoff_latitude": 40.752,
    "passenger_count": 1, "distance_km": haversine_distance(40.758, -73.985, 40.752, -73.978)}])

predicted_fare = forest_model.predict(sample_ride)[0]
print(f"\nPredicted sample fare: {predicted_fare:.2f}")

predicted_fare = linear_model.predict(sample_ride)[0]
print(f"\nPredicted sample fare: {predicted_fare:.2f}")
