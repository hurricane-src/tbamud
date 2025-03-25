//
// Created by ediazfer on 25/03/25.
//

#include "languages.h"
#include "conf.h"
#include "sysdep.h"
#include "structs.h"
#include "utils.h"
#include "db.h"
#include "dg_scripts.h"
#include "md5.h"
#include "quest.h"
#include "shop.h"
#include "spells.h"
#include "text_hashmap.h"

#include <inttypes.h>

#define LANGUAGE_EN 0
#define LANGUAGE_FR 1
#define LANGUAGE_MAX 2

text_hashmap_t words = {0};
text_hashmap_t words_fr = {0};
text_hashmap_t *words_by_language[LANGUAGE_MAX] = {&words, &words_fr};


static char *language_canonize(const char *text)
{
    char stack_buffer[1024];
    char *buffer = stack_buffer;
    size_t buffer_size = sizeof(stack_buffer);
    size_t buffer_offset = 0;
    // remove all '\r'
    size_t text_len = strlen(text);

    for(size_t i = 0; i <= text_len; i++)
    {
        if(text[i] != '\r')
        {
            if(buffer_offset >= buffer_size)
            {
                buffer_size *= 2;
                char *tmp = malloc(buffer_size);
                memcpy(tmp, buffer, buffer_offset);
                if(buffer != stack_buffer)
                {
                    free(buffer);
                }
                buffer = tmp;
            }
            buffer[buffer_offset++] = text[i];
        }
    }

    char *canonised_text = malloc(buffer_offset);
    memcpy(canonised_text, buffer, buffer_offset);
    if(buffer != stack_buffer)
    {
        free(buffer);
    }
    return canonised_text;
}

static void language_canonize_insert(const char *text)
{
    if(text != NULL)
    {
        char *canonised_text = language_canonize(text);
        uint64_t h = md5_sum_string(canonised_text);
        if(text_hashmap_insert_own(&words, h, canonised_text) == text_hashmap_duplicate)
        {
            free(canonised_text);
        }
    }
}

static void language_store_extra_descr_data(const struct extra_descr_data *extra)
{
    for(; extra != NULL; extra = extra->next)
    {
        language_canonize_insert(extra->description);
        language_canonize_insert(extra->keyword);
    }
}

static void language_store_rooms()
{
    for(int i = 0; i < top_of_world; ++i)
    {
        const struct room_data *room = &world[i];
        language_canonize_insert(room->name);
        language_canonize_insert(room->description);
        language_store_extra_descr_data(room->ex_description);

        for(int j = 0; j < NUM_OF_DIRS; ++j)
        {
            struct room_direction_data *dir = room->dir_option[j];
            if(dir != NULL)
            {
                language_canonize_insert(dir->general_description);
                language_canonize_insert(dir->keyword);
            }
        }
    }
}

static void language_store_msg_type(const struct msg_type *msg)
{
    language_canonize_insert(msg->attacker_msg);
    language_canonize_insert(msg->victim_msg);
    language_canonize_insert(msg->room_msg);
}

static void language_store_fight_messages()
{
    for(int i = 0; i < MAX_MESSAGES; ++i)
    {
        struct message_type *msg = fight_messages[i].msg;
        while(msg != NULL)
        {
            language_store_msg_type(&msg->die_msg);
            language_store_msg_type(&msg->miss_msg);
            language_store_msg_type(&msg->hit_msg);
            language_store_msg_type(&msg->god_msg);

            msg = msg->next;
        }
    }
}

static void language_store_spell_info_type()
{
    for(int i = 0; i < TOP_SPELL_DEFINE; ++i)
    {
        const struct spell_info_type* sit = &spell_info[i];
        language_canonize_insert(sit->name);
        language_canonize_insert(sit->wear_off_msg);
    }
}

static void language_store_char_player_data(const struct char_player_data * cpd)
{
    language_canonize_insert(cpd->name);
    language_canonize_insert(cpd->short_descr);
    language_canonize_insert(cpd->long_descr);
    language_canonize_insert(cpd->description);
    language_canonize_insert(cpd->title);
}

static void language_store_mob()
{
    for(int i = 0; i < top_of_mobt; ++i)
    {
        const struct char_data *mob = &mob_proto[i];
        const struct char_player_data *mob_data = &mob->player;
        language_store_char_player_data(mob_data);
    }
}

static void language_store_obj()
{
    for(int i = 0; i < top_of_objt; ++i)
    {
        const struct obj_data *obj = &obj_proto[i];

        language_canonize_insert(obj->name);
        language_canonize_insert(obj->description);
        language_canonize_insert(obj->short_description);
        language_canonize_insert(obj->action_description);
        language_store_extra_descr_data(obj->ex_description);
    }
}

static void language_store_zone()
{
    for(int i = 0; i < top_of_zone_table; ++i)
    {
        const struct zone_data *zone = &zone_table[i];
        language_canonize_insert(zone->name);
    }
}

static void language_store_quest()
{
    for(int i = 0; i < total_quests; ++i)
    {
        const struct aq_data *aq = &aquest_table[i];
        language_canonize_insert(aq->name);
        language_canonize_insert(aq->desc);
        language_canonize_insert(aq->info);
        language_canonize_insert(aq->done);
        language_canonize_insert(aq->quit);
    }
}

static void language_store_shop()
{
    for(int i = 0; i < top_shop; ++i)
    {
        struct shop_data *shop = &shop_index[i];
        language_canonize_insert(shop->type->keywords);
        language_canonize_insert(shop->no_such_item1);
        language_canonize_insert(shop->no_such_item2);
        language_canonize_insert(shop->missing_cash1);
        language_canonize_insert(shop->missing_cash2);
        language_canonize_insert(shop->do_not_buy);
        language_canonize_insert(shop->message_buy);
        language_canonize_insert(shop->message_sell);
    }
}

void language_init()
{
    if(words.capacity == 0)
    {
        text_hashmap_init(&words);
    }
    language_store_rooms();
    language_store_fight_messages();
    language_store_spell_info_type();
    language_store_mob();
    language_store_obj();
    language_store_zone();
    language_store_quest();
    language_store_shop();
    printf("size: %" PRIu64 "\n", words.size);
}

int language_encode_text(FILE *f, const char *text)
{
    for(;*text != '\0'; ++text)
    {
        char c = *text;
        switch(c)
        {
            case '\n':
            {
                putc('\\', f);
                putc('n', f);
                break;
            }
            case '\\':
            {
                putc('\\', f);
                putc('\\', f);
                break;
            }
            default:
            {
                putc(*text, f);
            }
        }
    }
}

int language_decode_text(FILE *f, char *text, size_t text_size)
{
    bool escaped = false;
    for(size_t i = 0; i < text_size; ++i)
    {
        int c = fgetc(f);

        if(c == EOF)
        {
            text[i] = '\0';
            return i;
        }

        switch(c)
        {
            case '\\':
            {
                if(escaped)
                {
                    escaped = false;
                    text[i] = '\\';
                }
                else
                {
                    escaped = true;
                }
            }

            case 'n':
            {
                if(!escaped)
                {
                    text[i] = 'n';
                }
                else
                {
                    escaped = false;
                    text[i] = '\n';
                }
            }

            case '\n':
            {
                text[i] = '\0';
                return i;
            }

            default:
            {
                escaped = false;
                text[i] = c;
            }
        }
    }
}

int language_store_file(const char *filename)
{
    FILE *file = fopen(filename, "w+");
    if(file == NULL)
    {
        perror("language_store_file: fopen: ");
        return -1;
    }
    text_hashmap_iterator_t iter;
    text_hashmap_iterator_init(&iter, &words);
    while(text_hashmap_iterator_has_next(&iter))
    {
        uint64_t key;
        const char *text = text_hashmap_iterator_next(&iter, &key);
        fprintf(file, "%08" PRIX64 "=", key);
        language_encode_text(file, text);
        putc('\n', file);
    }
}

void language_store()
{
    language_store_file("text/language.en");
}
