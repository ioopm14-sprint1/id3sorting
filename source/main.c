#include "id3.h"


int main(int argc, const char *argv[])
{
  // ID3_read_file("data/music10.mp3");
  struct ID3_file *file = ID3_open("data/music10.mp3");
  struct ID3_data *data = NULL;
  
  while((data = ID3_read(file))){
    printf("%s\n",data->data);
    ID3_data_free(&data);
   
  }
  ID3_close(&file);
  return 0;
}
