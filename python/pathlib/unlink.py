import pathlib

test = pathlib.Path("./test.txt")
test.unlink()
test.unlink(True)
