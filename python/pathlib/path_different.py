import pathlib

def path_diff(dir_path, path):
    parent = path.parent
    name = path.name
    diff_path = pathlib.Path(name)
    root_path = pathlib.Path("/")
    while True:
        if parent == dir_path:
            return diff_path
        if parent == root_path:
            return None
        name = parent.name
        diff_path = name/diff_path
        parent = parent.parent



if __name__ == "__main__":
    p1 = pathlib.Path("/home/hexu/git/demo_code/python/pathlib/get_sync_log_list/test")
    p2 = pathlib.Path("/home/hexu/git/demo_code/python/pathlib/get_sync_log_list/test/a/b/c")
    p3 = pathlib.Path("/home/hexu/git/demo_code/python/pathlib/get_sync_log_list/test/d.txt")
    print("path_diff({}, {}) is {}".format(p1, p2, path_diff(p1, p2)))
    print("path_diff({}, {}) is {}".format(p1, p3, path_diff(p1, p3)))
