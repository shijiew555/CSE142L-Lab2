#!/usr/bin/env python

import click
from cfiddle import *
import re

@click.command()
@click.argument("source", required=True)
def lint(source=None):
    preprocessed_source = strip_preprocessed_output(build(source)[0].preprocessed())
    raw_source = build(source)[0].source()

    forbidden = [ "inline", "__attribute__", "__asm__",  "pthread", "omp", "<thread>", "std::thread", "clone", "fork"]
    forbidden_patterns = [(x, f"(\W|^){x}(\W|$)") for x in forbidden]
    
    for line in preprocessed_source:
        for bare, pattern in forbidden_patterns:
            if re.search(pattern, line):
                raise click.ClickException(f"Lab source code check failed.\nYour code contains constructs that are forbidden for this lab:\nFound forbidden keyword '{bare}' in preprocessed output from {source}: {line}")



def strip_preprocessed_output(output):
    lines = output.split("\n")
    in_file = False
    output = []
    pattern = r'# (\d+) \"([\w\.\-\/]+)\".*'

    m = re.match(pattern, lines[0])
    if m:
        this_file = m.group(2)
    else:
        raise click.ClickException("Output doesn't start with line number directive")
    
    for l in lines[1:]:
        m = re.search(pattern, l)
        if m:
            if m.group(2) == this_file:
                in_file = True
            else:
                in_file = False
            
        if in_file:
            output.append(l)

    return output



if __name__== "__main__":
    lint()


