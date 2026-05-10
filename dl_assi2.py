import tensorflow as tf
from tensorflow.keras.datasets import imdb
from tensorflow.keras.preprocessing.sequence import pad_sequences
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Embedding, LSTM, Dense

# Load Dataset
(x_train, y_train), (x_test, y_test) = imdb.load_data(num_words=10000)

# Padding
x_train = pad_sequences(x_train, maxlen=200)
x_test = pad_sequences(x_test, maxlen=200)

# Create Model
model = Sequential()

model.add(Embedding(10000, 128, input_length=200))

model.add(LSTM(64))

model.add(Dense(1, activation='sigmoid'))

# Compile Model
model.compile(
    optimizer='adam',
    loss='binary_crossentropy',
    metrics=['accuracy']
)

# Train Model
model.fit(x_train, y_train, epochs=5, batch_size=64)

# Evaluate Model
loss, accuracy = model.evaluate(x_test, y_test)

print("Accuracy =", accuracy)