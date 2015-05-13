
(cl:in-package :asdf)

(defsystem "face_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "eye" :depends-on ("_package_eye"))
    (:file "_package_eye" :depends-on ("_package"))
    (:file "faceDetection" :depends-on ("_package_faceDetection"))
    (:file "_package_faceDetection" :depends-on ("_package"))
    (:file "face" :depends-on ("_package_face"))
    (:file "_package_face" :depends-on ("_package"))
  ))