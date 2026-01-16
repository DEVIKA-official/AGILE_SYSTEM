# import cv2
# import serial
# import time

# # ------------------ Serial to Arduino #1 ------------------
# # Change 'COM3' for Windows or '/dev/ttyUSB0' for Linux
# arduino = serial.Serial('COM3', 9600, timeout=1)
# time.sleep(2)  # Arduino ready

# # ------------------ Load Model ------------------
# recognizer = cv2.face.LBPHFaceRecognizer_create()
# recognizer.read('trainer.yml')
# face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# cap = cv2.VideoCapture(0)

# while True:
#     ret, frame = cap.read()
#     if not ret:
#         continue

#     gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#     faces = face_cascade.detectMultiScale(gray, 1.3, 5)

#     for (x,y,w,h) in faces:
#         face_img = gray[y:y+h, x:x+w]
#         id_, conf = recognizer.predict(face_img)
#         if conf < 50:  # adjust threshold
#             print(f"User {id_} recognized, confidence {conf}")
#             arduino.write(b"FACE_OK\n")  # Send signal to Arduino #1
#         else:
#             print(f"Unknown face, confidence {conf}")
#             arduino.write(b"FACE_FAIL\n")

#         cv2.rectangle(frame, (x,y), (x+w, y+h), (255,0,0), 2)

#     cv2.imshow('Face Recognition', frame)
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break

# cap.release()
# cv2.destroyAllWindows()
# arduino.close()


import cv2
import serial

ser = serial.Serial('COM5', 9600, timeout=1)

recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read("trainer.yml")

face_cascade = cv2.CascadeClassifier(
    "haarcascade_frontalface_default.xml"
)

cam = cv2.VideoCapture(0)

while True:
    ret, img = cam.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.2, 5)

    for (x,y,w,h) in faces:
        id, confidence = recognizer.predict(gray[y:y+h, x:x+w])

        if confidence < 50:
            ser.write(b"FACE_OK\n")
            print("Face OK")

    cv2.imshow("Face", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cam.release()
cv2.destroyAllWindows()
