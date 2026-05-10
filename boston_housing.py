# Step 1: Import libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense

from google.colab import files
uploaded = files.upload()

import pandas as pd

df = pd.read_csv("1_boston_housing.csv")

df.head()

# Clean column names (important)
df.columns = df.columns.str.replace('"', '')

# Step 3: Handle missing values
df.fillna(df.mean(), inplace=True)

# Step 4: Split features and target
X = df.drop("MEDV", axis=1)   # Features
y = df["MEDV"]                # Target (house price)

# Step 5: Train-test split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

# Step 6: Feature scaling (VERY IMPORTANT)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Step 7: Build Deep Neural Network
model = Sequential([
    Dense(64, activation='relu'),
    Dense(32, activation='relu'),
    Dense(1)
])

# Step 8: Compile model
model.compile(optimizer='adam', loss='mse')

# Step 9: Train model
model.fit(X_train, y_train, epochs=30, verbose=0)

# Step 10: Evaluate model
loss = model.evaluate(X_test, y_test)
print("Loss (MSE):", loss)

# Step 11: Predictions
pred = model.predict(X_test)

# Step 12: Compare Actual vs Predicted
result = pd.DataFrame({
    "Actual": y_test.values,
    "Predicted": pred.flatten()
})

print("\nActual vs Predicted:\n")
print(result.head(10))

# Step 13 (Optional): Add error column
result["Error"] = result["Actual"] - result["Predicted"]

print("\nWith Error:\n")
print(result.head(10))