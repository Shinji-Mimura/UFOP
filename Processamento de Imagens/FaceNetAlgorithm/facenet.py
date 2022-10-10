# Import the required modules
from facenet_pytorch import MTCNN
import torch
import cv2

device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

# Create the model
mtcnn = MTCNN(keep_all=True, device=device)

# Load the video and go from frame to frame
cap = cv2.VideoCapture(0)
while True:
   ret, frame = cap.read()
   if ret:
       frame = cv2.resize(frame, (600, 400))

      # Here we are going to use the facenet detector
       boxes, conf = mtcnn.detect(frame)

      # If there is no confidence that in the frame is a face, don't draw a rectangle around it
       if conf[0] != None:
           for (x, y, w, h) in boxes:
                text = f"{conf[0]*100:.2f}%"
                x, y, w, h = int(x), int(y), int(w), int(h)

                cv2.putText(frame, text, (x, y-20),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (170, 170, 170), 1)
                cv2.rectangle(frame, (x, y), (w, h), (255, 255, 255), 1)
   else:
       break

# Show the result
# If we were using Google Colab we would use their function cv2_imshow()

# For displaying images/frames
   cv2.imshow("Frame", frame)
   if cv2.waitKey(25) & 0xFF == ord('q'):
       break
 
cap.release()
cv2.destroyAllWindows()
