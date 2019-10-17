#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse

import typing
from typeguard import typechecked

import winapi_errors


@typechecked
def parse_command_line() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output")
    parser.add_argument("--cache", default=".error_constants.txt")
    parser.add_argument("-v", "--verbose", action="store_true")
    return parser.parse_args()


@typechecked
def generate_GetErrorLabel_c(
        error_constants: typing.Iterable[typing.Tuple[str, int]],
        output_file: typing.Optional[typing.Any] = None) -> None:

    if isinstance(output_file, str):
        with open(output_file, "w") as output_file:
            return generate_GetErrorLabel_c(error_constants, output_file)

    def write(data):
        if output_file is None:
            print(data)
        else:
            output_file.write(data + "\n")

    write("#include \"WindowsEx.h\"")
    write("")
    write("LPCSTR WINAPI GetErrorLabelA(DWORD dwErrorCode)")
    write("{")
    write("    switch (dwErrorCode)")
    write("    {")
    for i, x in enumerate(error_constants):
        if i > 0:
            write("")
        name = x[0]
        write("#ifdef {}".format(name))
        write("        case {}:".format(name))
        write("            return \"{}\";".format(name))
        write("#endif /* {} */".format(name))
    write("    }")
    write("    return NULL;")
    write("}")


def main():
    command_line_args = parse_command_line()
    if command_line_args.verbose:
        print("Retrieving WinApi error constants")
    error_constants = list(
        winapi_errors.unique_cached_error_constants(command_line_args.cache))
    error_constants.sort(key=lambda x: x[1])  # sorting by value
    if command_line_args.verbose:
        print("Generating GetErrorLabel.c")
    generate_GetErrorLabel_c(error_constants, command_line_args.output)


if __name__ == "__main__":
    main()
