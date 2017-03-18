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

run_test() {
    local test_name=$1
    local test_file=$suites_dir/$test_name.sh
    local out_file=$suites_dir/$test_name.out
    local exit_file=$suites_dir/$test_name.exit

    pushd $(dirname $test_file) > /dev/null
    test_out="$($rshell $test_file 2>&1)"
    test_exit=$?
    popd > /dev/null

    local success=1
    if [[ -f $out_file && "$test_out" != "$(cat $out_file)" ]]; then
        success=0
        echo "fail: $test_name output different from in $out_file; got:"
        echo "$test_out"
    fi
    if [[ -f $exit_file && "$test_exit" != "$(cat $exit_file)" ]]; then
        success=0
        echo "fail: $test_name exit different from $(cat $exit_file); got: $test_exit"
    fi

    if [[ $success -eq 1 ]]; then
        echo "pass: $test_name"
    fi
}

list_tests() {
    local suite_name=$1
    local suite_dir=$suites_dir/$suite_name
    find $suite_dir -type f -name "*.sh" \
        | sed -e 's/.sh$//g' \
        | sed -e "s@^$suites_dir/@@g"
}

run_test_suite() {
    local suite_name=$1
    for test_name in $(list_tests $suite_name); do
        run_test $test_name
    done
}

list_test_suites() {
    ls $suites_dir
}

run_test_suites() {
    for suite_name in $(list_test_suites); do
        run_test_suite $suite_name
    done
}
