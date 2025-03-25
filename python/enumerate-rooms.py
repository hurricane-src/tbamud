#!/usr/bin/python

import os
import re

script_path = os.path.abspath(__file__)
project_dir = os.path.dirname(os.path.dirname(script_path))

world_dir = os.path.join(project_dir, 'lib', 'world')

# https://www.circlemud.org/cdp/building/building-3.html

direction_numbers = {
    0: "North",
    1: "East",
    2: "South",
    3: "West",
    4: "Up",
    5: "Down"
}

def accumulate_until_tilde(container: str, line: str) -> (str, bool):
    m = re.match(r'^(.*)~', line)
    if m:
        container += m.group(1)
        return container, True
    else:
        container += line
        return container, False


def wld_process(filename: str) -> int:
    eof_not_found = True

    room_count = 0

    mode = 0

    with open(filename, 'r') as f:
        while eof_not_found:
            line = f.readline()
            if len(line) == 0:
                break
            match mode:
                case 0:
                    directions_descriptions = ["", "", "", "", "", ""]
                    directions_count = 0
                    room_extra_keywords = ""
                    room_extra_description = ""
                    room_name = ""
                    room_description = ""

                    m = re.search(r'^#(\d+)$', line)
                    if m:
                        room_id = m.group(1)
                        mode = 1
                    else:
                        m = re.search(r'^T\s+(\d+)$', line) # no clue
                        if m:
                            pass
                        else:
                            m = re.search(r'^[$]~$', line)
                            if m:
                                eof_not_found = False
                            else:
                                raise Exception(f"Expected room Id or $~: {line.strip()}")
                case 1:
                    room_name, done = accumulate_until_tilde(room_name, line)
                    if done:
                        mode = 2
                case 2:
                    room_description, done = accumulate_until_tilde(room_description, line)
                    if done:
                        mode = 3
                case 3: # zone-number room-bitvector sector-type
                    mode = 4
                case 4:
                    m = re.search(r'^S$', line)
                    if m:
                        # room is complete

                        text = room_name.strip()
                        text += '\n'
                        text += room_description.replace('\n', ' ').strip()
                        text += '\n'
                        text += f"There are {directions_count} exits out of here\n\n"
                        confirmed_exits = 0
                        for i in range(0, 6):
                            if len(directions_descriptions[i]) > 0:
                                confirmed_exits += 1
                                text += f"{direction_numbers[i]}: "
                                text += directions_descriptions[i].replace('\n', ' ').strip()
                                text += "\n"

                        if confirmed_exits != directions_count:
                            print(f"{confirmed_exits} != {directions_count}")

                        print("----- BEGIN -----")
                        print(f"Room: {room_id}")
                        print(text)
                        print("----- END -----")

                        room_count += 1

                        mode = 0
                    else:
                        m = re.search(r'^D(\d+)$', line)
                        if m:
                            direction_number = int(m.group(1))
                            direction_description = ""
                            directions_count += 1
                            mode = 5
                        else: # extra
                            m = re.search(r'^E$', line)
                            if m:
                                mode = 8
                            else:
                                raise Exception(f"Expected a direction with a number, an extra, or the end marker '{line.strip()}'")
                case 5:
                    direction_description, done = accumulate_until_tilde(direction_description, line)
                    if done:
                        directions_descriptions[direction_number] = direction_description
                        mode = 6
                case 6: # keyword list
                    direction_keyword_list = ""
                    direction_keyword_list, done = accumulate_until_tilde(direction_keyword_list, line)
                    if done:
                        room_extra_keywords = ""
                        mode = 7
                case 7: # door-flag key-number room-linked
                    mode = 4
                case 8: # extra description keyword list
                    room_extra_keywords, done = accumulate_until_tilde(room_extra_keywords, line)
                    if done:
                        room_extra_description = ""
                        mode = 9
                case 9:
                    room_extra_description, done = accumulate_until_tilde(room_extra_description, line)
                    if done:
                        mode = 4
    return room_count


def process_kind(name: str, processor):
    pwd = os.getcwd()
    file_count = 0
    try:
        ext = f'.{name}'
        kind_dir = os.path.join(world_dir, name)
        os.chdir(kind_dir)
        kind_files = os.listdir()
        total_count = 0
        for kind_file in kind_files:
            if kind_file.endswith(ext):
                try:
                    print(f"processing {kind_file}")
                    count = processor(kind_file)
                    print(f"processed {kind_file} and got {count} items")
                    total_count += count
                    file_count += 1
                except Exception as e:
                    print(f"failed to process {kind_file}: {e}")
                    exit(1)
        print(f"processed {name} and got {total_count} items in total (projected: {total_count * 0.04} EUR)")
    except Exception as ex:
        print(ex)
    os.chdir(pwd)
    print(f"processed {file_count} files")


def main():
    process_kind('wld', wld_process)


if __name__ == '__main__':
    main()