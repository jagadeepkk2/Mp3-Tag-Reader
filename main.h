
#include<string.h>
typedef struct _Mp3info
{
	int  id3size;
	char frame_id[5];
	int frame_size;

}Mp3info;

typedef enum
{
    e_success,
    e_failure
} Status;
typedef enum
{
    e_edit,
    e_view,
	e_help,
    e_unsupported
} OperationType;

OperationType check_operation_type(char *argv[]);
Status read_and_validate_view_args(char *argv[]);
Status read_and_validate_edit_args(char *argv[]);
Status view(char *argv[]);
Status edit(char *argv[]);
