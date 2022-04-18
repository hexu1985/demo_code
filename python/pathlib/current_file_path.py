import pathlib

cwd_path = pathlib.Path.cwd()
file_path = pathlib.Path(__file__)

print("cwd_path: {}".format(cwd_path))
print("file_path: {}".format(file_path))
