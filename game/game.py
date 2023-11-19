from ctypes import *
import os

SIZE = 20

class carrowtype(Structure):
    _fields_ = [
        ("type", c_uint16),
        ("flags", c_uint8),
    ]

class cgametype(Structure):
    _fields_ = []

dll = cdll.LoadLibrary(os.path.abspath("logicarrows.dll"))
dll.game_new.restype = POINTER(cgametype)
dll.game_get_arrow.restype = POINTER(carrowtype)

ARROW_DIRECTION_MASK = 0b00000011
ARROW_UP = 0b00
ARROW_RIGHT = 0b01
ARROW_BOTTOM =  0b10
ARROW_LEFT = 0b11
ARROW_FLIP = 0b00000100

class Arrow:
    def __init__(self):
        self.type = 0
        self.direction = ARROW_UP
        self.is_flip = 0

    @staticmethod
    def from_carrow(carrow: carrowtype):
        self = Arrow()
        self.type = carrow.type
        self.direction = carrow.flags & ARROW_DIRECTION_MASK
        self.is_flip = carrow.flags & 0b00000100 >> 2
        return self
    
    def to_carrow(self) -> carrowtype:
        return carrowtype(self.type, self.direction | (self.is_flip << 2))

class LogicArrows:
    def __init__(self):
        self.instance = dll.game_new()
    
    def delete(self):
        dll.game_free(self.instance)
    
    def get_arrow(self, x: int, y: int) -> Arrow:
        return Arrow.from_carrow(dll.game_get_arrow(self.instance, x, y)[0])
    
    def set_arrow(self, x: int, y: int, arrow: Arrow):
        dll.game_set_arrow(self.instance, x, y, arrow.to_carrow())
    
    def tick(self):
        dll.game_tick(self.instance)
        pass
