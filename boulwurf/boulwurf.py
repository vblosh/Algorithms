#!/usr/bin/env python3
import sys
from typing import List, Any


def match_list2d(
    haystack: List[List[Any]], needle: List[List[Any]], x: int, y: int
):
    for match_y, row in enumerate(needle):
        for match_x, should in enumerate(row):
            try:
                if haystack[y + match_y][x + match_x] != should:
                    return False
            except IndexError:
                return False
    return True


def set_list2d(
    target: List[List[Any]],
    x: int,
    y: int,
    length_y: int,
    length_x: int,
    value: Any,
):
    for off_y in range(length_y):
        for off_x in range(length_x):
            target[off_y + y][off_x + x] = value


MolehillMap = List[List[bool]]


def match_baulwurf_hill(molehill_map: MolehillMap, x: int, y: int):
    baulwurf_molemap_fragment = parse_molemap("xxx\n" "x x\n" "x x\n" "xxx\n")
    return match_list2d(molehill_map, baulwurf_molemap_fragment, x, y)


def count_baulwuerfe(molehill_map: MolehillMap):
    baulwurf_hill_count = 0
    for y, row in enumerate(molehill_map):
        for x, col in enumerate(row):
            if col and match_baulwurf_hill(molehill_map, x, y):
                set_list2d(molehill_map, x, y, 4, 3, False)
                baulwurf_hill_count += 1

    return baulwurf_hill_count


def parse_molemap(content: str) -> MolehillMap:
    return [[x == "X" or x == "x" for x in row] for row in content.split("\n")]


if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print(count_baulwuerfe(parse_molemap(sys.stdin.read())))
    else:
        for baulwurf_file in sys.argv[1:]:
            with open(baulwurf_file, "r") as baulwurf_map:
                count = count_baulwuerfe(parse_molemap(baulwurf_map.read()))
                print(f"{baulwurf_file}: {count}")

