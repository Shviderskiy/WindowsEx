#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
import scrapy
import requests

from typing import Tuple, Optional, Generator
from typeguard import typechecked


__all__ = (
    "parse_error_codes_urls",
    "parse_error_constants",
    "parse_wininet_error_constants",
    "parse_all_error_constants",
    "unique_cached_error_constants",
)


ERROR_GROUPS_URL = \
    "https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes"

WININET_ERRORS_URL = \
    "https://docs.microsoft.com/ru-ru/windows/win32/wininet/wininet-errors"


@typechecked
def parse_error_codes_urls() -> Generator[str, None, None]:
    response = requests.get(ERROR_GROUPS_URL)
    assert response.status_code == 200, ERROR_GROUPS_URL
    root = scrapy.selector.Selector(text=response.content)
    for li in root.xpath("//*[@id='main']/ul[2]/li"):
        realative_url = li.xpath("./a/@href").get()
        yield ERROR_GROUPS_URL.replace("system-error-codes", realative_url)


@typechecked
def parse_error_constants(
        url: str) -> Generator[Tuple[str, Optional[int]], None, None]:
    response = requests.get(url)
    assert response.status_code == 200, url
    root = scrapy.selector.Selector(text=response.content)
    dl = root.xpath("//*[@id='main']/dl[1]")
    code_regex = re.compile("(\\d+)\\s*")
    for dt, dd in zip(dl.xpath("./dt"), dl.xpath("./dd")):
        name = dt.xpath("./p/span[1]/@id").get()
        text = dd.xpath("./dl/dt[1]/p/text()").get()
        search_result = code_regex.search(text)
        if search_result is None:
            yield name, None
        else:
            yield name, int(search_result.group(0))


@typechecked
def parse_wininet_error_constants() -> Generator[Tuple[str, int], None, None]:
    for name, value in parse_error_constants(WININET_ERRORS_URL):
        # It's ugly, I know!
        if name not in (
                "ERROR_INVALID_HANDLE",
                "ERROR_MORE_DATA",
                "ERROR_NO_MORE_FILES",
                "ERROR_NO_MORE_ITEMS"):
            yield name, value


@typechecked
def parse_all_error_constants() -> Generator[Tuple[str, int], None, None]:
    for url in parse_error_codes_urls():
        for name, value in parse_error_constants(url):
            if name == "ERROR_INTERNET__":
                yield from parse_wininet_error_constants()
            else:
                yield name, value


@typechecked
def unique_cached_error_constants(
        cache_file: str) -> Generator[Tuple[str, int], None, None]:
    if os.path.exists(cache_file):
        for line in open(cache_file):
            line = line.strip()
            if line:
                name, value_str = line.split(" ")
                yield name, int(value_str)
        return
    with open(cache_file, "w") as cache_file:
        constants_names = set()
        for name, value in parse_all_error_constants():
            if name not in constants_names:
                cache_file.write("{} {}\n".format(name, value))
                constants_names.add(name)
                yield name, value
