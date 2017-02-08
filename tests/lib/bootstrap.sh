#!/usr/bin/env bash

# rshell
# Copyright (c) Jeremiah Griffin <jgrif007@ucr.edu>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
# SOFTWARE.

# Ensure that tests_dir is properly set
if [[ ! -d $tests_dir ]]; then
    echo "error: bootstrap sourced prior to setting tests_dir"
    exit 1
fi

# Set paths to directories
lib_dir=$tests_dir/lib
suites_dir=$tests_dir/suites

# Locate and confirm rshell executable for running tests
rshell=$(readlink -f $tests_dir/../bin/rshell)
if [[ ! -f $rshell ]]; then
    echo "error: expected rshell at $rshell"
    exit 1
fi

# Source library files
source $lib_dir/run.sh
