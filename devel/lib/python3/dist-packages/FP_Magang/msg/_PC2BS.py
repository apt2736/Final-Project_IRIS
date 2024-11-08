# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from FP_Magang/PC2BS.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class PC2BS(genpy.Message):
  _md5sum = "414e07ab141b8d50059180f242899e66"
  _type = "FP_Magang/PC2BS"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float32 bola_x
float32 bola_y
float32 motor1
float32 motor2
float32 motor3"""
  __slots__ = ['bola_x','bola_y','motor1','motor2','motor3']
  _slot_types = ['float32','float32','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       bola_x,bola_y,motor1,motor2,motor3

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(PC2BS, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.bola_x is None:
        self.bola_x = 0.
      if self.bola_y is None:
        self.bola_y = 0.
      if self.motor1 is None:
        self.motor1 = 0.
      if self.motor2 is None:
        self.motor2 = 0.
      if self.motor3 is None:
        self.motor3 = 0.
    else:
      self.bola_x = 0.
      self.bola_y = 0.
      self.motor1 = 0.
      self.motor2 = 0.
      self.motor3 = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_5f().pack(_x.bola_x, _x.bola_y, _x.motor1, _x.motor2, _x.motor3))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.bola_x, _x.bola_y, _x.motor1, _x.motor2, _x.motor3,) = _get_struct_5f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_5f().pack(_x.bola_x, _x.bola_y, _x.motor1, _x.motor2, _x.motor3))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.bola_x, _x.bola_y, _x.motor1, _x.motor2, _x.motor3,) = _get_struct_5f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_5f = None
def _get_struct_5f():
    global _struct_5f
    if _struct_5f is None:
        _struct_5f = struct.Struct("<5f")
    return _struct_5f
