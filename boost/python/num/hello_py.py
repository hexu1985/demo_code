__metaclass__ = type
class Num:
    def __init__(self):
        self.val = 0

    def setValue(self, val):
        self.val = val

    def getValue(self):
        return self.val

    value = property(getValue, setValue)
    rovalue = property(getValue)

