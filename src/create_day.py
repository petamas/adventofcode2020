import sys
import datetime
import os.path
import requests

if len(sys.argv)==1:
    iday = datetime.datetime.today().day
else:
    iday = int(sys.argv[1])

day = f'{iday:02d}'

print(f'Creating day #{day}')

src_content=f'''#include "stl.h"
#include "aoc.h"

namespace day{day} {{

int64_t solve(std::istream& is, Task task) {{
    return 0;
}}

}} // namespace day{day}
'''

test_content=f'''#include "stl.h"
#include "aoc.h"
#include "input{day}.h"
#include "gtest/gtest.h"

TEST(day{day}first, example)
{{
    std::stringstream ss(day{day}::example_input);
    EXPECT_EQ(day{day}::solve(ss, Task::FIRST), 0);
}}

TEST(day{day}first, personal)
{{
    std::stringstream ss(day{day}::personal_input);
    EXPECT_EQ(day{day}::solve(ss, Task::FIRST), 0);
}}

TEST(day{day}second, example)
{{
    std::stringstream ss(day{day}::example_input);
    EXPECT_EQ(day{day}::solve(ss, Task::SECOND), 0);
}}

TEST(day{day}second, personal)
{{
    std::stringstream ss(day{day}::personal_input);
    EXPECT_EQ(day{day}::solve(ss, Task::SECOND), 0);
}}
'''

session=os.environ.get('AOC_SESSION')
if session is None:
    personal_content=''
else:
    personal_content=requests.get(f'https://adventofcode.com/2020/day/{iday}/input', cookies={'session': session}).text

cmake_content = f'add_day({day})\n'
header_content = f'namespace day{day} {{ int64_t solve(std::istream& is, Task task); }}\n'

def write_content(name, content = ''):
    if os.path.exists(name):
        print(f'{name} already exists')
    else:
        print(f'Writing {name}')
        with open(name, 'w') as f:
            f.write(content)

def append_content(name, content):
    with open(name, 'r') as f:
        lines = f.readlines()
    if content in lines:
        print(f'{name} already contains day-specific info')
    else:
        with open(name, 'a') as f:
            print(f'Appending to {name}')
            f.write(content)

write_content(f'day{day}.cpp', src_content)
write_content(f'test/test_day{day}.cpp', test_content)
write_content(f'test/example{day}.in')
write_content(f'test/personal{day}.in', personal_content)
append_content('CMakeLists.txt', cmake_content)
append_content('aoc.h', header_content)
