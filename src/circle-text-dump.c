#include "conf.h"
#include "sysdep.h"
#include "structs.h"
#include "utils.h"
#include "db.h"

struct descriptor_data *descriptor_list = NULL; /* master desc list */

size_t send_to_char(struct char_data *ch, const char *messg, ...)
{
}

size_t write_to_output(struct descriptor_data *t, const char *txt, ...)
{
}

int main(int argc, char *argv[])
{
    boot_world();
}
