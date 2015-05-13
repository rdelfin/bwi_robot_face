; Auto-generated. Do not edit!


(cl:in-package face_detection-msg)


;//! \htmlinclude faceDetection.msg.html

(cl:defclass <faceDetection> (roslisp-msg-protocol:ros-message)
  ((faceCount
    :reader faceCount
    :initarg :faceCount
    :type cl:integer
    :initform 0)
   (frameWidth
    :reader frameWidth
    :initarg :frameWidth
    :type cl:integer
    :initform 0)
   (frameHeight
    :reader frameHeight
    :initarg :frameHeight
    :type cl:integer
    :initform 0)
   (faces
    :reader faces
    :initarg :faces
    :type (cl:vector face_detection-msg:face)
   :initform (cl:make-array 0 :element-type 'face_detection-msg:face :initial-element (cl:make-instance 'face_detection-msg:face))))
)

(cl:defclass faceDetection (<faceDetection>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <faceDetection>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'faceDetection)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name face_detection-msg:<faceDetection> is deprecated: use face_detection-msg:faceDetection instead.")))

(cl:ensure-generic-function 'faceCount-val :lambda-list '(m))
(cl:defmethod faceCount-val ((m <faceDetection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader face_detection-msg:faceCount-val is deprecated.  Use face_detection-msg:faceCount instead.")
  (faceCount m))

(cl:ensure-generic-function 'frameWidth-val :lambda-list '(m))
(cl:defmethod frameWidth-val ((m <faceDetection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader face_detection-msg:frameWidth-val is deprecated.  Use face_detection-msg:frameWidth instead.")
  (frameWidth m))

(cl:ensure-generic-function 'frameHeight-val :lambda-list '(m))
(cl:defmethod frameHeight-val ((m <faceDetection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader face_detection-msg:frameHeight-val is deprecated.  Use face_detection-msg:frameHeight instead.")
  (frameHeight m))

(cl:ensure-generic-function 'faces-val :lambda-list '(m))
(cl:defmethod faces-val ((m <faceDetection>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader face_detection-msg:faces-val is deprecated.  Use face_detection-msg:faces instead.")
  (faces m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <faceDetection>) ostream)
  "Serializes a message object of type '<faceDetection>"
  (cl:let* ((signed (cl:slot-value msg 'faceCount)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'frameWidth)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'frameHeight)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'faces))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'faces))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <faceDetection>) istream)
  "Deserializes a message object of type '<faceDetection>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'faceCount) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frameWidth) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frameHeight) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'faces) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'faces)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'face_detection-msg:face))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<faceDetection>)))
  "Returns string type for a message object of type '<faceDetection>"
  "face_detection/faceDetection")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'faceDetection)))
  "Returns string type for a message object of type 'faceDetection"
  "face_detection/faceDetection")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<faceDetection>)))
  "Returns md5sum for a message object of type '<faceDetection>"
  "44eaaaaf6a94a79d38417daa8da6203d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'faceDetection)))
  "Returns md5sum for a message object of type 'faceDetection"
  "44eaaaaf6a94a79d38417daa8da6203d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<faceDetection>)))
  "Returns full string definition for message of type '<faceDetection>"
  (cl:format cl:nil "int32 faceCount~%int32 frameWidth~%int32 frameHeight~%face[] faces~%~%================================================================================~%MSG: face_detection/face~%int32 x~%int32 y~%int32 width~%int32 height~%eye[] eyes~%~%================================================================================~%MSG: face_detection/eye~%int32 x~%int32 y~%int32 width~%int32 height~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'faceDetection)))
  "Returns full string definition for message of type 'faceDetection"
  (cl:format cl:nil "int32 faceCount~%int32 frameWidth~%int32 frameHeight~%face[] faces~%~%================================================================================~%MSG: face_detection/face~%int32 x~%int32 y~%int32 width~%int32 height~%eye[] eyes~%~%================================================================================~%MSG: face_detection/eye~%int32 x~%int32 y~%int32 width~%int32 height~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <faceDetection>))
  (cl:+ 0
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'faces) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <faceDetection>))
  "Converts a ROS message object to a list"
  (cl:list 'faceDetection
    (cl:cons ':faceCount (faceCount msg))
    (cl:cons ':frameWidth (frameWidth msg))
    (cl:cons ':frameHeight (frameHeight msg))
    (cl:cons ':faces (faces msg))
))
