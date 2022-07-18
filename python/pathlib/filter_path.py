import pathlib

path = pathlib.Path(".")
for subdir in path.glob("*"):
    if str(subdir).endswith(".py"):
            print(subdir)
