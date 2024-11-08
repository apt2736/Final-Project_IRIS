; Auto-generated. Do not edit!


(cl:in-package FP_Magang-msg)


;//! \htmlinclude BallCoordinates.msg.html

(cl:defclass <BallCoordinates> (roslisp-msg-protocol:ros-message)
  ((center_x
    :reader center_x
    :initarg :center_x
    :type cl:float
    :initform 0.0)
   (center_y
    :reader center_y
    :initarg :center_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass BallCoordinates (<BallCoordinates>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BallCoordinates>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BallCoordinates)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name FP_Magang-msg:<BallCoordinates> is deprecated: use FP_Magang-msg:BallCoordinates instead.")))

(cl:ensure-generic-function 'center_x-val :lambda-list '(m))
(cl:defmethod center_x-val ((m <BallCoordinates>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader FP_Magang-msg:center_x-val is deprecated.  Use FP_Magang-msg:center_x instead.")
  (center_x m))

(cl:ensure-generic-function 'center_y-val :lambda-list '(m))
(cl:defmethod center_y-val ((m <BallCoordinates>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader FP_Magang-msg:center_y-val is deprecated.  Use FP_Magang-msg:center_y instead.")
  (center_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BallCoordinates>) ostream)
  "Serializes a message object of type '<BallCoordinates>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'center_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'center_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BallCoordinates>) istream)
  "Deserializes a message object of type '<BallCoordinates>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'center_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'center_y) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BallCoordinates>)))
  "Returns string type for a message object of type '<BallCoordinates>"
  "FP_Magang/BallCoordinates")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BallCoordinates)))
  "Returns string type for a message object of type 'BallCoordinates"
  "FP_Magang/BallCoordinates")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BallCoordinates>)))
  "Returns md5sum for a message object of type '<BallCoordinates>"
  "c51e51b1031fa051202f8de7f01927c6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BallCoordinates)))
  "Returns md5sum for a message object of type 'BallCoordinates"
  "c51e51b1031fa051202f8de7f01927c6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BallCoordinates>)))
  "Returns full string definition for message of type '<BallCoordinates>"
  (cl:format cl:nil "float32 center_x~%float32 center_y~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BallCoordinates)))
  "Returns full string definition for message of type 'BallCoordinates"
  (cl:format cl:nil "float32 center_x~%float32 center_y~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BallCoordinates>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BallCoordinates>))
  "Converts a ROS message object to a list"
  (cl:list 'BallCoordinates
    (cl:cons ':center_x (center_x msg))
    (cl:cons ':center_y (center_y msg))
))
