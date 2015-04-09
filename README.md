# bwi_robot_face
BWI Spring 2015 Project by Ricardo Delfin, Jordan Lopez

This project consists of two primary parts:

**A)** Recognizing and tracking the location of faces in front of the robot

**B)** Displaying a face for the robot, whose eyes follow the detected faces



####Status of A: Recognizing and Tracking Faces
Using OpenCV, face tracking has been relatively easy to accomplish. The faceDetectionNode uses openCV and some premade cascade files, allowing us to recognize faces in front of standard webcams. It then broadcasts those faces on rostopic /detectedFaces, transmitting a message in the form of facesDetected.msg:
 ```      
-- facesDetected is a msg composed of the following
	int32 faceCount
	int32 frameWidth
	int32 frameHeight
	face[] faces
	--face is a msg composed of the following
		int32 x
		int32 y
		int32 width
		int32 height
		eye[] eyes
		--eye is a msg composed of the following
			int32 x
			int32 y
			int32 width
			int32 height
```

#####To-Do List for A:
- Kinect integration? From what I can tell so far, using a kinect may require jumping through a few hoops
- Better cascade files? Haven't had enough testing to determine if the ones we have are sufficient, or if there's any room for improvement
- faceDetectionNode does not die: pressing ctrl-C while the node is running does not kill the node. It's stubborn.

####Status of B: Displaying a Face
robot_face_node now listens to the messages published by faceDetectionNode on rostopic /detectedFaces and, using some very basic openGL, displays a very basic robot face with very basic eyes that follows face movement very basically.

#####To-Do List for B:
- Still pretty much everything.
- Current openGL implementation is far from optimized, and the graphics are not smooth at all. Need to make it look nice
- Improve performance of the node
- 3D seems very possible
- Find something better than openGL? I'm...open...to suggestions
