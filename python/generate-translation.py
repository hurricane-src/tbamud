import json
import shutil
from datetime import datetime

from googletrans import Translator
import asyncio
import os
import re

script_path = os.path.abspath(__file__)
project_dir = os.path.dirname(os.path.dirname(script_path))

language_en_filename = os.path.join(project_dir, 'lib', 'text', 'language.en')
language_filename = os.path.join(project_dir, 'lib', 'text', 'language')

# hash -> {original, text, confidence}

translator = Translator()

async def translate_language(text: str, lang: str):
    try:
        if(len(text) == 0):
            return "", 1
        result = await translator.translate(text, dest=lang, src="en")
        if result is not None:
            confidence = 0
            if result.extra_data is not None:
                if 'confidence' in result.extra_data:
                    confidence = result.extra_data['confidence']

            return result.text, confidence
    except Exception as ex:
        print(ex)
        return None, 0

def insert_str(text: str, text_to_insert: str, index: int) -> str:
    return text[:index] + text_to_insert + text[index:]

special_chars = {'\n', ' ', '\t'}

def restore_paragraphs(original: str, obtained: str) -> str:
    if len(original) == 0:
        return obtained, True
    original_dots = [pos for pos, char in enumerate(original) if char == '.']
    obtained_dots = [pos for pos, char in enumerate(obtained) if char == '.']
    if len(original_dots) != len(obtained_dots):
        print(f"Dots have been lost between original='{original}' and obtained={obtained}")
        return obtained, False
    for index in range(0, len(original_dots)):
        dot_index = original_dots[index]
        if dot_index + 1 < len(original):
            # get all blank characters between the dot and the start of the next sentence
            if original[dot_index + 1] in special_chars:
                start_index = dot_index + 1
                stop_index = start_index + 1
                while stop_index < len(original) and original[stop_index] in special_chars:
                    stop_index += 1
                # from start_index to stop_index
                replace_start_index = obtained_dots[index] + 1
                replace_stop_index = replace_start_index + 1
                while replace_stop_index < len(obtained) and obtained[replace_stop_index] in special_chars:
                    replace_stop_index += 1
                text = obtained[:replace_start_index] + original[start_index:stop_index] + obtained[replace_stop_index:]
                obtained = text
                n = stop_index - start_index
                for i in range(index + 1, len(obtained_dots)):
                    obtained_dots[i] += n
    if original[0] in special_chars:
        start_index = 0
        stop_index = start_index + 1
        while stop_index < len(original) and original[stop_index] in special_chars:
            stop_index += 1
        text = original[start_index:stop_index] + obtained
        obtained = text
    return obtained, True

def language_decode(text: str) -> str:
    text = text.replace('\\\\', '\\')
    text = text.replace('\\n', '\n')
    return text;

def language_encode(text: str) -> str:
    text = text.replace('\\', '\\\\')
    text = text.replace('\n', '\\n')
    return text;

async def process_language_en(lang: str):
    try:
        full_result = {}
        with open(f"{language_filename}.{lang}.json", "r", encoding="utf-8") as json_file:
            full_result = json.load(json_file)
    except FileNotFoundError:
        pass
    if not isinstance(full_result, dict):
        full_result = {}

    worth_saving = False
    try:
        with open(f"{language_filename}.{lang}", "w+", encoding="utf-8") as lang_file:
            with open(language_en_filename, 'r', encoding='utf-8') as f:
                line_num = 0
                while True:
                    line = f.readline()
                    if len(line) == 0:
                        break
                    line = line.strip()
                    line_num += 1
                    print(f"Line {line_num}")
                    m = re.match(r"^([0-9A-Fa-f]+)=(.*)$", line)
                    if m:
                        k = m.group(1)
                        v = m.group(2)
                        decoded = language_decode(v)
                        cleaned = decoded.replace('\n', ' ')
                        trimmed = cleaned.strip()
                        need_translate = True
                        if k in full_result:
                            if full_result[k]['originalTrimmed'] == trimmed:
                                need_translate = False

                        # now look in the original for \n after a dot and place them back.

                        if need_translate:
                            translated, confidence = await translate_language(trimmed, lang)
                            if translated is None:
                                print(f"giving up at line {line_num}!")
                                break
                            worth_saving = True
                        else:
                            translated = full_result[k]['translated']
                            confidence = full_result[k]['confidence']

                        # then store the full result
                        (restored, successfully_restored) = restore_paragraphs(decoded, translated)
                        encoded = language_encode(restored)

                        full_result[k] = {
                            "originalEncoded": v,
                            "originalTrimmed": trimmed,
                            "translated": translated,
                            "confidence": confidence,
                            "restored": restored,
                            "successfullyRestored": successfully_restored,
                            "encoded": encoded,
                        }
                        print(f"{k}={encoded}", file=lang_file)
                    else:
                        print(f"Error parsing line '{line}'")
    except Exception as e:
        print(e)

    if worth_saving:

        now = datetime.now()
        formatted_timestamp = now.strftime("%Y%m%d%H%M%S")
        if os.path.exists(f"{language_filename}.{lang}.json"):
            shutil.copy(f"{language_filename}.{lang}.json", f"{language_filename}.{lang}.{formatted_timestamp}.json")
        with open(f"{language_filename}.{lang}.json", "w+", encoding="utf-8") as json_file:
            json.dump(full_result, json_file, ensure_ascii=False, indent=4)

async def main():
    #await translate_language("Hello", "fr")
    #print(restore_paragraphs("The mists swirl, sometimes obscuring your vision completely, at other times clearing enough that you think you see the path.  Reality fades as the cold damp mist permeates your very being.    But there is something else now.  Something that wasn't there before.  Ahead is a tree unlike any seen before.  Upon this tree grows fruit of every size, color shape.  It is quite possibly the most amazing thing seen, as apples, bananas and ever oranges all grow and fall from this tree at an alarming rate.",
    #                         "The mists swirl, sometimes obscuring your vision completely, at other times clearing enough that you think you see the path.  Reality fades as the cold damp mist permeates your very being.    But there is something else now.  Something that wasn't there before.  Ahead is a tree unlike any seen before.  Upon this tree grows fruit of every size, color shape.  It is quite possibly the most amazing thing seen, as apples, bananas and ever oranges all grow and fall from this tree at an alarming rate."))
    #print(restore_paragraphs("   a.\n\nbc.\nd\nef. ghij.\n", "a. bc. def. ghij."))

    await process_language_en('fr')

if __name__ == '__main__':
    asyncio.run(main())