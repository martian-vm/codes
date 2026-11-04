
# 1. Import libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.metrics import silhouette_score

# 2. Load dataset
df = pd.read_csv("sales_data_sample.csv", encoding="latin1")

# 3. Select numerical features for clustering
features = ["QUANTITYORDERED", "PRICEEACH", "SALES"]
X = df[features].copy()
X = X.replace([np.inf, -np.inf], np.nan)
X = X.dropna()

# 5. Scale the features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# 6. Elbow Method
inertia_values = []
k_values = range(1, 11)

for k in k_values:
    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
    kmeans.fit(X_scaled)
    inertia_values.append(kmeans.inertia_)

# 7. Plot Elbow graph
plt.figure(figsize=(8, 5))
plt.xlabel("Number of Clusters (K)")
plt.ylabel("Inertia (WCSS)")
plt.title("Elbow Method for Optimal K")
plt.xticks(list(k_values))
plt.grid(True)
plt.plot(k_values, inertia_values, marker="o")
plt.show()

# 8. Select K after examining the elbow graph
optimal_k = 3
kmeans = KMeans(n_clusters=optimal_k, random_state=42, n_init=10)

# 9. Fit the final model and assign cluster labels
clusters = kmeans.fit_predict(X_scaled)
X["Cluster"] = clusters

# 10. Display cluster counts
print("\nNumber of records in each cluster:")
print(X["Cluster"].value_counts().sort_index())

# 11. Display cluster-wise averages
print("\nCluster-wise average values:")
print(X.groupby("Cluster")[features].mean().round(2))

# 12. Evaluate clustering with silhouette score
if len(set(clusters)) > 1:
    print("\nSilhouette Score:", round(silhouette_score(X_scaled, clusters), 4))




















# 13. Visualize clusters using PCA
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

plt.figure(figsize=(8, 5))
plt.scatter(
    X_pca[:, 0],
    X_pca[:, 1],
    c=clusters,
    cmap="viridis",
    s=20
)
plt.xlabel("Principal Component 1")
plt.ylabel("Principal Component 2")
plt.title("K-Means Sales Clusters")
plt.colorbar(label="Cluster")
plt.show()
