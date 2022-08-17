
def is_intersect(ts1_beg, ts1_end, ts2_beg, ts2_end):
    if ts1_end < ts2_beg or ts2_end < ts1_beg:
        return False
    return True

print(is_intersect(1,2, 1,2))

print(is_intersect(1,2, 3,4))
print(is_intersect(3,4, 1,2))

print(is_intersect(1,5, 3,4))
print(is_intersect(3,4, 1,5))

print(is_intersect(1,5, 3,6))
print(is_intersect(3,6, 1,5))
