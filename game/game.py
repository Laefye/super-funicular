from ctypes import *
import os

SIZE = 20

class carrowtype(Structure):
    _fields_ = [
        ("x", c_size_t),
        ("y", c_size_t),
        ("type", c_uint16),
        ("flags", c_uint8),
    ]

class cgametype(Structure):
    _fields_ = [
        ("arrow_map", carrowtype * SIZE * SIZE),
        ("power_map", c_uint8 * SIZE * SIZE),
        ("next_power_map", c_uint8 * SIZE * SIZE),
    ]

dll = cdll.LoadLibrary(os.path.abspath("logicarrows.dll"))
dll.game_new.restype = POINTER(cgametype)

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
        return carrowtype(0, 0, self.type, self.direction | (self.is_flip << 2))

class Arrows:
    def __init__(self, instance: cgametype) -> None:
        self.instance = instance
    
    def __iter__(self):
        self.x = 0
        self.y = 0
        return self
    
    def __next__(self):
        if (self.x > SIZE - 1):
            self.x = 0
            self.y += 1
        if (self.y > SIZE - 1):
            raise StopIteration
        result = (self.x, self.y, Arrow.from_carrow(self.instance[0].arrow_map[self.y][self.x]))
        self.x += 1
        return result

class Power:
    def __init__(self, instance: cgametype) -> None:
        self.instance = instance

    def __iter__(self):
        self.x = 0
        self.y = 0
        return self
    
    def __next__(self):
        if (self.x > SIZE - 1):
            self.x = 0
            self.y += 1
        if (self.y > SIZE - 1):
            raise StopIteration
        result = (self.x, self.y, self.instance[0].power_map[self.y][self.x])
        self.x += 1
        return result

class LogicArrows:
    def __init__(self):
        self.instance = dll.game_new()
    
    def delete(self):
        dll.game_delete(self.instance)
    
    def get_arrow(self, x: int, y: int) -> Arrow:
        return Arrow.from_carrow(self.instance[0].arrow_map[y][x])
    
    def set_arrow(self, x: int, y: int, arrow: Arrow):
        self.instance[0].arrow_map[y][x] = arrow.to_carrow()
    
    def arrows(self) -> Arrows:
        return Arrows(self.instance)
    
    def power(self) -> Arrows:
        return Power(self.instance)
    
    def tick(self):
        dll.game_tick(self.instance)
