import pathlib

path = pathlib.Path(".")
for subdir in path.glob("*"):
    if subdir.name.endswith(".py"):
            print(subdir)
