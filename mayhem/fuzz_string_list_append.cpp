#include <stdint.h>
#include <stdio.h>
#include <climits>

#include <fuzzer/FuzzedDataProvider.h>

typedef struct string_list_node_t {
  char* value;
  struct string_list_node_t* next;
} string_list_node_t;

typedef struct string_list_t {
  string_list_node_t* head;
  string_list_node_t* tail;
  size_t length;
} string_list_t;

extern "C" void string_list_init(string_list_t* list);

extern "C" void string_list_append(string_list_t* list, char* value);

extern "C" void string_list_destroy(string_list_t* list);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    int src_width = provider.ConsumeIntegralInRange<int>(0, INT_MAX);
    int src_height = provider.ConsumeIntegralInRange<int>(0, INT_MAX);
    int dest_width_inout = provider.ConsumeIntegral<int>();
    int dest_height_inout = provider.ConsumeIntegral<int>();
    int font_ratio = provider.ConsumeFloatingPointInRange<float>(1, 100);
    int zoom = provider.ConsumeIntegral<int>();
    int stretch = provider.ConsumeIntegral<int>();

    char* str = strdup( provider.ConsumeRandomLengthString(1000).c_str() );
    string_list_t sl;
    string_list_init(&sl);

    string_list_append(&sl, str);

    string_list_destroy(&sl);
    free(str);

    return 0;
}