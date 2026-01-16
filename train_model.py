import cv2
import os
import numpy as np

dataset_path = 'dataset'
recognizer = cv2.face.LBPHFaceRecognizer_create()
faces = []
ids = []

for user in os.listdir(dataset_path):
    user_path = os.path.join(dataset_path, user)
    for img_name in os.listdir(user_path):
        img_path = os.path.join(user_path, img_name)
        img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
        faces.append(img)
        ids.append(int(user))

recognizer.train(faces, np.array(ids))
recognizer.save('trainer.yml')
print("Training complete")
